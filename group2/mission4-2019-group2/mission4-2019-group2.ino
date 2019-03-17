#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_NeoPixel.h>

#define PIN A0
#define NUMPIXELS 16

#define TIMESTEP 0.01;

MPU6050 gyro_sensor;

// Timers
unsigned long timer = 0;


// Spin
float roll = 0;
float prev_roll=0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

void setup () {
  
  Serial.begin (115200);

  // Initialize MPU6050
  while (!gyro_sensor.begin (MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {
    Serial.println ("Could not find a valid MPU6050 sensor, check wiring!");
    delay (500);

  }

  pixels.begin ();
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  gyro_sensor.calibrateGyro ();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  gyro_sensor.setThreshold (3);
}

void loop (){
  
  timer = millis ();

  // Read normalized values
  Vector norm = gyro_sensor.readNormalizeGyro ();

  // Calculate Roll
  roll = roll + norm.XAxis * TIMESTEP;

  Serial.print (" spin = ");
  Serial.println (roll);  


  if (roll == prev_roll) {
    Serial.println ("no rot");
    light (4,0,0,0);

  } else if (roll < prev_roll) {
    Serial.println ("cw rot");
    light (4,0,0,255);

  } else if (roll > prev_roll) {
    Serial.println ("ccw rot");
    light (4,0,255,0);

  }
  
  
  prev_roll=roll;
  // Wait to full TIMESTEP period
  //delay((TIMESTEP*1000) - (millis() - timer));
  delay (10);
}
