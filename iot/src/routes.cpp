#include <LittleFS.h>
#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"
#include "led.h"

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void registerRoutes(AsyncWebServer &webServer) {
    webServer.serveStatic("/", LittleFS, "/www/").setDefaultFile("index.html");

    webServer.on("/color", HTTP_POST, [](AsyncWebServerRequest *request) {
    },  NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
        String body = (const char*) data;
        if (body.length() == 0) {
            request->send(400, "application/json", "{\"error\": \"body is empty\"}");
            return;
        }

        DynamicJsonDocument jsonDocument(256);
        ArduinoJson::deserializeJson(jsonDocument, body);

        auto pLedStripManager = LedStripManager::getInstance();
        pLedStripManager->setMode(LedStripMode::NONE);
        LedStripManager::getInstance()->setRGB(jsonDocument["r"], jsonDocument["g"], jsonDocument["b"]);

        request->send(200, "application/json", body);
    });

    webServer.on("/currentColor", HTTP_GET, [](AsyncWebServerRequest *request) {
        auto rgb = LedStripManager::getInstance()->getRGB();

        DynamicJsonDocument jsonDocument(256);

        jsonDocument["r"] = rgb.r;
        jsonDocument["g"] = rgb.g;
        jsonDocument["b"] = rgb.b;

        String response;
        serializeJson(jsonDocument, response);

        request->send(200, "application/json", response);
    });

    webServer.on("/mode", HTTP_POST, [](AsyncWebServerRequest *request) {
    },  NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
        String body = (const char*) data;
        if (body.length() == 0) {
            request->send(400, "application/json", "{\"error\": \"body is empty\"}");
            return;
        }

        DynamicJsonDocument jsonDocument(256);
        ArduinoJson::deserializeJson(jsonDocument, body);

        auto mode = static_cast<LedStripMode>(jsonDocument["mode"]);
        LedStripManager::getInstance()->setMode(mode);

        request->send(200, "application/json", body);
    });

    webServer.onNotFound(notFound);
}