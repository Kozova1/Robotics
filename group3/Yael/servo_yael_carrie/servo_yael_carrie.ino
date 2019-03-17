/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo; 
int pos = 0;  

void setup() {
  myservo.attach(8); 
  pinMode (9, OUTPUT);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { 
    myservo.write(pos);              
    delay(50);
    if (pos >= 45 && pos <=80) {
       digitalWrite(9, HIGH);
       
    } else {
      digitalWrite(9, LOW);
      }
                           
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);             
    delay(50);  
     if ( pos <= 80 && pos >=45) {
       digitalWrite(9, HIGH);                   
  } else {
    digitalWrite(9, LOW);
    }
}
}
