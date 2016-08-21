// This #include statement was automatically added by the Spark IDE.
#include "SparkTime.h"
#include "LiquidCrystal.h"
#include "blynk.h"

// Make sure to update these to match how you've wired your pins.
// pinout on LCD [RS, EN, D4, D5, D6, D7];
// pin nums LCD  [ 4,  6, 11, 12, 13, 14];
// Shield Shield [RS, EN, D4, D5, D6, D7];
// Spark Core    [D3, D5, D2, D4, D7, D8];
LiquidCrystal lcd(D0, D1, D2, D3, D4, D5);
char auth[] = "9022e10bd40743a892d1f4d5cece2a60";

UDP UDPClient;
SparkTime rtc;

unsigned long currentTime;
unsigned long lastTime = 0UL;

String timeStr="";
String dateStr="";
String Day;
String Alarm="";

int hourss=0;
int minss=0;
int Alhour=0;
int Almin=0;
int flagy=0;
int Number=5; // Number of seconds of the alaram buzz
int flag=0;

void setup() {
  Blynk.begin(auth);
  rtc.begin(&UDPClient, "north-america.pool.ntp.org");
  rtc.setTimeZone(1); // gmt offset
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  pinMode(A3,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
}

void loop() {
      Blynk.run();

//    Clear the screen before we start
      if (flagy=0){  lcd.clear();flagy=1;}

//    Setting the alarm mode
      if ( (digitalRead(A2))== HIGH){
        if (flag==0){lcd.clear();flag=1;}
        lcd.setCursor(0, 0);
        lcd.print("Alarm                ");

        if (digitalRead(A1)==HIGH){
          if (hourss < 23 )
          {
            hourss++;
            delay(100);
          }
          else { lcd.clear();hourss=0;}
        }

        if (digitalRead(A0)==HIGH){
          if (minss < 59 )
          {
            minss++;
            delay(100);
          }
          else {lcd.clear();minss=0;}
        }
        
        if (digitalRead(A3)==HIGH){lcd.clear();hourss=0;minss=0;delay(100);}

        lcd.setCursor(0, 1);
        lcd.print("      ");
        lcd.setCursor(6, 1);
        lcd.print(hourss);
        lcd.setCursor(8, 1);
        lcd.print(":");
        lcd.setCursor(9, 1);
        lcd.print(minss);
        lcd.setCursor(11, 1);
        lcd.print("     ");
      }
//    Displaying the time mode
      else {
        if (flag==1){lcd.clear();flag=0;}
        currentTime = rtc.now();
        timeStr = "";
        timeStr += rtc.hour12String(currentTime);
        timeStr += ":";
        timeStr += rtc.minuteString(currentTime);
        //Serial.println(timeStr);
        dateStr = "";
        dateStr += rtc.day(currentTime);
        dateStr += " ";
        dateStr += rtc.monthNameString(currentTime);
        //Serial.println(dateStr);
        Day="";
        Day+=rtc.dayOfWeekString(currentTime);

        lcd.setCursor(0, 1);
        lcd.print(Day);
        lcd.setCursor(11, 1);
        lcd.print(timeStr);
        lcd.setCursor(0, 0);
        lcd.print(dateStr);
      }
      Serial.println(rtc.hour(currentTime));
      Serial.println(rtc.minute(currentTime));


    //  if (Alarm == timeStr){
        if ( (rtc.hour(currentTime)==hourss) && (rtc.minute(currentTime)==minss) ){
        int i;
          for(i=0;i<255*Number;i++) // output sound of one frequency
          {
            digitalWrite(D6,HIGH);// Buzz sound
            delay(1);//delay 1ms
            digitalWrite(D6,LOW);// silent
            delay(1);//delay 1ms
          }
        flag=1;
        digitalWrite(D6,LOW);// silent

    }
}
