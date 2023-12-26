#ifndef IOT_CONFIG_H
#define IOT_CONFIG_H

#include <Arduino.h>
#include <ArduinoJson.h>

class Config {
private:
    String ssid_;
    String password_;
    String hostname_;
public:
    String getSSID();
    String getPassword();
    String getHostname();

    Config(String ssid, String password, String hostname) {
        this->ssid_ = ssid;
        this->password_ = password;
        this->hostname_ = hostname;
    }
};

Config* getConfiguration();

#endif
