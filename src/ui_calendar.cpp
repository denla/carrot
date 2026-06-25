#include "ui_calendar.h"
#include "ui_common.h"
#include "hw.h"
#include "module_registry.h"

LV_FONT_DECLARE(sf_pro_display_medium_24);
LV_FONT_DECLARE(sf_pro_display_medium_32);

#define COLOR_GRAY lv_color_hex(0x8E8E93)   // day names, inactive arrows
#define COLOR_DIM  lv_color_hex(0x3A3A3C)   // prev/next month day numbers
#define COLOR_BTN  lv_color_hex(0x2C2C2E)   // nav button background

#define COLS     7
#define PAD      9          // side margin; 7×66 + 2×9 = 480
#define CELL_W   66
#define CELL_H   53         // 6×53 = 318; Y_GRID + 318 = 480
#define BTN_D    44         // nav circle diameter
#define CIRCLE_D 48         // today highlight circle

// Vertical layout (top bar ends at 61):
#define Y_HDR    72         // header row top
#define HDR_H    40         // ~32pt line height
#define Y_DAYS   128        // Y_HDR + HDR_H + 16
#define Y_GRID   162        // Y_DAYS + 28 + 6

static lv_obj_t *cal_month_lbl      = nullptr;
static lv_obj_t *cal_highlights[42] = {};
static lv_obj_t *cal_labels[42]     = {};
static int        cal_year          = 0;
static int        cal_month         = 0;

static void on_delete(lv_event_t *) {
    cal_month_lbl = nullptr;
    memset(cal_highlights, 0, sizeof(cal_highlights));
    memset(cal_labels,     0, sizeof(cal_labels));
}

static void mod_destroy() { scr_calendar = nullptr; }

static Module calendar_module = {
    .name       = "Calendar",
    .icon       = "\xEE\x80\x83",
    .icon_font  = nullptr,
    .screen     = &scr_calendar,
    .create     = create_calendar_screen,
    .destroy    = mod_destroy,
    .update     = nullptr,
    .update_ms  = 0,
    .order      = 2,
};
REGISTER_MODULE(calendar_module)

