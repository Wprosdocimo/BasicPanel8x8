#include <Arduino.h>
// #include <FastLED.h>
// #include <WiFi.h>
// #include <ArduinoOTA.h>
#include <WebServer.h>
#include "OTA.h"
#include "Effects.h"

#define WIDTH 8
#define HEIGHT 8
#define NUM_LEDS WIDTH * HEIGHT

#define DATA_PIN 2

bool space;
bool bang;
bool bruxa;
bool fantasma;
bool poke;
bool mudaBrilho;
int brilho = 15;
bool swipe = true;

CRGB leds[NUM_LEDS];

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp32!");
  if (server.hasArg("brilho")) {
    mudaBrilho = true;
    brilho = server.arg("brilho").toInt();
  };
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void SERVERcomands() {
  server.on("/", handleRoot);
  server.on("/space", []() {
    server.send(200, "text/plain", "SPACE ON");
    space = true;
  });
  server.on("/bang", []() {
    server.send(200, "text/plain", "BANG ON");
    bang = true;
  });
  server.on("/bruxa", []() {
    server.send(200, "text/plain", "BRUXA ON");
    bruxa = true;
  });
  server.on("/fantasma", []() {
    server.send(200, "text/plain", "FANTASMA ON");
    fantasma = true;
  });
  server.on("/poke", []() {
    server.send(200, "text/plain", "POKE ON");
    poke = true;
  });
  server.on("/swipeoff", []() {
    server.send(200, "text/plain", "SWIPE OFF");
    swipe = false;
  });
  server.on("/swipeon", []() {
    server.send(200, "text/plain", "SWIPE ON");
    swipe = true;
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void setup()
{
  // put your setup code here, to run once:
  OTAconfig();
  SERVERcomands();
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(30);
}

void loop()
{
  // put your main code here, to run repeatedly:
  ArduinoOTA.handle();
  server.handleClient();
  FastLED.clear(NUM_LEDS);

  Pinheirinho(NUM_LEDS, leds);
  

  if (mudaBrilho) {
    FastLED.setBrightness(brilho);
    mudaBrilho = false;
  }
  if (swipe) {
    Swipe(NUM_LEDS, leds);
  }
  if (poke) {
    Poke(NUM_LEDS, leds);
    Swipe(NUM_LEDS, leds);
    poke = false;
  }
  if (space) {
    SpaceShift(NUM_LEDS, leds);
    Swipe(NUM_LEDS, leds);
    space = false;
  }
  if (bang) {
    Bang(NUM_LEDS, leds);
    Swipe(NUM_LEDS, leds);
    bang = false;
  }
  if (bruxa) {
    Bruxinha(NUM_LEDS, leds);
    Swipe(NUM_LEDS, leds);
    bruxa = false;
  }
  if (fantasma) {
    Fantasma(NUM_LEDS, leds);
    Swipe(NUM_LEDS, leds);
    fantasma = false;
  }
}