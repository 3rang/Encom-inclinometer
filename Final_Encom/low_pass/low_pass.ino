#include <AcceleroMMA7361.h>

AcceleroMMA7361 accelero;
int Xg;
int Yg;
int Zg;
double fXg = 0;
double fYg = 0;
double fZg = 0;
const float alpha = 0.26;
void setup()
{
  Serial.begin(9600);
  accelero.begin(13, 12, 11, 10, A0, A1, A2);
  accelero.setARefVoltage(3.3);                   //sets the AREF voltage to 3.3V
  accelero.setSensitivity(LOW);                   //sets the sensitivity to +/-6G
  accelero.calibrate();
}

void loop()
{
      double pitch, roll;
  Xg = accelero.getXRaw();
  Yg = accelero.getYRaw();
  Zg = accelero.getZRaw();
  
    fXg = Xg * alpha + (fXg * (1.0 - alpha));
    fYg = Yg * alpha + (fYg * (1.0 - alpha));
    fZg = Zg * alpha + (fZg * (1.0 - alpha));
   
    
  Serial.print("\nfXg: ");
  Serial.print(fXg);
  Serial.print("\tXg: ");
  Serial.print(Xg);
  Serial.print("\tfYg: ");
  Serial.print(fYg);
  Serial.print("\tYg: ");
  Serial.print(Yg);
  Serial.print("\tfZg: ");
  Serial.print(fZg);
  Serial.print("\tZg: ");
  Serial.print(Zg);
  delay(500);                                     //(make it readable)
}
