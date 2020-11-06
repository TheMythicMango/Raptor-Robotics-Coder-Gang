/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\satya                                            */
/*    Created:      Thu Nov 05 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

vex::competition Competition;
vex::brain Brain;
vex::controller Controller;

vex::motor RightTop = vex::motor(vex::PORT1);
vex::motor RightBack = vex::motor(vex::PORT10);
vex::motor LeftTop = vex::motor(vex::PORT11);
vex::motor LeftBack = vex::motor(vex::PORT20);

void autonomous (void){

}

void usercontrol (void){
  LeftTop.spin(vex::directionType::rev, Controller.Axis2.value() + Controller.Axis1.value() + Controller.Axis4.value(), vex::velocityUnits::pct);
  LeftBack.spin(vex::directionType::rev, Controller.Axis2.value() - Controller.Axis1.value() + Controller.Axis4.value(), vex::velocityUnits::pct);
  RightTop.spin(vex::directionType::fwd, Controller.Axis2.value() + Controller.Axis1.value() + Controller.Axis4.value(), vex::velocityUnits::pct);
  RightBack.spin(vex::directionType::rev, Controller.Axis2.value() - Controller.Axis1.value() + Controller.Axis4.value(), vex::velocityUnits::pct);
  vex::task::sleep(50);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  vex::task::sleep(50);
}
