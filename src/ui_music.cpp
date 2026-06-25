#include "ui_music.h"
#include "ui_common.h"
#include "hw.h"

LV_FONT_DECLARE(sf_pro_display_medium_24);
LV_FONT_DECLARE(sf_pro_display_medium_32);

#define COLOR_GRAY  lv_color_hex(0x7A7A7A)
#define COLOR_DARK  lv_color_hex(0x242424)

#define LEFT_M   32
#define ART_Y    93                          // 32 pad + 29 topbar + 32 gap
#define ART_CX   (LEFT_M + (416 - ART_W) / 2)

// Track info row starts 32px below bottom of album art
#define INFO_Y   (ART_Y + ART_H + 32)       // 93 + 130 + 32 = 255

// Controls start 91px below info row (71px title+artist + 20px gap)
#define CTRL_Y   (INFO_Y + 71 + 20)         // 346
#define BTN_H    90
#define BTN_RAD  32
#define BTN_GAP  8

static lv_obj_t *lbl_music_title     = nullptr;
static lv_obj_t *lbl_music_artist    = nullptr;
static lv_obj_t *lbl_music_playpause = nullptr;
static lv_obj_t *btn_playpause_bg    = nullptr;
static lv_obj_t *img_art             = nullptr;
static lv_img_dsc_t art_dsc          = {};

static void set_cmd(const char *cmd) {
    strlcpy((char *)music_pending_cmd, cmd, sizeof(music_pending_cmd));
}

static void on_prev  (lv_event_t *) { set_cmd("prev");   }
static void on_toggle(lv_event_t *) { set_cmd("toggle"); }
static void on_next  (lv_event_t *) { set_cmd("next");   }

