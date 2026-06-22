#pragma once
#include "globals.h"

// Creates a full-screen black object with padding/border/scroll cleared.
// Every new screen must be created via this helper to guarantee no padding.
lv_obj_t *make_screen();

// Horizontal separator line
lv_obj_t *make_separator(lv_obj_t *parent, int y);

// Transparent, non-scrollable row container
lv_obj_t *make_row(lv_obj_t *parent, int y, int w, int h);

// Animated screen transition (also shows/hides the shared top bar)
void nav_to(lv_obj_t *from, lv_obj_t *to, lv_scr_load_anim_t dir);

// Shared top bar (Back + time) that floats above all non-clock screens
void create_top_bar();

// Returns whichever clock screen is currently selected
inline lv_obj_t *active_clock() {
    if (clock_style == 1) return scr_clock2;
    if (clock_style == 2) return scr_clock3;
    if (clock_style == 3) return scr_clock4;
    return scr_clock;
}
