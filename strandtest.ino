#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include "rgb.h"

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_RGB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int color;
int center = 0;
int step = -1;
int maxSteps = 16;
float fadeRate = 0.6;
int diff;

//background color
uint32_t currentBg = random(256);
uint32_t nextBg = currentBg;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {
  //RGB mixColor = { 255 , 255 , 255 };
 //RGB rnd = generateRandomColor(mixColor);
  //colorWipe(strip.Color(random(256), random(256), random(256)), 30); // rand
  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(rnd.r, rnd.g, rnd.b), 50); // rand
  //theaterChaseRainbow(160);
  
  strip.show(); // Initialize all pixels to 'off'
  delay(25);

 //colorWipeTwoColors(strip.Color(255, 0, 0), strip.Color(0, 255, 0), 50);
  //colorWipeTwoColors(strip.Color(0, 0, 255), strip.Color(255, 255, 0), 50);
  for (int i = 0 ; i < 20 ; ++ i)
  {
    rainbow(4);
  }

  for (int i = 0 ; i < 2 ; ++ i) {
    colorWipe(strip.Color(255, 0, 0), 50, false); // Red
    colorWipe(strip.Color(0, 255, 0), 50, true); // Green
    colorWipe(strip.Color(255, 192, 255), 50, false); // orange
    colorWipe(strip.Color(0, 0, 255), 50, true); // Blue
    }


  
  //rainbowCycle(20);
  rainbowCycleBackwards(5);
  rainbowCycleBackwards(5);
  rainbowCycleBackwards(5);
  strip.show(); // Initialize all pixels to 'off'
}

void rainbowCycleBackwards(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=strip.numPixels() - 1; i > 0 ; i--) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

RGB generateRandomColor(RGB mix) {
    int red = random(256);
    int green = random(256);
    int blue = random(256);

    // mix the color

    red = (red + mix.r) / 2;
    green = (green + mix.g) / 2;
    blue = (blue + mix.b) / 2;
    RGB color = { red , green , blue };
    return color;
}

// Fill the dots one after the other with a color
void colorWipeTwoColors(uint32_t color1, uint32_t color2, uint8_t wait) {
    for(uint16_t i=0, j=strip.numPixels()-1; i<strip.numPixels(), j>0; i++, j--) {
      strip.setPixelColor(i, color1);
      strip.setPixelColor(j, color2);
      strip.show();
      delay(wait);
    }
  }



// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait, bool backwards) {
  if (backwards) {
    for(uint16_t i=strip.numPixels()-1; i>0; i--) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
    }
    
  }
  else {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
    }
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j=j+16) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
