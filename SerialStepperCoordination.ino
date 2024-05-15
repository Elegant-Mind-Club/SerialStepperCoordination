#include <AccelStepper.h>
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

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("setup()");
}

void loop()
{
  Serial.println("loop("+String(loopCounter)+")");
  delay(1) ;
  loopCounter++;
}