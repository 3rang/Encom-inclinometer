// Simple angle meter using ADXL335 accelerometer
//from electronicsblog.net/
#include <AcceleroMMA7361.h>

#define ADC_ref 3.3

#define zero_x 1.65

#define zero_y 1.65

#define zero_z 1.65

#define sensitivity_x 0.3

#define sensitivity_y 0.3

#define sensitivity_z 0.3
AcceleroMMA7361 accelero;

unsigned int x;
unsigned int y;
unsigned int z;

float xv;
float yv;
float zv;
float theta = 0;

float angle_x;
float angle_y;
float angle_z;

void setup()   {
  accelero.begin(13, 12, 11, 10, A0, A1, A2);
  accelero.setARefVoltage(3.3);                   //sets the AREF voltage to 3.3V
  accelero.setSensitivity(LOW);                   //sets the sensitivity to +/-6G

Serial.begin(115200);

}

void loop() {
x = accelero.getXRaw();
y = accelero.getYRaw();
z = accelero.getZRaw();


//xv=(x/1024.0*ADC_ref-zero_x)/sensitivity_x;
xv=x*(3.3/(1024));

//Serial.print ("x= ");
//Serial.print (xv);
//Serial.print(" g ");

//yv=(y/1024.0*ADC_ref-zero_y)/sensitivity_y;
yv=y*(3.3/(1024));

//Serial.print ("y= ");
//Serial.print (yv);
//Serial.print(" g ");

//zv=(z/1024.0*ADC_ref-zero_z)/sensitivity_z;
zv=z*(3.3/(1024.0));

//Serial.print ("z= ");
//Serial.print (zv);
//Serial.print(" g ");

Serial.print("\n");

//Serial.print("Rotation ");

//Serial.print("x= ");

//angle_x =atan2(-yv,-zv)*57.2957795;
//angle_x =atan(xv/sqrt(pow(yv,2)+pow(zv,2)))*(360/(2*3.141592));
angle_x = atan(sqrt(pow(yv,2)+pow(xv,2))/zv)*57.2957795;  

Serial.print(angle_x);
Serial.print(" deg");
//Serial.print(" ");

//Serial.print("y= ");

//angle_y =atan2(-xv,-zv)*57.2957795;

//Serial.print(angle_y);
//Serial.print(" deg");
//Serial.print(" ");

//Serial.print("z= ");

//angle_z =atan2(-yv,-xv)*57.2957795;

//Serial.print(angle_z);
//Serial.print(" deg");
//Serial.print("\n");

delay(500);
}

