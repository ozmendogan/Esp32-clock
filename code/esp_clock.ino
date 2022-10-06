 
#include <ESP32Time.h>
#include <string.h>

ESP32Time rtc(3600);

//Sleep mode external pin
volatile byte ext_Sleep_Pin = 33;
volatile byte battery_Pin = 26;
volatile int battery_Volt = 1800;

//clock
volatile byte Sec[] = {15, 16, 21, 25 , 13};
volatile byte Hour = 4;
volatile bool step = false;
volatile byte Common[] = {12, 19 , 23 , 17, 18, 14};
String input_string = "";
volatile byte Ss = 0;
volatile byte Mm = 0;
volatile byte Hh = 0;

//alarm
volatile byte HoursClock = 7;
volatile byte MinutesClock = 30 ;
volatile bool alarmState = true ;
volatile byte s = 0;

//music
volatile byte buzzerPin = 27;
volatile byte notaSayisi = 8;
volatile int kdo = 262;
volatile int re = 294;
volatile int mi = 330;
volatile int fa = 349;
volatile int sol = 392;
volatile int la = 440;
volatile int si = 494;
volatile int ido = 523;

void setup() {
  
  Serial.begin(115200);
  
   
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1);
  
  
  pinMode(battery_Pin,INPUT);
  pinMode(ext_Sleep_Pin,INPUT);
  for (int i=0; i<5; i++){
        pinMode(Sec[i], INPUT);
        
    }
    pinMode(Hour, INPUT);
    for (int i=0; i<6; i++){
        pinMode(Common[i], INPUT);
    }

    
}
 void loop(){

   battery_Volt = analogRead(battery_Pin);
   Serial.println(battery_Volt);
   if(battery_Volt<1600){
      esp_deep_sleep_start();
    } 
   
   int Hours   = rtc.getHour();
   int Seconds = rtc.getSecond();
   int  Minutes= rtc.getMinute();
   
   Clock_Leds(Hours, Seconds);
   //Serial.println(Hours);
   //Serial.println(Minutes);
   
   //Serial.println("****************************************");
   //Serial.println(HoursClock);
   //Serial.println(MinutesClock);
   
   if(Hours== HoursClock && Minutes==MinutesClock && alarmState == true ){
      ibo();
    
    }

   if(Serial.available() > 0){
                char c = Serial.read();
                if (c == '\n') { 
                    Command();
                    input_string = "";
                }
                else if (c == '/')
                { 
                    Command();
                    input_string = "";
                }
                else
                {
                    input_string += c;
                }
            }
   
}

void Command(){
  
  int s1, s2, s3;
    char StringBuffer[13];
    Serial.println("");
    
    
    // TIME:12:6:0
    if (input_string.startsWith("TIME:") == true)       
    {
        input_string.replace("TIME:", "");    
        input_string.toCharArray(StringBuffer,13);
        s1=atoi(strtok(StringBuffer,":"));
        s2=atoi(strtok(NULL,":"));
        s3=atoi(strtok(NULL,":"));
        rtc.setTime(s3, s2, s1-1 ,17,1,2042);
        
        Serial.println("Ok");
        Serial.println("Time set to: ");
        Serial.println(rtc.getTime());
        
    }
    
    // ALARMSET:7:30:0
    else if (input_string.startsWith("ALARMSET:") == true)
    {
        input_string.replace("ALARMSET:", "");    
        input_string.toCharArray(StringBuffer,13);
        s1=atoi(strtok(StringBuffer,":"));
        s2=atoi(strtok(NULL,":"));
        s3=atoi(strtok(NULL,":"));

        HoursClock = s1;
        MinutesClock = s2;
        
        
    }
    
    // ALARMON
    else if (input_string.startsWith("ALARMON") == true)     
    {
        alarmState = false ;
        Serial.println ("Alarm is On.");
       
    }
    else
    {
      Serial.println("nott");
      }
  
  
  
  }



