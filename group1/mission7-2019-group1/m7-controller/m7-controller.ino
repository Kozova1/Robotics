#include "TFT9341.h"
#include "touch.h"
#include <SoftwareSerial.h>
SoftwareSerial EEBlue(5, 6);
unsigned int x,y;
byte b=0;
String state;
void setup() {  
  Serial.begin(9600);
  EEBlue.begin(9600);
  lcd.begin();
  lcd.setRotation(2);//0,1,2,3
  
  }//End of setup function

void loop() {

  // Feed any data from bluetooth to Terminal.
  if (EEBlue.available()){
    state=getString();
    //Serial.println(state);
  }
 
  // Feed all data from termial to bluetooth
  if (Serial.available())
    EEBlue.write(Serial.read());
  
  lcd.setColor (BLACK);
  lcd.setFont(6);
  lcd.gotoxy(30,50);
  lcd.print("Cir:");
  lcd.print(state);
  lcd.print("   ");
  b++;
  delay(50);
}

String getString(){ //Strings need to start with $ and end with /
  int failure=0;
  String ans="";
  char c = EEBlue.read();
  while(c!='/'){
    if(isAscii(c))
      ans+=c;
    c = EEBlue.read();
    if(failure>500){
      ans="fail";
      break;
    }
    if(ans[0]!='$'){
      ans="fail";
      break;
    }
    failure++;
  }
  String ans2=ans;
  if(ans[0]=='$')
    ans2=ans.substring(1,ans.length());
  Serial.println(ans2); //debug
  return ans2;
}
