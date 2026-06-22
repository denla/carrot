#include "ui_clock4.h"
#include "ui_common.h"
#include "hw.h"
#include <math.h>

LV_FONT_DECLARE(sf_pro_display_medium_24);

#define CX          240
#define CY          240
#define TICK_R      200   // radius of hour tick dots
#define HOUR_LEN     95
#define MIN_LEN     155
#define SEC_LEN     170
#define SEC_TAIL     38   // counterweight behind center

static lv_obj_t *hand_hour;
static lv_obj_t *hand_min;
static lv_obj_t *hand_sec;
static lv_point_t pts_hour[2];
static lv_point_t pts_min[2];
static lv_point_t pts_sec[2];

static void calc_hand(int len, float angle_deg, lv_point_t *p0, lv_point_t *p1) {
    float rad = (angle_deg - 90.0f) * (float)M_PI / 180.0f;
    p0->x = CX;
    p0->y = CY;
    p1->x = CX + (int16_t)(len * cosf(rad));
    p1->y = CY + (int16_t)(len * sinf(rad));
}

static void calc_sec_hand(float angle_deg, lv_point_t *p0, lv_point_t *p1) {
    float rad = (angle_deg - 90.0f) * (float)M_PI / 180.0f;
    p0->x = CX - (int16_t)(SEC_TAIL * cosf(rad));
    p0->y = CY - (int16_t)(SEC_TAIL * sinf(rad));
    p1->x = CX + (int16_t)(SEC_LEN * cosf(rad));
    p1->y = CY + (int16_t)(SEC_LEN * sinf(rad));
}

static void on_clock4_gesture(lv_event_t *) {
    if (lv_scr_act() != scr_clock4) return;
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    if (dir == LV_DIR_LEFT)  nav_to_weather (scr_clock4, LV_SCR_LOAD_ANIM_MOVE_LEFT);
    if (dir == LV_DIR_RIGHT) nav_to_settings(scr_clock4, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
    if (dir == LV_DIR_TOP)   nav_to_nav     (scr_clock4, LV_SCR_LOAD_ANIM_MOVE_TOP);
}

static void on_clock4_tap(lv_event_t *) {
    if (lv_scr_act() != scr_clock4) return;
    nav_to_nav(scr_clock4, LV_SCR_LOAD_ANIM_MOVE_TOP);
}

void create_clock4_screen() {
    if (scr_clock4) return;
    scr_clock4 = make_screen();
    lv_obj_add_event_cb(scr_clock4, on_clock4_gesture, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(scr_clock4, on_clock4_tap,     LV_EVENT_CLICKED,  NULL);

    // ── Date label ────────────────────────────────────────────────────────────
    lbl_c4_date = lv_label_create(scr_clock4);
    lv_obj_set_style_text_font(lbl_c4_date, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_c4_date, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_pos(lbl_c4_date, 32, 32);
    lv_label_set_text(lbl_c4_date, "-- ------, --");

    // ── Hour tick marks (12 dots) ─────────────────────────────────────────────
    for (int i = 0; i < 12; i++) {
        float rad = (i * 30.0f - 90.0f) * (float)M_PI / 180.0f;
        int x = CX + (int)(TICK_R * cosf(rad));
        int y = CY + (int)(TICK_R * sinf(rad));
        int r = (i % 3 == 0) ? 5 : 3;  // cardinal marks slightly larger
        lv_obj_t *dot = lv_obj_create(scr_clock4);
        lv_obj_set_size(dot, r * 2, r * 2);
        lv_obj_set_pos(dot, x - r, y - r);
        lv_obj_set_style_radius(dot, LV_RADIUS_CIRCLE, LV_PART_MAIN);
        lv_obj_set_style_bg_color(dot, lv_color_hex(0x3a3a3a), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(dot, LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_border_width(dot, 0, LV_PART_MAIN);
        lv_obj_clear_flag(dot, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
    }

    // ── Minute hand ───────────────────────────────────────────────────────────
    hand_min = lv_line_create(scr_clock4);
    lv_obj_set_style_line_color(hand_min, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_line_width(hand_min, 3, LV_PART_MAIN);
    lv_obj_set_style_line_rounded(hand_min, true, LV_PART_MAIN);

    // ── Hour hand ─────────────────────────────────────────────────────────────
    hand_hour = lv_line_create(scr_clock4);
    lv_obj_set_style_line_color(hand_hour, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_line_width(hand_hour, 8, LV_PART_MAIN);
    lv_obj_set_style_line_rounded(hand_hour, true, LV_PART_MAIN);

    // ── Second hand ───────────────────────────────────────────────────────────
    hand_sec = lv_line_create(scr_clock4);
    lv_obj_set_style_line_color(hand_sec, lv_color_hex(0xFF001A), LV_PART_MAIN);
    lv_obj_set_style_line_width(hand_sec, 2, LV_PART_MAIN);
    lv_obj_set_style_line_rounded(hand_sec, true, LV_PART_MAIN);

    // ── Center cap ────────────────────────────────────────────────────────────
    lv_obj_t *cap = lv_obj_create(scr_clock4);
    lv_obj_set_size(cap, 14, 14);
    lv_obj_set_pos(cap, CX - 7, CY - 7);
    lv_obj_set_style_radius(cap, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_style_bg_color(cap, lv_color_hex(0xFF001A), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cap, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(cap, 0, LV_PART_MAIN);
    lv_obj_clear_flag(cap, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
}

static HWDateTime cached_dt   = {};
static uint32_t  last_rtc_ms  = 0;
static bool      dt_valid      = false;

void update_clock4() {
    if (!scr_clock4) return;
    uint32_t now = millis();

    // Read RTC once per second
    if (!dt_valid || now - last_rtc_ms >= 1000) {
        cached_dt   = hw_get_datetime();
        last_rtc_ms = now;
        dt_valid    = true;

        if (cached_dt.month >= 1 && cached_dt.month <= 12 && cached_dt.week <= 6) {
            char date_str[40];
            snprintf(date_str, sizeof(date_str), "%d %s, %s",
                     cached_dt.day, months_ru[cached_dt.month - 1], weekdays_ru[cached_dt.week]);
            lv_label_set_text(lbl_c4_date, date_str);
        }
    }

    // Sub-second interpolation via millis
    float sec_frac = (now - last_rtc_ms) / 1000.0f;
    float s_angle  = (cached_dt.second + sec_frac) * 6.0f;
    float m_angle  = cached_dt.minute * 6.0f + (cached_dt.second + sec_frac) * 0.1f;
    float h_angle  = (cached_dt.hour % 12) * 30.0f + cached_dt.minute * 0.5f;

    calc_hand(HOUR_LEN, h_angle, &pts_hour[0], &pts_hour[1]);
    calc_hand(MIN_LEN,  m_angle, &pts_min[0],  &pts_min[1]);
    calc_sec_hand(s_angle, &pts_sec[0], &pts_sec[1]);

    lv_line_set_points(hand_hour, pts_hour, 2);
    lv_line_set_points(hand_min,  pts_min,  2);
    lv_line_set_points(hand_sec,  pts_sec,  2);
}
