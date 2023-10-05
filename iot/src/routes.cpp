#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"

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

    webServer.onNotFound(notFound);
}