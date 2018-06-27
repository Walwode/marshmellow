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
    case none: return "None"; break;
    case strobe: return "Strobe"; break;
    case confetti: return "Confetti"; break;
    case sparkle: return "Sparkle"; break;
    case meteorrain: return "Meteor Rain"; break;
    case runninglights: return "Running Lights"; break;
    case rainbowGlitter: return "Rainbow with Glitter"; break;
    case sinelon: return "Sinelon"; break;
    case white: return "White"; break;
	case multi1: return "Confetti RainbowGlitter Sinelon"; break;
    default: return "Unkown";
  }
  return "SWITCH ERROR";
}
