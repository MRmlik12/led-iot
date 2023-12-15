#include <Arduino.h>
#include <FastLED.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#endif
#include <ESPAsyncWebServer.h>
#include <routes.h>
#include "config.h"
#include "led.h"

CRGB leds[LED_COUNT];
AsyncWebServer server(80);
LedManager led;

void setup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);
    FastLED.addLeds<WS2812B, 2>(leds, LED_COUNT);
    FastLED.setBrightness(80);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    registerRoutes(server);
    server.begin();
}

void loop() {
    EVERY_N_MILLIS(500) {
        FastLED.showColor(led.getRGB());
    }
}

