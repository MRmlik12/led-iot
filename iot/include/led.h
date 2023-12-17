#ifndef IOT_LED_H
#define IOT_LED_H

#include <FastLED.h>

class LedStripManager {
private:
    int r_ = 0;
    int g_ = 0;
    int b_ = 0;
protected:
    LedStripManager() {}
    static LedStripManager* instance_;
public:
    LedStripManager(LedStripManager &other) = delete;
    static LedStripManager *getInstance();
    void operator=(const LedStripManager &) = delete;

    void setRGB(int rColor, int gColor, int bColor);
    CRGB getRGB();
};

#endif
