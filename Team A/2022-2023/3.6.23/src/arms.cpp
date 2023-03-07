#include "arms.hpp"
#include "movement.hpp"

PID Arms::pidFly(0,0,0,0);
// void Arms::launchGoal(double dist){
//   double distSq = dist*dist;
//   // 19.07 x - 172.6 x + 554.5 x - 689.7 x + 594.6
//   double flyVel = 19.07*distSq*distSq - 172.6*distSq*dist + 554.5*distSq - 689.7*dist + 594.6;
//   if(flyVel>430){
//     flyVel = 410;
//   }
//   launchVel(flyVel,state);
// }

//out of 600;
float predictVoltage(float vel){ return (vel)/57+.9;}

float Arms::targetVel = 0;
float Arms::voltMod = 0;
void Arms::initFly(float actVel, float targVel, float voltMod){
  if(targVel == 0){fly.move_voltage(0);}
  setFly(targVel, voltMod);
  Arms::pidFly = PID(targVel-actVel, .005, .05, 0, 12, 12, 0, 0, 0,5,.1, .1, true);
  // Arms::pidFly = PID(targVel-actVel, 0,.1,0,0,0,1,1,6,7,.1,.1, true);
}
void Arms::initFlyFast(float actVel, float targVel, float voltMod){
  if(targVel == 0){fly.move_voltage(0);}
  setFly(targVel, voltMod);
  // Arms::pidFly = PID(targVel-actVel, .005, .05, 0, 12, 12, 0, 0, 0,5,.1, .1, true);
  Arms::pidFly = PID(targVel-actVel, 0,.1,0,0,0,1,1,6,7,.1,.1, true);
}
void Arms::setFly(float vel, float voltM){
  targetVel = vel;
  Arms::voltMod = voltM;
}
void Arms::launchVel(float actVel){
  if(targetVel == 0) return;
  float out = pidFly.run(actVel, targetVel);
  out+=predictVoltage(targetVel);
  out+=voltMod;
  fly.move_voltage(out*1000);
}
float Arms::getVolts(float actVel){
  float out = pidFly.run(actVel, targetVel);
  out+=predictVoltage(targetVel);
  out+=voltMod;
  return out;
}


// pros::vision_color_code_t Arms::rollerCode = vision.create_color_code(1, 2); 

static int i = 0;
bool Arms::rollerTo(State *state, bool red){
  optic.set_led_pwm(100);
  intake.move_voltage(-12000);
  if(( red&&(optic.get_hue()<60 || optic.get_hue()>320)) || ( !red&&optic.get_hue()>210&&optic.get_hue()<310 )){ 
    i=0;
    return true;
  }
  else{i++;}
  if(i<5){return true;}
  else{i = 0; return false;}

}