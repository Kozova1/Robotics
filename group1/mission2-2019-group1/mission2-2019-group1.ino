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

  if(closeBytes(18,red,green,blue)){
    wingLight(3,128,128,128);
    Serial.println("white");
  }else
  if(red>blue && red>green){
    wingLight(0,128,0,0);
    Serial.println("red");
  }else
  if(blue>red && blue>green){
    wingLight(1,0,0,128);
    Serial.println("blue");
  }else
  if(green>blue && green>red){
    wingLight(2,0,128,0);
    Serial.println("green");
  }
  
  
}