int Clock_Leds(int Hours , int Seconds)
{

    if (Seconds == 0){
        Ss = 60;
    }else{
        Ss = Seconds;
    }
    if (Hours == 0){
        Hh = 12;
    }
    else{
        Hh = Hours;
    }


  step = false;
    for(int i = 0; i<Ss; i++){
        s = i/12;
        LedsOff();
        pinMode(Sec[s], OUTPUT);
        pinMode(Common[((i-(s*12))/2)], OUTPUT);            
        if (!step){
            digitalWrite(Sec[s], LOW);
            digitalWrite(Common[((i-(s*12))/2)], HIGH);
        }else{
            digitalWrite(Sec[s], HIGH);
            digitalWrite(Common[((i-(s*12))/2)], LOW);
        }
        step = !step;
        delayMicroseconds(100);
    }

  step = false;
    for(int i = 0; i<Hh; i++){
        LedsOff();
        pinMode(Hour, OUTPUT);
        pinMode(Common[i/2], OUTPUT);   
        if (!step){
            digitalWrite(Hour, LOW);
            digitalWrite(Common[i/2], HIGH);
        }else{
            digitalWrite(Hour, HIGH);
            digitalWrite(Common[i/2], LOW);
        }
        step = !step;
        delayMicroseconds(100);
        
    }
  
  }

void LedsOff(){

    pinMode(Common[5], INPUT);
    pinMode(Hour, INPUT);
    for(int i = 0; i<5; i++){        
        pinMode(Sec[i], INPUT);
        pinMode(Common[i], INPUT);
    }
}


