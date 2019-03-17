#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

SoftwareSerial EEBlue(8, 9);

const int echoPin = A0;
// defines variables
long duration;
int distance;
int lastDis=19;

#define PIN            3      //A1
#define NUMPIXELS      16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

byte flag=0;

void setup() {
//pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
pixels.begin();
EEBlue.begin(9600);
}
void loop() {
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
