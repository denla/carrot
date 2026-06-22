#include "ui_clock.h"
#include "ui_common.h"
#include "hw.h"

LV_FONT_DECLARE(london_120);
LV_FONT_DECLARE(sf_pro_display_medium_24);

static void on_clock_gesture(lv_event_t *e) {
    if (lv_scr_act() != scr_clock) return;
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    if (dir == LV_DIR_LEFT)  nav_to_weather (scr_clock, LV_SCR_LOAD_ANIM_MOVE_LEFT);
    if (dir == LV_DIR_RIGHT) nav_to_settings(scr_clock, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
    if (dir == LV_DIR_TOP)   nav_to_nav     (scr_clock, LV_SCR_LOAD_ANIM_MOVE_TOP);
}

static void on_clock_tap(lv_event_t *) {
    if (lv_scr_act() != scr_clock) return;
    nav_to_nav(scr_clock, LV_SCR_LOAD_ANIM_MOVE_TOP);
}

void create_clock_screen() {
    if (scr_clock) return;
    scr_clock = make_screen();
    lv_obj_add_event_cb(scr_clock, on_clock_gesture, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(scr_clock, on_clock_tap,     LV_EVENT_CLICKED,  NULL);

    lbl_time = lv_label_create(scr_clock);
    lv_obj_set_style_text_font(lbl_time, &london_120, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_time, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text(lbl_time, "00:00");
    lv_obj_align(lbl_time, LV_ALIGN_CENTER, 0, -10);

    lbl_date = lv_label_create(scr_clock);
    lv_obj_set_style_text_font(lbl_date, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_date, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text(lbl_date, "-- ------, --");
    lv_obj_align(lbl_date, LV_ALIGN_BOTTOM_MID, 0, -44);
}

void update_clock() {
    HWDateTime dt = hw_get_datetime();

    char time_str[6];
    snprintf(time_str, sizeof(time_str), "%02d:%02d", dt.hour, dt.minute);

    if (lbl_time)     lv_label_set_text(lbl_time,     time_str);
    if (lbl_top_time) lv_label_set_text(lbl_top_time, time_str);
    if (lbl_w_time)   lv_label_set_text(lbl_w_time,   time_str);

    if (lbl_date && dt.month >= 1 && dt.month <= 12 && dt.week <= 6) {
        char date_str[40];
        snprintf(date_str, sizeof(date_str), "%d %s, %s",
                 dt.day, months_ru[dt.month - 1], weekdays_ru[dt.week]);
        lv_label_set_text(lbl_date, date_str);
    }
}
