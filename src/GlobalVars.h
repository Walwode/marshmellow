enum pattern {
  none,
  strobe,
  confetti,
  sparkle,
  meteorrain,
  runninglights,
  rainbowGlitter,
  sinelon,
  multi1,
  white
};

uint8_t prevPattern;
uint8_t currPattern;
uint8_t currMultiPattern;
uint8_t currBrightness;

String enumToString(uint8_t currEnum) {
  switch (currEnum) {
    case none: return F("None"); break;
    case strobe: return F("Strobe"); break;
    case confetti: return F("Confetti"); break;
    case sparkle: return F("Sparkle"); break;
    case meteorrain: return F("Meteor Rain"); break;
    case runninglights: return F("Running Lights"); break;
    case rainbowGlitter: return F("Rainbow with Glitter"); break;
    case sinelon: return F("Sinelon"); break;
    case white: return F("White"); break;
    case multi1: return F("Confetti RainbowGlitter Sinelon"); break;
    default: return F("Unkown");
  }
  return F("SWITCH ERROR");
}
