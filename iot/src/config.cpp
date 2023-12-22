#include <LittleFS.h>
#include "config.h"

Config* getConfiguration() {
    auto file = LittleFS.open("config.json", "r");
    auto content = file.readString();

    DynamicJsonDocument json(256);
    ArduinoJson::deserializeJson(json, content);

    return new Config(json["ssid"], json["password"]);
}

String Config::getSSID() {
    return ssid_;
}

String Config::getPassword() {
    return password_;
}
