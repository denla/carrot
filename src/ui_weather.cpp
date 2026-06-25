#include "ui_weather.h"
#include "ui_common.h"
#include "hw.h"
#include "module_registry.h"
#include <string.h>

LV_FONT_DECLARE(london_120);
LV_FONT_DECLARE(sf_pro_display_medium_24);
LV_FONT_DECLARE(sf_symbols_icons_32);

#define COLOR_GRAY lv_color_hex(0x7A7A7A)

static lv_obj_t *lbl_w_icon  = nullptr;
static lv_obj_t *lbl_w_hilow = nullptr;

static void on_delete(lv_event_t *) {
    lbl_w_icon = lbl_w_hilow = nullptr;
}

// ── Подбор иконки по русскому описанию OWM ────────────────────────────────
// Порядок важен: специфичные условия проверяются первыми.
// Fallback — cloud.fill (E002), не крашится ни при каком вводе.

static const char *icon_for_desc(const char *desc) {
    if (!desc || !desc[0]) return WI_CLOUD;

    if (strstr(desc, "гроза"))                    return WI_THUNDER_RAIN;

    if (strstr(desc, "ливень")          ||
        strstr(desc, "сильный дождь")   ||
        strstr(desc, "очень сильный")   ||
        strstr(desc, "проливн"))                   return WI_HEAVY_RAIN;

    if (strstr(desc, "дождь")           ||
        strstr(desc, "морось"))                    return WI_RAIN;

    if (strstr(desc, "метель")          ||
        strstr(desc, "снегопад")        ||
        strstr(desc, "снежн")           ||
        strstr(desc, "снег"))                      return WI_SNOW;

    if (strstr(desc, "ясно"))                      return WI_SUN;

    if (strstr(desc, "небольшая облачность") ||
        strstr(desc, "переменная")      ||
        strstr(desc, "прояснени"))                 return WI_CLOUD_SUN;

    return WI_CLOUD;  // cloud.fill — пасмурно, туман, всё неизвестное
}

// ── Прозрачный контейнер ──────────────────────────────────────────────────

