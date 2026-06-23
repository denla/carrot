#include "ui_github.h"
#include "ui_common.h"

LV_FONT_DECLARE(sf_pro_display_medium_24);

#define GH_COLS     7
#define GH_ROWS     3
#define DOT_SIZE    43
#define DOT_HSTEP   62   // 43 px dot + 19 px gap
#define DOT_VSTEP   59   // 43 px dot + 16 px gap
#define X0          32
#define Y_CONTRIB   81
#define Y_LABELS   130   // Y_CONTRIB + 29 + 20
#define Y_DOTS     175   // Y_LABELS  + 29 + 16

static lv_obj_t *s_lbl_contrib = nullptr;
static lv_obj_t *s_dots[GH_ROWS][GH_COLS] = {};

static lv_color_t dot_color(int16_t v) {
    if (v <= 0) return lv_color_hex(0x242424);
    if (v <= 2) return lv_color_hex(0x4C0C06); // rgba(#FF2713, 0.3) on black
    return lv_color_hex(0xFF2713);
}

static void on_delete(lv_event_t *) {
    s_lbl_contrib = nullptr;
    memset(s_dots, 0, sizeof(s_dots));
}

void create_github_screen() {
    if (scr_github) return;
    scr_github = make_screen();
    lv_obj_add_event_cb(scr_github, on_delete, LV_EVENT_DELETE, NULL);

    s_lbl_contrib = lv_label_create(scr_github);
    lv_obj_set_style_text_font(s_lbl_contrib, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(s_lbl_contrib, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_pos(s_lbl_contrib, X0, Y_CONTRIB);

    static const char *day_labels[GH_COLS] = {"M", "T", "W", "T", "F", "S", "S"};
    for (int c = 0; c < GH_COLS; c++) {
        lv_obj_t *lbl = lv_label_create(scr_github);
        lv_obj_set_style_text_font(lbl, &sf_pro_display_medium_24, LV_PART_MAIN);
        lv_obj_set_style_text_color(lbl, lv_color_hex(0x7A7A7A), LV_PART_MAIN);
        lv_obj_set_style_text_align(lbl, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
        lv_obj_set_size(lbl, DOT_SIZE, 29);
        lv_obj_set_pos(lbl, X0 + c * DOT_HSTEP, Y_LABELS);
        lv_label_set_text(lbl, day_labels[c]);
    }

    for (int r = 0; r < GH_ROWS; r++) {
        for (int c = 0; c < GH_COLS; c++) {
            lv_obj_t *dot = lv_obj_create(scr_github);
            lv_obj_set_size(dot, DOT_SIZE, DOT_SIZE);
            lv_obj_set_pos(dot, X0 + c * DOT_HSTEP, Y_DOTS + r * DOT_VSTEP);
            lv_obj_set_style_radius(dot, DOT_SIZE / 2, LV_PART_MAIN);
            lv_obj_set_style_bg_color(dot, lv_color_hex(0x242424), LV_PART_MAIN);
            lv_obj_set_style_bg_opa(dot, LV_OPA_COVER, LV_PART_MAIN);
            lv_obj_set_style_border_width(dot, 0, LV_PART_MAIN);
            lv_obj_set_style_pad_all(dot, 0, LV_PART_MAIN);
            lv_obj_clear_flag(dot, LV_OBJ_FLAG_SCROLLABLE);
            s_dots[r][c] = dot;
        }
    }

    update_github_screen();
}

void update_github_screen() {
    if (!scr_github) return;

    if (s_lbl_contrib) {
        char buf[40];
        snprintf(buf, sizeof(buf), "%d contributions", g_github.total);
        lv_label_set_text(s_lbl_contrib, buf);
    }

    for (int r = 0; r < GH_ROWS; r++) {
        for (int c = 0; c < GH_COLS; c++) {
            if (s_dots[r][c])
                lv_obj_set_style_bg_color(s_dots[r][c],
                    dot_color(g_github.contributions[r * GH_COLS + c]), LV_PART_MAIN);
        }
    }
}
