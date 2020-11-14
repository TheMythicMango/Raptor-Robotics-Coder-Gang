/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\satya                                            */
/*    Created:      Sun Nov 08 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#import "odomfunc.cpp"
#import "autonFunc.cpp"

using namespace vex;

competition Competition;
//controller
controller Controller = controller(primary);

vex::task updatePos;

void auton(void){
  test_odometry();
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  updatePos = vex::task(positionTrack);
  calibratePositionTrackers();
  //Competition.autonomous(auton);
  //test_odometry();
}