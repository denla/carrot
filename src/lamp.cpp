#include "lamp.h"
#include "config.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <mbedtls/md.h>
#include <Arduino_JSON.h>
#include <time.h>
#include "globals.h"

LampState g_lamp = {false, 500, 500, false};
static volatile bool s_updated = false;

// ── Pending command ───────────────────────────────────────────────────────────

enum CmdType { CMD_NONE, CMD_POWER, CMD_BRIGHT, CMD_TEMP };
static volatile CmdType s_cmd = CMD_NONE;
static volatile int     s_val = 0;

void lamp_cmd_power(bool on)    { s_val = on ? 1 : 0; s_cmd = CMD_POWER;  }
void lamp_cmd_brightness(int v) { s_val = constrain(v, 10, 1000); s_cmd = CMD_BRIGHT; }
void lamp_cmd_color_temp(int v) { s_val = constrain(v, 0, 1000);  s_cmd = CMD_TEMP;   }

bool lamp_take_update() {
    if (!s_updated) return false;
    s_updated = false;
    return true;
}

// ── Timestamp ─────────────────────────────────────────────────────────────────

static String tuya_ts() {
    time_t now = time(nullptr);
    return String((unsigned long long)now * 1000ULL);
}

// ── Crypto helpers ────────────────────────────────────────────────────────────

static String sha256hex(const String &s) {
    uint8_t h[32];
    mbedtls_md_context_t ctx;
    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(MBEDTLS_MD_SHA256), 0);
    mbedtls_md_starts(&ctx);
    mbedtls_md_update(&ctx, (const uint8_t *)s.c_str(), s.length());
    mbedtls_md_finish(&ctx, h);
    mbedtls_md_free(&ctx);
    char hex[65]; for (int i = 0; i < 32; i++) sprintf(hex + i*2, "%02x", h[i]);
    return String(hex);
}

static String hmacSHA256hex(const String &key, const String &data) {
    uint8_t h[32];
    mbedtls_md_context_t ctx;
    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(MBEDTLS_MD_SHA256), 1);
    mbedtls_md_hmac_starts(&ctx, (const uint8_t *)key.c_str(), key.length());
    mbedtls_md_hmac_update(&ctx, (const uint8_t *)data.c_str(), data.length());
    mbedtls_md_hmac_finish(&ctx, h);
    mbedtls_md_free(&ctx);
    char hex[65]; for (int i = 0; i < 32; i++) sprintf(hex + i*2, "%02X", h[i]);
    return String(hex);
}

// ── Token ─────────────────────────────────────────────────────────────────────

static String   s_token;
static uint32_t s_token_ts = 0;

static bool tuya_get_token() {
    const char *path = "/v1.0/token?grant_type=1";
    String t = tuya_ts();
    String str_to_sign = "GET\n" + sha256hex("") + "\n\n" + path;
    String msg = String(TUYA_ACCESS_ID) + t + str_to_sign;
    String sig = hmacSHA256hex(TUYA_ACCESS_SECRET, msg);

    WiFiClientSecure cli; cli.setInsecure();
    HTTPClient http; http.begin(cli, String(TUYA_API_HOST) + path);
    http.addHeader("client_id",   TUYA_ACCESS_ID);
    http.addHeader("sign",        sig);
    http.addHeader("t",           t);
    http.addHeader("sign_method", "HMAC-SHA256");
    int code = http.GET();
    String body = (code > 0) ? http.getString() : "";
    http.end();
    USBSerial.printf("[lamp] token HTTP %d  body=%s\n", code, body.c_str());
    if (code != 200) return false;
    JSONVar j = JSON.parse(body);
    if (JSON.typeof(j["result"]["access_token"]) != String("undefined")) {
        s_token    = (const char *)j["result"]["access_token"];
        s_token_ts = millis();
        USBSerial.println("[lamp] token OK");
        return true;
    }
    return false;
}

static bool ensure_token() {
    if (s_token.length() > 0 && (millis() - s_token_ts) < 7000000UL) return true;
    return tuya_get_token();
}

// ── Generic API calls ─────────────────────────────────────────────────────────

static String tuya_post(const String &path, const String &body) {
    if (!ensure_token()) return "";
    String t   = tuya_ts();
    String str_to_sign = "POST\n" + sha256hex(body) + "\n\n" + path;
    String msg = String(TUYA_ACCESS_ID) + s_token + t + str_to_sign;
    String sig = hmacSHA256hex(TUYA_ACCESS_SECRET, msg);

    WiFiClientSecure cli; cli.setInsecure();
    HTTPClient http; http.begin(cli, String(TUYA_API_HOST) + path);
    http.addHeader("client_id",    TUYA_ACCESS_ID);
    http.addHeader("access_token", s_token);
    http.addHeader("sign",         sig);
    http.addHeader("t",            t);
    http.addHeader("sign_method",  "HMAC-SHA256");
    http.addHeader("Content-Type", "application/json");
    int code = http.POST(body);
    String resp = (code > 0) ? http.getString() : "";
    http.end();
    return resp;
}

