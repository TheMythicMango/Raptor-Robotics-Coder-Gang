/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\satya                                            */
/*    Created:      Wed Dec 02 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

//defines motors and competitions and stuff
competition Competition;
controller Controller;

vex::motor LeftMotor = vex::motor(PORT14, ratio18_1);
vex::motor RightMotor = vex::motor(PORT15, ratio18_1);
vex::motor IntakeMotor = vex::motor(PORT1, ratio18_1);
vex::motor LeftClaw = vex::motor(PORT3, ratio18_1);
vex::motor RightClaw = vex::motor(PORT8, ratio18_1);

void autonomous(void){
  //move forward for 1 seconds
  LeftMotor.spin(vex::directionType::rev, 80, vex::velocityUnits::pct);
  RightMotor.spin(vex::directionType::fwd, 80, vex::velocityUnits::pct);
  task::sleep(1000);
  //stops drivetrain motors and starts intake motor
  LeftMotor.spin(vex::directionType::rev, 0, vex::velocityUnits::pct);
  RightMotor.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  IntakeMotor.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
  LeftClaw.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
  RightClaw.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
  task::sleep(5000);
  IntakeMotor.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  LeftClaw.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  RightClaw.spin(vex::directionType::rev, 0, vex::velocityUnits::pct);
  task::sleep(100);
  LeftMotor.spin(vex::directionType::fwd, 80, vex::velocityUnits::pct);
  RightMotor.spin(vex::directionType::rev, 80, vex::velocityUnits::pct);
  task::sleep(500);
  LeftMotor.spin(vex::directionType::rev, 0, vex::velocityUnits::pct);
  RightMotor.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
}


void driverControl(void){
  while(1){
    //direction type, a speed(0, 127), a velocity unit
    LeftMotor.spin(vex::directionType::rev, Controller.Axis3.value(), vex::velocityUnits::pct);
    RightMotor.spin(vex::directionType::fwd, Controller.Axis2.value(), vex::velocityUnits::pct);

    //moves claws inwards
    if(Controller.ButtonL1.pressing()){
      LeftClaw.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
      RightClaw.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
    }
    //moves claws outwards
    if(Controller.ButtonL2.pressing()){
      LeftClaw.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
      RightClaw.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
    }
    //moves intake inwards
    if(Controller.ButtonR1.pressing()){
      IntakeMotor.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
    }
    //moves intake outwards
    if(Controller.ButtonR2.pressing()){
      IntakeMotor.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
    }
    else{
      //turn all motors to 0
      LeftClaw.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
      RightClaw.spin(vex::directionType::rev, 0, vex::velocityUnits::pct);
      IntakeMotor.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
    }
  }
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Competition.autonomous(autonomous);
  Competition.drivercontrol(driverControl);
}