static int day_of_week(int y, int m, int d) {
    static const int t[] = {0,3,2,5,0,3,5,1,4,6,2,4};
    if (m < 3) y--;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

// Returns 0=Mon … 6=Sun for the 1st of the month
static int first_weekday(int y, int m) {
    int d = day_of_week(y, m, 1);
    return (d == 0) ? 6 : d - 1;
}

static int days_in_month(int y, int m) {
    static const int dim[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int d = dim[m - 1];
    if (m == 2 && ((y%4==0 && y%100!=0) || y%400==0)) d = 29;
    return d;
}

static void redraw_calendar() {
    static const char *month_names[12] = {
        "Январь","Февраль","Март","Апрель","Май","Июнь",
        "Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"
    };

    char header[40];
    snprintf(header, sizeof(header), "%s %d", month_names[cal_month - 1], cal_year);
    lv_label_set_text(cal_month_lbl, header);

    HWDateTime now = hw_get_datetime();
    bool same_month = (now.year == cal_year && now.month == cal_month);

    int first_col  = first_weekday(cal_year, cal_month);
    int total_days = days_in_month(cal_year, cal_month);
    int prev_total = days_in_month(
        cal_month == 1 ? cal_year - 1 : cal_year,
        cal_month == 1 ? 12 : cal_month - 1
    );

    for (int i = 0; i < 42; i++) {
        int day, in_month;
        if (i < first_col) {
            day      = prev_total - (first_col - 1 - i);
            in_month = 0;
        } else if (i - first_col < total_days) {
            day      = i - first_col + 1;
            in_month = 1;
        } else {
            day      = i - first_col - total_days + 1;
            in_month = 0;
        }

        bool today = same_month && in_month && (day == now.day);

        char txt[4];
        snprintf(txt, sizeof(txt), "%d", day);
        lv_label_set_text(cal_labels[i], txt);

        lv_color_t text_col;
        if (today)       text_col = lv_color_black();
        else if (in_month) text_col = lv_color_white();
        else             text_col = COLOR_DIM;
        lv_obj_set_style_text_color(cal_labels[i], text_col, LV_PART_MAIN);

        if (today) lv_obj_clear_flag(cal_highlights[i], LV_OBJ_FLAG_HIDDEN);
        else       lv_obj_add_flag  (cal_highlights[i], LV_OBJ_FLAG_HIDDEN);
    }
}

static void on_cal_prev(lv_event_t *) {
    cal_month--;
    if (cal_month < 1) { cal_month = 12; cal_year--; }
    redraw_calendar();
}

static void on_cal_next(lv_event_t *) {
    cal_month++;
    if (cal_month > 12) { cal_month = 1; cal_year++; }
    redraw_calendar();
}

static void on_cal_gesture(lv_event_t *) {
    if (lv_scr_act() != scr_calendar) return;
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    if (dir == LV_DIR_LEFT)  on_cal_next(nullptr);
    if (dir == LV_DIR_RIGHT) on_cal_prev(nullptr);
}

static lv_obj_t *make_nav_btn(lv_obj_t *parent, int x, int y,
                               const char *symbol, lv_event_cb_t cb) {
    lv_obj_t *btn = lv_obj_create(parent);
    lv_obj_set_size(btn, BTN_D, BTN_D);
    lv_obj_set_pos(btn, x, y);
    lv_obj_set_style_radius(btn, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, COLOR_BTN, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(btn, 0, LV_PART_MAIN);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x48484A), LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *lbl = lv_label_create(btn);
    lv_obj_set_style_text_font(lbl, &sf_pro_display_medium_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text(lbl, symbol);
    lv_obj_align(lbl, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(lbl, LV_OBJ_FLAG_EVENT_BUBBLE);
    return btn;
}

void create_calendar_screen() {
    if (scr_calendar) return;
    HWDateTime now = hw_get_datetime();
    cal_year  = now.year;
    cal_month = now.month;

    scr_calendar = make_screen();
    lv_obj_add_event_cb(scr_calendar, on_delete,       LV_EVENT_DELETE,  NULL);
    lv_obj_add_event_cb(scr_calendar, on_cal_gesture,  LV_EVENT_GESTURE, NULL);
    lv_obj_add_event_cb(scr_calendar, [](lv_event_t *){ redraw_calendar(); },
                        LV_EVENT_SCREEN_LOADED, NULL);

    // ── Header row: nav buttons + month label ─────────────────────────────────
    int btn_y = Y_HDR + (HDR_H - BTN_D) / 2;

    make_nav_btn(scr_calendar, PAD,               btn_y, "<", on_cal_prev);
    make_nav_btn(scr_calendar, 480 - PAD - BTN_D, btn_y, ">", on_cal_next);

    cal_month_lbl = lv_label_create(scr_calendar);
    lv_obj_set_style_text_font(cal_month_lbl, &sf_pro_display_medium_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(cal_month_lbl, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_align(cal_month_lbl, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_width(cal_month_lbl, 480 - 2 * (PAD + BTN_D + 8));
    lv_obj_align(cal_month_lbl, LV_ALIGN_TOP_MID, 0, Y_HDR);

    // ── Day-name row ─────────────────────────────────────────────────────────
    static const char *day_names[7] = {"П","В","С","Ч","П","С","В"};
    for (int c = 0; c < COLS; c++) {
        lv_obj_t *lbl = lv_label_create(scr_calendar);
        lv_obj_set_style_text_font(lbl, &sf_pro_display_medium_24, LV_PART_MAIN);
        lv_obj_set_style_text_color(lbl, COLOR_GRAY, LV_PART_MAIN);
        lv_obj_set_style_text_align(lbl, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
        lv_obj_set_width(lbl, CELL_W);
        lv_obj_set_pos(lbl, PAD + c * CELL_W, Y_DAYS);
        lv_label_set_text(lbl, day_names[c]);
    }

    // ── Grid: highlight circles first (drawn below labels) ───────────────────
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < COLS; c++) {
            int idx = r * COLS + c;
            int cx  = PAD + c * CELL_W + CELL_W / 2;
            int cy  = Y_GRID + r * CELL_H + CELL_H / 2;

            cal_highlights[idx] = lv_obj_create(scr_calendar);
            lv_obj_set_size(cal_highlights[idx], CIRCLE_D, CIRCLE_D);
            lv_obj_set_pos(cal_highlights[idx], cx - CIRCLE_D/2, cy - CIRCLE_D/2);
            lv_obj_set_style_radius(cal_highlights[idx], LV_RADIUS_CIRCLE, LV_PART_MAIN);
            lv_obj_set_style_bg_color(cal_highlights[idx], lv_color_white(), LV_PART_MAIN);
            lv_obj_set_style_bg_opa(cal_highlights[idx], LV_OPA_COVER, LV_PART_MAIN);
            lv_obj_set_style_border_width(cal_highlights[idx], 0, LV_PART_MAIN);
            lv_obj_clear_flag(cal_highlights[idx], LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_add_flag(cal_highlights[idx], LV_OBJ_FLAG_HIDDEN);
        }
    }

    // ── Grid: day number labels ───────────────────────────────────────────────
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < COLS; c++) {
            int idx = r * COLS + c;
            int cy  = Y_GRID + r * CELL_H + CELL_H / 2;

            cal_labels[idx] = lv_label_create(scr_calendar);
            lv_obj_set_style_text_font(cal_labels[idx], &sf_pro_display_medium_24, LV_PART_MAIN);
            lv_obj_set_style_text_color(cal_labels[idx], lv_color_white(), LV_PART_MAIN);
            lv_obj_set_style_text_align(cal_labels[idx], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
            lv_obj_set_width(cal_labels[idx], CELL_W);
            lv_obj_set_pos(cal_labels[idx], PAD + c * CELL_W, cy - 14);
            lv_label_set_text(cal_labels[idx], "");
        }
    }

    redraw_calendar();
}

void update_calendar_date() {
    if (lv_scr_act() == scr_calendar) redraw_calendar();
}
