#include "ui_common.h"

LV_FONT_DECLARE(sf_pro_display_medium_24);
LV_FONT_DECLARE(sf_symbols_icons_28);

#define COLOR_RED    lv_color_hex(0xFF1313)
#define ICON_CHEVRON "\xEE\x80\x80"

lv_obj_t *make_screen() {
    lv_obj_t *scr = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(scr, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(scr, 0, LV_PART_MAIN);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    return scr;
}

lv_obj_t *make_separator(lv_obj_t *parent, int y) {
    lv_obj_t *sep = lv_obj_create(parent);
    lv_obj_set_size(sep, SCREEN_W - 32, 1);
    lv_obj_set_pos(sep, 16, y);
    lv_obj_set_style_bg_color(sep, lv_color_hex(0x2a2a2a), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(sep, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(sep, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(sep, 0, LV_PART_MAIN);
    lv_obj_clear_flag(sep, LV_OBJ_FLAG_SCROLLABLE);
    return sep;
}

lv_obj_t *make_row(lv_obj_t *parent, int y, int w, int h) {
    lv_obj_t *row = lv_obj_create(parent);
    lv_obj_set_size(row, w, h);
    lv_obj_set_pos(row, (SCREEN_W - w) / 2, y);
    lv_obj_set_style_bg_opa(row, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(row, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(row, 0, LV_PART_MAIN);
    lv_obj_clear_flag(row, LV_OBJ_FLAG_SCROLLABLE);
    return row;
}

static void on_top_back(lv_event_t *) {
    lv_obj_t *cur = lv_scr_act();
    if (cur == scr_nav)      nav_to(scr_nav,      active_clock(),  LV_SCR_LOAD_ANIM_MOVE_BOTTOM);
    else if (cur == scr_weather)   nav_to(scr_weather,   scr_nav, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
    else if (cur == scr_settings)  nav_to(scr_settings,  scr_nav, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
    else if (cur == scr_calendar)  nav_to(scr_calendar,  scr_nav, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
    else if (cur == scr_music)     nav_to(scr_music,     scr_nav, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
}

void nav_to(lv_obj_t *from, lv_obj_t *to, lv_scr_load_anim_t dir) {
    // Show top bar on all screens except clock screens
    if (top_bar) {
        bool show = (to != scr_clock && to != scr_clock2 && to != scr_clock3 && to != scr_clock4);
        if (show) lv_obj_clear_flag(top_bar, LV_OBJ_FLAG_HIDDEN);
        else      lv_obj_add_flag(top_bar,   LV_OBJ_FLAG_HIDDEN);
    }

    bool from_clock = (from == scr_clock || from == scr_clock2 || from == scr_clock3 || from == scr_clock4);
    bool to_clock   = (to   == scr_clock || to   == scr_clock2 || to   == scr_clock3 || to   == scr_clock4);

    if (from_clock || to_clock || !anim_enabled) {
        lv_scr_load(to);
    } else {
        lv_scr_load_anim(to, dir, 280, 0, false);
    }
}

void create_top_bar() {
    lv_obj_t *layer = lv_layer_top();

    top_bar = lv_obj_create(layer);
    lv_obj_set_size(top_bar, SCREEN_W, 32 + 29);  // top padding + bar height
    lv_obj_set_pos(top_bar, 0, 0);
    lv_obj_set_style_bg_opa(top_bar, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(top_bar, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(top_bar, 0, LV_PART_MAIN);
    lv_obj_clear_flag(top_bar, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(top_bar, LV_OBJ_FLAG_HIDDEN);  // hidden on clock screens

    // Back button (chevron + "Back")
    lv_obj_t *btn = lv_obj_create(top_bar);
    lv_obj_set_size(btn, 130, 29);
    lv_obj_set_pos(btn, 40, 32);
    lv_obj_set_style_bg_opa(btn, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(btn, 0, LV_PART_MAIN);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(btn, on_top_back, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_opa(btn, LV_OPA_50, LV_STATE_PRESSED);

    lv_obj_t *ico = lv_label_create(btn);
    lv_obj_set_style_text_font(ico, &sf_symbols_icons_28, LV_PART_MAIN);
    lv_obj_set_style_text_color(ico, COLOR_RED, LV_PART_MAIN);
    lv_label_set_text(ico, ICON_CHEVRON);
    lv_obj_align(ico, LV_ALIGN_LEFT_MID, 0, 0);

    lv_obj_t *lbl_back = lv_label_create(btn);
    lv_obj_set_style_text_font(lbl_back, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_back, COLOR_RED, LV_PART_MAIN);
    lv_label_set_text(lbl_back, "Back");
    lv_obj_align(lbl_back, LV_ALIGN_LEFT_MID, 34, 0);

    // Time (right)
    lbl_top_time = lv_label_create(top_bar);
    lv_obj_set_style_text_font(lbl_top_time, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_top_time, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text(lbl_top_time, "00:00");
    lv_obj_align(lbl_top_time, LV_ALIGN_TOP_RIGHT, -40, 32);
}
