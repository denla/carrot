#pragma once
#include "globals.h"
#include "SensorPCF85063.hpp"

struct HWDateTime {
    int year, month, day, hour, minute, second, week;
};

void hw_init_i2c();
void hw_init_rtc();
void hw_init_touch();
void hw_init_display();
void hw_init_lvgl();

void       set_brightness(uint8_t pct);
void       set_backlight(bool on);
void       hw_display_restart();
void       hw_display_check_sync(); // call from loop() — restarts panel if vsync stalled
inline uint32_t hw_vsync_count() { extern volatile uint32_t s_vsync_count; return s_vsync_count; }
uint8_t    read_ch32_input();
HWDateTime hw_get_datetime();
void       hw_set_datetime(int y, int m, int d, int h, int mi, int s);
