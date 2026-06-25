#include "ui_lamp.h"
#include "ui_common.h"
#include "lamp.h"

LV_FONT_DECLARE(sf_pro_display_medium_24);
LV_FONT_DECLARE(sf_pro_display_medium_32);

#define COLOR_ON    lv_color_hex(0xFF2713)
#define COLOR_OFF   lv_color_hex(0x242424)
#define COLOR_DIM   lv_color_hex(0x3A3A3A)
#define BTN_SIZE    160
#define STEP_BRIGHT 100
#define STEP_TEMP   100

static lv_obj_t *s_btn_power   = nullptr;
static lv_obj_t *s_lbl_bright  = nullptr;
static lv_obj_t *s_lbl_temp    = nullptr;
static lv_obj_t *s_lbl_status  = nullptr;

static void on_delete(lv_event_t *) {
    s_btn_power  = nullptr;
    s_lbl_bright = nullptr;
    s_lbl_temp   = nullptr;
    s_lbl_status = nullptr;
}

// ── Button helpers ────────────────────────────────────────────────────────────

static lv_obj_t *make_round_btn(lv_obj_t *parent, int x, int y, int size,
                                 lv_color_t color, const char *label,
                                 lv_event_cb_t cb) {
    lv_obj_t *btn = lv_obj_create(parent);
    lv_obj_set_size(btn, size, size);
    lv_obj_set_pos(btn, x, y);
    lv_obj_set_style_radius(btn, size / 2, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, color, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x555555), LV_STATE_PRESSED);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
    if (cb) lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, nullptr);

    if (label && label[0]) {
        lv_obj_t *lbl = lv_label_create(btn);
        lv_label_set_text(lbl, label);
        lv_obj_set_style_text_font(lbl, &sf_pro_display_medium_32, LV_PART_MAIN);
        lv_obj_set_style_text_color(lbl, lv_color_white(), LV_PART_MAIN);
        lv_obj_align(lbl, LV_ALIGN_CENTER, 0, 0);
    }
    return btn;
}

static lv_obj_t *make_rect_btn(lv_obj_t *parent, int x, int y, int w, int h,
                                const char *label, lv_event_cb_t cb) {
    lv_obj_t *btn = lv_obj_create(parent);
    lv_obj_set_size(btn, w, h);
    lv_obj_set_pos(btn, x, y);
    lv_obj_set_style_radius(btn, h / 2, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, COLOR_DIM, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x555555), LV_STATE_PRESSED);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
    if (cb) lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, nullptr);

    lv_obj_t *lbl = lv_label_create(btn);
    lv_label_set_text(lbl, label);
    lv_obj_set_style_text_font(lbl, &sf_pro_display_medium_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl, lv_color_white(), LV_PART_MAIN);
    lv_obj_align(lbl, LV_ALIGN_CENTER, 0, 0);
    return btn;
}

// ── Callbacks ─────────────────────────────────────────────────────────────────

static void on_power(lv_event_t *) {
    lamp_cmd_power(!g_lamp.on);
    g_lamp.on = !g_lamp.on;
    update_lamp_screen();
}

static void on_bright_minus(lv_event_t *) {
    int v = constrain(g_lamp.brightness - STEP_BRIGHT, 10, 1000);
    lamp_cmd_brightness(v);
    g_lamp.brightness = v;
    update_lamp_screen();
}

static void on_bright_plus(lv_event_t *) {
    int v = constrain(g_lamp.brightness + STEP_BRIGHT, 10, 1000);
    lamp_cmd_brightness(v);
    g_lamp.brightness = v;
    update_lamp_screen();
}

static void on_temp_minus(lv_event_t *) {
    int v = constrain(g_lamp.color_temp - STEP_TEMP, 0, 1000);
    lamp_cmd_color_temp(v);
    g_lamp.color_temp = v;
    update_lamp_screen();
}

static void on_temp_plus(lv_event_t *) {
    int v = constrain(g_lamp.color_temp + STEP_TEMP, 0, 1000);
    lamp_cmd_color_temp(v);
    g_lamp.color_temp = v;
    update_lamp_screen();
}

// ── Create / update ───────────────────────────────────────────────────────────

void create_lamp_screen() {
    if (scr_lamp) return;
    scr_lamp = make_screen();
    lv_obj_add_event_cb(scr_lamp, on_delete, LV_EVENT_DELETE, nullptr);

    // ── Power button (centre) ─────────────────────────────────────────────────
    int cx = (SCREEN_W - BTN_SIZE) / 2;
    s_btn_power = make_round_btn(scr_lamp, cx, 110, BTN_SIZE,
                                  g_lamp.on ? COLOR_ON : COLOR_OFF,
                                  g_lamp.on ? "ON" : "OFF", on_power);

    // ── Brightness row ────────────────────────────────────────────────────────
    int row1_y = 295;
    lv_obj_t *lbl_b = lv_label_create(scr_lamp);
    lv_label_set_text(lbl_b, "Яркость");
    lv_obj_set_style_text_font(lbl_b, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_b, lv_color_hex(0x7A7A7A), LV_PART_MAIN);
    lv_obj_set_pos(lbl_b, 32, row1_y);

    make_rect_btn(scr_lamp, 32,  row1_y + 36, 80, 60, "−", on_bright_minus);
    make_rect_btn(scr_lamp, 368, row1_y + 36, 80, 60, "+", on_bright_plus);

    s_lbl_bright = lv_label_create(scr_lamp);
    lv_obj_set_style_text_font(s_lbl_bright, &sf_pro_display_medium_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(s_lbl_bright, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_align(s_lbl_bright, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_size(s_lbl_bright, 240, 60);
    lv_obj_set_pos(s_lbl_bright, 120, row1_y + 36);

    // ── Color temp row ────────────────────────────────────────────────────────
    int row2_y = 385;
    lv_obj_t *lbl_t = lv_label_create(scr_lamp);
    lv_label_set_text(lbl_t, "Цветовая температура");
    lv_obj_set_style_text_font(lbl_t, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_t, lv_color_hex(0x7A7A7A), LV_PART_MAIN);
    lv_obj_set_pos(lbl_t, 32, row2_y);

    make_rect_btn(scr_lamp, 32,  row2_y + 36, 80, 60, "☀", on_temp_minus);
    make_rect_btn(scr_lamp, 368, row2_y + 36, 80, 60, "❄", on_temp_plus);

    s_lbl_temp = lv_label_create(scr_lamp);
    lv_obj_set_style_text_font(s_lbl_temp, &sf_pro_display_medium_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(s_lbl_temp, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_align(s_lbl_temp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_size(s_lbl_temp, 240, 60);
    lv_obj_set_pos(s_lbl_temp, 120, row2_y + 36);

    update_lamp_screen();
}

void update_lamp_screen() {
    if (!scr_lamp) return;

    if (s_btn_power) {
        lv_obj_set_style_bg_color(s_btn_power, g_lamp.on ? COLOR_ON : COLOR_OFF, LV_PART_MAIN);
        lv_obj_t *lbl = lv_obj_get_child(s_btn_power, 0);
        if (lbl) lv_label_set_text(lbl, g_lamp.on ? "ON" : "OFF");
    }

    if (s_lbl_bright) {
        char buf[16];
        snprintf(buf, sizeof(buf), "%d%%", (g_lamp.brightness * 100) / 1000);
        lv_label_set_text(s_lbl_bright, buf);
    }

    if (s_lbl_temp) {
        int pct = (g_lamp.color_temp * 100) / 1000;
        char buf[16];
        snprintf(buf, sizeof(buf), "%d%%", pct);
        lv_label_set_text(s_lbl_temp, buf);
    }
}
