#include "TFT9341.h"
#include "touch.h"
#include <SoftwareSerial.h>
SoftwareSerial EEBlue(5, 6);
unsigned int x,y;
byte b=0;
String state;
String colur;
int tt;
void setup() {  
  Serial.begin(9600);
  EEBlue.begin(9600);
  lcd.begin();
  lcdtouch.begin();
  lcd.setRotation(2);//0,1,2,3
  lcdtouch.InitTypeTouch(2);
  lcd.fillRoundRect (10,140,90, 90, 10 ,RED);
  lcd.fillRoundRect (215,140,90, 90, 10 ,GREEN);
  lcd.setFont(6);
  lcd.gotoxy(30,50);
  lcd.setColor (BLACK);
  lcd.print("select:");
  }//End of setup function

void loop() {

  // Feed any data from bluetooth to Terminal.
  if (EEBlue.available()){
    state=getString();
    //Serial.println(state);
  }

  int t = readTouch();
  Serial.println(tt);
  if(t==1 || t==2)
    tt=t;
  EEBlue.print(tt);
  // Feed all data from termial to bluetooth
  //if (Serial.available())
    //EEBlue.write(Serial.read());
  if(tt==1){
    lcd.setColor (BLACK);
    lcd.setFont(6);
    lcd.gotoxy(30,50);
    lcd.print("Dis:");
    lcd.print(state);
    lcd.print("      ");
    b++;
    delay(50);
  }else 
  if(tt==2){
    switch((int)(state.charAt(0))){
      case 48:
        colur="white";
        break;
      case 49:
        colur="red";
        break;
      case 50:
        colur="blue";
        break;
      case 51:
        colur="green";
        break;
      default:
        colur="fail";
        break;
    }
    lcd.setColor (BLACK);
    lcd.setFont(5);
    lcd.gotoxy(30,50);
    lcd.print("Col:");
    lcd.print(colur);
    lcd.print("      ");
    b++;
  }
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
  //Serial.println(ans2); //debug
  return ans2;
}

int readTouch(){
  delay(10);
  lcdtouch.readxy();
  x = lcdtouch.readx();
  y = lcdtouch.ready();
  if(x > 10 && x<10+90 && y> 140 && y< 140+90){
       lcd.gotoxy(120,20);
       return 1;
      }
  else if(x > 215 && x<215+90 && y> 140 && y< 140+90){
       lcd.gotoxy(120,20);
       return 2;
  }
  return 0;
}
