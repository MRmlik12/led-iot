#ifndef IOT_LED_H
#define IOT_LED_H

#define LED_COUNT 26

#include <FastLED.h>

#include "config.h"
#include "modes.h"

class Context;

class LedStripState {
protected:
    Context *context_;
public:
    virtual ~LedStripState() {
    }

    void set_context(Context *context_) {
        this->context_ = context_;
    }

    virtual void Handle() = 0;
};

class Context {
private:
    LedStripState *state_;
protected:
    Context() {}
public:
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
public:
    void Handle() override;
};

class LedStripManager : LedConfiguration {
private:
    static LedStripManager* instance_;
protected:
    LedStripManager(LedConfiguration *configuration): LedConfiguration(configuration->getR(), configuration->getG(), configuration->getB(), configuration->getBrightness(), configuration->getMode()) {
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
