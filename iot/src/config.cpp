#include <LittleFS.h>
#include "config.h"

#define CONFIG_FILE "config.json"
#define LED_FILE "led.json"

File getFile(const char *path, const char *mode) {
    return LittleFS.open(path,  mode);
}

DynamicJsonDocument getJsonDocument(const char *path, size_t size) {
    auto file = getFile(path, "r");
    auto content = file.readString();

    DynamicJsonDocument json(size);
    ArduinoJson::deserializeJson(json, content);

    return json;
}

Config* Config::getConfiguration() {
    auto json = getJsonDocument(CONFIG_FILE, 256);

    return new Config(json["ssid"], json["password"], json["hostname"]);
}

String Config::getSSID() {
    return ssid_;
}

String Config::getPassword() {
    return password_;
}

String Config::getHostname() {
    return hostname_;
}

int LedConfiguration::getR() {
    return this->r_;
}

int LedConfiguration::getB() {
    return this->b_;
}

int LedConfiguration::getG() {
    return this->g_;
}

uint8_t LedConfiguration::getBrightness() {
    return this->brightness_;
}

LedStripMode LedConfiguration::getMode() {
    return this->mode_;
}

LedConfiguration* LedConfiguration::getConfiguration() {
    auto json = getJsonDocument(LED_FILE, 256);

    return new LedConfiguration(json["r"], json["g"], json["b"], json["brightness"], json["mode"]);
}

void LedConfiguration::save() {
    DynamicJsonDocument json(256);
    json["r"] = r_;
    json["g"] = g_;
    json["b"] = b_;
    json["brightness"] = brightness_;

    auto file = getFile("led.json", "w");
    ArduinoJson::serializeJson(json, file);
    file.close();
}
