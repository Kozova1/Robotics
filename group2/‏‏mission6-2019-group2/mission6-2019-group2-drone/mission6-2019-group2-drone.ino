#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include "Adafruit_TCS34725.h"

SoftwareSerial EEBlue(8, 9);

const int echoPin = A0;
// defines variables
long duration;
int distance;
int lastDis=19;
char state;

#define PIN            3      //A1
#define NUMPIXELS      16

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

byte flag=0;

void setup() {
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(9600); // Starts the serial communication
  pixels.begin();

  EEBlue.begin(9600);
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
}
void loop() {
  if (EEBlue.available()){
    state=EEBlue.read();
  }
  if(state=='1'){
    dis();
  }
  else if(state=='2'){
    col();
  }
}

void dis(){
  duration = pulseIn(echoPin, HIGH);
  delay(300);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  
  if(abs(lastDis-distance)>200){
    Serial.println(distance);
    distance=lastDis;
  }
  
  Serial.print("Distance: ");
  Serial.println(distance);
  
  EEBlue.print("$");
  EEBlue.print(distance);
  EEBlue.print("/");
  
  lastDis=distance;
  //light
  
  if(distance<100 && flag!=1){
    light(1,125,0,0);
    flag=1;
  }
  else if(distance<200 && distance>=100 && flag!=2){
    light(2,0,125,0);
    flag=2;
  }
  else if(distance<300 && distance>=200 && flag!=3){
    light(3,0,0,125);
    flag=3;
  }
  else if(distance>=300 && flag!=4){
    light(4,125,32,0);
    flag=4;
  }
}

void col(){
  flag=0;
  
  uint16_t clear, red, green, blue;
  
  tcs.getRawData(&red, &green, &blue, &clear);
  
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.println(blue);

  if(closeBytes(18,red,green,blue)){
    light(3,128,128,128);
    Serial.println("white");
    EEBlue.print("$");
    EEBlue.print("0");
    EEBlue.print("/");
  }else
  if(red>blue && red>green){
    light(0,128,0,0);
    Serial.println("red");
    EEBlue.print("$");
    EEBlue.print("1");
    EEBlue.print("/");
  }else
  if(blue>red && blue>green){
    light(1,0,0,128);
    Serial.println("blue");
    EEBlue.print("$");
    EEBlue.print("2");
    EEBlue.print("/");
  }else
  if(green>blue && green>red){
    light(2,0,128,0);
    Serial.println("green");
    EEBlue.print("$");
    EEBlue.print("3");
    EEBlue.print("/");
  }
}
