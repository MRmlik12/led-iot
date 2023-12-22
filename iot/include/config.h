#ifndef IOT_CONFIG_H
#define IOT_CONFIG_H

#include <Arduino.h>
#include <ArduinoJson.h>

class Config {
private:
    String ssid_;
    String password_;
public:
    String getSSID();
    String getPassword();

    Config(String ssid, String password) {
        this->ssid_ = ssid;
        this->password_ = password;
    }
};

Config* getConfiguration();

#endif
