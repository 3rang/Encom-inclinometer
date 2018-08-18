/*
///////////////////////////////////////////////////////////////////
// FrieedBOX @ 2016-17 Copyright recieved
// Auther:-          Tarang Patel
// File:-            Encom.c
// Purpose:-         Inclination Meter
// For :-            MAIT HR 180 Pilling Machine
//////////////////////////////////////////////////////////////////
*/
#include <AcceleroMMA7361.h>
#include "FastLED.h"
#include <Wire.h>
#include <SoftwareSerial.h>

#define NUM_LEDS 8  // Number of LEDs per Stick
#define DATA_PIN_Xp 3  // Pin 2 connected to RGB X
#define DATA_PIN_Xn 5  //
#define DATA_PIN_Yp 4  // Pin 3 connected to RGB Y
#define DATA_PIN_Yn 6

CRGB leds_Xp[NUM_LEDS];
CRGB leds_Xn[NUM_LEDS];
CRGB leds_Yp[NUM_LEDS];
CRGB leds_Yn[NUM_LEDS];
SoftwareSerial mySerial(3,2); // pin 2 = TX, pin 3 = RX (unused)
AcceleroMMA7361 accelero;
/*
char x1[5];
char y1[5];
char *p="Booting Process...";
char *m="      Welcome";
*/
int x;
int y;
int z;
int fXg = 470;
int fYg = 370;
//double fZg = 512;
const float alpha = 0.26;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  mySerial.begin(9600); 
  FastLED.addLeds<NEOPIXEL,DATA_PIN_Xp>(leds_Xp, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,DATA_PIN_Xn>(leds_Xn, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,DATA_PIN_Yp>(leds_Yp, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,DATA_PIN_Yn>(leds_Yn, NUM_LEDS);
  accelero.begin(13, 12, 11, 10, A0, A1, A2);
  accelero.setARefVoltage(3.3);                   //sets the AREF voltage to 3.3V
  accelero.setSensitivity(LOW);                   //sets the sensitivity to +/-6G
  //accelero.calibrate();
  delay(500); // wait for display to boot up
  //mySerial.write(25); // cursor to beginning of first lin
  mySerial.write(22);
  mySerial.write(12);
  //char x1[5];
  //char y1[5];
  char *p="Booting Process...";
  char *m="      Welcome";

  delay(100);
  while(*p)
  {
  mySerial.write(*p);
  p++;
  }
  delay(2000);
  mySerial.write(22);
  mySerial.write(12);
  while(*m)
  {
  mySerial.write(*m);
  m++;
  }
  delay(1000);
  mySerial.write(22);
  mySerial.write(12);
  delay(500);
  mySerial.write("    FriedBOX");
}
  void loop()
{ 
  
FastLED.clear();
char x1[5];
char y1[5];

x = accelero.getXRaw();
y = accelero.getYRaw();
z = accelero.getZRaw();
delay(100);

    fXg = x * alpha + (fXg * (1.0 - alpha));
    fYg = y * alpha + (fYg * (1.0 - alpha));
   // fZg = z * alpha + (fZg * (1.0 - alpha));
   
   sprintf(x1,"%d",fXg);
   sprintf(y1,"%d",fYg);
  mySerial.write(148);
  mySerial.write("X=");
  mySerial.write(151);
  mySerial.write(x1);
  mySerial.write(156);
  mySerial.write("Y=");
  mySerial.write(159);
  mySerial.write(y1);
/*
  int xpvalue = fXg;
    int numLedsToLight1 = map(xpvalue, 465, 425, 1, NUM_LEDS);
  for(int led = 0; led < numLedsToLight1; led++)                     // x- postivie 
  { 
    if(led < 3 ) leds_Xp[8-led] = CRGB::Green;
    if(led >=3 & led < 6)leds_Xp[8-led] = CRGB::Orange;
    if(led >=6 & led <= 8)  leds_Xp[8-led] = CRGB::Red;
    FastLED.setBrightness(10);
    FastLED.show();
  }   
  
 
  int xnvalue = fXg;
    int numLedsToLight2 = map(xnvalue, 465, 500, 0, NUM_LEDS);
 
  for(int led = 0; led < numLedsToLight2; led++) 
  { 
    if(led >=6 & led <= 8)leds_Xn[8-led] = CRGB::Red;
    if(led >3 & led < 6)leds_Xn[8-led] = CRGB::Orange;
     if(led <= 3) leds_Xn[8-led] = CRGB::Green;
     FastLED.setBrightness(10);    
    FastLED.show();
  }  

  int ypvalue = fYg;
  int numLedsToLight3 = map(ypvalue, 369, 388, 0, NUM_LEDS);
  for(int led = 0; led < numLedsToLight3; led++) 
  {
    if(led <= 3) leds_Yp[8-led] = CRGB::Green;
    if(led > 3 & led < 6)leds_Yp[8-led] = CRGB::Orange;
    if(led >=6 & led <= 8)leds_Yp[8-led] = CRGB::Red;
     FastLED.setBrightness(10);   
    FastLED.show();
  }
*/
  int ynvalue = fYg;
  int numLedsToLight4 = map(ynvalue, 369, 350, 0, NUM_LEDS);
  for(int led = 0; led < numLedsToLight4; led++) 
  {
        
    FastLED.show();
    if(led >=6 & led <= 8 )leds_Yn[8-led] = CRGB::Red;
    if(led >=3 & led < 6)leds_Yn[8-led] = CRGB::Orange;
     if(led < 3 ) leds_Yn[8-led] = CRGB::Green;
     FastLED.setBrightness(10);  
    FastLED.show();  
  }

 /* Wait a little before reading again */
  delay(250);

}



 
  
  

