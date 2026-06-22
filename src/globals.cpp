#include "globals.h"

HWCDC USBSerial;

bool    bt_enabled    = false;
bool    wifi_enabled  = false;
uint8_t brightness_pct  = 85;
uint8_t ch32_output_reg = 0xFF;
uint32_t lastMillis     = 0;

Preferences prefs;
char owm_lat[16]  = "55.8896";
char owm_lon[16]  = "37.4428";
char owm_city[48] = "Химки";
char owm_key[48]  = OWM_KEY;

volatile int  pending_brightness  = -1;
volatile int  pending_clock_style = -1;
PendingTime   pending_time        = {};
uint8_t       clock_style         = 0;
volatile bool anim_enabled        = true;

WeatherData  g_weather      = {0, 0, 0, "нет данных", {0,0,0,0,0}, {0,0,0,0,0}, {"","","","",""}, false};
QueueHandle_t g_weather_queue = nullptr;

MusicData    g_music        = {"", "", false, false};
QueueHandle_t g_music_queue = nullptr;
volatile char music_pending_cmd[8] = "";

uint8_t      *g_art_buf   = nullptr;
volatile bool g_art_ready = false;

lv_obj_t *scr_clock    = nullptr;
lv_obj_t *scr_clock2   = nullptr;
lv_obj_t *scr_clock3   = nullptr;
lv_obj_t *scr_clock4   = nullptr;
lv_obj_t *scr_nav      = nullptr;
lv_obj_t *scr_settings = nullptr;
lv_obj_t *scr_weather  = nullptr;
lv_obj_t *scr_calendar = nullptr;
lv_obj_t *scr_music    = nullptr;

lv_obj_t *lbl_time = nullptr;
lv_obj_t *lbl_date = nullptr;

lv_obj_t *top_bar        = nullptr;
lv_obj_t *lbl_top_time   = nullptr;
lv_obj_t *lbl_bt_val     = nullptr;
lv_obj_t *lbl_wifi_val   = nullptr;
lv_obj_t *lbl_bright_val = nullptr;

lv_obj_t *lbl_w_city     = nullptr;
lv_obj_t *lbl_w_temp     = nullptr;
lv_obj_t *lbl_w_time     = nullptr;
lv_obj_t *lbl_w_fday[5]  = {};
lv_obj_t *lbl_w_fcond[5] = {};
lv_obj_t *lbl_w_ftemp[5] = {};

lv_obj_t *lbl_c2_dow = nullptr;
lv_obj_t *lbl_c2_date    = nullptr;
lv_obj_t *lbl_c2_time    = nullptr;

lv_obj_t *lbl_c3_date    = nullptr;
lv_obj_t *lbl_c3_hour    = nullptr;
lv_obj_t *lbl_c3_min     = nullptr;

lv_obj_t *lbl_c4_date    = nullptr;

const char *weekdays_ru[7]      = {"вс", "пн", "вт", "ср", "чт", "пт", "сб"};
const char *weekdays_full_ru[7] = {"воскресенье", "понедельник", "вторник", "среда", "четверг", "пятница", "суббота"};
const char *months_ru[12]  = {
    "января", "февраля", "марта", "апреля", "мая", "июня",
    "июля", "августа", "сентября", "октября", "ноября", "декабря"
};
