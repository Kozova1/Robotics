#include <Adafruit_NeoPixel.h>

const int echoPin = A0;
// defines variables
long duration;
int distance;

#define PIN            3      //A1
#define NUMPIXELS      16
#define REVERSED       true   //From wires = false  =[0,1,2,3], from end = true    =[3,2,1,0]

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

byte flag=0;

void setup() {
//pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
pixels.begin();
}
void loop() {

duration = pulseIn(echoPin, HIGH);
delay(100);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

//light(1,255,0,0);

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
