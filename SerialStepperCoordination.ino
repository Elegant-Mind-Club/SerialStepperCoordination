//This commit has a working joystick control
#include <AccelStepper.h>

#define xpul 24
#define xdir 30

#define ypul 25
#define ydir 31

#define zpul 26
#define zdir 32

const int x_pin = 0;
const int y_pin = 1;
const int switch_pin = 53;

int xpos;
int ypos;
int zpos;
int sw;
int on;

int xspeed;
int yspeed;
int zspeed;

AccelStepper sx(1,xpul,xdir);
AccelStepper sy(1,ypul,ydir);
AccelStepper sz(1,zpul,zdir);

long newpos[3];

//serial tracking
bool finished_move = true;
float start_time;
int index = 0;
String pos;

void setup()
{
  pinMode(switch_pin, INPUT);
  digitalWrite(switch_pin, INPUT_PULLUP);
  // sx.setMaxSpeed(50000000);
  // sy.setMaxSpeed(50000000);
  // sz.setMaxSpeed(50000000);
  // //sx.setAcceleration(1000);
  sx.setMaxSpeed(100000);
  // sx.setAcceleration(25000);

  sy.setMaxSpeed(100000);
  // sy.setAcceleration(25000);

  sz.setMaxSpeed(100000);
  // sz.setAcceleration(25000);

  Serial.begin(115200);
}

// Moving based on speed
void loop()
{
  // xspeed = map(analogRead(A0), 0, 1023, -30000, 30000);
  // yspeed = map(analogRead(A1), 0, 1023, -30000, 30000);
  // zspeed = map(analogRead(A1), 0, 1023, -30000, 30000); // Change this pin
  // sw = digitalRead(switch_pin);
  // on = 0;
  while(Serial.available()> 0){
    char input = Serial.read();
    Serial.println("read");
    Serial.println(input);
    if(input == ',' && index < 2) //read pos terms before end of line, max 3 directions = max 2 directions end with comma
    {
      newpos[index] = pos.toFloat();
      Serial.println(String(newpos[index]));
      index++;
      pos = "";
    }
    else if(input == '\\') 
    {
      //record last pos
      newpos[index] = pos.toFloat();
      Serial.println(String(newpos[index]));
      index++;
      pos = "";
      //send command
      xpos = newpos[0];
      ypos = newpos[1];
      zpos = newpos[2];
      // sx.setSpeed(sx.currentPosition() + xpos);
      // sy.setSpeed(sy.currentPosition() + ypos);
      // sz.setSpeed(sz.currentPosition() + zpos);
      //start_time = millis(); //ms
      // finished_move = run(xpos,ypos,zpos);
      run(xpos,ypos,zpos);
      Serial.println("Moving to x: " + String(xpos) + "; y: " + String(ypos) + "; z: " + String(zpos));
      // //reset variables
      // if(finished_move)
      // {
      //   finished_move = false;
      index = 0; 
      
        // for(int i=0;i<3;i++)
        // {
        //   newpos[i]=0;
        // }
    }
    else //collect char of same pos term in one string
    {
      Serial.println("add_num");
      pos = pos + input;
    }
  }
}

boolean run(float xspeed,float yspeed,float zspeed)
{
  if(-1000 < zspeed && zspeed < 1000){ // Threshold 30
      zspeed = 0;
      sz.setSpeed(0);
      sz.runSpeed();
  }
  else{
      sz.setSpeed(zspeed);
      sz.runSpeed();
  }
  
  if(-1000 < xspeed && xspeed < 1000){ // Threshold 30
    xspeed = 0;
    sx.setSpeed(0);
    sx.runSpeed();
  }
  else{
    sx.setSpeed(xspeed);
    sx.runSpeed();
  }

  if(-1000 < yspeed && yspeed < 1000){ // Threshold 15
    yspeed = 0;
    sy.setSpeed(0);
    sy.runSpeed();
  }
  else{
    sy.setSpeed(yspeed);
    sy.runSpeed();
  }

  // if(!sx.runSpeed() && !sy.runSpeed() && !sz.runSpeed())
  // {
  //   return true;
  // }

}
  
  // Printing pos values
    // Serial.print("X-axis:  ");
    // Serial.println(xpos);

    // Serial.print("Y-axis:  ");
    // Serial.println(ypos);

    // Serial.print("Z-axis:  ");
    // Serial.println(zpos);
  // 

// Moving based on position
// void loop()
// {
//   xpos = map(analogRead(A0), 0, 1023, -500, 500);
//   ypos = map(analogRead(A1), 0, 1023, -500, 500);
//   zpos = map(analogRead(A1), 0, 1023, -500, 500); // Change this pin
//   sw = digitalRead(switch_pin);
//   on = 0;

//   if (sw == LOW){
//     if(-30 < zpos && zpos < 30){ // Threshold 30
//       zpos = 0;
//       sz.setCurrentPosition(0);
//       sz.run();
//     }
//     else{
//       sz.moveTo(sz.currentPosition() + zpos);
//       sz.runSpeedToPosition();
//     }

//   }
  
//   else{
//     // fix stick drift
//     if(-30 < xpos && xpos < 30){ // Threshold 30
//       xpos = 0;
//       sx.setCurrentPosition(0);
//       sx.run();
//       Serial.println("runing");
//     }
//     else{
//       sx.moveTo(sx.currentPosition() + xpos);
//       sx.runSpeedToPosition();
//     }

//     if(-30 < ypos && ypos < 30){ // Threshold 15
//       ypos = 0;
//       sy.setCurrentPosition(0);
//       sy.run();
//     }
//     else{
//       sy.moveTo(sy.currentPosition() - ypos);
//       sy.runSpeedToPosition();
//     }
//   }  
  
//   // Printing pos values
//     // Serial.print("X-axis:  ");
//     // Serial.println(xpos);

//     // Serial.print("Y-axis:  ");
//     // Serial.println(ypos);

//     // Serial.print("Z-axis:  ");
//     // Serial.println(zpos);
//   // 
// }

// Test set up code
// Serial.begin(115200);
//   delay(1000);
//   Serial.println("setup()");

//   sx.setMaxSpeed(30000);
//   sx.setSpeed(400);
//   sy.setMaxSpeed(30000);
//   sy.setSpeed(400);
//   sz.setMaxSpeed(30000);
//   sz.setSpeed(400);

//   sx.setCurrentPosition(0);
//   sy.setCurrentPosition(0);
//   sz.setCurrentPosition(0);
//   newpos[0] = -35000;
//   newpos[1] = 20000;
//   newpos[2] = 10000;

//   sx.moveTo(newpos[0]);
//   sy.moveTo(newpos[1]);
//   sz.moveTo(newpos[2]);

// void loop()
// {
//   sx.run(); 
//   sy.run();
//   sz.run();
// }
