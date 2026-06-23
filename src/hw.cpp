#include "hw.h"
#include <Wire.h>
#include "Arduino_GFX_Library.h"
#include "TouchDrvGT911.hpp"


// ── Display hardware (private to this module) ─────────────────────────────────

static Arduino_DataBus *bus = new Arduino_SWSPI(
    GFX_NOT_DEFINED, 42, 2, 1, GFX_NOT_DEFINED);

static Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
    40, 39, 38, 41,
    46, 3, 8, 18, 17,
    14, 13, 12, 11, 10, 9,
    5, 45, 48, 47, 21,
    1, 10, 8, 50,
    1, 10, 8, 20);

static Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
    SCREEN_W, SCREEN_H, rgbpanel, 0, true,
    bus, GFX_NOT_DEFINED, st7701_type1_init_operations, sizeof(st7701_type1_init_operations));

static TouchDrvGT911 GT911;
static int16_t touch_x[5], touch_y[5];

static SensorPCF85063 rtc;

// ── Display sync watchdog ─────────────────────────────────────────────────────

static volatile uint32_t s_vsync_count = 0;

static bool IRAM_ATTR vsync_isr(esp_lcd_panel_handle_t,
                                 const esp_lcd_rgb_panel_event_data_t *,
                                 void *) {
    s_vsync_count++;
    return false;
}

// ── LVGL callbacks ────────────────────────────────────────────────────────────

static void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    esp_lcd_panel_draw_bitmap(rgbpanel->getPanelHandle(),
        area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_p);
    lv_disp_flush_ready(disp);
}

