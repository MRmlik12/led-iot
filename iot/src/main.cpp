#include <Arduino.h>
#include <LittleFS.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#endif
#include <ESPAsyncWebServer.h>
#include <routes.h>
#include "config.h"
#include "led.h"

AsyncWebServer server(80);

void setup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);

    setupFastLED();

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    LittleFS.begin();

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    registerRoutes(server);
    server.begin();
}

void loop() {
    auto pLedStripManager = LedStripManager::getInstance();
    pLedStripManager->context->request();
}

