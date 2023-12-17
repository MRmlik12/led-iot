#include <FastLED.h>
#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"
#include "led.h"

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void registerRoutes(AsyncWebServer &webServer) {
    webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        DynamicJsonDocument jsonModel(256);
        jsonModel["version"] = "1";
        String json;
        ArduinoJson::serializeJson(jsonModel, json);
        request->send(200, "application/json", json);
    });

    webServer.on("/color", HTTP_POST, [](AsyncWebServerRequest *request) {
    },  NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
        String body = (const char*) data;
        if (body.length() == 0) {
            request->send(400, "application/json", "{\"error\": \"body is empty\"}");
            return;
        }

        DynamicJsonDocument jsonDocument(256);
        ArduinoJson::deserializeJson(jsonDocument, body);

        LedStripManager::getInstance()->setRGB(jsonDocument["r"], jsonDocument["g"], jsonDocument["b"]);

        request->send(200, "application/json", body);
    });

    webServer.onNotFound(notFound);
}