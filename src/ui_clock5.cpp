#include "ui_clock5.h"
#include "ui_common.h"
#include "hw.h"
#include <time.h>

LV_FONT_DECLARE(london_120);
LV_FONT_DECLARE(sf_pro_display_medium_24);
LV_FONT_DECLARE(sf_symbols_icons_28);

#define CONTENT_Y    54
#define COL_L_X      32
#define COL_L_W      272
#define COL_R_X      336
#define COL_R_W      108
#define ROW_H        53
#define WEATHER_Y    365   // CONTENT_Y(54) + CONTENT_H(371) - circle(60)

#define ICON_WEATHER "\xEE\x80\x82"

static const char *k_dow[7] = {"ПН","ВТ","СР","ЧТ","ПТ","СБ","ВС"};  // Mon=0..Sun=6

static lv_obj_t *s_lbl_hour = nullptr;
static lv_obj_t *s_lbl_min  = nullptr;
static lv_obj_t *s_lbl_temp = nullptr;
static lv_obj_t *s_pills[7] = {};
static lv_obj_t *s_date[7]  = {};

static void on_delete(lv_event_t *) {
    s_lbl_hour = s_lbl_min = s_lbl_temp = nullptr;
    for (int i = 0; i < 7; i++) s_pills[i] = s_date[i] = nullptr;
}

