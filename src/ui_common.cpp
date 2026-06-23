#include "ui_common.h"
#include "ui_nav.h"
#include "ui_weather.h"
#include "ui_settings.h"
#include "ui_calendar.h"
#include "ui_music.h"
#include "ui_github.h"

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

// Null all global widget pointers for a lazy screen before it is destroyed.
static void null_lazy_widgets(lv_obj_t *scr) {
    if (scr == scr_weather) {
        lbl_w_city = lbl_w_temp = lbl_w_time = nullptr;
        for (int i = 0; i < 5; i++) lbl_w_fday[i] = lbl_w_fcond[i] = lbl_w_ftemp[i] = nullptr;
    } else if (scr == scr_settings) {
        lbl_bright_val = nullptr;
        lbl_mem_heap = lbl_mem_lvgl = lbl_mem_psram = nullptr;
    }
}

void nav_to(lv_obj_t *from, lv_obj_t *to, lv_scr_load_anim_t dir) {
    if (top_bar) {
        bool show = (to != scr_clock && to != scr_clock2 && to != scr_clock3 && to != scr_clock4);
        if (show) lv_obj_clear_flag(top_bar, LV_OBJ_FLAG_HIDDEN);
        else      lv_obj_add_flag(top_bar,   LV_OBJ_FLAG_HIDDEN);
    }

    bool from_clock = (from == scr_clock || from == scr_clock2 || from == scr_clock3 || from == scr_clock4);
    bool to_clock   = (to   == scr_clock || to   == scr_clock2 || to   == scr_clock3 || to   == scr_clock4);

    lv_obj_t *old_scr = from;

    if (!from_clock) {
        // Null global widget pointers so update_xxx() functions skip safely
        null_lazy_widgets(from);
        // Null the screen pointer — new navigations will recreate on demand
        if      (from == scr_nav)      scr_nav      = nullptr;
        else if (from == scr_weather)  scr_weather  = nullptr;
        else if (from == scr_settings) scr_settings = nullptr;
        else if (from == scr_calendar) scr_calendar = nullptr;
        else if (from == scr_music)    scr_music    = nullptr;
        else if (from == scr_github)   scr_github   = nullptr;
    }

    if (from_clock || to_clock || !anim_enabled) {
        lv_scr_load(to);
        if (!from_clock && old_scr) lv_obj_del(old_scr);
    } else {
        lv_scr_load_anim(to, dir, 280, 0, true);  // auto_del destroys old_scr after animation
    }
}

// ── Lazy navigation helpers ───────────────────────────────────────────────────

void nav_to_nav(lv_obj_t *from, lv_scr_load_anim_t dir) {
    if (!scr_nav) create_nav_screen();
    nav_to(from, scr_nav, dir);
}

void nav_to_weather(lv_obj_t *from, lv_scr_load_anim_t dir) {
    if (!scr_weather) {
        create_weather_screen();
        update_weather_screen();
    }
    nav_to(from, scr_weather, dir);
}

void nav_to_settings(lv_obj_t *from, lv_scr_load_anim_t dir) {
    if (!scr_settings) create_settings_screen();
    nav_to(from, scr_settings, dir);
}

void nav_to_calendar(lv_obj_t *from) {
    if (!scr_calendar) create_calendar_screen();
    nav_to(from, scr_calendar, LV_SCR_LOAD_ANIM_MOVE_LEFT);
}

void nav_to_music(lv_obj_t *from) {
    if (!scr_music) {
        create_music_screen();
        update_music_screen();
        if (g_art_ready) { g_art_ready = false; update_music_art(); }
    }
    nav_to(from, scr_music, LV_SCR_LOAD_ANIM_MOVE_LEFT);
}

void nav_to_github(lv_obj_t *from) {
    if (!scr_github) {
        create_github_screen();
        update_github_screen();
    }
    nav_to(from, scr_github, LV_SCR_LOAD_ANIM_MOVE_LEFT);
}

// ── Top bar ───────────────────────────────────────────────────────────────────

static void on_top_back(lv_event_t *) {
    lv_obj_t *cur = lv_scr_act();
    if (cur == scr_nav) {
        nav_to(scr_nav, active_clock(), LV_SCR_LOAD_ANIM_MOVE_BOTTOM);
    } else {
        nav_to_nav(cur, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
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

    // Temporary: memory stats in center of top bar
}
