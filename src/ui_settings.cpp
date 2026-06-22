#include "ui_settings.h"
#include "ui_common.h"
#include "hw.h"

LV_FONT_DECLARE(sf_pro_display_medium_24);
LV_FONT_DECLARE(sf_pro_display_medium_32);

static lv_timer_t *mem_timer = nullptr;

static void refresh_mem_labels() {
    if (!lbl_mem_heap) return;

    char buf[32];

    uint32_t free_heap  = ESP.getFreeHeap();
    uint32_t total_heap = ESP.getHeapSize();
    snprintf(buf, sizeof(buf), "%lu / %lu KB", free_heap / 1024, total_heap / 1024);
    lv_label_set_text(lbl_mem_heap, buf);

    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
    snprintf(buf, sizeof(buf), "%u / %u KB",
             (mon.total_size - mon.free_size) / 1024, mon.total_size / 1024);
    lv_label_set_text(lbl_mem_lvgl, buf);

    uint32_t free_psram  = ESP.getFreePsram();
    uint32_t total_psram = ESP.getPsramSize();
    if (total_psram > 0) {
        snprintf(buf, sizeof(buf), "%lu / %lu KB", free_psram / 1024, total_psram / 1024);
    } else {
        strlcpy(buf, "\xe2\x80\x93", sizeof(buf));
    }
    lv_label_set_text(lbl_mem_psram, buf);
}

static void on_mem_timer(lv_timer_t *) { refresh_mem_labels(); }

static void make_stat_row(lv_obj_t *parent, int y, const char *title, lv_obj_t **out_val) {
    lv_obj_t *row = make_row(parent, y, SCREEN_W - 32, 74);

    lv_obj_t *lbl_n = lv_label_create(row);
    lv_obj_set_style_text_font(lbl_n, &sf_pro_display_medium_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_n, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text(lbl_n, title);
    lv_obj_align(lbl_n, LV_ALIGN_LEFT_MID, 0, 0);

    *out_val = lv_label_create(row);
    lv_obj_set_style_text_font(*out_val, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(*out_val, lv_color_hex(0x666666), LV_PART_MAIN);
    lv_label_set_text(*out_val, "...");
    lv_obj_align(*out_val, LV_ALIGN_RIGHT_MID, 0, 0);
}

void create_settings_screen() {
    if (scr_settings) return;
    scr_settings = make_screen();
    lv_obj_add_flag(scr_settings, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(scr_settings, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(scr_settings, LV_OBJ_FLAG_SCROLL_ELASTIC);

    lv_obj_add_event_cb(scr_settings, [](lv_event_t *) {
        if (mem_timer) { lv_timer_del(mem_timer); mem_timer = nullptr; }
    }, LV_EVENT_DELETE, NULL);

    int y = 81;
    make_separator(scr_settings, y); y += 1;

    // ── Brightness ────────────────────────────────────────────────────────────
    {
        lv_obj_t *row = make_row(scr_settings, y, SCREEN_W - 32, 80);
        lv_obj_t *lbl_n = lv_label_create(row);
        lv_obj_set_style_text_font(lbl_n, &sf_pro_display_medium_32, LV_PART_MAIN);
        lv_obj_set_style_text_color(lbl_n, lv_color_white(), LV_PART_MAIN);
        lv_label_set_text(lbl_n, "Brightness");
        lv_obj_align(lbl_n, LV_ALIGN_LEFT_MID, 0, 0);

        lbl_bright_val = lv_label_create(row);
        lv_obj_set_style_text_font(lbl_bright_val, &sf_pro_display_medium_24, LV_PART_MAIN);
        lv_obj_set_style_text_color(lbl_bright_val, lv_color_hex(0x666666), LV_PART_MAIN);
        char b[8]; snprintf(b, sizeof(b), "%d%%", brightness_pct);
        lv_label_set_text(lbl_bright_val, b);
        lv_obj_align(lbl_bright_val, LV_ALIGN_RIGHT_MID, 0, 0);
    }
    make_separator(scr_settings, y + 80); y += 81;

    // ── Brightness slider ─────────────────────────────────────────────────────
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

    // ── Memory section header ─────────────────────────────────────────────────
    {
        lv_obj_t *hdr = lv_label_create(scr_settings);
        lv_obj_set_style_text_font(hdr, &sf_pro_display_medium_24, LV_PART_MAIN);
        lv_obj_set_style_text_color(hdr, lv_color_hex(0x444444), LV_PART_MAIN);
        lv_label_set_text(hdr, "ПАМЯТЬ");
        lv_obj_set_pos(hdr, 16, y + 8);
    }
    y += 38;
    make_separator(scr_settings, y); y += 1;

    // ── Memory stat rows ──────────────────────────────────────────────────────
    make_stat_row(scr_settings, y, "DRAM",  &lbl_mem_heap);
    make_separator(scr_settings, y + 74); y += 75;

    make_stat_row(scr_settings, y, "LVGL",  &lbl_mem_lvgl);
    make_separator(scr_settings, y + 74); y += 75;

    make_stat_row(scr_settings, y, "PSRAM", &lbl_mem_psram);
    make_separator(scr_settings, y + 74); y += 75;

    // ── Restart button ────────────────────────────────────────────────────────
    {
        lv_obj_t *row = make_row(scr_settings, y, SCREEN_W - 32, 80);
        lv_obj_add_flag(row, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(row, [](lv_event_t *) {
            delay(80);
            ESP.restart();
        }, LV_EVENT_CLICKED, NULL);
        lv_obj_set_style_opa(row, LV_OPA_50, LV_STATE_PRESSED);

        lv_obj_t *lbl = lv_label_create(row);
        lv_obj_set_style_text_font(lbl, &sf_pro_display_medium_32, LV_PART_MAIN);
        lv_obj_set_style_text_color(lbl, lv_color_hex(0xFF3030), LV_PART_MAIN);
        lv_label_set_text(lbl, "Restart");
        lv_obj_align(lbl, LV_ALIGN_CENTER, 0, 0);
    }
    make_separator(scr_settings, y + 80);

    refresh_mem_labels();
    mem_timer = lv_timer_create(on_mem_timer, 2000, NULL);
}
