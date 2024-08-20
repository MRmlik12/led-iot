#ifndef IOT_LED_H
#define IOT_LED_H

#define LED_COUNT 26

#include <FastLED.h>

#include "config.h"
#include "modes.h"

static CRGB leds[LED_COUNT];

class Context;

class LedStripState {
protected:
    Context *context_;
public:
    virtual ~LedStripState() = default;

    void set_context(Context *context_) {
        this->context_ = context_;
    }

    virtual void Handle() = 0;
};

class Context {
private:
    LedStripState *state_;
public:
    Context() : state_(nullptr) {}

    Context(LedStripState *state) : state_(nullptr) {
        this->transitionTo(state);
    }

    ~Context() {
        delete state_;
    }

    void transitionTo(LedStripState *state);
    void request();
};

class NoneLedStripState : public LedStripState {
private:
    CRGB lastColor_ = {0, 0, 0};
public:
    void Handle() override;
};

class WaveLedStripState : public LedStripState {
private:
    uint8_t lastHue_ = 0;
public:
    void Handle() override;
};

class LedStripManager : LedConfiguration {
private:
    static LedStripManager* instance_;
protected:
    LedStripManager(LedConfiguration *configuration): LedConfiguration(configuration->getR(), configuration->getG(), configuration->getB(), configuration->getBrightness(), configuration->getMode()) {
        context = new Context();
        this->setRGB(configuration->getR(), configuration->getB(), configuration->getG());
        this->setBrightness(configuration->getBrightness());
        this->setMode(configuration->getMode());
    }

    LedStripManager(): LedConfiguration(0, 0, 0, 0, NONE) {
        context = new Context(new NoneLedStripState);
    }

public:
    Context *context;

    LedStripManager(LedStripManager &other) = delete;
    static LedStripManager *getInstance();
    void operator=(const LedStripManager &) = delete;

    void setRGB(int rColor, int gColor, int bColor);
    void setMode(LedStripMode mode);
    void setBrightness(uint8_t level);
    void loadConfiguration(LedConfiguration *configuration);
    LedStripMode getMode();
    CRGB getRGB();
    uint8_t getBrightness();
};

void setupFastLED();

#endif
