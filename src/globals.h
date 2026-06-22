#pragma once
#include <Arduino.h>
#include <lvgl.h>
#include <Preferences.h>
#include "HWCDC.h"
#include "config.h"

LV_FONT_DECLARE(offbit_bold_32);
LV_FONT_DECLARE(offbit_bold_20);

#define LVGL_TICK_MS  2
#define SDA_PIN       15
#define SCL_PIN       7
#define SCREEN_W      480
#define SCREEN_H      480
#define BL_GPIO       4
#define BL_LEDC_FREQ  5000
#define BL_LEDC_BITS  8
#define BL_BIT        6

// ── Shared types ─────────────────────────────────────────────────────────────

struct MusicData {
    char title[128];
    char artist[64];
    bool playing;
    bool valid;
};

struct WeatherData {
    int     temp;
    int     tmin;
    int     tmax;
    char    desc[48];
    int     ftemp[5];
    uint8_t fdow[5];
    char    fcond[5][32];
    bool    valid;
};

struct PendingTime {
    int  year, month, day, hour, minute, second;
    bool valid;
};

// ── Hardware ─────────────────────────────────────────────────────────────────

extern HWCDC USBSerial;

// ── App state ────────────────────────────────────────────────────────────────

extern bool    bt_enabled;
extern bool    wifi_enabled;
extern uint8_t brightness_pct;
extern uint8_t ch32_output_reg;
extern uint32_t lastMillis;

// ── Persistent settings ──────────────────────────────────────────────────────

extern Preferences prefs;
extern char owm_lat[16];
extern char owm_lon[16];
extern char owm_city[48];
extern char owm_key[48];

// ── Pending actions (set from web task, consumed in loop) ────────────────────

extern volatile int  pending_brightness;
extern volatile int  pending_clock_style;
extern PendingTime   pending_time;
extern uint8_t       clock_style;
extern volatile bool anim_enabled;

// ── Weather data ─────────────────────────────────────────────────────────────

extern WeatherData   g_weather;
extern QueueHandle_t g_weather_queue;

// ── Music data ───────────────────────────────────────────────────────────────

extern MusicData      g_music;
extern QueueHandle_t  g_music_queue;
extern volatile char  music_pending_cmd[8];

// ── Album art ────────────────────────────────────────────────────────────────

#define ART_W    130
#define ART_H    130
#define ART_SIZE (ART_W * ART_H * 2)   // RGB565, 2 bytes per pixel

extern uint8_t         *g_art_buf;      // PSRAM, allocated in setup()
extern volatile bool    g_art_ready;    // set by web task, cleared by loop task

// ── Screens ──────────────────────────────────────────────────────────────────

extern lv_obj_t *scr_clock;
extern lv_obj_t *scr_clock2;
extern lv_obj_t *scr_clock3;
extern lv_obj_t *scr_clock4;
extern lv_obj_t *scr_nav;
extern lv_obj_t *scr_settings;
extern lv_obj_t *scr_weather;
extern lv_obj_t *scr_calendar;
extern lv_obj_t *scr_music;

// Clock widgets
extern lv_obj_t *lbl_time;
extern lv_obj_t *lbl_date;

// Shared top bar (lv_layer_top)
extern lv_obj_t *top_bar;
extern lv_obj_t *lbl_top_time;

// Settings widgets
extern lv_obj_t *lbl_bt_val;
extern lv_obj_t *lbl_wifi_val;
extern lv_obj_t *lbl_bright_val;

// Weather widgets (time shown via shared top bar)
extern lv_obj_t *lbl_w_city;
extern lv_obj_t *lbl_w_temp;
extern lv_obj_t *lbl_w_time;
extern lv_obj_t *lbl_w_fday[5];
extern lv_obj_t *lbl_w_fcond[5];
extern lv_obj_t *lbl_w_ftemp[5];

// Clock2 widgets
extern lv_obj_t *lbl_c2_dow;
extern lv_obj_t *lbl_c2_date;
extern lv_obj_t *lbl_c2_time;

// Clock3 widgets
extern lv_obj_t *lbl_c3_date;
extern lv_obj_t *lbl_c3_hour;
extern lv_obj_t *lbl_c3_min;

// Clock4 widgets
extern lv_obj_t *lbl_c4_date;

// ── Locale strings ───────────────────────────────────────────────────────────

extern const char *weekdays_ru[7];
extern const char *weekdays_full_ru[7];
extern const char *months_ru[12];
