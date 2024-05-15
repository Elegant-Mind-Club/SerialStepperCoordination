#include <AccelStepper.h>
#define xpul 24
#define xdir 30

#define ypul 25
#define ydir 31

#define zpul 26
#define zdir 42

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.println("setup()");
}

void loop()
{
  Serial.println("loop()");
  delay( 1000) ;
}