static void on_gesture(lv_event_t *) {
    if (lv_scr_act() != scr_music) return;
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    if (dir == LV_DIR_RIGHT) nav_to_nav(scr_music, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
}

// Rounded rectangle button inside a flex-grow container
static lv_obj_t *make_btn(lv_obj_t *row, const char *sym, lv_color_t bg,
                           lv_color_t fg, lv_event_cb_t cb, lv_obj_t **out_lbl) {
    lv_obj_t *btn = lv_obj_create(row);
    lv_obj_set_height(btn, BTN_H);
    lv_obj_set_flex_grow(btn, 1);
    lv_obj_set_style_bg_color(btn, bg, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(btn, BTN_RAD, LV_PART_MAIN);
    lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(btn, 0, LV_PART_MAIN);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_opa(btn, LV_OPA_70, LV_STATE_PRESSED | LV_PART_MAIN);

    lv_obj_t *lbl = lv_label_create(btn);
    lv_obj_set_style_text_font(lbl, &lv_font_montserrat_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl, fg, LV_PART_MAIN);
    lv_label_set_text(lbl, sym);
    lv_obj_align(lbl, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(lbl, LV_OBJ_FLAG_EVENT_BUBBLE);

    if (out_lbl) *out_lbl = lbl;
    return btn;
}

void create_music_screen() {
    if (scr_music) return;
    scr_music = make_screen();
    lv_obj_add_event_cb(scr_music, on_gesture, LV_EVENT_GESTURE, NULL);

    // ── Album art ─────────────────────────────────────────────────────────────
    // Dark placeholder — always visible, art renders on top once loaded
    lv_obj_t *art_bg = lv_obj_create(scr_music);
    lv_obj_set_size(art_bg, ART_W, ART_H);
    lv_obj_set_pos(art_bg, ART_CX, ART_Y);
    lv_obj_set_style_bg_color(art_bg, COLOR_DARK, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(art_bg, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(art_bg, BTN_RAD, LV_PART_MAIN);
    lv_obj_set_style_border_width(art_bg, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(art_bg, 0, LV_PART_MAIN);
    lv_obj_clear_flag(art_bg, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);

    img_art = lv_img_create(scr_music);
    memset(&art_dsc, 0, sizeof(art_dsc));
    art_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
    art_dsc.header.w  = ART_W;
    art_dsc.header.h  = ART_H;
    art_dsc.data_size = ART_SIZE;
    art_dsc.data      = nullptr;
    lv_obj_set_size(img_art, ART_W, ART_H);
    lv_obj_set_pos(img_art, ART_CX, ART_Y);
    lv_obj_set_style_radius(img_art, BTN_RAD, LV_PART_MAIN);
    lv_obj_set_style_clip_corner(img_art, true, LV_PART_MAIN);
    lv_obj_set_style_pad_all(img_art, 0, LV_PART_MAIN);
    lv_obj_clear_flag(img_art, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(img_art, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_HIDDEN);

    // ── Track title ───────────────────────────────────────────────────────────
    lbl_music_title = lv_label_create(scr_music);
    lv_obj_set_style_text_font(lbl_music_title, &sf_pro_display_medium_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_music_title, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_size(lbl_music_title, 416, LV_SIZE_CONTENT);
    lv_obj_set_pos(lbl_music_title, LEFT_M, INFO_Y);
    lv_label_set_long_mode(lbl_music_title, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(lbl_music_title, "нет данных");

    // ── Artist (4px gap below title) ──────────────────────────────────────────
    lbl_music_artist = lv_label_create(scr_music);
    lv_obj_set_style_text_font(lbl_music_artist, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_music_artist, COLOR_GRAY, LV_PART_MAIN);
    lv_obj_set_size(lbl_music_artist, 416, LV_SIZE_CONTENT);
    lv_obj_set_pos(lbl_music_artist, LEFT_M, INFO_Y + 38 + 4);
    lv_label_set_long_mode(lbl_music_artist, LV_LABEL_LONG_DOT);
    lv_label_set_text(lbl_music_artist, "—");

    // ── Control buttons (flex row) ────────────────────────────────────────────
    lv_obj_t *ctrl = lv_obj_create(scr_music);
    lv_obj_set_size(ctrl, 416, BTN_H);
    lv_obj_set_pos(ctrl, LEFT_M, CTRL_Y);
    lv_obj_set_style_bg_opa(ctrl, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(ctrl, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(ctrl, 0, LV_PART_MAIN);
    lv_obj_clear_flag(ctrl, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_flow(ctrl, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_column(ctrl, BTN_GAP, LV_PART_MAIN);

    // [Prev]  [Play/Pause — white when paused]  [Next]
    make_btn(ctrl, LV_SYMBOL_PREV, COLOR_DARK, lv_color_white(), on_prev,   nullptr);
    btn_playpause_bg = make_btn(ctrl, LV_SYMBOL_PLAY, lv_color_white(), lv_color_black(), on_toggle, &lbl_music_playpause);
    make_btn(ctrl, LV_SYMBOL_NEXT, COLOR_DARK, lv_color_white(), on_next,   nullptr);

    // Restore art if already loaded (screen was destroyed and recreated)
    if (g_art_buf) update_music_art();
}

void update_music_screen() {
    if (!scr_music || !g_music.valid) return;

    if (lbl_music_title)
        lv_label_set_text(lbl_music_title, g_music.title[0] ? g_music.title : "нет данных");
    if (lbl_music_artist)
        lv_label_set_text(lbl_music_artist, g_music.artist[0] ? g_music.artist : "—");

    bool playing = g_music.playing;

    // Paused  → white button, black icon (play)
    // Playing → dark button,  white icon (pause)  — same as Prev/Next
    if (btn_playpause_bg)
        lv_obj_set_style_bg_color(btn_playpause_bg,
                                  playing ? COLOR_DARK : lv_color_white(), LV_PART_MAIN);
    if (lbl_music_playpause) {
        lv_label_set_text(lbl_music_playpause, playing ? LV_SYMBOL_PAUSE : LV_SYMBOL_PLAY);
        lv_obj_set_style_text_color(lbl_music_playpause,
                                    playing ? lv_color_white() : lv_color_black(), LV_PART_MAIN);
    }
}

void update_music_art() {
    if (!scr_music || !img_art || !g_art_buf) return;
    art_dsc.data = (const uint8_t *)g_art_buf;
    lv_img_set_src(img_art, &art_dsc);
    lv_obj_clear_flag(img_art, LV_OBJ_FLAG_HIDDEN);
    lv_obj_invalidate(img_art);
}
