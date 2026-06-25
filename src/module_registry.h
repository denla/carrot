#pragma once
#include <lvgl.h>

struct Module {
    const char      *name;
    const char      *icon;
    const lv_font_t *icon_font;  // nullptr → sf_symbols_icons_32
    lv_obj_t       **screen;
    void           (*create)();
    void           (*destroy)();  // nulls global widget ptrs and *screen; does NOT call lv_obj_del
    void           (*update)();   // nullptr = no update
    uint32_t         update_ms;   // 0 = every loop(), >0 = ms interval
    int              order;       // sort key for nav menu
    uint32_t         _last_ms;    // internal: last update timestamp
    Module          *_next;       // internal: linked list (unused, reserved)
};

namespace ModuleRegistry {
    void    add(Module *m);
    int     count();
    Module *get(int i);
}

#define REGISTER_MODULE(var)                                   \
    namespace {                                                \
        struct _ModReg_##var {                                 \
            _ModReg_##var() { ModuleRegistry::add(&var); }    \
        } _modreg_##var;                                       \
    }
