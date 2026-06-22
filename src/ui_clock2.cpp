#include "ui_clock2.h"
#include "ui_common.h"
#include "hw.h"

LV_FONT_DECLARE(london_120);
LV_FONT_DECLARE(sf_pro_display_medium_24);

static void on_clock2_gesture(lv_event_t *) {
    if (lv_scr_act() != scr_clock2) return;
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    if (dir == LV_DIR_LEFT)  nav_to_weather (scr_clock2, LV_SCR_LOAD_ANIM_MOVE_LEFT);
    if (dir == LV_DIR_RIGHT) nav_to_settings(scr_clock2, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
    if (dir == LV_DIR_TOP)   nav_to_nav     (scr_clock2, LV_SCR_LOAD_ANIM_MOVE_TOP);
}

static void on_clock2_tap(lv_event_t *) {
    if (lv_scr_act() != scr_clock2) return;
    nav_to_nav(scr_clock2, LV_SCR_LOAD_ANIM_MOVE_TOP);
}

void create_clock2_screen() {
    if (scr_clock2) return;
    scr_clock2 = make_screen();
    lv_obj_add_event_cb(scr_clock2, on_clock2_gesture, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(scr_clock2, on_clock2_tap,     LV_EVENT_CLICKED,  NULL);

    lbl_c2_dow = lv_label_create(scr_clock2);
    lv_obj_set_style_text_font(lbl_c2_dow, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_c2_dow, lv_color_hex(0x999999), LV_PART_MAIN);
    lv_label_set_text(lbl_c2_dow, "-------");
    lv_obj_set_pos(lbl_c2_dow, 28, 340);

    lbl_c2_date = lv_label_create(scr_clock2);
    lv_obj_set_style_text_font(lbl_c2_date, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_c2_date, lv_color_hex(0x999999), LV_PART_MAIN);
    lv_label_set_text(lbl_c2_date, "-- ------");
    lv_obj_set_pos(lbl_c2_date, 28, 372);

    lbl_c2_time = lv_label_create(scr_clock2);
    lv_obj_set_style_text_font(lbl_c2_time, &london_120, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_c2_time, lv_color_hex(0xFF3213), LV_PART_MAIN);
    lv_label_set_text(lbl_c2_time, "00:00");
    lv_obj_set_pos(lbl_c2_time, 28, 200);
}

void update_clock2() {
    if (!scr_clock2) return;
    HWDateTime dt = hw_get_datetime();

    if (dt.week <= 6)
        lv_label_set_text(lbl_c2_dow, weekdays_full_ru[dt.week]);

    if (dt.month >= 1 && dt.month <= 12) {
        char date_str[32];
        snprintf(date_str, sizeof(date_str), "%d %s", dt.day, months_ru[dt.month - 1]);
        lv_label_set_text(lbl_c2_date, date_str);
    }

    char time_str[6];
    snprintf(time_str, sizeof(time_str), "%d:%02d", dt.hour, dt.minute);
    lv_label_set_text(lbl_c2_time, time_str);
}
