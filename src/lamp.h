#pragma once
#include <Arduino.h>

struct LampState {
    bool on;
    int  brightness;  // 10–1000
    int  color_temp;  // 0–1000 (0 = warm, 1000 = cool)
    bool valid;
};

extern LampState g_lamp;

// Returns true if new state arrived since last call (main loop should redraw).
bool lamp_take_update();

// Starts the background task; call once after WiFi.begin().
void lamp_init();

// Enqueue a command; executed by the background task.
void lamp_cmd_power(bool on);
void lamp_cmd_brightness(int v);   // clamps to 10–1000
void lamp_cmd_color_temp(int v);   // clamps to 0–1000
