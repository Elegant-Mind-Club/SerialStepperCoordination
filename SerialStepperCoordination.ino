#include <AccelStepper.h>
#include <MultiStepper.h>


#define xpul 24
#define xdir 30

#define ypul 25
#define ydir 31

#define zpul 26
#define zdir 42

int loopCounter = 0;
int xpos;
int ypos;
int zpos;

AccelStepper sx(1,xpul,xdir);
AccelStepper sy(1,ypul,ydir);
AccelStepper sz(1,zpul,zdir);
//MultiStepper Control;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("setup()");
  sx.setMaxSpeed(50000000);
  sy.setMaxSpeed(50000000);
  sz.setMaxSpeed(50000000);
  sx.setAcceleration(1000);
}

void loop()
{
  Serial.println("loop("+String(loopCounter)+")");
  int distance = 100;
  int speed = 100;
  sx.setSpeed(speed);
  sx.moveTo(distance);
  sx.runSpeedToPosition();
  sy.setSpeed(speed);
  sy.moveTo(distance);
  sy.runSpeedToPosition();
  sz.setSpeed(speed);
  sz.moveTo(distance);
  sz.runSpeedToPosition();
  delay(1) ;
  loopCounter++;
  if(loopCounter>=32767){
    Serial.println("Max loopCounter reached!");
    loopCounter = 0;
  }
}