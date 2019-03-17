#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_NeoPixel.h>

#define PIN A0
#define NUMPIXELS 16

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Spin
float roll = 0;
float lastRoll=0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

void setup() 
{
  Serial.begin(115200);

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
  
  
  lastRoll=roll;
  // Wait to full timeStep period
  //delay((timeStep*1000) - (millis() - timer));
  delay(10);
}
