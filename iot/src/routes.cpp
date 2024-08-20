#include <LittleFS.h>
#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"
#include "led.h"

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void registerRoutes(AsyncWebServer &webServer) {
    webServer.serveStatic("/", LittleFS, "/www/").setDefaultFile("index.html");

    webServer.on("/api/current", HTTP_GET, [](AsyncWebServerRequest *request) {
        DynamicJsonDocument jsonDocument(256);

        auto pLedStripManager = LedStripManager::getInstance();

        auto rgb = pLedStripManager->getRGB();
        jsonDocument["r"] = rgb.r;
        jsonDocument["g"] = rgb.g;
        jsonDocument["b"] = rgb.b;

        jsonDocument["mode"] = pLedStripManager->getMode();
        jsonDocument["brightness"] = pLedStripManager->getBrightness();

        String body;
        ArduinoJson::serializeJson(jsonDocument, body);

        request->send(200, "application/json", body);
    });

    webServer.on("/api/update", HTTP_POST, [](AsyncWebServerRequest *request) {
    },  NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
        String body = reinterpret_cast<const char *>(data);
        if (body.length() == 0) {
            request->send(400, "application/json", "{\"error\": \"body is empty\"}");
            return;
        }

        DynamicJsonDocument jsonDocument(256);
        ArduinoJson::deserializeJson(jsonDocument, body);

        auto r = jsonDocument["r"];
        auto g = jsonDocument["g"];
        auto b = jsonDocument["b"];
        auto mode = static_cast<LedStripMode>(jsonDocument["mode"]);
        auto level = static_cast<uint8_t>(jsonDocument["brightness"]);

        auto pLedStripManager = LedStripManager::getInstance();

        if (r != nullptr && g != nullptr && b != nullptr && mode == NONE) {
            pLedStripManager->setRGB(r, g, b);
        }

        if (mode != pLedStripManager->getMode()) {
            pLedStripManager->setMode(mode);
        }

        if (level != pLedStripManager->getBrightness()) {
            pLedStripManager->setBrightness(level);
        }

        pLedStripManager->setMode(mode);

        request->send(200, "application/json", body);
    });

    webServer.onNotFound(notFound);
}