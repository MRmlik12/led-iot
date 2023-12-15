#include <FastLED.h>
#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"
#include "led.h"
LedManager ledManager;

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

    webServer.on("/color", HTTP_GET, [](AsyncWebServerRequest *request) {
        auto rColor = request->getParam("r")->value().toInt();
        auto gColor = request->getParam("g")->value().toInt();
        auto bColor = request->getParam("b")->value().toInt();

        ledManager.setRGB(rColor, gColor, bColor);

        DynamicJsonDocument jsonModel(256);
        jsonModel["r"] = rColor;
        jsonModel["g"] = gColor;
        jsonModel["b"] = bColor;
        String json;
        ArduinoJson::serializeJson(jsonModel, json);
        request->send(200, "application/json", json);
    });

    webServer.onNotFound(notFound);
}