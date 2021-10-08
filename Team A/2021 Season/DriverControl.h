#include "PIDauton.h"

using namespace vex;

bool Reverse = false;

void usercontrol(void){
  while(1){
    //Reverse controls
    if(Controller.ButtonA.pressing() && !Reverse){
      Reverse = true;
    }
    if(Controller.ButtonA.pressing() && Reverse){
      Reverse = false;
    }

    //Movement
    if(!Reverse){
      RightBack.spin(directionType::fwd, Controller.Axis3.value(), velocityUnits::pct); 
      RightFront.spin(directionType::fwd, Controller.Axis3.value(), velocityUnits::pct);
      LeftBack.spin(directionType::rev, Controller.Axis2.value(), velocityUnits::pct); 
      LeftFront.spin(directionType::rev, Controller.Axis2.value(), velocityUnits::pct);
    }
    else if(Reverse){
      RightBack.spin(directionType::rev, Controller.Axis3.value(), velocityUnits::pct); 
      RightFront.spin(directionType::rev, Controller.Axis3.value(), velocityUnits::pct);
      LeftBack.spin(directionType::fwd, Controller.Axis2.value(), velocityUnits::pct); 
      LeftFront.spin(directionType::fwd, Controller.Axis2.value(), velocityUnits::pct);
    }

    //Lift
    if(!LimitSwitch.pressing()){
      if(Controller.ButtonR1.pressing()){
        LiftMotor.spin(directionType::fwd, 127, velocityUnits::pct);
      }
      else if(Controller.ButtonR2.pressing()){
        LiftMotor.spin(directionType::rev, 127, velocityUnits::pct);
      }
      else{
        LiftMotor.stop();
      }
    }
    else{
      LiftMotor.stop();
    }

    //Tread
    if(Controller.ButtonL1.pressing()){
      TreadMotor.spin(directionType::fwd, 127, velocityUnits::pct);
    }
    else if(Controller.ButtonL2.pressing()){
      TreadMotor.spin(directionType::fwd, 127, velocityUnits::pct);
    }
    else{
      TreadMotor.stop();
    }
  }
  vex::task::sleep(10);
}
