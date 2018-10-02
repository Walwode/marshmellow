#include <Arduino.h>
#include <FastLED.h>
#include <Scheduler.h>

FASTLED_USING_NAMESPACE
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    45
#define FRAMES_PER_SECOND  120
#define MILLI_AMPS 1000

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];
CRGB leds5[NUM_LEDS];
CRGB leds6[NUM_LEDS];

class MLedHandler : public Task {
  
public:
  MLedHandler() {};
  ~MLedHandler() {};

  static void doPattern(uint8_t patternEnum);
  
  static void patternOff();
  static void patternStrobe();
  static void patternConfetti();
  static void patternSparkle();
  static void patternMeteorRain();
  static void patternRunningLights();
  static void patternRainbowGlitter();
  static void patternSinelon();
  static void patternConfettiRainbowGlitterSinelon();
  static void patternWhite();

protected:
  void loop();
  void setup();
  
};

void MLedHandler::setup() {
  Serial.print(F("[NeoPixel] Init stripes... "));
  FastLED.addLeds<LED_TYPE, 2, COLOR_ORDER>(leds1, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 3, COLOR_ORDER>(leds2, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 4, COLOR_ORDER>(leds3, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 5, COLOR_ORDER>(leds4, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 6, COLOR_ORDER>(leds4, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 7, COLOR_ORDER>(leds4, NUM_LEDS).setCorrection(TypicalLEDStrip);

  currBrightness = 50;
  FastLED.setBrightness(currBrightness);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS);
  Serial.println(F("done"));
}

void MLedHandler::loop() {
  doPattern(currPattern);
  FastLED.show();
  FastLED.delay(1000/FRAMES_PER_SECOND);
}

void MLedHandler::doPattern(uint8_t patternEnum) {
  switch (patternEnum) {
    case none: patternOff(); break;
    case strobe: patternStrobe(); break;
    case confetti: patternConfetti(); break;
    case sparkle: patternSparkle(); break;
    case meteorrain: patternMeteorRain(); break;
    case runninglights: patternRunningLights(); break;
    case rainbowGlitter: patternRainbowGlitter(); break;
    case sinelon: patternSinelon(); break;
    case multi1: patternConfettiRainbowGlitterSinelon();
    case white: patternWhite(); break;
  }
}

void MLedHandler::patternOff() {
  // Serial.println("[Pattern] Off...");
  fadeToBlackBy(leds1, NUM_LEDS, 10);
  fadeToBlackBy(leds2, NUM_LEDS, 10);
  fadeToBlackBy(leds3, NUM_LEDS, 10);
  fadeToBlackBy(leds4, NUM_LEDS, 10);
  fadeToBlackBy(leds5, NUM_LEDS, 10);
  fadeToBlackBy(leds6, NUM_LEDS, 10);
}

void MLedHandler::patternStrobe() {
  // Serial.println("[Pattern] Strobe...");
  EVERY_N_MILLISECONDS(100) {
    fadeLightBy(leds1, NUM_LEDS, 20);
    fadeLightBy(leds2, NUM_LEDS, 20);
    fadeLightBy(leds3, NUM_LEDS, 20);
    fadeLightBy(leds4, NUM_LEDS, 20);
    fadeLightBy(leds5, NUM_LEDS, 20);
    fadeLightBy(leds6, NUM_LEDS, 20);
  }
  EVERY_N_MILLISECONDS(200) {
    fadeToBlackBy(leds1, NUM_LEDS, 10);
    fadeToBlackBy(leds2, NUM_LEDS, 10);
    fadeToBlackBy(leds3, NUM_LEDS, 10);
    fadeToBlackBy(leds4, NUM_LEDS, 10);
    fadeToBlackBy(leds5, NUM_LEDS, 10);
    fadeToBlackBy(leds6, NUM_LEDS, 10);
  }
}

void MLedHandler::patternConfetti() {
  // Serial.println("[Pattern] Confetti...");
  EVERY_N_MILLISECONDS(20) { gHue++; }
  
  fadeToBlackBy(leds1, NUM_LEDS, 10);
  fadeToBlackBy(leds2, NUM_LEDS, 10);
  fadeToBlackBy(leds3, NUM_LEDS, 10);
  fadeToBlackBy(leds4, NUM_LEDS, 10);
  fadeToBlackBy(leds5, NUM_LEDS, 10);
  fadeToBlackBy(leds6, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds1[pos] += CHSV(gHue + random8(64), 200, 255);
  leds2[pos] += CHSV(gHue + random8(64), 200, 255);
  leds3[pos] += CHSV(gHue + random8(64), 200, 255);
  leds4[pos] += CHSV(gHue + random8(64), 200, 255);
  leds5[pos] += CHSV(gHue + random8(64), 200, 255);
  leds6[pos] += CHSV(gHue + random8(64), 200, 255);
}

void MLedHandler::patternSparkle() {
  // Serial.println("[Pattern] Sparkle...");
}

void MLedHandler::patternMeteorRain() {
  // Serial.println("[Pattern] Meteor Rain...");
}

void MLedHandler::patternRunningLights() {
  // Serial.println("[Pattern] Running Lights...");
}

void MLedHandler::patternRainbowGlitter() {
  // Serial.println("[Pattern] Rainbow with Glitter...");
  EVERY_N_MILLISECONDS( 20 ) { gHue++; }
  
  fill_rainbow(leds1, NUM_LEDS, gHue, 7);
  fill_rainbow(leds2, NUM_LEDS, gHue, 7);
  fill_rainbow(leds3, NUM_LEDS, gHue, 7);
  fill_rainbow(leds4, NUM_LEDS, gHue, 7);
  fill_rainbow(leds5, NUM_LEDS, gHue, 7);
  fill_rainbow(leds6, NUM_LEDS, gHue, 7);
  if (random8() < 80) {
    leds1[ random16(NUM_LEDS) ] += CRGB::White;
    leds2[ random16(NUM_LEDS) ] += CRGB::White;
    leds3[ random16(NUM_LEDS) ] += CRGB::White;
    leds4[ random16(NUM_LEDS) ] += CRGB::White;
    leds5[ random16(NUM_LEDS) ] += CRGB::White;
    leds6[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void MLedHandler::patternSinelon() {
  // Serial.println("[Pattern] Sinelon...");
  EVERY_N_MILLISECONDS(20) { gHue++; }
  
  fadeToBlackBy(leds1, NUM_LEDS, 20);
  fadeToBlackBy(leds2, NUM_LEDS, 20);
  fadeToBlackBy(leds3, NUM_LEDS, 20);
  fadeToBlackBy(leds4, NUM_LEDS, 20);
  fadeToBlackBy(leds5, NUM_LEDS, 20);
  fadeToBlackBy(leds6, NUM_LEDS, 20);
  int pos = beatsin16(13, 0, NUM_LEDS - 1);
  leds1[pos] += CHSV( gHue, 255, 192);
  leds2[pos] += CHSV( gHue, 255, 192);
  leds3[pos] += CHSV( gHue, 255, 192);
  leds4[pos] += CHSV( gHue, 255, 192);
  leds5[pos] += CHSV( gHue, 255, 192);
  leds6[pos] += CHSV( gHue, 255, 192);
}

void MLedHandler::patternWhite() {  
  // Serial.println("[Pattern] White...");
  fadeLightBy(leds1, NUM_LEDS, 1);
  fadeLightBy(leds2, NUM_LEDS, 1);
  fadeLightBy(leds3, NUM_LEDS, 1);
  fadeLightBy(leds4, NUM_LEDS, 1);
  fadeLightBy(leds5, NUM_LEDS, 1);
  fadeLightBy(leds6, NUM_LEDS, 1);
}

void MLedHandler::patternConfettiRainbowGlitterSinelon() {
  if (!((currMultiPattern == confetti) || (currMultiPattern == rainbowGlitter) || (currMultiPattern == sinelon))) currMultiPattern = confetti;
  
  EVERY_N_SECONDS(10) {
    switch (currMultiPattern) {
	  case confetti: currMultiPattern = rainbowGlitter; break;
	  case rainbowGlitter: currMultiPattern = sinelon; break;
	  case sinelon: currMultiPattern = confetti; break;
    }
  } // change patterns periodically
  
  doPattern(currMultiPattern);
}