void ibo(){

    blinkLed1();
    tone(buzzerPin, mi);
    delay(1000);
    blinkLed2();
    noTone(buzzerPin);
    delay(140);
    blinkLed1();
    tone(buzzerPin, mi);
    delay(233);
    blinkLed2();
    noTone(buzzerPin);
    delay(140);
    blinkLed1();
    tone(buzzerPin, sol);
    delay(248);
    blinkLed2();
    noTone(buzzerPin);
    delay(140);  
    tone(buzzerPin, si);
    blinkLed1();
    delay(270);
    blinkLed2();
    noTone(buzzerPin);
    delay(120);  
    tone(buzzerPin, sol);
    blinkLed1();
    delay(250);
    noTone(buzzerPin);
    delay(180);  
    tone(buzzerPin, la);
    blinkLed2();
    delay(690);
    blinkLed1();
    noTone(buzzerPin);
    delay(30);
    blinkLed2();  
    tone(buzzerPin, si);
    delay(200);
    blinkLed1();
    noTone(buzzerPin);
    delay(500); 
    blinkLed2();      
    tone(buzzerPin, mi);
    delay(230);
    blinkLed1();
    noTone(buzzerPin);
    delay(190);
    blinkLed2();  
    tone(buzzerPin, sol);
    delay(130);
    blinkLed1();
    noTone(buzzerPin);
    delay(220); 
    blinkLed2(); 
    tone(buzzerPin, si);
    delay(230);
    blinkLed1();
    noTone(buzzerPin);
    delay(135);
    blinkLed2();  
    tone(buzzerPin, sol);
    delay(238);
    blinkLed1();
    noTone(buzzerPin);
    delay(125);
    blinkLed2();  
    tone(buzzerPin, la);
    delay(340);
    blinkLed1();
    noTone(buzzerPin);
    delay(10);
    blinkLed2();  
    tone(buzzerPin, si);
    delay(396);
    blinkLed1();
    noTone(buzzerPin);
    delay(10);
    blinkLed2();  
    tone(buzzerPin, sol);
    delay(144);
    blinkLed1();
    noTone(buzzerPin);
    delay(34);
    blinkLed2();  
    tone(buzzerPin, fa);
    delay(146);
    blinkLed1();
    noTone(buzzerPin);
    delay(20);
    blinkLed2();  
    tone(buzzerPin, mi);
    delay(225);
    blinkLed1();
    noTone(buzzerPin);
    delay(145);
    blinkLed2();  
    tone(buzzerPin, mi);
    delay(233);
    blinkLed1();
    noTone(buzzerPin);
    delay(140);
    blinkLed2();      
    tone(buzzerPin, sol);
    delay(248);
    blinkLed1();
    noTone(buzzerPin);
    delay(140);
    blinkLed2();     
    tone(buzzerPin, si);
    delay(270);
    blinkLed1();
    noTone(buzzerPin);
    delay(120);
    blinkLed2();  
    tone(buzzerPin, sol);
    delay(250);
    blinkLed1();
    noTone(buzzerPin);
    delay(180);
    blinkLed2();  
    tone(buzzerPin, la);
    delay(690);
    blinkLed1();
    noTone(buzzerPin);
    delay(30);
    blinkLed2();  
    tone(buzzerPin, si);
    delay(200);
    blinkLed1();
    noTone(buzzerPin);
    delay(500);
    blinkLed2();  
    tone(buzzerPin, mi);
    delay(230);
    blinkLed1();
    noTone(buzzerPin);
    delay(190);
    blinkLed2();  
    tone(buzzerPin, sol);
    delay(130);
    blinkLed1();
    noTone(buzzerPin);
    delay(220);
    blinkLed2();  
    tone(buzzerPin, si);
    delay(230);
    blinkLed1();
    noTone(buzzerPin);
    delay(135);
    blinkLed2();  
    tone(buzzerPin, sol);
    delay(238);
    blinkLed1();
    noTone(buzzerPin);
    delay(125);
    blinkLed2();  
    tone(buzzerPin, la);
    delay(340);
    blinkLed1();
    noTone(buzzerPin);
    delay(10);
    blinkLed2();  
    tone(buzzerPin, si);
    delay(396);
    blinkLed1();
    noTone(buzzerPin);
    delay(10);
    blinkLed2();  
    tone(buzzerPin, sol);
    delay(144);
    blinkLed1();
    noTone(buzzerPin);
    delay(34);
    blinkLed2();  
    tone(buzzerPin, fa);
    delay(146);
    blinkLed1();
    noTone(buzzerPin);
    delay(20);
    blinkLed2();  
    tone(buzzerPin, mi);
    delay(225);
    blinkLed1();
    noTone(buzzerPin);
    delay(420);
    blinkLed2(); 
    tone(buzzerPin, mi);
    delay(670);
    blinkLed1();
    noTone(buzzerPin);
    delay(15);
    blinkLed2();  
    tone(buzzerPin, la);
    delay(460);
    blinkLed1();
    noTone(buzzerPin);
    delay(25);
    blinkLed2();  
    tone(buzzerPin, sol);
    delay(636);
    blinkLed1();
    noTone(buzzerPin);
    delay(50);
    blinkLed2();  
    tone(buzzerPin, fa);
    delay(573);
    blinkLed1();
    noTone(buzzerPin);
    delay(158);
    blinkLed2();  
    tone(buzzerPin, fa);
    delay(1080);
    blinkLed1();
    noTone(buzzerPin);
    delay(20);
    blinkLed2();  
    tone(buzzerPin, si);
    delay(410);
    blinkLed1();
    noTone(buzzerPin);
    delay(60);
    blinkLed2();   
    tone(buzzerPin, la);
    delay(563);
    blinkLed1();
    noTone(buzzerPin);
    delay(40);
    blinkLed2();  
    tone(buzzerPin, sol);
    delay(385);
    blinkLed1();
    noTone(buzzerPin);
    delay(336);
    blinkLed2();  
    tone(buzzerPin, si);
    delay(896);
    blinkLed1();
    noTone(buzzerPin);
    delay(50);
    blinkLed2();  
    tone(buzzerPin, si);
    delay(147);
    blinkLed1();
    noTone(buzzerPin);
    delay(55);
    blinkLed2();  
    tone(buzzerPin, la);
    delay(112);
    blinkLed1();
    noTone(buzzerPin);
    delay(75);
    blinkLed2();  
    tone(buzzerPin, la);
    delay(934);
    blinkLed1();
    noTone(buzzerPin);
    delay(87);
    blinkLed2();   
    tone(buzzerPin, la);
    delay(169);
    blinkLed1();
    noTone(buzzerPin);
    delay(66);
    blinkLed2();  
    tone(buzzerPin, sol);
    delay(164);
    blinkLed1();
    noTone(buzzerPin);
    delay(60);
    blinkLed2();  
    tone(buzzerPin, si);
    delay(724);
    blinkLed1();
    noTone(buzzerPin);
    delay(82);
    blinkLed2();  
    tone(buzzerPin, si);
    delay(156);
    blinkLed1();
    noTone(buzzerPin);
    delay(49);
    blinkLed2();  
    tone(buzzerPin, la);
    delay(126);
    blinkLed1();
    noTone(buzzerPin);
    delay(60);
    blinkLed2();  
    tone(buzzerPin, la);
    delay(705);
    blinkLed1();
    noTone(buzzerPin);
    delay(257);
    blinkLed2();  
    tone(buzzerPin, la);
    delay(142);
    blinkLed1();
    noTone(buzzerPin);
    delay(68);
    blinkLed2();  
    tone(buzzerPin, sol);
    delay(106);
    blinkLed1();
    noTone(buzzerPin);
    delay(79);
    blinkLed2();  
    tone(buzzerPin, sol);
    delay(874);
    blinkLed1();
    noTone(buzzerPin);
    delay(25);
    blinkLed2();  
    tone(buzzerPin, la);
    delay(309);
    blinkLed1();
    noTone(buzzerPin);
    delay(46);
    blinkLed2();  
    tone(buzzerPin, fa);
    delay(642);
    blinkLed1();
    noTone(buzzerPin);
    delay(25);
    blinkLed2();  
    tone(buzzerPin, mi);
    delay(285);
    blinkLed1();
    noTone(buzzerPin);
    delay(431);
    blinkLed2();
    tone(buzzerPin, mi);
    delay(670);
    blinkLed1();
    noTone(buzzerPin);
    delay(15);
    blinkLed2();  
    tone(buzzerPin, la);
    delay(460);
    blinkLed1();
    noTone(buzzerPin);
    delay(25);
    blinkLed2();  
    tone(buzzerPin, sol);
    delay(636);
    blinkLed1();
    noTone(buzzerPin);
    delay(50);
    blinkLed2();  
    tone(buzzerPin, fa);
    delay(573);
    blinkLed1();
    noTone(buzzerPin);
    delay(158);
    blinkLed2();  
    tone(buzzerPin, fa);
    delay(1080);
    blinkLed1();
    noTone(buzzerPin);
    delay(20);
    blinkLed2();  
    tone(buzzerPin, si);
    delay(410);
    blinkLed1();
    noTone(buzzerPin);
    delay(60);
    blinkLed2();  
    tone(buzzerPin, la);
    delay(563);
    blinkLed1();
    noTone(buzzerPin);
    delay(40);
    blinkLed2();  
    tone(buzzerPin, sol);
    delay(385);
    blinkLed1();
    noTone(buzzerPin);
    delay(336);
    blinkLed2();
     
    tone(buzzerPin, si);
    delay(336);
    noTone(buzzerPin);
    pinMode(27,OUTPUT);      //OFF THE ALARM PIN
    digitalWrite(27,LOW);
    
    LedsOff();

  }

