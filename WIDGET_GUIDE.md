# Как добавить виджет в CarrotOS

## 1. Структура Module

```cpp
struct Module {
    const char      *name;        // название в меню навигации
    const char      *icon;        // строка-глиф иконки
    const lv_font_t *icon_font;   // шрифт иконки; nullptr → sf_symbols_icons_32
    lv_obj_t       **screen;      // указатель на глобальный scr_xxx
    void           (*create)();   // создать экран (вызывается при первом открытии)
    void           (*destroy)();  // обнулить глобальные указатели виджетов + *screen
    void           (*update)();   // nullptr если обновление не нужно
    uint32_t         update_ms;   // 0 = каждый loop(), >0 = интервал в мс
    int              order;       // порядок в меню (1–99)
};
```

## 2. Минимальный пример

```cpp
// src/ui_mywidget.cpp
#include "ui_mywidget.h"
#include "ui_common.h"
#include "module_registry.h"

static lv_obj_t *s_lbl = nullptr;

static void on_delete(lv_event_t *) { s_lbl = nullptr; }

void create_mywidget_screen() {
    if (scr_mywidget) return;
    scr_mywidget = make_screen();
    lv_obj_add_event_cb(scr_mywidget, on_delete, LV_EVENT_DELETE, NULL);

    s_lbl = lv_label_create(scr_mywidget);
    lv_label_set_text(s_lbl, "Hello");
    lv_obj_center(s_lbl);
}

// ── Module ────────────────────────────────────────────────────────────────────

static void mod_destroy() { scr_mywidget = nullptr; }

static Module mywidget_module = {
    .name      = "My Widget",
    .icon      = LV_SYMBOL_BELL,
    .icon_font = &lv_font_montserrat_32,
    .screen    = &scr_mywidget,
    .create    = create_mywidget_screen,
    .destroy   = mod_destroy,
    .update    = nullptr,
    .update_ms = 0,
    .order     = 7,
};
REGISTER_MODULE(mywidget_module)
```

```cpp
// src/ui_mywidget.h
#pragma once
#include "globals.h"
void create_mywidget_screen();
```

```cpp
// src/globals.h — добавить:
extern lv_obj_t *scr_mywidget;
```

```cpp
// src/globals.cpp — добавить:
lv_obj_t *scr_mywidget = nullptr;
```

Больше ничего менять не нужно — меню и цикл обновлений подхватят модуль автоматически.

---

## 3. Доступные данные

### Время и дата (RTC)

```cpp
HWDateTime dt = hw_get_datetime();
dt.year    // int, 2024–
dt.month   // 1–12
dt.day     // 1–31
dt.hour    // 0–23
dt.minute  // 0–59
dt.second  // 0–59
dt.week    // 0=Sun, 1=Mon, ..., 6=Sat
```

Функция читает RTC напрямую, вызывать можно в любом месте.

---

### Погода (`g_weather`)

```cpp
extern WeatherData g_weather;
extern QueueHandle_t g_weather_queue;  // обновляется фоновой задачей

struct WeatherData {
    int     temp;           // текущая температура, °C
    int     tmin, tmax;     // мин/макс за день
    char    desc[48];       // описание на русском: "ясно", "дождь", ...
    int     ftemp[5];       // прогноз: температура на 5 дней
    uint8_t fdow[5];        // прогноз: день недели (0=Sun)
    char    fcond[5][32];   // прогноз: описание условий
    bool    valid;          // false пока данные не пришли
};
```

Иконки погоды (sf_symbols_icons_32 / sf_symbols_icons_28):
```cpp
WI_SUN          // "\xEE\x80\x85"  — ясно
WI_CLOUD_SUN    // "\xEE\x80\x86"  — переменная облачность
WI_RAIN         // "\xEE\x80\x87"  — дождь
WI_HEAVY_RAIN   // "\xEE\x80\x88"  — ливень
WI_SNOW         // "\xEE\x80\x89"  — снег
WI_THUNDER_RAIN // "\xEE\x80\x8B"  — гроза
WI_CLOUD        // "\xEE\x80\x90"  — облачно (fallback)
// определены в ui_weather.h
```