static String tuya_get(const String &path) {
    if (!ensure_token()) return "";
    String t   = tuya_ts();
    String str_to_sign = "GET\n" + sha256hex("") + "\n\n" + path;
    String msg = String(TUYA_ACCESS_ID) + s_token + t + str_to_sign;
    String sig = hmacSHA256hex(TUYA_ACCESS_SECRET, msg);

    WiFiClientSecure cli; cli.setInsecure();
    HTTPClient http; http.begin(cli, String(TUYA_API_HOST) + path);
    http.addHeader("client_id",    TUYA_ACCESS_ID);
    http.addHeader("access_token", s_token);
    http.addHeader("sign",         sig);
    http.addHeader("t",            t);
    http.addHeader("sign_method",  "HMAC-SHA256");
    int code = http.GET();
    String resp = (code > 0) ? http.getString() : "";
    http.end();
    return resp;
}

// ── Status fetch ──────────────────────────────────────────────────────────────

static void fetch_status() {
    String path = "/v1.0/iot-03/devices/" + String(TUYA_DEVICE_ID) + "/status";
    String resp = tuya_get(path);
    USBSerial.printf("[lamp] status resp=%s\n", resp.length() ? resp.c_str() : "(empty)");
    if (!resp.length()) return;
    JSONVar j = JSON.parse(resp);
    if (!j["success"]) return;
    JSONVar arr = j["result"];
    for (int i = 0; i < arr.length(); i++) {
        String code = (const char *)arr[i]["code"];
        if      (code == "switch_led")       g_lamp.on         = (bool)arr[i]["value"];
        else if (code == "bright_value_v2")  g_lamp.brightness = (int) arr[i]["value"];
        else if (code == "temp_value_v2")    g_lamp.color_temp = (int) arr[i]["value"];
    }
    USBSerial.printf("[lamp] on=%d bright=%d temp=%d\n", g_lamp.on, g_lamp.brightness, g_lamp.color_temp);
    g_lamp.valid = true;
    s_updated    = true;
}

// ── Send command ──────────────────────────────────────────────────────────────

static void send_cmd(const String &code, const String &val_json) {
    String path = "/v1.0/iot-03/devices/" + String(TUYA_DEVICE_ID) + "/commands";
    String body = "{\"commands\":[{\"code\":\"" + code + "\",\"value\":" + val_json + "}]}";
    String resp = tuya_post(path, body);
    USBSerial.printf("[lamp] cmd %s=%s  resp=%s\n", code.c_str(), val_json.c_str(), resp.c_str());
}

// ── Background task ───────────────────────────────────────────────────────────

static void lamp_task(void *) {
    // Wait for WiFi before any API call
    while (WiFi.status() != WL_CONNECTED) vTaskDelay(pdMS_TO_TICKS(1000));
    USBSerial.println("[lamp] WiFi up, syncing NTP...");

    // Tuya API requires real Unix timestamp; sync via NTP
    configTime(0, 0, "pool.ntp.org", "time.google.com");
    time_t now;
    while ((now = time(nullptr)) < 1700000000L) vTaskDelay(pdMS_TO_TICKS(500));
    USBSerial.printf("[lamp] NTP ok, t=%lld\n", (long long)now);

    fetch_status();

    uint32_t last_poll = millis();

    while (true) {
        // Execute pending command
        CmdType cmd = s_cmd;
        int     val = s_val;
        s_cmd = CMD_NONE;

        if (cmd == CMD_POWER) {
            send_cmd("switch_led", val ? "true" : "false");
            s_updated = true;
        } else if (cmd == CMD_BRIGHT) {
            send_cmd("bright_value_v2", String(val));
            s_updated = true;
        } else if (cmd == CMD_TEMP) {
            send_cmd("temp_value_v2", String(val));
            s_updated = true;
        }

        if (millis() - last_poll > 15000) {
            last_poll = millis();
            fetch_status();
        }

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

// ── Public ────────────────────────────────────────────────────────────────────

void lamp_init() {
    xTaskCreatePinnedToCore(lamp_task, "lamp", 16384, NULL, 1, NULL, 1);
}
