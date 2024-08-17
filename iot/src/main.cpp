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
    LittleFS.begin();

    auto config = Config::getConfiguration();

    WiFi.mode(WIFI_STA);
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
    WiFi.begin(config->getSSID(), config->getPassword());

    setupFastLED();

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    if (!MDNS.begin(config->getHostname())) {
        delay(500);
    }

    MDNS.addService("http", "tcp", 80);

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    registerRoutes(server);
    server.begin();
}

void loop() {
    MDNS.update();

    auto pLedStripManager = LedStripManager::getInstance();
    pLedStripManager->context->request();
}
