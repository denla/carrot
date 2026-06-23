#include <Arduino.h>
#include <esp_task_wdt.h>
#include "globals.h"
#include "hw.h"
#include "ui_common.h"
#include "ui_clock.h"
#include "ui_clock2.h"
#include "ui_clock3.h"
#include "ui_clock4.h"
#include "ui_weather.h"
#include "ui_music.h"
#include "weather.h"
#include "web_api.h"
#include <WiFi.h>

static void create_active_clock() {
    switch (clock_style) {
        case 1: create_clock2_screen(); break;
        case 2: create_clock3_screen(); break;
        case 3: create_clock4_screen(); break;
        default: create_clock_screen(); break;
    }
}

static void destroy_active_clock() {
    if (scr_clock)  { lbl_time = lbl_date = nullptr;
                      lv_obj_del(scr_clock);  scr_clock  = nullptr; }
    if (scr_clock2) { lbl_c2_dow = lbl_c2_date = lbl_c2_time = nullptr;
                      lv_obj_del(scr_clock2); scr_clock2 = nullptr; }
    if (scr_clock3) { lbl_c3_date = lbl_c3_hour = lbl_c3_min = nullptr;
                      lv_obj_del(scr_clock3); scr_clock3 = nullptr; }
    if (scr_clock4) { lbl_c4_date = nullptr;
                      lv_obj_del(scr_clock4); scr_clock4 = nullptr; }
}

void setup() {
    USBSerial.begin(115200);

    prefs.begin("carrotos", true);
    brightness_pct = max((uint8_t)30, prefs.getUChar("brightness", 85));
    clock_style    = prefs.getUChar("clockstyle", 0);
    prefs.getString("lat",  owm_lat,  sizeof(owm_lat));
    prefs.getString("lon",  owm_lon,  sizeof(owm_lon));
    prefs.getString("city", owm_city, sizeof(owm_city));
    if (prefs.isKey("owmkey")) prefs.getString("owmkey", owm_key, sizeof(owm_key));
    else                       strncpy(owm_key, OWM_KEY, sizeof(owm_key) - 1);
    anim_enabled = prefs.getBool("anim", true);
    prefs.end();

    g_weather_queue = xQueueCreate(1, sizeof(WeatherData));
    g_music_queue   = xQueueCreate(1, sizeof(MusicData));
    g_art_buf       = (uint8_t*)ps_malloc(ART_SIZE);

    hw_init_i2c();
    hw_init_rtc();
    hw_init_touch();
    hw_init_display();
    hw_init_lvgl();

    create_active_clock();
    create_top_bar();

    lv_scr_load(active_clock());
    update_clock();
    update_clock2();
    update_clock3();
    update_clock4();
    set_brightness(brightness_pct);

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    USBSerial.printf("Heap=%u PSRAM=%u/%u\n",
        ESP.getFreeHeap(), ESP.getFreePsram(), ESP.getPsramSize());

    xTaskCreatePinnedToCore(web_server_task, "webserver", 16384, NULL, 1, NULL, 1);

    USBSerial.println("CarrotOS ready");
}

void loop() {
    lv_timer_handler();
    hw_display_check_sync();
    delay(5);

    if (millis() - lastMillis >= 1000) {
        lastMillis = millis();
        update_clock();
        update_clock2();
        update_clock3();
    }

    static uint32_t lastClock4Ms = 0;
    if (scr_clock4 && millis() - lastClock4Ms >= 33) {
        lastClock4Ms = millis();
        update_clock4();
    }

    WeatherData wd;
    if (xQueueReceive(g_weather_queue, &wd, 0) == pdTRUE) {
        g_weather = wd;
        update_weather_screen();
    }

    MusicData md;
    if (xQueueReceive(g_music_queue, &md, 0) == pdTRUE) {
        g_music = md;
        update_music_screen();
        if (g_art_ready) {
            g_art_ready = false;
            update_music_art();
        }
    } else if (g_art_ready) {
        g_art_ready = false;
        update_music_art();
    }

    if (pending_brightness >= 0) {
        set_brightness((uint8_t)pending_brightness);
        pending_brightness = -1;
    }

    if (pending_clock_style >= 0) {
        destroy_active_clock();
        clock_style = (uint8_t)pending_clock_style;
        pending_clock_style = -1;
        create_active_clock();
        if (top_bar) lv_obj_add_flag(top_bar, LV_OBJ_FLAG_HIDDEN);
        lv_scr_load(active_clock());
        update_clock();
        update_clock2();
        update_clock3();
        update_clock4();
    }

    if (pending_time.valid) {
        pending_time.valid = false;
        hw_set_datetime(pending_time.year, pending_time.month, pending_time.day,
                        pending_time.hour, pending_time.minute, pending_time.second);
        update_clock();
        update_clock2();
        update_clock3();
    }
}
