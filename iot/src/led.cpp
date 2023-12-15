#include <FastLED.h>
#include "led.h"

int r, g, b = 0;

void LedManager::setRGB(int rColor, int gColor, int bColor) {
    r = rColor;
    g = gColor;
    b = bColor;
}

CRGB LedManager::getRGB() {
    return CRGB(r, g, b);
}


