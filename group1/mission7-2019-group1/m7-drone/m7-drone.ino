#include <SoftwareSerial.h>
#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_NeoPixel.h>

#define PIN A0
#define NUMPIXELS 16

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.3;

// Spin
float roll = 0;
float lastRoll=0;
int rollnum=0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
SoftwareSerial EEBlue(8, 9);

void setup() 
{
  Serial.begin(115200);
  EEBlue.begin(9600);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  pixels.begin ();
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);
}

void loop()
{
  timer = millis();

  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Roll
  roll = roll + norm.XAxis * timeStep;

  Serial.print(" spin = ");
  Serial.println(roll);  

  rollnum=(roll/360);

  Serial.print(" rollnum = ");
  Serial.println(rollnum);

  EEBlue.print("$");
  EEBlue.print(rollnum);
  EEBlue.print("/");

  /*
  if(roll==lastRoll){
    Serial.println("0");
    light(4,0,0,0);
  }else if(roll<lastRoll){
    Serial.println("1");
    light(4,0,0,255);
  }else if(roll>lastRoll){
    Serial.println("2");
    light(4,0,255,0);
  }
  */

  if(abs(rollnum)==1){
    light(1,0,255,0);
  }else if(abs(rollnum)==2){
    light(2,0,0,255);
  }else if(abs(rollnum)==3){
    light(3,255,0,0);
  }else if(abs(rollnum)==4){
    light(4,255,255,255);
  }else{
    light(4,0,0,0);
  }
  
  
  lastRoll=roll;
  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));
  //delay(100);
}
