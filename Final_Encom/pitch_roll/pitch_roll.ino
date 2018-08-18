#include <Wire.h>
//#include <ADXL345.h>
 #include <AcceleroMMA7361.h>

const float alpha = 0.5;
 
double fXg = 0;
double fYg = 0;
double fZg = 0;
 
AcceleroMMA7361 acc;
 
void setup()
{
    acc.begin();
    Serial.begin(9600);
    delay(100);
   // acc.calibrate();

}
 
void loop()
{
    double pitch, roll, Xg, Yg, Zg;
    //acc.read(&Xg, &Yg, &Zg);
    Xg = acc.getXRaw();
    Yg = acc.getXRaw();
    Zg = acc.getXRaw();

    //Low Pass Filter
    fXg = Xg * alpha + (fXg * (1.0 - alpha));
    fYg = Yg * alpha + (fYg * (1.0 - alpha));
    fZg = Zg * alpha + (fZg * (1.0 - alpha));
    Serial.print(fXg);
    Serial.write(" : ");
    Serial.print(fYg);
    Serial.print("\t");
    //Roll & Pitch Equations
    roll  = (atan2(fYg, fZg));
    pitch = (atan2(-fXg, sqrt(fYg*fYg + fZg*fZg)));
 
    Serial.print(pitch);
    Serial.print(" : ");
    Serial.println(roll);
 
    delay(1000);
}

