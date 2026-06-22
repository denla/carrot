#include "ui_music.h"
#include "ui_common.h"
#include "hw.h"

LV_FONT_DECLARE(sf_pro_display_medium_24);
LV_FONT_DECLARE(sf_pro_display_medium_32);

#define COLOR_RED  lv_color_hex(0xFF1313)
#define COLOR_GRAY lv_color_hex(0x7A7A7A)
#define COLOR_DARK lv_color_hex(0x242424)

// Layout (480×480, top bar 61px):
//   gap 32 → ART_Y=93 : album art 130×130
//   +14px gap          : track title (32pt, ~40px)
//   +40px              : artist (24pt, ~30px)
//   gap 32 → BTN_Y=339 : control buttons
#define LEFT_M  32
#define ART_Y   93
#define BTN_D   80
#define BTN_Y   339
#define BTN_CX0 (LEFT_M + BTN_D / 2)
#define BTN_CX1 (BTN_CX0 + 96)
#define BTN_CX2 (BTN_CX1 + 96)
#define ART_RADIUS 16

static lv_obj_t   *lbl_music_artist    = nullptr;
static lv_obj_t   *lbl_music_title     = nullptr;
static lv_obj_t   *lbl_music_playpause = nullptr;
static lv_obj_t   *btn_playpause_bg    = nullptr;
static lv_obj_t   *img_art             = nullptr;
static lv_img_dsc_t art_dsc            = {};

static void set_cmd(const char *cmd) {
    strlcpy((char *)music_pending_cmd, cmd, sizeof(music_pending_cmd));
}

static void on_prev   (lv_event_t *) { set_cmd("prev");   }
static void on_toggle (lv_event_t *) { set_cmd("toggle"); }
static void on_next   (lv_event_t *) { set_cmd("next");   }

static void on_music_gesture(lv_event_t *) {
    if (lv_scr_act() != scr_music) return;
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    if (dir == LV_DIR_RIGHT) nav_to_nav(scr_music, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
}

// Creates a circular button: symbol at center, event cb on click
static lv_obj_t *make_btn(lv_obj_t *parent, int cx, int cy,
                           const char *symbol, lv_color_t bg,
                           lv_event_cb_t cb, lv_obj_t **out_lbl) {
    lv_obj_t *circle = lv_obj_create(parent);
    lv_obj_set_size(circle, BTN_D, BTN_D);
    lv_obj_set_pos(circle, cx - BTN_D/2, cy - BTN_D/2);
    lv_obj_set_style_radius(circle, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_style_bg_color(circle, bg, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(circle, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(circle, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(circle, 0, LV_PART_MAIN);
    lv_obj_clear_flag(circle, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(circle, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(circle, cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(circle, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *lbl = lv_label_create(circle);
    lv_obj_set_style_text_font(lbl, &lv_font_montserrat_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text(lbl, symbol);
    lv_obj_align(lbl, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(lbl, LV_OBJ_FLAG_EVENT_BUBBLE);  // clicks pass through to circle

    if (out_lbl) *out_lbl = lbl;
    return circle;
}

void create_music_screen() {
    if (scr_music) return;
    scr_music = make_screen();
    lv_obj_add_event_cb(scr_music, on_music_gesture, LV_EVENT_GESTURE, NULL);

    // ── Album art (top, hidden until art arrives) ──────────────────────────────
    img_art = lv_img_create(scr_music);
    memset(&art_dsc, 0, sizeof(art_dsc));
    art_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
    art_dsc.header.w  = ART_W;
    art_dsc.header.h  = ART_H;
    art_dsc.data_size = ART_SIZE;
    art_dsc.data      = nullptr;
    lv_obj_set_size(img_art, ART_W, ART_H);
    lv_obj_align(img_art, LV_ALIGN_TOP_LEFT, LEFT_M, ART_Y);
    lv_obj_set_style_radius(img_art, ART_RADIUS, LV_PART_MAIN);
    lv_obj_set_style_clip_corner(img_art, true, LV_PART_MAIN);
    lv_obj_set_style_pad_all(img_art, 0, LV_PART_MAIN);
    lv_obj_clear_flag(img_art, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(img_art, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(img_art, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(img_art, LV_OBJ_FLAG_HIDDEN);

    // ── Track title (below art, white, 32pt, scrolling) ───────────────────────
    lbl_music_title = lv_label_create(scr_music);
    lv_obj_set_style_text_font(lbl_music_title, &sf_pro_display_medium_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_music_title, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_align(lbl_music_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_width(lbl_music_title, 480 - LEFT_M * 2);
    lv_obj_align(lbl_music_title, LV_ALIGN_TOP_LEFT, LEFT_M, ART_Y + ART_H + 14);
    lv_label_set_long_mode(lbl_music_title, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(lbl_music_title, "нет данных");

    // ── Artist (below title, gray, 24pt) ──────────────────────────────────────
    lbl_music_artist = lv_label_create(scr_music);
    lv_obj_set_style_text_font(lbl_music_artist, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_music_artist, COLOR_GRAY, LV_PART_MAIN);
    lv_obj_set_style_text_align(lbl_music_artist, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_width(lbl_music_artist, 480 - LEFT_M * 2);
    lv_obj_align(lbl_music_artist, LV_ALIGN_TOP_LEFT, LEFT_M, ART_Y + ART_H + 54);
    lv_label_set_long_mode(lbl_music_artist, LV_LABEL_LONG_DOT);
    lv_label_set_text(lbl_music_artist, "—");

    // ── Control buttons ───────────────────────────────────────────────────────
    int btn_cy = BTN_Y + BTN_D / 2;
    make_btn(scr_music, BTN_CX0, btn_cy, LV_SYMBOL_PREV,  COLOR_DARK, on_prev,   nullptr);
    btn_playpause_bg = make_btn(scr_music, BTN_CX1, btn_cy, LV_SYMBOL_PLAY, COLOR_DARK, on_toggle, &lbl_music_playpause);
    make_btn(scr_music, BTN_CX2, btn_cy, LV_SYMBOL_NEXT,  COLOR_DARK, on_next,   nullptr);
}

void update_music_screen() {
    if (!scr_music) return;
    if (!g_music.valid) return;

    if (lbl_music_artist)
        lv_label_set_text(lbl_music_artist, g_music.artist[0] ? g_music.artist : "—");

    if (lbl_music_title)
        lv_label_set_text(lbl_music_title,
                          g_music.title[0] ? g_music.title : "нет данных");

    if (lbl_music_playpause)
        lv_label_set_text(lbl_music_playpause,
                          g_music.playing ? LV_SYMBOL_PAUSE : LV_SYMBOL_PLAY);

    if (btn_playpause_bg)
        lv_obj_set_style_bg_color(btn_playpause_bg,
                                  g_music.playing ? COLOR_RED : COLOR_DARK,
                                  LV_PART_MAIN);
}

void update_music_art() {
    if (!scr_music) return;
    if (!img_art || !g_art_buf) return;
    art_dsc.data = (const uint8_t *)g_art_buf;
    lv_img_set_src(img_art, &art_dsc);
    lv_obj_clear_flag(img_art, LV_OBJ_FLAG_HIDDEN);
    lv_obj_invalidate(img_art);
}
