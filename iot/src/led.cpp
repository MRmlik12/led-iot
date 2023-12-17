#include <FastLED.h>
#include "led.h"

LedStripManager* LedStripManager::instance_ = nullptr;;

LedStripManager *LedStripManager::getInstance() {
    if(instance_ ==nullptr) {
        instance_ = new LedStripManager();
    }
    return instance_;
}

void LedStripManager::setRGB(int rColor, int gColor, int bColor) {
    r_ = rColor;
    g_ = gColor;
    b_ = bColor;
}

CRGB LedStripManager::getRGB() {
    return CRGB(r_, g_, b_);
}


