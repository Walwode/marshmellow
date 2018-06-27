#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>

FASTLED_USING_NAMESPACE
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    45
#define FRAMES_PER_SECOND  120

enum pattern {
  none,
  strobe,
  confetti,
  sparkle,
  meteorrain,
  runninglights,
  rainbowGlitter,
  sinelon,
  white
};

uint8_t prevPattern;
uint8_t currPattern;
uint8_t currBrightness = 50;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

ESP8266WebServer server(80);

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];
CRGB leds5[NUM_LEDS];
CRGB leds6[NUM_LEDS];

String htmlResponse;
String htmlPre = "<!DOCTYPE html>"
                 "<html>"
                 "  <head>"
                 "    <style type=\"text/css\">"
                 "      body {margin: auto;width: 95%;font-family: Verdana;font-size:2.5em;}"
                 "      \#patterns a {text-decoration: none;color: \#000;}"
                 "      \#title {font-weight: bold;text-align: center;margin-bottom: .5em;margin-top: .5em;}"
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
  Serial.println("[WiFi] Hotspot \"Walt's Marshmellow Hat\"");
  // IPAddress ip(192, 168, 1, 100);
  // IPAddress gateway(192, 168, 1, 254);
  // IPAddress subnet(255, 255, 255, 0);
  // WiFi.config(ip, gateway, subnet);
  // WiFi.begin();
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Walt's Marshmellow Hat", "taxitaxi");
  delay(500);
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

  FastLED.setBrightness(currBrightness);
  Serial.println("[NeoPixel] Pixels initialized");
}

void httpRequest() {
  Serial.print("[HTTP] HttpRequest...");
  Serial.println(server.args());

  prevPattern = currPattern;
  currPattern = server.arg("pattern").toInt();

  Serial.println("[HTTP] HttpResponse...");
  cretateHttpResponse();
  server.send(200, "text/html", htmlResponse);
}

void loop() {
  server.handleClient();
  
  switch (currPattern) {
    case none: patternOff(); break;
    case strobe: patternStrobe(); break;
    case confetti: patternConfetti(); break;
    case sparkle: patternSparkle(); break;
    case meteorrain: patternMeteorRain(); break;
    case runninglights: patternRunningLights(); break;
    case rainbowGlitter: patternRainbowGlitter(); break;
    case sinelon: patternSinelon(); break;
    case white: patternWhite(); break;
  }

  FastLED.show();
  FastLED.delay(1000/FRAMES_PER_SECOND);

  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  // EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
}

void patternOff() {
  // Serial.println("[Pattern] Off...");
  fadeToBlackBy( leds1, NUM_LEDS, 10);
  fadeToBlackBy( leds2, NUM_LEDS, 10);
  fadeToBlackBy( leds3, NUM_LEDS, 10);
  fadeToBlackBy( leds4, NUM_LEDS, 10);
  fadeToBlackBy( leds5, NUM_LEDS, 10);
  fadeToBlackBy( leds6, NUM_LEDS, 10);
}
void patternStrobe() {
  // Serial.println("[Pattern] Strobe...");
}
void patternConfetti() {
  // Serial.println("[Pattern] Confetti...");
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
void patternSparkle() {
  // Serial.println("[Pattern] Sparkle...");
}
void patternMeteorRain() {
  // Serial.println("[Pattern] Meteor Rain...");
  byte red = 0xff;
  byte green = 0xff;
  byte blue = 0xff;
  byte meteorSize = 10;
  byte meteorTrailDecay = 64;
  boolean meteorRandomDecay = true;
  
  setAll(0,0,0);
  
  for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlackBy(leds1, j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      } 
    }
  }
}
void patternRunningLights() {
  // Serial.println("[Pattern] Running Lights...");
}
void patternRainbowGlitter() {
  // Serial.println("[Pattern] Rainbow with Glitter...");
  fill_rainbow( leds1, NUM_LEDS, gHue, 7);
  fill_rainbow( leds2, NUM_LEDS, gHue, 7);
  fill_rainbow( leds3, NUM_LEDS, gHue, 7);
  fill_rainbow( leds4, NUM_LEDS, gHue, 7);
  fill_rainbow( leds5, NUM_LEDS, gHue, 7);
  fill_rainbow( leds6, NUM_LEDS, gHue, 7);
  if( random8() < 80) {
    leds1[ random16(NUM_LEDS) ] += CRGB::White;
    leds2[ random16(NUM_LEDS) ] += CRGB::White;
    leds3[ random16(NUM_LEDS) ] += CRGB::White;
    leds4[ random16(NUM_LEDS) ] += CRGB::White;
    leds5[ random16(NUM_LEDS) ] += CRGB::White;
    leds6[ random16(NUM_LEDS) ] += CRGB::White;
  }
}
void patternSinelon() {
  // Serial.println("[Pattern] Sinelon...");
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
void patternWhite() {  
  // Serial.println("[Pattern] White...");
}

String enumToString(uint8_t currEnum) {
  switch (currEnum) {
    case none: return "None"; break;
    case strobe: return "Strobe"; break;
    case confetti: return "Confetti"; break;
    case sparkle: return "Sparkle"; break;
    case meteorrain: return "Meteor Rain"; break;
    case runninglights: return "Running Lights"; break;
    case rainbowGlitter: return "Rainbow with Glitter"; break;
    case sinelon: return "Sinelon"; break;
    case white: return "White"; break;
    default: return "Unkown";
  }
  return "SWITCH ERROR";
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
  leds1[Pixel].r = red;
  leds1[Pixel].g = green;
  leds1[Pixel].b = blue;
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  FastLED.show();
}

void cretateHttpResponse() {
  htmlResponse = htmlPre;
  for (uint8_t i = none; i < white; i++) {
    htmlResponse += "<a href=\"?pattern=" + String(i) + "\"><div"
                    + String((currPattern == i) ? " style=\"background-color: \#339933\"" : "") +
                    ">" + enumToString(i) + "</div></a>";
  }
  htmlResponse += htmlPost;
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

