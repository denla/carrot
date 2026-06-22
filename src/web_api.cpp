#include "web_api.h"
#include "weather.h"
#include "hw.h"
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

static WebServer mgmt_server(80);

static void cors_headers() {
    mgmt_server.sendHeader("Access-Control-Allow-Origin", "*");
    mgmt_server.sendHeader("Access-Control-Allow-Methods", "GET,POST,OPTIONS");
    mgmt_server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

static void api_status() {
    cors_headers();
    char json[640];
    char owm_key_masked[16] = "\xe2\x80\x94"; // —
    if (owm_key[0]) {
        snprintf(owm_key_masked, sizeof(owm_key_masked), "%.8s\xe2\x80\xa6", owm_key);
    }
    snprintf(json, sizeof(json),
        "{\"temp\":%d,\"desc\":\"%s\",\"brightness\":%d,"
        "\"ip\":\"%s\",\"rssi\":%d,\"weather_valid\":%s,"
        "\"city\":\"%s\",\"lat\":\"%s\",\"lon\":\"%s\","
        "\"owm_key\":\"%s\",\"clock_style\":%d,\"anim_enabled\":%s}",
        g_weather.temp, g_weather.desc, brightness_pct,
        WiFi.localIP().toString().c_str(), WiFi.RSSI(),
        g_weather.valid ? "true" : "false",
        owm_city, owm_lat, owm_lon,
        owm_key_masked, clock_style,
        anim_enabled ? "true" : "false");
    mgmt_server.send(200, "application/json", json);
}

static void api_set_brightness() {
    cors_headers();
    if (mgmt_server.hasArg("value")) {
        int v = constrain(mgmt_server.arg("value").toInt(), 10, 100);
        pending_brightness = v;
        prefs.begin("carrotos", false);
        prefs.putUChar("brightness", (uint8_t)v);
        prefs.end();
        mgmt_server.send(200, "application/json", "{\"ok\":true}");
    } else {
        mgmt_server.send(400, "application/json", "{\"error\":\"missing value\"}");
    }
}

static void api_set_time() {
    cors_headers();
    if (mgmt_server.hasArg("year") && mgmt_server.hasArg("month") &&
        mgmt_server.hasArg("day")  && mgmt_server.hasArg("hour")  &&
        mgmt_server.hasArg("minute")) {
        pending_time = {
            mgmt_server.arg("year").toInt(),
            mgmt_server.arg("month").toInt(),
            mgmt_server.arg("day").toInt(),
            mgmt_server.arg("hour").toInt(),
            mgmt_server.arg("minute").toInt(),
            mgmt_server.hasArg("second") ? mgmt_server.arg("second").toInt() : 0,
            true
        };
        mgmt_server.send(200, "application/json", "{\"ok\":true}");
    } else {
        mgmt_server.send(400, "application/json", "{\"error\":\"missing fields\"}");
    }
}

static void api_set_city() {
    cors_headers();
    if (!mgmt_server.hasArg("q")) {
        mgmt_server.send(400, "application/json", "{\"error\":\"missing q\"}");
        return;
    }
    String q = mgmt_server.arg("q");
    if (geocode_city(q)) {
        char resp[256];
        snprintf(resp, sizeof(resp),
            "{\"ok\":true,\"city\":\"%s\",\"lat\":\"%s\",\"lon\":\"%s\"}",
            owm_city, owm_lat, owm_lon);
        mgmt_server.send(200, "application/json", resp);
    } else {
        mgmt_server.send(404, "application/json", "{\"error\":\"city not found\"}");
    }
}

static void api_set_clockstyle() {
    cors_headers();
    if (!mgmt_server.hasArg("style")) {
        mgmt_server.send(400, "application/json", "{\"error\":\"missing style\"}");
        return;
    }
    int s = mgmt_server.arg("style").toInt();
    if (s < 0 || s > 3) {
        mgmt_server.send(400, "application/json", "{\"error\":\"invalid style\"}");
        return;
    }
    Preferences p;
    p.begin("carrotos", false);
    p.putUChar("clockstyle", (uint8_t)s);
    p.end();
    pending_clock_style = s;
    mgmt_server.send(200, "application/json", "{\"ok\":true}");
}

static void api_set_owmkey() {
    cors_headers();
    if (!mgmt_server.hasArg("key")) {
        mgmt_server.send(400, "application/json", "{\"error\":\"key required\"}");
        return;
    }
    String key = mgmt_server.arg("key");
    key.trim();
    if (key.length() < 8 || key.length() >= sizeof(owm_key)) {
        mgmt_server.send(400, "application/json", "{\"error\":\"invalid key\"}");
        return;
    }
    key.toCharArray(owm_key, sizeof(owm_key));
    Preferences p;
    p.begin("carrotos", false);
    p.putString("owmkey", owm_key);
    p.end();
    mgmt_server.send(200, "application/json", "{\"ok\":true}");
}

// POST /api/weather — React app fetches OWM and pushes ready data here
static void api_push_weather() {
    cors_headers();
    WeatherData wd = {};
    if (mgmt_server.hasArg("temp"))  wd.temp = mgmt_server.arg("temp").toInt();
    if (mgmt_server.hasArg("tmin"))  wd.tmin = mgmt_server.arg("tmin").toInt();
    if (mgmt_server.hasArg("tmax"))  wd.tmax = mgmt_server.arg("tmax").toInt();
    if (mgmt_server.hasArg("desc"))  mgmt_server.arg("desc").toCharArray(wd.desc, sizeof(wd.desc));
    for (int i = 0; i < 5; i++) {
        char k[9];
        snprintf(k, sizeof(k), "ftemp%d", i); if (mgmt_server.hasArg(k)) wd.ftemp[i] = mgmt_server.arg(k).toInt();
        snprintf(k, sizeof(k), "fdow%d",  i); if (mgmt_server.hasArg(k)) wd.fdow[i]  = (uint8_t)mgmt_server.arg(k).toInt();
        snprintf(k, sizeof(k), "fcond%d", i); if (mgmt_server.hasArg(k)) mgmt_server.arg(k).toCharArray(wd.fcond[i], sizeof(wd.fcond[i]));
    }
    wd.valid = true;
    xQueueOverwrite(g_weather_queue, &wd);
    mgmt_server.send(200, "application/json", "{\"ok\":true}");
}

static void api_set_animations() {
    cors_headers();
    if (!mgmt_server.hasArg("enabled")) {
        mgmt_server.send(400, "application/json", "{\"error\":\"missing enabled\"}");
        return;
    }
    bool en = mgmt_server.arg("enabled").toInt() != 0;
    anim_enabled = en;
    Preferences p;
    p.begin("carrotos", false);
    p.putBool("anim", en);
    p.end();
    mgmt_server.send(200, "application/json", "{\"ok\":true}");
}

static uint8_t b64v(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return 0;
}

static size_t b64_decode(const char *src, size_t slen, uint8_t *dst, size_t dmax) {
    size_t out = 0, i = 0;
    while (out < dmax) {
        char c[4]; int n = 0;
        while (i < slen && n < 4) {
            char ch = src[i++];
            if ((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')||(ch>='0'&&ch<='9')||ch=='+'||ch=='/'||ch=='=')
                c[n++] = ch;
        }
        if (n < 4) break;
        uint32_t v = ((uint32_t)b64v(c[0])<<18)|((uint32_t)b64v(c[1])<<12)|
                     ((uint32_t)b64v(c[2])<<6)|b64v(c[3]);
        dst[out++] = v >> 16;
        if (c[2] != '=' && out < dmax) dst[out++] = (v >> 8) & 0xFF;
        if (c[3] != '=' && out < dmax) dst[out++] = v & 0xFF;
    }
    return out;
}

// POST /api/music — track info (title/artist/playing) + optional base64 art in one request
static void api_push_music() {
    cors_headers();
    MusicData md = {};
    if (mgmt_server.hasArg("title"))  mgmt_server.arg("title").toCharArray(md.title,  sizeof(md.title));
    if (mgmt_server.hasArg("artist")) mgmt_server.arg("artist").toCharArray(md.artist, sizeof(md.artist));
    md.playing = mgmt_server.hasArg("playing") && mgmt_server.arg("playing") != "0";
    md.valid = true;
    xQueueOverwrite(g_music_queue, &md);
    // Optional inline art — decoded and flagged here so loop() can update both atomically
    if (g_art_buf && mgmt_server.hasArg("art")) {
        const String &artB64 = mgmt_server.arg("art");
        if (artB64.length() > 0) {
            size_t n = b64_decode(artB64.c_str(), artB64.length(), g_art_buf, ART_SIZE);
            if (n == ART_SIZE) g_art_ready = true;
        }
    }
    mgmt_server.send(200, "application/json", "{\"ok\":true}");
}

// POST /api/music/art — raw body is base64 of RGB565 pixels (ART_W×ART_H, 2 bytes/pixel LE)
static void api_push_art() {
    cors_headers();
    if (!g_art_buf || !mgmt_server.hasArg("plain")) {
        mgmt_server.send(400, "text/plain", "err");
        return;
    }
    const String &body = mgmt_server.arg("plain");
    size_t n = b64_decode(body.c_str(), (size_t)body.length(), g_art_buf, ART_SIZE);
    if (n == ART_SIZE) g_art_ready = true;
    mgmt_server.send(200, "text/plain", "ok");
}

// GET /api/music/cmd — bridge script polls for button presses, clears after read
static void api_get_music_cmd() {
    cors_headers();
    char cmd[8];
    strlcpy(cmd, (const char *)music_pending_cmd, sizeof(cmd));
    music_pending_cmd[0] = '\0';
    mgmt_server.send(200, "text/plain", cmd);
}

static void api_restart() {
    cors_headers();
    mgmt_server.send(200, "application/json", "{\"ok\":true}");
    delay(100);
    ESP.restart();
}

void web_server_task(void *pv) {
    while (WiFi.status() != WL_CONNECTED)
        vTaskDelay(500 / portTICK_PERIOD_MS);

    MDNS.begin("carrotos");

    auto handle_options = []() { cors_headers(); mgmt_server.send(204); };
    mgmt_server.on("/api/status",     HTTP_GET,     api_status);
    mgmt_server.on("/api/status",     HTTP_OPTIONS, handle_options);
    mgmt_server.on("/api/brightness", HTTP_POST,    api_set_brightness);
    mgmt_server.on("/api/brightness", HTTP_OPTIONS, handle_options);
    mgmt_server.on("/api/time",       HTTP_POST,    api_set_time);
    mgmt_server.on("/api/time",       HTTP_OPTIONS, handle_options);
    mgmt_server.on("/api/city",       HTTP_POST,    api_set_city);
    mgmt_server.on("/api/city",       HTTP_OPTIONS, handle_options);
    mgmt_server.on("/api/owmkey",      HTTP_POST,    api_set_owmkey);
    mgmt_server.on("/api/owmkey",      HTTP_OPTIONS, handle_options);
    mgmt_server.on("/api/clockstyle",  HTTP_POST,    api_set_clockstyle);
    mgmt_server.on("/api/clockstyle",  HTTP_OPTIONS, handle_options);
    mgmt_server.on("/api/weather",     HTTP_POST,    api_push_weather);
    mgmt_server.on("/api/weather",     HTTP_OPTIONS, handle_options);
    mgmt_server.on("/api/animations",   HTTP_POST,    api_set_animations);
    mgmt_server.on("/api/animations",   HTTP_OPTIONS, handle_options);
    mgmt_server.on("/api/music",         HTTP_POST,    api_push_music);
    mgmt_server.on("/api/music",         HTTP_OPTIONS, handle_options);
    mgmt_server.on("/api/music/cmd",     HTTP_GET,     api_get_music_cmd);
    mgmt_server.on("/api/music/art",     HTTP_POST,    api_push_art);
    mgmt_server.on("/api/music/art",     HTTP_OPTIONS, handle_options);
    mgmt_server.on("/api/restart",       HTTP_POST,    api_restart);
    mgmt_server.on("/api/restart",       HTTP_OPTIONS, handle_options);
    mgmt_server.onNotFound([]() {
        cors_headers();
        mgmt_server.send(404, "application/json", "{\"error\":\"not found\"}");
    });
    mgmt_server.begin();
    USBSerial.printf("Web API: http://%s  or  http://carrotos.local\n",
                     WiFi.localIP().toString().c_str());

    for (;;) {
        mgmt_server.handleClient();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
