#define LED_COUNT 26

#include <FastLED.h>
#include "led.h"


LedStripManager* LedStripManager::instance_ = nullptr;

LedStripManager *LedStripManager::getInstance() {
    if(instance_ == nullptr) {
        instance_ = new LedStripManager();
    }
    return instance_;
}

void LedStripManager::setRGB(int rColor, int gColor, int bColor) {
    r_ = rColor;
    g_ = gColor;
    b_ = bColor;
    FastLED.showColor(CRGB(r_, g_, b_));
}

CRGB LedStripManager::getRGB() {
    return CRGB(r_, g_, b_);
}

void LedStripManager::setMode(LedStripMode mode) {
    mode_ = mode;

    switch (mode) {
        case NONE:
            context->transitionTo(new NoneLedStripState);
            break;
        case WAVE:
            context->transitionTo(new WaveLedStripState);
            break;
        default:
            break;
    }
}

LedStripMode LedStripManager::getMode() {
    return mode_;
}

void LedStripManager::setBrightness(uint8_t level) {
    brightness_ = level;
    FastLED.setBrightness(level);
}

uint8_t LedStripManager::getBrightness() {
    return brightness_;
}

void Context::transitionTo(LedStripState *state) {
    if (this->state_ != nullptr)
        delete this->state_;

    this->state_ = state;
    this->state_->set_context(this);
}

void Context::request() {
    this->state_->Handle();
}

void WaveLedStripState::Handle() {
    uint8_t thisSpeed = 10;
    uint8_t deltaHue= 10;
    uint8_t thisHue = beat8(thisSpeed,255);

    fill_rainbow(leds, LED_COUNT, thisHue, deltaHue);
    FastLED.show();
}

void NoneLedStripState::Handle() {
    if (this->lastColor_ == LedStripManager::getInstance()->getRGB()) {
        return;
    }

    this->lastColor_ = LedStripManager::getInstance()->getRGB();
    FastLED.showColor(this->lastColor_);
}

void setupFastLED() {
    FastLED.addLeds<WS2812B, 5>(leds, LED_COUNT);
    FastLED.setMaxRefreshRate(200);
    FastLED.setBrightness(80);
    FastLED.clear(true);
}
