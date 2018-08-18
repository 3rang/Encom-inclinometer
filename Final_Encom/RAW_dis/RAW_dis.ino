#include <AcceleroMMA7361.h>
#include <SoftwareSerial.h>

// Attach the serial display's RX line to digital pin 2
SoftwareSerial mySerial(3, 2); // pin 2 = TX, pin 3 = RX (unused)
AcceleroMMA7361 accelero;
char x1[5];
char y1[5];

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600); // set up serial port for 9600 baud
  accelero.begin(13, 12, 11, 10, A0, A1, A2);
  accelero.setARefVoltage(3.3);                   //sets the AREF voltage to 3.3V
  accelero.setSensitivity(LOW);                   //sets the sensitivity to +/-6G
  //accelero.calibrate();


  delay(500); // wait for display to boot up
  //mySerial.write(25); // cursor to beginning of first lin
  mySerial.write(22);
  mySerial.write(12);
  delay(1000);
  mySerial.write("    FriedBOX");

}

int x;
int y;
int z;
float smooth;
//  int t;
void loop()
{
  delay(1000);
  x = accelero.getXRaw();
  y = accelero.getYRaw();
  z = accelero.getZRaw();
  //smooth=smooth-(0.025*(smooth-x));
  //mySerial.write(12);
  sprintf(x1, "%d", x);
  sprintf(y1, "%d", y);
  mySerial.write(148);
  mySerial.write("X=");
  mySerial.write(151);
  // delay(1000);
  mySerial.write(x1);
  //delay(100);
  mySerial.write(156);
  mySerial.write("Y=");
  mySerial.write(159);
  mySerial.write(y1);

  // mySerial.write(148);
  delay(100);
  //(make it readable)
}