static lv_obj_t *make_box(lv_obj_t *parent, int x, int y, int w, int h) {
    lv_obj_t *box = lv_obj_create(parent);
    lv_obj_set_size(box, w, h);
    lv_obj_set_pos(box, x, y);
    lv_obj_set_style_bg_opa(box, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(box, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(box, 0, LV_PART_MAIN);
    lv_obj_clear_flag(box, LV_OBJ_FLAG_SCROLLABLE);
    return box;
}

// ── Жест свайп вправо → назад ─────────────────────────────────────────────

static void on_weather_gesture(lv_event_t *) {
    if (lv_scr_act() != scr_weather) return;
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    if (dir == LV_DIR_RIGHT) nav_to_nav(scr_weather, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
}

// ── Создание экрана ────────────────────────────────────────────────────────
//
// Shared top_bar (h=61px) покрывает верх → контент начинается с y=93.
//
// y=93   h=164  — текущая погода: большая температура | иконка + Tmax°/Tmin°
// y=289  h=159  — 5 колонок прогноза (space-between): день / иконка / темп

void create_weather_screen() {
    if (scr_weather) return;
    scr_weather = make_screen();
    lv_obj_add_event_cb(scr_weather, on_delete,         LV_EVENT_DELETE,  NULL);
    lv_obj_add_event_cb(scr_weather, on_weather_gesture, LV_EVENT_GESTURE, NULL);

    // ── Текущая погода (y=93, h=164) ─────────────────────────────────────
    // Большая температура (слева, до ~325px)
    lbl_w_temp = lv_label_create(scr_weather);
    lv_obj_set_style_text_font(lbl_w_temp, &london_120, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_w_temp, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text(lbl_w_temp, "--");
    lv_obj_set_pos(lbl_w_temp, 32, 93);

    // Правая колонка (x=357, y=93, w=91, h=85): иконка сверху, Tmax/Tmin снизу
    lv_obj_t *right_col = make_box(scr_weather, 357, 93, 91, 85);
    lv_obj_set_flex_flow(right_col, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(right_col, LV_FLEX_ALIGN_SPACE_BETWEEN,
                          LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lbl_w_icon = lv_label_create(right_col);
    lv_obj_set_style_text_font(lbl_w_icon, &sf_symbols_icons_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_w_icon, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text(lbl_w_icon, WI_CLOUD);

    // Tmax (белый) + " / Tmin" (серый) через recolor
    lbl_w_hilow = lv_label_create(right_col);
    lv_label_set_recolor(lbl_w_hilow, true);
    lv_obj_set_style_text_font(lbl_w_hilow, &sf_pro_display_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_w_hilow, COLOR_GRAY, LV_PART_MAIN);  // base = gray
    lv_obj_set_style_text_align(lbl_w_hilow, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_long_mode(lbl_w_hilow, LV_LABEL_LONG_CLIP);
    lv_obj_set_width(lbl_w_hilow, 91);
    lv_label_set_text(lbl_w_hilow, "#FFFFFF --\xc2\xb0# / --\xc2\xb0");

    // ── Прогноз (y=289, h=159) ───────────────────────────────────────────
    // 5 колонок, space-between; каждая: день (серый) / иконка / температура

    lv_obj_t *fc = make_box(scr_weather, 32, 289, 416, 159);
    lv_obj_set_flex_flow(fc, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(fc, LV_FLEX_ALIGN_SPACE_BETWEEN,
                          LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    for (int i = 0; i < 5; i++) {
        lv_obj_t *col = make_box(fc, 0, 0, 62, 159);
        lv_obj_set_flex_flow(col, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_align(col, LV_FLEX_ALIGN_SPACE_BETWEEN,
                              LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        lbl_w_fday[i] = lv_label_create(col);
        lv_obj_set_style_text_font(lbl_w_fday[i], &sf_pro_display_medium_24, LV_PART_MAIN);
        lv_obj_set_style_text_color(lbl_w_fday[i], COLOR_GRAY, LV_PART_MAIN);
        lv_obj_set_style_text_align(lbl_w_fday[i], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
        lv_label_set_text(lbl_w_fday[i], "--");

        lbl_w_fcond[i] = lv_label_create(col);
        lv_obj_set_style_text_font(lbl_w_fcond[i], &sf_symbols_icons_32, LV_PART_MAIN);
        lv_obj_set_style_text_color(lbl_w_fcond[i], lv_color_white(), LV_PART_MAIN);
        lv_label_set_text(lbl_w_fcond[i], WI_CLOUD);

        lbl_w_ftemp[i] = lv_label_create(col);
        lv_obj_set_style_text_font(lbl_w_ftemp[i], &sf_pro_display_medium_24, LV_PART_MAIN);
        lv_obj_set_style_text_color(lbl_w_ftemp[i], lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_text_align(lbl_w_ftemp[i], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
        lv_label_set_text(lbl_w_ftemp[i], "--\xc2\xb0");
    }
}

// ── Обновление данных ──────────────────────────────────────────────────────

static void mod_create() {
    create_weather_screen();
    update_weather_screen();
}

static void mod_destroy() {
    lbl_w_city = lbl_w_temp = lbl_w_time = nullptr;
    for (int i = 0; i < 5; i++) lbl_w_fday[i] = lbl_w_fcond[i] = lbl_w_ftemp[i] = nullptr;
    scr_weather = nullptr;
}

static void mod_update() {
    WeatherData wd;
    if (xQueueReceive(g_weather_queue, &wd, 0) == pdTRUE) {
        g_weather = wd;
        update_weather_screen();
    }
}

static Module weather_module = {
    .name       = "Weather",
    .icon       = "\xEE\x80\x82",
    .icon_font  = nullptr,
    .screen     = &scr_weather,
    .create     = mod_create,
    .destroy    = mod_destroy,
    .update     = mod_update,
    .update_ms  = 0,
    .order      = 1,
};
REGISTER_MODULE(weather_module)

void update_weather_screen() {
    if (!scr_weather) return;
    if (!g_weather.valid) return;

    if (lbl_w_icon)  lv_label_set_text(lbl_w_icon, icon_for_desc(g_weather.desc));

    char tmp[20];
    snprintf(tmp, sizeof(tmp), "%d", g_weather.temp);
    if (lbl_w_temp) lv_label_set_text(lbl_w_temp, tmp);

    // "#FFFFFF 24°# / 14°" → tmax белый, " / tmin" серые (base color = gray)
    snprintf(tmp, sizeof(tmp), "#FFFFFF %d\xc2\xb0# / %d\xc2\xb0", g_weather.tmax, g_weather.tmin);
    if (lbl_w_hilow) lv_label_set_text(lbl_w_hilow, tmp);

    // Однобуквенные аббревиатуры дней (как в макете)
    static const char *dow_letter[7] = {"S", "M", "T", "W", "T", "F", "S"};

    for (int i = 0; i < 5; i++) {
        if (lbl_w_fday[i])
            lv_label_set_text(lbl_w_fday[i], dow_letter[g_weather.fdow[i] % 7]);
        if (lbl_w_fcond[i])
            lv_label_set_text(lbl_w_fcond[i], icon_for_desc(g_weather.fcond[i]));
        if (lbl_w_ftemp[i]) {
            snprintf(tmp, sizeof(tmp), "%d\xc2\xb0", g_weather.ftemp[i]);
            lv_label_set_text(lbl_w_ftemp[i], tmp);
        }
    }
}
