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
    pixels.setPixelColor(12, 255,255,255);
    pixels.setPixelColor(13, 255,255,255);
    pixels.setPixelColor(14, 255,255,255);
    pixels.setPixelColor(15, 255,255,255);
  }else if(red>green && red>blue){
    pixels.clear();
    pixels.setPixelColor(0, 0,255,0);
    pixels.setPixelColor(1, 0,255,0);
    pixels.setPixelColor(2, 0,255,0);
    pixels.setPixelColor(3, 0,255,0);
  }else if(green>red && green>blue){
    pixels.clear();
    pixels.setPixelColor(4, 255,0,0);
    pixels.setPixelColor(5, 255,0,0);
    pixels.setPixelColor(6, 255,0,0);
    pixels.setPixelColor(7, 255,0,0);
  }else if(blue>red && blue>green){
    pixels.clear();
    pixels.setPixelColor(8, 0,0,255);
    pixels.setPixelColor(9, 0,0,255);
    pixels.setPixelColor(10, 0,0,255);
    pixels.setPixelColor(11, 0,0,255);
  }
  pixels.show();
}
