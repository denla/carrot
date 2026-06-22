#include "ui_clock3.h"
#include "ui_common.h"
#include "hw.h"

LV_FONT_DECLARE(cybersiberia_130);
LV_FONT_DECLARE(sf_pro_display_medium_24);

static void on_clock3_gesture(lv_event_t *) {
    if (lv_scr_act() != scr_clock3) return;
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    if (dir == LV_DIR_LEFT)  nav_to_weather (scr_clock3, LV_SCR_LOAD_ANIM_MOVE_LEFT);
    if (dir == LV_DIR_RIGHT) nav_to_settings(scr_clock3, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
    if (dir == LV_DIR_TOP)   nav_to_nav     (scr_clock3, LV_SCR_LOAD_ANIM_MOVE_TOP);
}

static void on_clock3_tap(lv_event_t *) {
    if (lv_scr_act() != scr_clock3) return;
    nav_to_nav(scr_clock3, LV_SCR_LOAD_ANIM_MOVE_TOP);
}

void create_clock3_screen() {
    if (scr_clock3) return;
    scr_clock3 = make_screen();
    lv_obj_add_event_cb(scr_clock3, on_clock3_gesture, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(scr_clock3, on_clock3_tap,     LV_EVENT_CLICKED,  NULL);

    // Date row — top right, SF Pro 24pt
    lbl_c3_date = lv_label_create(scr_clock3);
    lv_obj_set_style_text_font(lbl_c3_date, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_c3_date, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_align(lbl_c3_date, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_size(lbl_c3_date, 416, 29);
    lv_obj_set_pos(lbl_c3_date, 32, 32);
    lv_label_set_text(lbl_c3_date, "-- ------, --");

    // Hours — CyberSiberia 130pt, right-aligned, red
    lbl_c3_hour = lv_label_create(scr_clock3);
    lv_obj_set_style_text_font(lbl_c3_hour, &cybersiberia_130, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_c3_hour, lv_color_hex(0xFF001A), LV_PART_MAIN);
    lv_obj_set_style_text_align(lbl_c3_hour, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);
    lv_obj_set_size(lbl_c3_hour, 416, LV_SIZE_CONTENT);
    lv_obj_set_pos(lbl_c3_hour, 32, 240);
    lv_label_set_text(lbl_c3_hour, "00");

    // Minutes — CyberSiberia 130pt, right-aligned, grey
    lbl_c3_min = lv_label_create(scr_clock3);
    lv_obj_set_style_text_font(lbl_c3_min, &cybersiberia_130, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_c3_min, lv_color_hex(0x626262), LV_PART_MAIN);
    lv_obj_set_style_text_align(lbl_c3_min, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);
    lv_obj_set_size(lbl_c3_min, 416, LV_SIZE_CONTENT);
    lv_obj_set_pos(lbl_c3_min, 32, 342);
    lv_label_set_text(lbl_c3_min, "00");
}

void update_clock3() {
    if (!scr_clock3) return;
    HWDateTime dt = hw_get_datetime();

    char hour_str[4];
    snprintf(hour_str, sizeof(hour_str), "%02d", dt.hour);
    lv_label_set_text(lbl_c3_hour, hour_str);

    char min_str[4];
    snprintf(min_str, sizeof(min_str), "%02d", dt.minute);
    lv_label_set_text(lbl_c3_min, min_str);

    if (dt.month >= 1 && dt.month <= 12 && dt.week <= 6) {
        char date_str[40];
        snprintf(date_str, sizeof(date_str), "%d %s, %s",
                 dt.day, months_ru[dt.month - 1], weekdays_ru[dt.week]);
        lv_label_set_text(lbl_c3_date, date_str);
    }
}