static void my_touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
    uint8_t touched = GT911.getPoint(touch_x, touch_y, GT911.getSupportTouchPoint());
    if (touched > 0) {
        data->point.x = touch_x[0];
        data->point.y = touch_y[0];
        data->state   = LV_INDEV_STATE_PR;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

static void lvgl_tick_cb(void *) { lv_tick_inc(LVGL_TICK_MS); }

// ── Public API ────────────────────────────────────────────────────────────────

void hw_init_i2c() {
    Wire.begin(SDA_PIN, SCL_PIN);
    delay(80); // CH32V003 needs time to boot before first I2C command
    Wire.beginTransmission(0x24); Wire.write(0x02); Wire.write(0xFF); Wire.endTransmission();
    Wire.beginTransmission(0x24); Wire.write(0x03); Wire.write(0x3A); Wire.endTransmission();
}

void hw_init_rtc() {
    if (!rtc.begin(Wire, PCF85063_SLAVE_ADDRESS, SDA_PIN, SCL_PIN)) {
        USBSerial.println("RTC fail, continuing anyway");
    }
    RTC_DateTime dt = rtc.getDateTime();
    if (dt.year < 2024) rtc.setDateTime(2026, 6, 18, 12, 0, 0);
}

void hw_init_touch() {
    GT911.setPins(-1, -1);
    uint8_t addrs[] = {GT911_SLAVE_ADDRESS_L, GT911_SLAVE_ADDRESS_H};
    for (uint8_t addr : addrs) {
        if (GT911.begin(Wire, addr, SDA_PIN, SCL_PIN)) {
            GT911.setMaxTouchPoint(1);
            USBSerial.printf("GT911 at 0x%02X\n", addr);
            break;
        }
    }
}

void hw_display_restart() {
#if defined(ESP32) && (CONFIG_IDF_TARGET_ESP32S3)
    esp_lcd_panel_handle_t h = rgbpanel->getPanelHandle();
    if (h) esp_lcd_rgb_panel_restart(h);
#endif
}

void hw_display_check_sync() {
#if defined(ESP32) && (CONFIG_IDF_TARGET_ESP32S3)
    static uint32_t last_vsync = 0;
    static uint32_t last_ms    = 0;
    uint32_t now = millis();
    if (now - last_ms < 500) return;   // check every 500ms
    uint32_t cur = s_vsync_count;
    if (cur == last_vsync) {           // vsync stalled — panel lost sync
        hw_display_restart();
        USBSerial.println("[disp] vsync stall — restarted panel");
    }
    last_vsync = cur;
    last_ms    = now;
#endif
}

void hw_init_display() {
    // After a soft reset (USB replug, ESP.restart()) the RGB panel is still
    // powered and running its DMA. Delay lets the panel accept new SPI init
    // commands; without it gfx->begin() silently fails.
    if (esp_reset_reason() != ESP_RST_POWERON) {
        delay(500);
    }

    set_brightness(brightness_pct);
    ledcAttach(BL_GPIO, BL_LEDC_FREQ, BL_LEDC_BITS);
    ledcWrite(BL_GPIO, (brightness_pct * 255) / 100);
    gfx->begin();


    esp_lcd_rgb_panel_event_callbacks_t cbs = {};
    cbs.on_vsync = vsync_isr;
    esp_lcd_rgb_panel_register_event_callbacks(rgbpanel->getPanelHandle(), &cbs, nullptr);
}

void hw_init_lvgl() {
    static lv_disp_draw_buf_t draw_buf;
    static const size_t BUF_PX = SCREEN_W * (SCREEN_H / 10);
    static lv_color_t *lvgl_buf1 = (lv_color_t*)heap_caps_malloc(BUF_PX * sizeof(lv_color_t), MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    static lv_color_t *lvgl_buf2 = (lv_color_t*)heap_caps_malloc(BUF_PX * sizeof(lv_color_t), MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    assert(lvgl_buf1 && lvgl_buf2 && "LVGL SRAM buffer alloc failed");

    lv_init();
    lv_disp_draw_buf_init(&draw_buf, lvgl_buf1, lvgl_buf2, BUF_PX);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res  = SCREEN_W;
    disp_drv.ver_res  = SCREEN_H;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.sw_rotate = 1;
    disp_drv.rotated   = LV_DISP_ROT_180;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type    = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    const esp_timer_create_args_t tick_args = { .callback = &lvgl_tick_cb, .name = "lvgl_tick" };
    esp_timer_handle_t tick_timer;
    esp_timer_create(&tick_args, &tick_timer);
    esp_timer_start_periodic(tick_timer, LVGL_TICK_MS * 1000);

    lv_disp_set_bg_color(lv_disp_get_default(), lv_color_black());
    lv_disp_set_bg_opa(lv_disp_get_default(), LV_OPA_COVER);

    // 1×1 invisible object on the system layer. A 15 ms timer invalidates it,
    // forcing flush_cb ~67 fps even on static screens. Without this, the PSRAM
    // controller idles between LVGL updates and the DMA FIFO underruns, showing
    // as horizontal jitter that disappears only when animations are running.
    static lv_obj_t *hb_obj = lv_obj_create(lv_layer_sys());
    lv_obj_set_size(hb_obj, 1, 1);
    lv_obj_set_pos(hb_obj, 0, 0);
    lv_obj_set_style_bg_opa(hb_obj, LV_OPA_0, 0);
    lv_obj_set_style_border_width(hb_obj, 0, 0);
    lv_obj_set_style_pad_all(hb_obj, 0, 0);
    lv_timer_create([](lv_timer_t *t) {
        lv_obj_invalidate(static_cast<lv_obj_t *>(t->user_data));
    }, 15, hb_obj);
}

void set_brightness(uint8_t pct) {
    brightness_pct = pct;
    uint8_t duty = (uint8_t)(((100 - pct) / 100.0f) * 255);
    Wire.beginTransmission(0x24); Wire.write(0x05); Wire.write(duty); Wire.endTransmission();
    char b[8]; snprintf(b, sizeof(b), "%d%%", pct);
    if (lbl_bright_val) lv_label_set_text(lbl_bright_val, b);
}

void set_backlight(bool on) {
    if (on) ch32_output_reg |=  (1 << BL_BIT);
    else    ch32_output_reg &= ~(1 << BL_BIT);
    Wire.beginTransmission(0x24); Wire.write(0x02); Wire.write(ch32_output_reg); Wire.endTransmission();
}

uint8_t read_ch32_input() {
    Wire.beginTransmission(0x24); Wire.write(0x00); Wire.endTransmission(false);
    Wire.requestFrom(0x24, 1);
    return Wire.available() ? Wire.read() : 0xFF;
}

HWDateTime hw_get_datetime() {
    RTC_DateTime dt = rtc.getDateTime();
    return { dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second, dt.week };
}

void hw_set_datetime(int y, int m, int d, int h, int mi, int s) {
    rtc.setDateTime(y, m, d, h, mi, s);
}
