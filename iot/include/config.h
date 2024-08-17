#ifndef IOT_CONFIG_H
#define IOT_CONFIG_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "modes.h"

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

    static Config* getConfiguration();
};

class LedConfiguration {
protected:
    int r_;
    int g_;
    int b_;
    uint8_t brightness_;
    LedStripMode mode_;
public:
    LedConfiguration(int r, int g, int b, uint8_t brightness, LedStripMode mode) {
        this->r_ = r;
        this->g_ = g;
        this->b_ = b;
        this->brightness_ = brightness;
        this->mode_ = mode;
    }

    int getR();
    int getG();
    int getB();
    uint8_t getBrightness();
    LedStripMode getMode();

    static LedConfiguration* getConfiguration();
    void save();
};

#endif