static void on_gesture(lv_event_t *) {
    if (lv_scr_act() != scr_clock5) return;
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    if (dir == LV_DIR_LEFT)  nav_to_weather (scr_clock5, LV_SCR_LOAD_ANIM_MOVE_LEFT);
    if (dir == LV_DIR_RIGHT) nav_to_settings(scr_clock5, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
    if (dir == LV_DIR_TOP)   nav_to_nav     (scr_clock5, LV_SCR_LOAD_ANIM_MOVE_TOP);
}

static void on_tap(lv_event_t *) {
    if (lv_scr_act() != scr_clock5) return;
    nav_to_nav(scr_clock5, LV_SCR_LOAD_ANIM_MOVE_TOP);
}

void create_clock5_screen() {
    if (scr_clock5) return;
    scr_clock5 = make_screen();
    lv_obj_add_event_cb(scr_clock5, on_delete,  LV_EVENT_DELETE,  NULL);
    lv_obj_add_event_cb(scr_clock5, on_gesture, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(scr_clock5, on_tap,     LV_EVENT_CLICKED, NULL);

    // Hours — london_120, white
    s_lbl_hour = lv_label_create(scr_clock5);
    lv_obj_set_style_text_font(s_lbl_hour, &london_120, LV_PART_MAIN);
    lv_obj_set_style_text_color(s_lbl_hour, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_align(s_lbl_hour, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_size(s_lbl_hour, COL_L_W, LV_SIZE_CONTENT);
    lv_obj_set_pos(s_lbl_hour, COL_L_X, CONTENT_Y);
    lv_label_set_text(s_lbl_hour, "00");

    // Minutes — london_120, dark gray
    s_lbl_min = lv_label_create(scr_clock5);
    lv_obj_set_style_text_font(s_lbl_min, &london_120, LV_PART_MAIN);
    lv_obj_set_style_text_color(s_lbl_min, lv_color_hex(0x383838), LV_PART_MAIN);
    lv_obj_set_style_text_align(s_lbl_min, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_size(s_lbl_min, COL_L_W, LV_SIZE_CONTENT);
    lv_obj_set_pos(s_lbl_min, COL_L_X, CONTENT_Y + 105);
    lv_label_set_text(s_lbl_min, "00");

    // Weather icon circle
    lv_obj_t *ico_bg = lv_obj_create(scr_clock5);
    lv_obj_set_size(ico_bg, 60, 60);
    lv_obj_set_pos(ico_bg, COL_L_X, WEATHER_Y);
    lv_obj_set_style_radius(ico_bg, 30, LV_PART_MAIN);
    lv_obj_set_style_bg_color(ico_bg, lv_color_hex(0x242424), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ico_bg, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(ico_bg, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(ico_bg, 0, LV_PART_MAIN);
    lv_obj_clear_flag(ico_bg, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t *ico = lv_label_create(ico_bg);
    lv_obj_set_style_text_font(ico, &sf_symbols_icons_28, LV_PART_MAIN);
    lv_obj_set_style_text_color(ico, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text(ico, ICON_WEATHER);
    lv_obj_align(ico, LV_ALIGN_CENTER, 0, 0);

    // Temperature label
    s_lbl_temp = lv_label_create(scr_clock5);
    lv_obj_set_style_text_font(s_lbl_temp, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(s_lbl_temp, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_pos(s_lbl_temp, COL_L_X + 72, WEATHER_Y + 18);
    lv_label_set_text(s_lbl_temp, "--\xC2\xB0");

    // Calendar rows (right column)
    for (int i = 0; i < 7; i++) {
        lv_obj_t *pill = lv_obj_create(scr_clock5);
        s_pills[i] = pill;
        lv_obj_set_size(pill, COL_R_W, ROW_H);
        lv_obj_set_pos(pill, COL_R_X, CONTENT_Y + i * ROW_H);
        lv_obj_set_style_radius(pill, ROW_H / 2, LV_PART_MAIN);
        lv_obj_set_style_bg_opa(pill, LV_OPA_TRANSP, LV_PART_MAIN);
        lv_obj_set_style_border_width(pill, 0, LV_PART_MAIN);
        lv_obj_set_style_pad_all(pill, 0, LV_PART_MAIN);
        lv_obj_clear_flag(pill, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);

        lv_obj_t *dow_lbl = lv_label_create(pill);
        lv_obj_set_style_text_font(dow_lbl, &sf_pro_display_medium_24, LV_PART_MAIN);
        lv_obj_set_style_text_color(dow_lbl, lv_color_hex(0x7A7A7A), LV_PART_MAIN);
        lv_label_set_text(dow_lbl, k_dow[i]);
        lv_obj_align(dow_lbl, LV_ALIGN_LEFT_MID, 11, 0);

        lv_obj_t *date_lbl = lv_label_create(pill);
        s_date[i] = date_lbl;
        lv_obj_set_style_text_font(date_lbl, &sf_pro_display_medium_24, LV_PART_MAIN);
        lv_obj_set_style_text_color(date_lbl, lv_color_white(), LV_PART_MAIN);
        lv_label_set_text(date_lbl, "--");
        lv_obj_align(date_lbl, LV_ALIGN_RIGHT_MID, -11, 0);
    }
}

void update_clock5() {
    if (!scr_clock5) return;

    HWDateTime dt = hw_get_datetime();

    // Time
    char buf[8];
    snprintf(buf, sizeof(buf), "%d", dt.hour);
    if (s_lbl_hour) lv_label_set_text(s_lbl_hour, buf);
    snprintf(buf, sizeof(buf), "%02d", dt.minute);
    if (s_lbl_min)  lv_label_set_text(s_lbl_min, buf);

    // Temperature
    if (s_lbl_temp && g_weather.valid) {
        char tbuf[12];
        snprintf(tbuf, sizeof(tbuf), "%d\xC2\xB0", g_weather.temp);
        lv_label_set_text(s_lbl_temp, tbuf);
    }

    // Calendar rows: dt.week is 0=Sun, 1=Mon, ..., 6=Sat
    int today_row = (dt.week == 0) ? 6 : (dt.week - 1);  // Mon=0..Sun=6

    struct tm now_tm = {};
    now_tm.tm_year = dt.year - 1900;
    now_tm.tm_mon  = dt.month - 1;
    now_tm.tm_mday = dt.day;
    now_tm.tm_hour = 12;
    time_t now_t = mktime(&now_tm);

    for (int i = 0; i < 7; i++) {
        if (!s_pills[i] || !s_date[i]) continue;

        time_t row_t = now_t + (time_t)(i - today_row) * 86400L;
        struct tm *rtm = localtime(&row_t);

        char ds[4];
        snprintf(ds, sizeof(ds), "%d", rtm->tm_mday);
        lv_label_set_text(s_date[i], ds);

        bool today = (i == today_row);
        lv_obj_set_style_bg_color(s_pills[i], lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa (s_pills[i], today ? LV_OPA_COVER : LV_OPA_TRANSP, LV_PART_MAIN);
        lv_obj_set_style_text_color(s_date[i], today ? lv_color_black() : lv_color_white(), LV_PART_MAIN);
    }
}
