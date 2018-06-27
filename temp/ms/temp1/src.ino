#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>

FASTLED_USING_NAMESPACE
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    45
#define FRAMES_PER_SECOND  120

enum pattern {
  none,
  strobe,
  confetti,
  sparkle,
  meteorrain,
  runninglights
};

pattern currentPattern;
int currentBrightness = 50;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];
CRGB leds5[NUM_LEDS];
CRGB leds6[NUM_LEDS];

ESP8266WebServer server(80);

String htmlResponse;

String htmlPre = "<!DOCTYPE html>"
                 "<html>"
                 "  <head>"
                 "    <style type=\"text/css\">"
                 "      body {margin: auto;width: 20em;font-family: Verdana;}"
                 "      \#patterns a {text-decoration: none;color: \#000;}"
                 "      \#title {font-size: 2em;font-weight: bold;text-align: center;margin-bottom: .5em;margin-top: .5em;}"
                 "      \#patterns div {background-color: \#999999;text-align: center;line-height: 3em;margin-bottom: .2em;}"
                 "      \#patterns div:hover {background-color: \#cccccc;}"
                 "    </style>"
                 "  </head>"
                 "  <body>"
                 "    <div id=\"title\">Marshmellow Hat Control</div>"
                 "    <div id=\"patterns\">";
String htmlPost = "</div>"
                 "  </body>"
                 "</html>";
// String htmlPre;
// String htmlPost;

void setup() {
  delay(1000); // 3 second delay for recovery

  Serial.begin(115200);
  Serial.println("[WiFi] Hotspot \"Marshmellow\"");
  IPAddress ip(192, 168, 1, 100);
  IPAddress gateway(192, 168, 1, 254);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Walt's Marshmellow Hat", "taxitaxi");
  delay(500);
  WiFi.begin();
  Serial.print("[WiFi] IP Adresse ");
  Serial.println(WiFi.softAPIP());

  server.on("/", httpRequest);
  // server.on("/.html", Ereignis_SchalteON);
  // server.on("/0.html", Ereignis_SchalteOFF);

  server.begin();
  Serial.println("[WiFi] Server startet");

  FastLED.addLeds<LED_TYPE, 2, COLOR_ORDER>(leds1, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 3, COLOR_ORDER>(leds2, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 4, COLOR_ORDER>(leds3, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 5, COLOR_ORDER>(leds4, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 6, COLOR_ORDER>(leds4, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 7, COLOR_ORDER>(leds4, NUM_LEDS).setCorrection(TypicalLEDStrip);

  FastLED.setBrightness(currentBrightness);
  Serial.println("[NeoPixel] Pixels initialized");
}

void httpRequest() {
  Serial.println("[HTTP] HttpRequest...");

  /*
  for (int i = none; i < runninglights; i++) {
    // <a href=\"?pattern=0\"><div style=\"background-color: #339933\">None</div></a>
    // <a href=\"?pattern=1\"><div>Strobe</div></a>
    // <a href=\"?pattern=2\"><div>Confetti</div></a>
    // <a href=\"?pattern=3\"><div>Sparkle</div></a>
    // <a href=\"?pattern=4\"><div>Meteor Rain</div></a>
    // <a href=\"?pattern=5\"><div>Running Lights</div></a>
  }

  // for (int i = 0; i < server.args(); i++) {
  // server.argName(i); server.arg(i);
  switch (server.arg("pattern").toInt()) {
    case none:
    case strobe:
      strobe123();
      break;
  }
  */
  
  htmlResponse = "Test HTML";
  server.send(200, "text/html", htmlResponse);
}

void loop() {
  server.handleClient();
}

void strobe123() {

}





/*


  void loop()
  {
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
  }

  #define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

  void nextPattern()
  {
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
  }

  void rainbow()
  {
  // FastLED's built-in rainbow generator
  fill_rainbow( leds1, NUM_LEDS, gHue, 7);
  fill_rainbow( leds2, NUM_LEDS, gHue, 7);
  fill_rainbow( leds3, NUM_LEDS, gHue, 7);
  fill_rainbow( leds4, NUM_LEDS, gHue, 7);
  fill_rainbow( leds5, NUM_LEDS, gHue, 7);
  fill_rainbow( leds6, NUM_LEDS, gHue, 7);
  }

  void rainbowWithGlitter()
  {
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
  }

  void addGlitter( fract8 chanceOfGlitter)
  {
  if( random8() < chanceOfGlitter) {
    leds1[ random16(NUM_LEDS) ] += CRGB::White;
    leds2[ random16(NUM_LEDS) ] += CRGB::White;
    leds3[ random16(NUM_LEDS) ] += CRGB::White;
    leds4[ random16(NUM_LEDS) ] += CRGB::White;
    leds5[ random16(NUM_LEDS) ] += CRGB::White;
    leds6[ random16(NUM_LEDS) ] += CRGB::White;
  }
  }

  void confetti()
  {
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds1, NUM_LEDS, 10);
  fadeToBlackBy( leds2, NUM_LEDS, 10);
  fadeToBlackBy( leds3, NUM_LEDS, 10);
  fadeToBlackBy( leds4, NUM_LEDS, 10);
  fadeToBlackBy( leds5, NUM_LEDS, 10);
  fadeToBlackBy( leds6, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds1[pos] += CHSV( gHue + random8(64), 200, 255);
  leds2[pos] += CHSV( gHue + random8(64), 200, 255);
  leds3[pos] += CHSV( gHue + random8(64), 200, 255);
  leds4[pos] += CHSV( gHue + random8(64), 200, 255);
  leds5[pos] += CHSV( gHue + random8(64), 200, 255);
  leds6[pos] += CHSV( gHue + random8(64), 200, 255);
  }

  void sinelon()
  {
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds1, NUM_LEDS, 20);
  fadeToBlackBy( leds2, NUM_LEDS, 20);
  fadeToBlackBy( leds3, NUM_LEDS, 20);
  fadeToBlackBy( leds4, NUM_LEDS, 20);
  fadeToBlackBy( leds5, NUM_LEDS, 20);
  fadeToBlackBy( leds6, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds1[pos] += CHSV( gHue, 255, 192);
  leds2[pos] += CHSV( gHue, 255, 192);
  leds3[pos] += CHSV( gHue, 255, 192);
  leds4[pos] += CHSV( gHue, 255, 192);
  leds5[pos] += CHSV( gHue, 255, 192);
  leds6[pos] += CHSV( gHue, 255, 192);
  }

  void bpm()
  {
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds1[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    leds2[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    leds3[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    leds4[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    leds5[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    leds6[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
  }

  void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds1, NUM_LEDS, 20);
  fadeToBlackBy( leds2, NUM_LEDS, 20);
  fadeToBlackBy( leds3, NUM_LEDS, 20);
  fadeToBlackBy( leds4, NUM_LEDS, 20);
  fadeToBlackBy( leds5, NUM_LEDS, 20);
  fadeToBlackBy( leds6, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds1[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    leds2[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    leds3[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    leds4[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    leds5[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    leds6[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
  }

*/
