#pragma once
#include "globals.h"

// Weather icon codepoints in sf_symbols_icons font (U+E005–U+E00F)
#define WI_SUN             "\xEE\x80\x85"   // U+E005 sun.max.fill
#define WI_CLOUD_SUN       "\xEE\x80\x86"   // U+E006 cloud.sun.fill
#define WI_RAIN            "\xEE\x80\x87"   // U+E007 cloud.rain.fill
#define WI_HEAVY_RAIN      "\xEE\x80\x88"   // U+E008 cloud.heavyrain.fill
#define WI_SNOW            "\xEE\x80\x89"   // U+E009 cloud.snow.fill
#define WI_SNOWFLAKE       "\xEE\x80\x8A"   // U+E00A snowflake
#define WI_THUNDER_RAIN    "\xEE\x80\x8B"   // U+E00B cloud.bolt.rain.fill
#define WI_CLOUD_SUN_BOLT  "\xEE\x80\x8C"   // U+E00C cloud.sun.bolt.fill
#define WI_CLOUD_SUN_RAIN  "\xEE\x80\x8D"   // U+E00D cloud.sun.rain.fill
#define WI_CLOUD_SUN_RAIN2 "\xEE\x80\x8E"   // U+E00E cloud.sun.rain.fill (variant)
#define WI_MOON_RAIN       "\xEE\x80\x8F"   // U+E00F cloud.moon.rain.fill
#define WI_CLOUD           "\xEE\x80\x90"   // U+E010 cloud.fill (same-size fallback)

void create_weather_screen();
void update_weather_screen();
