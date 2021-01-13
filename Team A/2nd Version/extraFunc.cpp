#include "vex.h"
#import "odomfunc.cpp"
//controller
controller Controller = controller(primary);

using namespace vex;

void SpinClawsIn(void){

}

void SpinClawsOut(void){

}

void StopClaws(void){

}

void RollersUp(void){

}

void RollersDown(void){

}

void StopRollers(void){

}

void GetRidOffBall(void){

}

void setLeftDriveFront(vex::directionType type, int percentage){
  if(percentage>=0){
    percentage = 1.2*pow(1.043,percentage) - 1.2 + 0.2*percentage;
  }
  else{
    percentage = -percentage;
    percentage = 1.2*pow(1.043, percentage) - 1.2 + 0.2*percentage;
    percentage = -percentage;
  }
  
  LeftFront.spin(type, percentage, vex::velocityUnits::pct);
}

void setLeftDriveBack(vex::directionType type, int percentage){
  if(percentage>=0){
    percentage = 1.2*pow(1.043,percentage) - 1.2 + 0.2*percentage;
  }
  else{
    percentage = -percentage;
    percentage = 1.2*pow(1.043, percentage) - 1.2 + 0.2*percentage;
    percentage = -percentage;
  }

  LeftBack.spin(type, percentage, vex::velocityUnits::pct);
}

void setRightDriveFront(vex::directionType type, int percentage){
  if(percentage>=0){
    percentage = 1.2*pow(1.043,percentage) - 1.2 + 0.2*percentage;
  }
  else{
    percentage = -percentage;
    percentage = 1.2*pow(1.043, percentage) - 1.2 + 0.2*percentage;
    percentage = -percentage;
  }
  
  RightFront.spin(type, percentage, vex::velocityUnits::pct);
}

void setRightDriveBack(vex::directionType type, int percentage){
  if(percentage>=0){
    percentage = 1.2*pow(1.043,percentage) - 1.2 + 0.2*percentage;
  }
  else{
    percentage = -percentage;
    percentage = 1.2*pow(1.043, percentage) - 1.2 + 0.2*percentage;
    percentage = -percentage;
  }

  RightBackk.spin(type, percentage, vex::velocityUnits::pct);
}
void UserControl(void){
  while(1){  
    setLeftDriveFront(vex::directionType::fwd, (Controller.Axis3.value() + Controller.Axis4.value()));
    setLeftDriveBack(vex::directionType::fwd, (Controller.Axis3.value() - Controller.Axis4.value()));
    setRightDriveFront(vex::directionType::fwd, (-Controller.Axis2.value() + Controller.Axis1.value()));
    setRightDriveBack(vex::directionType::fwd, (-Controller.Axis2.value() - Controller.Axis1.value()));
        
    if(Controller.ButtonR2.pressing()){
      SpinClawsIn();
    }
    else if(Controller.ButtonR1.pressing()){
      SpinClawsOut();
    }
    else if(Controller.ButtonX.pressing()){
      GetRidOffBall();
    }
    else{
      StopClaws();
    }  

    if(Controller.ButtonL1.pressing()){
      RollersUp();
    }
    else if(Controller.ButtonL2.pressing()){
      RollersDown();
    }
    else{
      StopRollers();
    }
  }
  vex::task::sleep(10);
}
