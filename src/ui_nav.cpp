#include "ui_nav.h"
#include "ui_calendar.h"
#include "ui_music.h"
#include "ui_common.h"
#include "hw.h"
#include "ui_github.h"

LV_FONT_DECLARE(sf_pro_display_medium_24);
LV_FONT_DECLARE(sf_pro_display_medium_32);
LV_FONT_DECLARE(sf_symbols_icons_28);
LV_FONT_DECLARE(sf_symbols_icons_32);

#define COLOR_ITEM_BG  lv_color_hex(0x242424)
#define PADDING        32
#define ITEM_H         100
#define ITEM_GAP       8
#define ITEM_RADIUS    50
#define ICON_CLOCK     "\xEE\x80\x81"
#define ICON_WEATHER   "\xEE\x80\x82"
#define ICON_NOTES     "\xEE\x80\x83"
#define ICON_SETTINGS  "\xEE\x80\x84"

static void on_clock_item(lv_event_t *) {
    nav_to(scr_nav, active_clock(), LV_SCR_LOAD_ANIM_MOVE_BOTTOM);
}
static void on_weather_item(lv_event_t *)  { nav_to_weather (scr_nav); }
static void on_settings_item(lv_event_t *) { nav_to_settings(scr_nav); }
static void on_calendar_item(lv_event_t *) { nav_to_calendar(scr_nav); }
static void on_music_item(lv_event_t *)    { nav_to_music   (scr_nav); }
static void on_github_item(lv_event_t *)   { nav_to_github  (scr_nav); }

// ── Menu item ─────────────────────────────────────────────────────────────────

static void make_item(lv_obj_t *list, const char *icon_str, const char *label,
                      lv_event_cb_t cb, bool disabled,
                      const lv_font_t *icon_font = nullptr) {
    lv_obj_t *item = lv_obj_create(list);
    lv_obj_set_size(item, SCREEN_W - 2 * PADDING, ITEM_H);
    lv_obj_set_style_bg_color(item, COLOR_ITEM_BG, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(item, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(item, ITEM_RADIUS, LV_PART_MAIN);
    lv_obj_set_style_border_width(item, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(item, 32, LV_PART_MAIN);
    lv_obj_set_style_pad_right(item, 32, LV_PART_MAIN);
    lv_obj_set_style_pad_top(item, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(item, 0, LV_PART_MAIN);
    lv_obj_clear_flag(item, LV_OBJ_FLAG_SCROLLABLE);

    lv_color_t fg = disabled ? lv_color_hex(0x444444) : lv_color_white();

    lv_obj_t *ico = lv_label_create(item);
    lv_obj_set_style_text_font(ico, icon_font ? icon_font : &sf_symbols_icons_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(ico, fg, LV_PART_MAIN);
    lv_label_set_text(ico, icon_str);
    lv_obj_align(ico, LV_ALIGN_LEFT_MID, 0, 0);

    lv_obj_t *lbl = lv_label_create(item);
    lv_obj_set_style_text_font(lbl, &sf_pro_display_medium_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl, fg, LV_PART_MAIN);
    lv_label_set_text(lbl, label);
    lv_obj_align(lbl, LV_ALIGN_LEFT_MID, 60, 0);

    if (!disabled && cb) {
        lv_obj_add_flag(item, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(item, cb, LV_EVENT_CLICKED, NULL);
        lv_obj_set_style_bg_color(item, lv_color_hex(0x3a3a3a), LV_PART_MAIN | LV_STATE_PRESSED);
    }
}

// ── Public ────────────────────────────────────────────────────────────────────

static lv_obj_t *nav_list = nullptr;

static void on_nav_screen_loaded(lv_event_t *) {
    // Kill residual swipe inertia from the gesture that opened this screen
    lv_indev_t *indev = lv_indev_get_next(NULL);
    while (indev) { lv_indev_reset(indev, NULL); indev = lv_indev_get_next(indev); }

    if (!nav_list) return;
    lv_obj_scroll_to_y(nav_list, 0, LV_ANIM_OFF);

    // Disable scrolling briefly so the tail of the swipe can't re-scroll the list
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

    // Scrollable list container — starts below shared top bar (32 pad + 29 bar + 20 gap = 81)
    int list_y = 81;
    lv_obj_t *list = lv_obj_create(scr_nav);
    nav_list = list;
    lv_obj_set_size(list, SCREEN_W, SCREEN_H - list_y);
    lv_obj_set_pos(list, 0, list_y);
    lv_obj_set_style_bg_opa(list, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(list, PADDING, LV_PART_MAIN);
    lv_obj_set_style_pad_right(list, PADDING, LV_PART_MAIN);
    lv_obj_set_style_pad_top(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(list, PADDING, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(list, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(list, LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(list, ITEM_GAP, LV_PART_MAIN);

    make_item(list, ICON_CLOCK,    "Clock",    on_clock_item,    false);
    make_item(list, ICON_WEATHER,  "Weather",  on_weather_item,  false);
    make_item(list, ICON_NOTES,    "Calendar", on_calendar_item, false);
    make_item(list, LV_SYMBOL_AUDIO, "Music",  on_music_item,    false, &lv_font_montserrat_32);
    make_item(list, LV_SYMBOL_EDIT, "GitHub",   on_github_item,   false, &lv_font_montserrat_32);
    make_item(list, ICON_SETTINGS, "Settings", on_settings_item, false);
}
