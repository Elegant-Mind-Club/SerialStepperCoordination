#include <AccelStepper.h>
#include <MultiStepper.h>


#define xpul 24
#define xdir 30

#define ypul 26
#define ydir 32

#define zpul 25
#define zdir 31

int loopCounter = 0;
int xpos;
int ypos;
int zpos;

AccelStepper sx(1,xpul,xdir);
AccelStepper sy(1,ypul,ydir);
AccelStepper sz(1,zpul,zdir);
MultiStepper StepperControl;
long newpos[3];

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("setup()");
  // sx.setMaxSpeed(50000000);
  // sy.setMaxSpeed(50000000);
  // sz.setMaxSpeed(50000000);
  // //sx.setAcceleration(1000);
  sx.setMaxSpeed(3000);
  sx.setSpeed(200);
  sy.setMaxSpeed(3000);
  sy.setSpeed(200);
  sz.setMaxSpeed(3000);
  sz.setSpeed(200);

  StepperControl.addStepper(sx);
  StepperControl.addStepper(sy);
  StepperControl.addStepper(sz);
  sx.setCurrentPosition(0);
  sy.setCurrentPosition(0);
  sz.setCurrentPosition(0);
  newpos[0] = -30000;
  newpos[1] = 0;
  newpos[2] = 0;
  StepperControl.moveTo(newpos);
  StepperControl.runSpeedToPosition(); // I think this is grouping the stepper motors together and trying to end them at the same time.
  delay(200);
}


void loop()
{
  Serial.println("loop("+String(loopCounter)+")");
  int distance = -100;
  int speed = 100;
  // sx.setSpeed(speed);
  // sx.moveTo(distance);
  // sx.runSpeedToPosition();
  // sy.setSpeed(speed);
  // sy.moveTo(distance);
  // sy.runSpeedToPosition();
  // sz.setSpeed(speed);
  // sz.moveTo(distance);
  // sz.runSpeedToPosition();
  // delay(1) ;
  loopCounter++;
  if(loopCounter>=32767){
    Serial.println("Max loopCounter reached!");
    loopCounter = 0;
  }
}

