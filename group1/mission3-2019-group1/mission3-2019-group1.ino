#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_NeoPixel.h>

#define PIN A0
#define NEOPIXELS 16

MPU6050 mpu;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NEOPIXELS, PIN, NEO_RGB + NEO_KHZ800);

void setup() 
{
  Serial.begin(115200);

  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  pixels.begin ();
  // If you want, you can set accelerometer offsets
  // mpu.setAccelOffsetX();
  // mpu.setAccelOffsetY();
  // mpu.setAccelOffsetZ();
  
  checkSettings();
}

void checkSettings()
{
  Serial.println();
  
  Serial.print(" * Sleep Mode:            ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Clock Source:          ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Accelerometer:         ");
  switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }  

  Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());
  
  Serial.println();
}

void loop()
{
  Vector normAccel = mpu.readNormalizeAccel();

  double pitch2=normAccel.YAxis;
  double roll2=normAccel.ZAxis;

  double pitch=map(pitch2, -10.5,10.5,-90,90);
  double roll=map(roll2, -10.5,10.5,-90,90);
  
  Serial.print("pitch= ");
  Serial.print(pitch);
  Serial.print(" roll= ");
  Serial.println(roll);

  Serial.println(sqrt(((double)pitch*(double)pitch)+((double)roll*(double)roll)));
  
  if(sqrt(((double)pitch*(double)pitch)+((double)roll*(double)roll))>21.21){
    if(pitch>0 && roll>0){
      wingLight(2,255,0,0);
    }else if(pitch<0 && roll>0){
      wingLight(3,255,0,0);
    }else if(pitch>0 && roll<0){
      wingLight(1,255,0,0);
    }else if(pitch<0 && roll<0){
      wingLight(0,255,0,0);
    }
  }else{
    pixels.clear();
    pixels.show();
  }
  delay(100);
}
