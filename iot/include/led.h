#ifndef IOT_LED_H
#define IOT_LED_H

#include <FastLED.h>

class LedManager {
public:
    void setRGB(int rColor, int gColor, int bColor);
    CRGB getRGB();
};

#endif
