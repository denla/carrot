#include "ui_clock4.h"
#include "ui_common.h"
#include "hw.h"
#include <math.h>

LV_FONT_DECLARE(sf_pro_display_medium_24);

#define CX       240
#define CY       240
#define GOLD     lv_color_hex(0xC9A84C)

// Hand geometry
#define HOUR_LEN       108   // tip distance from center
#define HOUR_STEM_END   38   // thin part ends here
#define HOUR_PILL_S     34   // pill starts here (4px overlap for seamless join)

#define MIN_LEN        158
#define MIN_STEM_END    55
#define MIN_PILL_S      51

#define SEC_LEN        172
#define SEC_TAIL        42

#define PILL_W          10   // wide pill line width
#define STEM_W           2   // thin stem line width

// Hour hand (stem + pill)
static lv_obj_t   *hour_stem,  *hour_pill;
static lv_point_t  pts_hour_stem[2], pts_hour_pill[2];

// Minute hand (stem + pill)
static lv_obj_t   *min_stem,   *min_pill;
static lv_point_t  pts_min_stem[2],  pts_min_pill[2];

// Second hand
static lv_obj_t   *hand_sec;
static lv_point_t  pts_sec[2];

static void calc_two_part(float angle_deg,
                          int stem_end, int pill_start, int tip,
                          lv_point_t stem[2], lv_point_t pill[2]) {
    float rad = (angle_deg - 90.0f) * (float)M_PI / 180.0f;
    float dx = cosf(rad), dy = sinf(rad);

    stem[0].x = CX;                                stem[0].y = CY;
    stem[1].x = CX + (int16_t)(stem_end   * dx);  stem[1].y = CY + (int16_t)(stem_end   * dy);

    pill[0].x = CX + (int16_t)(pill_start * dx);  pill[0].y = CY + (int16_t)(pill_start * dy);
    pill[1].x = CX + (int16_t)(tip        * dx);  pill[1].y = CY + (int16_t)(tip        * dy);
}

static void calc_sec(float angle_deg, lv_point_t *p0, lv_point_t *p1) {
    float rad = (angle_deg - 90.0f) * (float)M_PI / 180.0f;
    p0->x = CX - (int16_t)(SEC_TAIL * cosf(rad));
    p0->y = CY - (int16_t)(SEC_TAIL * sinf(rad));
    p1->x = CX + (int16_t)(SEC_LEN  * cosf(rad));
    p1->y = CY + (int16_t)(SEC_LEN  * sinf(rad));
}

static lv_obj_t *make_line(lv_obj_t *parent, lv_color_t color, int width) {
    lv_obj_t *ln = lv_line_create(parent);
    lv_obj_set_style_line_color(ln, color, LV_PART_MAIN);
    lv_obj_set_style_line_width(ln, width, LV_PART_MAIN);
    lv_obj_set_style_line_rounded(ln, true, LV_PART_MAIN);
    return ln;
}

static void on_gesture(lv_event_t *) {
    if (lv_scr_act() != scr_clock4) return;
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    if (dir == LV_DIR_LEFT)  nav_to_weather (scr_clock4, LV_SCR_LOAD_ANIM_MOVE_LEFT);
    if (dir == LV_DIR_RIGHT) nav_to_settings(scr_clock4, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
    if (dir == LV_DIR_TOP)   nav_to_nav     (scr_clock4, LV_SCR_LOAD_ANIM_MOVE_TOP);
}

static void on_tap(lv_event_t *) {
    if (lv_scr_act() != scr_clock4) return;
    nav_to_nav(scr_clock4, LV_SCR_LOAD_ANIM_MOVE_TOP);
}

void create_clock4_screen() {
    if (scr_clock4) return;
    scr_clock4 = make_screen();
    lv_obj_add_event_cb(scr_clock4, on_gesture, LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(scr_clock4, on_tap,     LV_EVENT_CLICKED,  NULL);

    // Date label — white, right side at 3 o'clock
    lbl_c4_date = lv_label_create(scr_clock4);
    lv_obj_set_style_text_font(lbl_c4_date, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_c4_date, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_pos(lbl_c4_date, CX + 118, CY - 14);
    lv_label_set_text(lbl_c4_date, "--");

    // Minute hand: thin stem (behind) then wide pill (on top)
    min_stem = make_line(scr_clock4, lv_color_white(), STEM_W);
    min_pill = make_line(scr_clock4, lv_color_white(), PILL_W);

    // Hour hand: thin stem then wide pill
    hour_stem = make_line(scr_clock4, lv_color_white(), STEM_W);
    hour_pill = make_line(scr_clock4, lv_color_white(), PILL_W);

    // Second hand — gold, thin, with tail
    hand_sec = make_line(scr_clock4, GOLD, 2);

    // Center cap: white ring
    lv_obj_t *cap_white = lv_obj_create(scr_clock4);
    lv_obj_set_size(cap_white, 16, 16);
    lv_obj_set_pos(cap_white, CX - 8, CY - 8);
    lv_obj_set_style_radius(cap_white, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_style_bg_color(cap_white, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cap_white, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(cap_white, 0, LV_PART_MAIN);
    lv_obj_clear_flag(cap_white, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);

    // Center cap: black core
    lv_obj_t *cap_black = lv_obj_create(scr_clock4);
    lv_obj_set_size(cap_black, 8, 8);
    lv_obj_set_pos(cap_black, CX - 4, CY - 4);
    lv_obj_set_style_radius(cap_black, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_style_bg_color(cap_black, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cap_black, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(cap_black, 0, LV_PART_MAIN);
    lv_obj_clear_flag(cap_black, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
}

static HWDateTime cached_dt  = {};
static uint32_t  last_rtc_ms = 0;
static bool      dt_valid    = false;

void update_clock4() {
    if (!scr_clock4) return;
    uint32_t now = millis();

    if (!dt_valid || now - last_rtc_ms >= 1000) {
        cached_dt   = hw_get_datetime();
        last_rtc_ms = now;
        dt_valid    = true;
        if (lbl_c4_date) {
            char ds[4];
            snprintf(ds, sizeof(ds), "%d", cached_dt.day);
            lv_label_set_text(lbl_c4_date, ds);
        }
    }

    float sec_frac = (now - last_rtc_ms) / 1000.0f;
    float s_angle  = (cached_dt.second + sec_frac) * 6.0f;
    float m_angle  = cached_dt.minute * 6.0f + (cached_dt.second + sec_frac) * 0.1f;
    float h_angle  = (cached_dt.hour % 12) * 30.0f + cached_dt.minute * 0.5f;

    calc_two_part(m_angle, MIN_STEM_END,  MIN_PILL_S,  MIN_LEN,  pts_min_stem,  pts_min_pill);
    calc_two_part(h_angle, HOUR_STEM_END, HOUR_PILL_S, HOUR_LEN, pts_hour_stem, pts_hour_pill);
    calc_sec(s_angle, &pts_sec[0], &pts_sec[1]);

    lv_line_set_points(min_stem,  pts_min_stem,  2);
    lv_line_set_points(min_pill,  pts_min_pill,  2);
    lv_line_set_points(hour_stem, pts_hour_stem, 2);
    lv_line_set_points(hour_pill, pts_hour_pill, 2);
    lv_line_set_points(hand_sec,  pts_sec,       2);
}
