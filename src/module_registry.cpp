#include "module_registry.h"
#include <cstdlib>

static Module *s_mods[16];
static int     s_count  = 0;
static bool    s_sorted = false;

void ModuleRegistry::add(Module *m) {
    if (s_count < 16) s_mods[s_count++] = m;
    s_sorted = false;
}

static int cmp_mod(const void *a, const void *b) {
    return (*(const Module **)a)->order - (*(const Module **)b)->order;
}

static void ensure_sorted() {
    if (!s_sorted && s_count > 0) {
        qsort(s_mods, s_count, sizeof(Module *), cmp_mod);
        s_sorted = true;
    }
}

int     ModuleRegistry::count() { ensure_sorted(); return s_count; }
Module *ModuleRegistry::get(int i) { ensure_sorted(); return s_mods[i]; }
