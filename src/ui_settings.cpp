#include "ui_settings.h"
#include "ui_common.h"
#include "hw.h"

static void on_bt_row_clicked(lv_event_t *)  { bt_enabled   = !bt_enabled;   lv_label_set_text(lbl_bt_val,   bt_enabled   ? "On" : "Off"); }
static void on_wifi_row_clicked(lv_event_t *){ wifi_enabled = !wifi_enabled; lv_label_set_text(lbl_wifi_val, wifi_enabled ? "On" : "Off"); }

static lv_obj_t *make_settings_row(lv_obj_t *parent, int y, const char *title,
                                   lv_obj_t **out_val, const char *val_text,
                                   lv_event_cb_t cb) {
    lv_obj_t *row = make_row(parent, y, SCREEN_W - 32, 80);
    if (cb) lv_obj_add_event_cb(row, cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *lbl_n = lv_label_create(row);
    lv_obj_set_style_text_font(lbl_n, &offbit_bold_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_n, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text(lbl_n, title);
    lv_obj_align(lbl_n, LV_ALIGN_LEFT_MID, 0, 0);

    if (out_val) {
        *out_val = lv_label_create(row);
        lv_obj_set_style_text_font(*out_val, &offbit_bold_32, LV_PART_MAIN);
        lv_obj_set_style_text_color(*out_val, lv_color_hex(0x666666), LV_PART_MAIN);
        lv_label_set_text(*out_val, val_text);
        lv_obj_align(*out_val, LV_ALIGN_RIGHT_MID, 0, 0);
    }
    return row;
}

void create_settings_screen() {
    scr_settings = make_screen();

    // Rows start below shared top bar (32 pad + 29 bar + 20 gap = 81)
    int y = 81;
    make_separator(scr_settings, y); y += 1;

    make_settings_row(scr_settings, y, "Bluetooth", &lbl_bt_val,   "Off", on_bt_row_clicked);
    make_separator(scr_settings, y + 80); y += 81;

    make_settings_row(scr_settings, y, "Wi-Fi",     &lbl_wifi_val, "Off", on_wifi_row_clicked);
    make_separator(scr_settings, y + 80); y += 81;

    char b[8]; snprintf(b, sizeof(b), "%d%%", brightness_pct);
    make_settings_row(scr_settings, y, "Brightness", &lbl_bright_val, b, NULL);
    make_separator(scr_settings, y + 80); y += 81;

    // Brightness slider
    lv_obj_t *slider = lv_slider_create(scr_settings);
    lv_obj_set_size(slider, SCREEN_W - 64, 8);
    lv_obj_set_pos(slider, 32, y + 8);
    lv_slider_set_range(slider, 10, 100);
    lv_slider_set_value(slider, brightness_pct, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(slider, lv_color_hex(0x333333), LV_PART_MAIN);
    lv_obj_set_style_bg_color(slider, lv_color_white(), LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(slider, lv_color_white(), LV_PART_KNOB);
    lv_obj_set_style_radius(slider, 4, LV_PART_KNOB);
    lv_obj_set_style_pad_all(slider, 6, LV_PART_KNOB);
    lv_obj_add_event_cb(slider, [](lv_event_t *e) {
        set_brightness(lv_slider_get_value(lv_event_get_target(e)));
    }, LV_EVENT_VALUE_CHANGED, NULL);
    make_separator(scr_settings, y + 44); y += 45;

    make_settings_row(scr_settings, y, "About", nullptr, nullptr, nullptr);
    make_separator(scr_settings, y + 80);
}