void tone(byte pin, int freq) {
  ledcSetup(0, 2200 , 8); // setup beeper
  ledcAttachPin(pin, 0); // attach beeper
  ledcWriteTone(0, freq); // play tone
  buzzerPin = pin; // store pin
}
void noTone(byte buzzerPin) {
  tone(buzzerPin, 0);
}

void blinkLed2(){
  for (int i=0; i<5; i++){
        pinMode(Sec[i], OUTPUT);
        
    }
    pinMode(Hour, OUTPUT);
    for (int i=0; i<6; i++){
        pinMode(Common[i], OUTPUT);
    }

  digitalWrite(15,LOW);
  digitalWrite(16,LOW);
  digitalWrite(21,LOW);
  digitalWrite(25,LOW);
  digitalWrite(13,LOW);
  
  digitalWrite(4,LOW);
  
  digitalWrite(12,HIGH);
  digitalWrite(19,HIGH);
  digitalWrite(23,HIGH);
  digitalWrite(17,HIGH);
  digitalWrite(18,HIGH);
  digitalWrite(14,HIGH);
  
  
  }


void blinkLed1(){
  for (int i=0; i<5; i++){
        pinMode(Sec[i], OUTPUT);
        
    }
    pinMode(Hour, OUTPUT);
    for (int i=0; i<6; i++){
        pinMode(Common[i], OUTPUT);
    }

  digitalWrite(15,HIGH);
  digitalWrite(16,HIGH);
  digitalWrite(21,HIGH);
  digitalWrite(25,HIGH);
  digitalWrite(13,HIGH);
  
  digitalWrite(4,HIGH);
  
  digitalWrite(12,LOW);
  digitalWrite(19,LOW);
  digitalWrite(23,LOW);
  digitalWrite(17,LOW);
  digitalWrite(18,LOW);
  digitalWrite(14,LOW);
 
  }
  
