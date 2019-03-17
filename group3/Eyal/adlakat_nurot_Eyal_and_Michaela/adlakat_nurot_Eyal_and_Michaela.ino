

 #include <Adafruit_NeoPixel.h>
 #define PIN A0
 #define NEOPIXELS 16
 #define echoPin 3
 #define distance

 Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NEOPIXELS, PIN, NEO_RGB + NEO_KHZ800);
 void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
}


void loop(){
 

word readUS(){
  word duration, distance, echoPin;
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58;
  return distance;

  
   if (distance<100) {
  pixels.begin ();
  pixels.setPixelColor(0, 0,255,0);
  pixels.setPixelColor(4, 0,255,0);
  pixels.setPixelColor(8, 0,255,0);
  pixels.setPixelColor(12, 0,255,0);
  
  else if (distance>100 && distance<=200) {
  pixels.begin ();
  pixels.setPixelColor(0, 255,0,0);
  pixels.setPixelColor(4, 255,0,0);
  pixels.setPixelColor(8, 255,0,0);
  pixels.setPixelColor(12, 255,0,0);
  pixels.setPixelColor(1, 255,0,0);
  pixels.setPixelColor(5, 255,0,0);
  pixels.setPixelColor(9, 255,0,0);
  pixels.setPixelColor(13, 255,0,0);
  
    else if (distance>200 && distance<300) {
      pixels.begin ();
  pixels.setPixelColor(0, 0,0,255);
  pixels.setPixelColor(4, 0,0,255);
  pixels.setPixelColor(8, 0,0,255);
  pixels.setPixelColor(12, 0,0,255);
  pixels.setPixelColor(1, 0,0,255);
  pixels.setPixelColor(5, 0,0,255);
  pixels.setPixelColor(9, 0,0,255);
  pixels.setPixelColor(13, 0,0,255);
  pixels.setPixelColor(2, 0,0,255);
  pixels.setPixelColor(6, 0,0,255);
  pixels.setPixelColor(10, 0,0,255);
  pixels.setPixelColor(14, 0,0,255);
 
  else if (distance>300){
    pixels.begin ();
  pixels.setPixelColor(0, 60,255,5);
  pixels.setPixelColor(4, 60,255,5);
  pixels.setPixelColor(8, 60,255,5);
  pixels.setPixelColor(12, 60,255,5);
  pixels.setPixelColor(1, 60,255,5);
  pixels.setPixelColor(5, 60,255,5);
  pixels.setPixelColor(9, 60,255,5);
  pixels.setPixelColor(13, 60,255,5);
  pixels.setPixelColor(2, 60,255,5);
  pixels.setPixelColor(6, 60,255,5);
  pixels.setPixelColor(10, 60,255,5);
  pixels.setPixelColor(14, 60,255,5);
  pixels.setPixelColor(3, 60,255,5);
  pixels.setPixelColor(7, 60,255,5);
  pixels.setPixelColor(11, 60,255,5);
  pixels.setPixelColor(15, 60,255,5);
  pixels.show();
   Serial.print("Distance = ");
  Serial.println(readUS());
  delay(50);
}
  }
  }
   }
}
