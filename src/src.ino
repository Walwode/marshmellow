#include <Arduino.h>
#include <Scheduler.h>

#include "GlobalVars.h"
#include "MLedHandler.h"
#include "MWebServer.h"

MWebServer webServer;
MLedHandler ledHandler;

void setup() {
  delay(1000);
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  
  // fooHandler::setup(bar);...
  
  Scheduler.start(&webServer);
  Scheduler.start(&ledHandler);
}

void loop() {
  Scheduler.begin();
  Serial.println(F("unreachable code"));
}

