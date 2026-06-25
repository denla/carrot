#include "ui_nav.h"
#include "ui_calendar.h"
#include "ui_music.h"
#include "ui_common.h"
#include "hw.h"
#include "ui_github.h"

LV_FONT_DECLARE(sf_pro_display_medium_32);
LV_FONT_DECLARE(sf_symbols_icons_32);

#define ICON_CLOCK    "\xEE\x80\x81"
#define ICON_WEATHER  "\xEE\x80\x82"
#define ICON_NOTES    "\xEE\x80\x83"
#define ICON_SETTINGS "\xEE\x80\x84"

#define CIRCLE_SIZE   90
#define CIRCLE_GAP    16
#define ROW_H         112
#define ROW_PAD_V     11

static void on_clock_item   (lv_event_t *) { nav_to(scr_nav, active_clock(), LV_SCR_LOAD_ANIM_MOVE_BOTTOM); }
static void on_weather_item (lv_event_t *) { nav_to_weather (scr_nav); }
static void on_settings_item(lv_event_t *) { nav_to_settings(scr_nav); }
static void on_calendar_item(lv_event_t *) { nav_to_calendar(scr_nav); }
static void on_music_item   (lv_event_t *) { nav_to_music   (scr_nav); }
static void on_github_item  (lv_event_t *) { nav_to_github  (scr_nav); }
static void on_lamp_item    (lv_event_t *) { nav_to_lamp    (scr_nav); }

// ── Menu row: [dark circle with icon] [label] ─────────────────────────────────

static void make_item(lv_obj_t *list, const char *icon_str, const char *label,
                      lv_event_cb_t cb, const lv_font_t *icon_font = &sf_symbols_icons_32) {
    lv_obj_t *row = lv_obj_create(list);
    lv_obj_set_size(row, LV_PCT(100), ROW_H);
    lv_obj_set_style_bg_opa(row, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_bg_color(row, lv_color_hex(0x1c1c1c), LV_STATE_PRESSED | LV_PART_MAIN);
    lv_obj_set_style_bg_opa(row, LV_OPA_COVER, LV_STATE_PRESSED | LV_PART_MAIN);
    lv_obj_set_style_radius(row, ROW_H / 2, LV_PART_MAIN);
    lv_obj_set_style_border_width(row, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(row, ROW_PAD_V, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(row, ROW_PAD_V, LV_PART_MAIN);
    lv_obj_set_style_pad_left(row, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(row, 0, LV_PART_MAIN);
    lv_obj_clear_flag(row, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(row, LV_OBJ_FLAG_CLICKABLE);
    if (cb) lv_obj_add_event_cb(row, cb, LV_EVENT_CLICKED, NULL);

    // Icon circle
    lv_obj_t *circle = lv_obj_create(row);
    lv_obj_set_size(circle, CIRCLE_SIZE, CIRCLE_SIZE);
    lv_obj_align(circle, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_bg_color(circle, lv_color_hex(0x242424), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(circle, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(circle, CIRCLE_SIZE / 2, LV_PART_MAIN);
    lv_obj_set_style_border_width(circle, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(circle, 0, LV_PART_MAIN);
    lv_obj_clear_flag(circle, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t *ico = lv_label_create(circle);
    lv_obj_set_style_text_font(ico, icon_font, LV_PART_MAIN);
    lv_obj_set_style_text_color(ico, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text(ico, icon_str);
    lv_obj_align(ico, LV_ALIGN_CENTER, 0, 0);

    // Label
    lv_obj_t *lbl = lv_label_create(row);
    lv_obj_set_style_text_font(lbl, &sf_pro_display_medium_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text(lbl, label);
    lv_obj_align(lbl, LV_ALIGN_LEFT_MID, CIRCLE_SIZE + CIRCLE_GAP, 0);
}

// ── Public ────────────────────────────────────────────────────────────────────

static lv_obj_t *nav_list = nullptr;

static void on_nav_screen_loaded(lv_event_t *) {
    lv_indev_t *indev = lv_indev_get_next(NULL);
    while (indev) { lv_indev_reset(indev, NULL); indev = lv_indev_get_next(indev); }

    if (!nav_list) return;
    lv_obj_scroll_to_y(nav_list, 0, LV_ANIM_OFF);

    lv_obj_clear_flag(nav_list, LV_OBJ_FLAG_SCROLLABLE);
    lv_timer_t *t = lv_timer_create([](lv_timer_t *t) {
        lv_obj_add_flag((lv_obj_t *)t->user_data, LV_OBJ_FLAG_SCROLLABLE);
    }, 300, nav_list);
    lv_timer_set_repeat_count(t, 1);
}

void create_nav_screen() {
    if (scr_nav) return;
    scr_nav = make_screen();
    lv_obj_add_event_cb(scr_nav, on_nav_screen_loaded, LV_EVENT_SCREEN_LOADED, NULL);

    // Scrollable column — starts below shared top bar (32 pad + 29 bar + 20 gap = 81)
    int list_y = 81;
    lv_obj_t *list = lv_obj_create(scr_nav);
    nav_list = list;
    lv_obj_set_size(list, SCREEN_W, SCREEN_H - list_y);
    lv_obj_set_pos(list, 0, list_y);
    lv_obj_set_style_bg_opa(list, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(list, 32, LV_PART_MAIN);
    lv_obj_set_style_pad_right(list, 32, LV_PART_MAIN);
    lv_obj_set_style_pad_top(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(list, 32, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(list, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(list, LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(list, 0, LV_PART_MAIN);

    make_item(list, ICON_CLOCK,       "Clock",    on_clock_item);
    make_item(list, ICON_WEATHER,     "Weather",  on_weather_item);
    make_item(list, ICON_NOTES,       "Calendar", on_calendar_item);
    make_item(list, LV_SYMBOL_AUDIO,  "Music",    on_music_item,    &lv_font_montserrat_32);
    make_item(list, LV_SYMBOL_EDIT,   "GitHub",   on_github_item,   &lv_font_montserrat_32);
    make_item(list, LV_SYMBOL_POWER,  "Lamp",     on_lamp_item,     &lv_font_montserrat_32);
    make_item(list, ICON_SETTINGS,    "Settings", on_settings_item);
}
