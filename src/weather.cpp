#include "weather.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

static String url_encode(const String& s) {
    String r = "";
    for (int i = 0; i < (int)s.length(); i++) {
        uint8_t c = (uint8_t)s[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') || c == '-' || c == '_' || c == '.' || c == '~') {
            r += (char)c;
        } else {
            char buf[4];
            snprintf(buf, sizeof(buf), "%%%02X", c);
            r += buf;
        }
    }
    return r;
}

bool geocode_city(const String& q) {
    if (WiFi.status() != WL_CONNECTED) return false;
    if (!owm_key[0]) { USBSerial.println("geocode: no api key"); return false; }

    WiFiClientSecure geo_client;
    geo_client.setInsecure();
    HTTPClient http;
    http.setTimeout(10000);
    String url = String("https://api.openweathermap.org/geo/1.0/direct?q=") +
                 url_encode(q) + "&limit=1&appid=" + owm_key;
    http.begin(geo_client, url);
    int code = http.GET();
    USBSerial.printf("Geocode HTTP %d (%s) for: %s\n",
                     code, http.errorToString(code).c_str(), q.c_str());
    if (code != 200) { http.end(); return false; }
    String body = http.getString();
    http.end();

    if (body.length() < 5 || body[1] == ']') {
        USBSerial.println("geocode: empty result");
        return false;
    }

    int rp = body.indexOf("\"ru\":\"");
    if (rp >= 0) {
        int s = rp + 6;
        body.substring(s, body.indexOf("\"", s)).toCharArray(owm_city, sizeof(owm_city));
    } else {
        int np = body.indexOf("\"name\":\"");
        if (np >= 0) {
            int s = np + 8;
            body.substring(s, body.indexOf("\"", s)).toCharArray(owm_city, sizeof(owm_city));
        }
    }

    int lp = body.indexOf("\"lat\":");
    if (lp < 0) return false;
    { int s = lp + 6; String v = body.substring(s); int e = 0;
      while (e < (int)v.length() && (isDigit(v[e]) || v[e]=='.'||v[e]=='-')) e++;
      v.substring(0, e).toCharArray(owm_lat, sizeof(owm_lat)); }

    int lonp = body.indexOf("\"lon\":");
    if (lonp < 0) return false;
    { int s = lonp + 6; String v = body.substring(s); int e = 0;
      while (e < (int)v.length() && (isDigit(v[e]) || v[e]=='.'||v[e]=='-')) e++;
      v.substring(0, e).toCharArray(owm_lon, sizeof(owm_lon)); }

    USBSerial.printf("City: %s  lat=%s  lon=%s\n", owm_city, owm_lat, owm_lon);
    prefs.begin("carrotos", false);
    prefs.putString("city", owm_city);
    prefs.putString("lat",  owm_lat);
    prefs.putString("lon",  owm_lon);
    prefs.end();
    return true;
}