Чтобы получать обновления в `update()`:
```cpp
static void mod_update() {
    WeatherData wd;
    if (xQueueReceive(g_weather_queue, &wd, 0) == pdTRUE) {
        g_weather = wd;
        // обновить UI
    }
}
// update_ms = 0  (каждый loop)
```

---

### Музыка (`g_music`)

```cpp
extern MusicData g_music;
extern QueueHandle_t g_music_queue;

struct MusicData {
    char title[128];   // название трека
    char artist[64];   // исполнитель
    bool playing;      // true = воспроизводится
    bool valid;        // false пока не подключился клиент
};
```

Управление воспроизведением:
```cpp
extern volatile char music_pending_cmd[8];
// Записать одну из команд: "toggle", "next", "prev"
strlcpy((char *)music_pending_cmd, "toggle", sizeof(music_pending_cmd));
```

Обложка альбома (RGB565, 130×130 px):
```cpp
extern uint8_t        *g_art_buf;    // буфер в PSRAM
extern volatile bool   g_art_ready;  // true когда новая обложка готова
#define ART_W  130
#define ART_H  130
#define ART_SIZE (ART_W * ART_H * 2)
```

Чтобы отрисовать обложку:
```cpp
static lv_img_dsc_t art_dsc = {};
// в create:
art_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
art_dsc.header.w  = ART_W;
art_dsc.header.h  = ART_H;
art_dsc.data_size = ART_SIZE;

// в update:
if (g_art_ready) {
    g_art_ready  = false;
    art_dsc.data = g_art_buf;
    lv_img_set_src(img_obj, &art_dsc);
}
```

---

### GitHub (`g_github`)

```cpp
extern GitHubData g_github;
extern QueueHandle_t g_github_queue;

struct GitHubData {
    char    username[64];
    int16_t contributions[21]; // [week*7+day], week 0 = 3 недели назад, day 0 = понедельник
    int16_t total;             // сумма за 3 недели
    bool    valid;
};
```

---

## 4. Шрифты

| Переменная | Размер | Использование |
|---|---|---|
| `sf_pro_display_medium_24` | 24px | текст, подписи, даты |
| `sf_pro_display_medium_32` | 32px | заголовки, кнопки |
| `london_120` | ~120px | цифры часов |
| `sf_symbols_icons_28` | 28px | иконки в кружках |
| `sf_symbols_icons_32` | 32px | иконки в меню, по умолчанию |
| `lv_font_montserrat_32` | 32px | встроенный LVGL (стрелки, символы) |

Объявление перед использованием:
```cpp
LV_FONT_DECLARE(sf_pro_display_medium_24);
```

---

## 5. Системные иконки (PUA U+E001–U+E004, шрифт sf_symbols_icons_32/28)

```cpp
"\xEE\x80\x81"  // clock.fill      — часы
"\xEE\x80\x82"  // cloud.sun.fill  — погода
"\xEE\x80\x83"  // calendar        — календарь
"\xEE\x80\x84"  // gearshape.fill  — настройки
"\xEE\x80\x80"  // chevron.left    — назад (top bar)
```

---

## 6. UI-хелперы (ui_common.h)

```cpp
lv_obj_t *make_screen();                          // чёрный экран без паддингов
lv_obj_t *make_row(parent, y, w, h);              // прозрачный контейнер
lv_obj_t *make_separator(parent, y);              // горизонтальная линия

// Навигация (вызывать из gesture/tap обработчиков)
nav_to_nav(from);
nav_to_weather(from);
nav_to_settings(from);
nav_to_calendar(from);
nav_to_music(from);
nav_to_github(from);
```

---

## 7. Константы экрана

```cpp
#define SCREEN_W  480
#define SCREEN_H  480
// Top bar высота: 32px padding + 29px bar = 61px
// Контент начинается с y = 81 (61 + 20px gap)
```
