/*
///////////////////////////////////////////////////////////////////
// FrieedBOX @ 2016-17 Copyright recieved
// Author:-          Tarang Patel
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
#define DATA_PIN 7

CRGB leds_Xp[NUM_LEDS];
CRGB leds_Xn[NUM_LEDS];
CRGB leds_Yp[NUM_LEDS];
CRGB leds_Yn[NUM_LEDS];
CRGB leds[1];
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
int fZg = 512;
const float alpha = 0.40;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  mySerial.begin(9600); 
  FastLED.addLeds<NEOPIXEL,DATA_PIN_Xp>(leds_Xp, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,DATA_PIN_Xn>(leds_Xn, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,DATA_PIN_Yp>(leds_Yp, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,DATA_PIN_Yn>(leds_Yn, NUM_LEDS);
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  accelero.begin(13, 12, 11, 10, A0, A1, A2);
  accelero.setARefVoltage(3.3);                   //sets the AREF voltage to 3.3V
  accelero.setSensitivity(LOW);                   //sets the sensitivity to +/-6G
  //accelero.calibrate();
  delay(500); // wait for display to boot up
  //mySerial.write(25); // cursor to beginning of first lin
  mySerial.write(22);
  mySerial.write(12);
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
  
  rawdata_filter();
  
  center_led();
  
  four_axis_leds();
  
  lcd_dispaly();
  
 /* Wait a little before reading again */
  delay(300);

}

void four_axis_leds()
{
  
//  This function is workes for 4-axis leds indications
//  Author            :    Tarang Patel
//  Fuction arguments :    None
//  Return type       :    void

 int xpvalue = fXg;
    int numLedsToLight1 = map(xpvalue, 473, 425, 0, NUM_LEDS);
  for(int ledxp = 0; ledxp < numLedsToLight1; ledxp++)                     // x- postivie 
  { 
   
    if(ledxp < 3 ) leds_Xp[8-ledxp] = CRGB::Green;
    if(ledxp >=3 & ledxp < 6)leds_Xp[8-ledxp] = CRGB::Orange;
    if(ledxp >=6 & ledxp <= 8)  leds_Xp[8-ledxp] = CRGB::Red;
    FastLED.setBrightness(10);
    FastLED.show();
   
  }   
  int xnvalue = fXg;
    int numLedsToLight2 = map(xnvalue, 470, 500, 0, NUM_LEDS);
 
  for(int ledxn = 0; ledxn < numLedsToLight2; ledxn++)                    // x - negative
  { 
    if(ledxn >=6 & ledxn <= 8)leds_Xn[8-ledxn] = CRGB::Red;
    if(ledxn >3 & ledxn < 6)leds_Xn[8-ledxn] = CRGB::Orange;
     if(ledxn <= 3) leds_Xn[8-ledxn] = CRGB::Green;
     FastLED.setBrightness(10);    
    FastLED.show();
  }  

  int ypvalue = fYg;
  int numLedsToLight3 = map(ypvalue, 374, 388, 0, NUM_LEDS);
  for(int ledyp = 0; ledyp < numLedsToLight3; ledyp++)                          // y - positive
  {
    if(ledyp <= 3) leds_Yp[8-ledyp] = CRGB::Green;
    if(ledyp > 3 & ledyp < 6)leds_Yp[8-ledyp] = CRGB::Orange;
    if(ledyp >=6 & ledyp <= 8)leds_Yp[8-ledyp] = CRGB::Red;
     FastLED.setBrightness(10);   
    FastLED.show();
  }

  int ynvalue = fYg;
  int numLedsToLight4 = map(ynvalue, 373, 350, 0, NUM_LEDS);
      for(int ledyn = 0; ledyn < numLedsToLight4; ledyn++)                     // y - negative
  {
        
    FastLED.show();
    if(ledyn >=6 & ledyn <= 8 )leds_Yn[8-ledyn] = CRGB::Red;
    if(ledyn >=3 & ledyn < 6)leds_Yn[8-ledyn] = CRGB::Orange;
     if(ledyn < 3 ) leds_Yn[8-ledyn] = CRGB::Green;
     FastLED.setBrightness(10);  
    FastLED.show();  
  }

}

void center_led()
{
  
//  This function is workes for centre leds indications
//  Author            :    Tarang Patel
//  Fuction arguments :    None
//  Return type       :    void

  leds[0] = CRGB::Red;   
  FastLED.show();

}

void  rawdata_filter()

{
  
//  This function is workes for get the raw data from sensor and pass it through low pass filer with (alpha value = 0.40)
//  Author            :    Tarang Patel
//  Fuction arguments :    None
//  Return type       :    void

x = accelero.getXRaw();
y = accelero.getYRaw();
z = accelero.getZRaw();
delay(100);
//////////////////////////////////////////////////////
//  Low - pass filter
//  alpha = 0.40
////////////////////////////////////////////////////// 
   fXg = x * alpha + (fXg * (1.0 - alpha));
   fYg = y * alpha + (fYg * (1.0 - alpha));
   fZg = z * alpha + (fZg * (1.0 - alpha));
//////////////////////////////////////////////////////   
   
}

void lcd_dispaly()
{
 
//  This function is workes for LCD interface
//  Author            :    Tarang Patel
//  Fuction arguments :    None
//  Return type       :    void  
  int val=0;

  char x1[0];
  char y1[1];
  //sprintf(y1,"%d",fYg);
  mySerial.write(148);
  mySerial.write("X=");
 // mySerial.write(151);
 // mySerial.write(x1); 
  mySerial.write(156);
  mySerial.write("Y=");
//  mySerial.write(159);
//  mySerial.write(y1); 
  
 int numLedx = map(fXg, 473, 425, 0, 9);
   //   for(int ledx ; ledx < numLed; ledx++)                    // x - negative
//  { 
      mySerial.write(8);
      mySerial.write(152);
      mySerial.write(" ");
      sprintf(x1,"%d",numLedx);
      mySerial.write(151);
      mySerial.write(x1); 
 // }  
  
  int numLedy = map(fYg, 374, 350, 0, 9);
   //   for(int ledx ; ledx < numLed; ledx++)                    // x - negative
//  { 
      mySerial.write(8);
      mySerial.write(160);
      mySerial.write(" ");
      sprintf(y1,"%d",numLedy);
      mySerial.write(159);
      mySerial.write(y1); 
 // }  
  
  
  
}
  

