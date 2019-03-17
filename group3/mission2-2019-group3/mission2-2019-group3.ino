#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_NeoPixel.h>

#define PIN A0
#define NEOPIXELS 16

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NEOPIXELS, PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  pixels.begin ();

}

void loop() {
  uint16_t clear, red, green, blue;
  
  tcs.getRawData(&red, &green, &blue, &clear);
  
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.println(blue);

  if(clear>400){
    pixels.clear();
    for(int i=12; i<16; i++){
      pixels.setPixelColor(i, 255,255,255);
    }
    pixels.show();
  }else if(red>green && red>blue){
    pixels.clear();
    for(int i=0; i<4; i++){
      pixels.setPixelColor(i, 0,255,0);
    }
    pixels.show();
  }else if(green>red && green>blue){
    pixels.clear();
    for(int i=4; i<8; i++){
      pixels.setPixelColor(i, 255,0,0);
    }
    pixels.show();
  }else if(blue>red && blue>green){
    pixels.clear();
    for(int i=8; i<12; i++){
      pixels.setPixelColor(i, 0,0,255);
    }
    pixels.show();
  }
}
