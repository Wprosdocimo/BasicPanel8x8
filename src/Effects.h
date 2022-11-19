#include <FastLED.h>
#include "images.h"
#include "paletas.h"

void Mostra(int NUM_LEDS, CRGB *leds,const long *image,int delaytime = 500) {
  FastLED.clear(NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = pgm_read_dword(&(image[i]));  // Read array from Flash
  }
  FastLED.show();
  delay(delaytime);
}

void SpaceShift(int NUM_LEDS, CRGB *leds) {
  // Put Spaceship1 first frame
  for (int passtime = 0; passtime < 4; passtime++) { // Display it 8 times
    Mostra(NUM_LEDS, leds, Spaceship1);
    Mostra(NUM_LEDS, leds, Spaceship2);
  }
}

void Bruxinha(int NUM_LEDS, CRGB *leds) {
  // Put Spaceship1 first frame
  for (int passtime = 0; passtime < 4; passtime++) { // Display it 8 times
    Mostra(NUM_LEDS, leds, Bruxa1);
    Mostra(NUM_LEDS, leds, Bruxa2);
  }
}

void Fantasma(int NUM_LEDS, CRGB *leds) {
  // Put Spaceship1 first frame
  for (int passtime = 0; passtime < 4; passtime++) { // Display it 8 times
    Mostra(NUM_LEDS, leds, Fantasma1);
    Mostra(NUM_LEDS, leds, Fantasma2);
  }
}

void Poke(int NUM_LEDS, CRGB *leds) {
  // Put Spaceship1 first frame
  for (int passtime = 0; passtime < 4; passtime++) { // Display it 8 times
    Mostra(NUM_LEDS, leds, poke1);
    Mostra(NUM_LEDS, leds, poke2);
    Mostra(NUM_LEDS, leds, poke3);
  }
}

void fadeall(int NUM_LEDS, CRGB *leds) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(250);  //SWEEP
  }
}

void Swipe(int NUM_LEDS, CRGB *leds, bool fade = false) { // Swipe effect
  static uint8_t hue = 0;
  //    First slide the led in one direction
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    if (fade) {
      fadeall(NUM_LEDS, leds);
    } else {
      leds[i] = CRGB::Black;
    }
    delay(25);
  }

  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    if (fade) {
      fadeall(NUM_LEDS, leds);
    } else {
      leds[i] = CRGB::Black;
    }
    delay(10);
  }
}

void Bang(int NUM_LEDS, CRGB *leds) {
  // 3 2 1 0 BANG
  for (int passtime = 0; passtime < 1; passtime++) { // Display it 8 times
    Mostra(NUM_LEDS, leds, Number3, 1000);
    Mostra(NUM_LEDS, leds, Number2, 1000);
    Mostra(NUM_LEDS, leds, Number1, 1000);
    Mostra(NUM_LEDS, leds, Number0, 1000);
  }
  // Put Bang0 first frame
  for (int passtime = 0; passtime < 4; passtime++) {
    Mostra(NUM_LEDS, leds, Bang0, 350);
    Mostra(NUM_LEDS, leds, Bang1, 350);
    Mostra(NUM_LEDS, leds, Bang2, 350);
  }
}

void Ztest(int NUM_LEDS, CRGB *leds) {
  for (int passtime = 0; passtime < 1; passtime++) { // Display it 8 times
  Mostra(NUM_LEDS, leds, Z1, 1000);
  Mostra(NUM_LEDS, leds, Z2, 1000);
  Mostra(NUM_LEDS, leds, Z3, 1000);
  Mostra(NUM_LEDS, leds, Z4, 1000);
  Mostra(NUM_LEDS, leds, Z5, 1000);
  }
}



CRGBPalette16 returnPalette(int selPalette) {
  switch (selPalette) {
    case 1:
      return brownGreenPalette;
      break;
    case 2:
      return heatPalette;
      break;
    case 3:
      return purplePalette;
      break;
    case 4:
      return greenbluePalette;
      break;
    case 5:
      return sunsetPalette;
      break;
    case 6:
      return fireandicePalette;
      break;
    case 7:
      return turqPalette;
      break;
    case 8:
      return autumnrosePalette;
      break;
    case 9:
      return bhw1_06Palette;
      break;
    case 10:
      return xmasPalette;
      break;
    case 11:
      return justduckyPalette;
      break;
    default:
      return heatPalette;
      break;
  }
}

void PixelsAleatorios(int NUM_LEDS, CRGB *leds) {
  CRGBPalette16 selPalette = returnPalette(random(1, NUM_PALETTES + 1));
  for (int i = 0; i < 1000; i++) {
    if (i % 5 == 0) {
      leds[random16(0, NUM_LEDS - 1)] = ColorFromPalette(selPalette, random8(), 255, LINEARBLEND);
    }
    fadeToBlackBy(leds, NUM_LEDS, 1);
    FastLED.show();
    delay(10);
  }
}

void PixelsAleatorios2(int NUM_LEDS, CRGB *leds) {
  CRGBPalette16 selPalette = returnPalette(random(1, NUM_PALETTES + 1));
  int pixels[6] = {3, 11, 26, 30, 41, 47}; 
  for (int i = 0; i < 500; i++) {
    if (i % 5 == 0) {
      leds[pixels[random(0, 6)]] = ColorFromPalette(selPalette, random8(), 255, LINEARBLEND);
    }
    // fadeToBlackBy(leds, NUM_LEDS, 1);
    FastLED.show();
    delay(10);
  }
}

void Pinheirinho(int NUM_LEDS, CRGB *leds){
  FastLED.clear(NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = pgm_read_dword(&(pinheirinho[i]));  // Read array from Flash
  }
  FastLED.show();
  delay(50);
  PixelsAleatorios2(NUM_LEDS, leds);
  fadeToBlackBy(leds, NUM_LEDS, 10);
  delay(300);
}