#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Scheduler.h>

ESP8266WebServer server(80);

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

class MWebServer : public Task {
  
public:
  MWebServer() {};
  ~MWebServer() {};

  static void cretateHttpResponse();
  static void httpRequest();

protected:
  void loop();
  void setup();
  
};

void MWebServer::setup() {
  Serial.println(F("[WiFi] Hotspot \"Walt's Marshmellow Hat\""));
  // IPAddress ip(192, 168, 1, 100);
  // IPAddress gateway(192, 168, 1, 254);
  // IPAddress subnet(255, 255, 255, 0);
  // WiFi.config(ip, gateway, subnet);
  // WiFi.begin();
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Walt's Marshmellow Hat", "taxitaxi");
  delay(500);
  Serial.print(F("[WiFi] IP Adresse "));
  Serial.println(WiFi.softAPIP());

  server.on(F("/"), httpRequest);
  // server.on("/foo.html", foobar);

  server.begin();
  Serial.println(F("[WiFi] Server startet"));
}

void MWebServer::loop() {
  server.handleClient();
}

void MWebServer::httpRequest() {
  Serial.print(F("[HTTP] HttpRequest..."));
  Serial.println(server.args());

  prevPattern = currPattern;
  currPattern = server.arg("pattern").toInt();

  Serial.println(F("[HTTP] HttpResponse..."));
  cretateHttpResponse();
  server.send(200, F("text/html"), htmlResponse);
}

void MWebServer::cretateHttpResponse() {
  htmlResponse = htmlPre;
  for (uint8_t i = none; i < white; i++) {
    htmlResponse += "<a href=\"?pattern=" + String(i) + "\"><div"
                    + String((currPattern == i) ? " style=\"background-color: \#339933\"" : "") +
                    ">" + enumToString(i) + "</div></a>";
  }
  htmlResponse += htmlPost;
}
