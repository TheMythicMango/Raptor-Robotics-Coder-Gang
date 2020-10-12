/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\satya                                            */
/*    Created:      Tue Sep 15 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Vision15             vision        15              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "VisionSensor.h"

using namespace vex;

vex::brain Brain;
vex::competition Competition;

//motors, PORTS WILL CHANGE
vex::motor RightMotor = vex::motor(vex::PORT8);
vex::motor LeftMotor = vex::motor(vex::PORT9, true);
vex::motor MiddleMotor = vex::motor(vex::PORT7);
vex::motor bottomMotorSpin = vex::motor(vex::PORT20);
vex::motor frontMotorBottom = vex::motor(vex::PORT18, true);
vex::motor backMotorTop = vex::motor(vex::PORT19);
vex::motor rightClaw = vex::motor(vex::PORT5);
vex::motor leftClaw = vex::motor(vex::PORT6);
//Vision sensor is in PORT15

vex::controller Controller1 = vex::controller();

//for calibrating what balls we want and don't want
bool isRed = false;
bool isBlue = true;

//theta values for the auton
int thetaOne = 90;
int thetaTwo = 120;
int thetaThree = 45;
int thetaFour = 45;

//functions to set our ball color
void setBlue(){
  isBlue = true;
  isRed = false;
}


void setRed(){
  isRed = true;
  isBlue = false;
}


//functions used for autonomous
//move bot forwards, enter speed you want it to go and how long
void moveForwardx(int speed, int milliseconds){
  RightMotor.spin(vex::directionType::fwd, speed, velocityUnits::pct);
  LeftMotor.spin(vex::directionType::fwd, speed, velocityUnits::pct);
  vex::task::sleep(milliseconds);
}


//rotates bot "θ" degrees
void rotateTheta(int theta){
  RightMotor.rotateFor(theta, vex::rotationUnits::deg);
  LeftMotor.rotateFor(theta*-1, vex::rotationUnits::deg);
}


//moves claws so they bring things inward for x milliseconds
void moveClawsIn(int milliseconds){
  rightClaw.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
  leftClaw.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
  vex::task::sleep(milliseconds);
}


//moves a single ball through the robot into the goal
void moveOneBallUp(){
  frontMotorBottom.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
  bottomMotorSpin.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
  backMotorTop.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
  vex::task::sleep(300);
}


//testing for now/ ***LEARN ABOUT PIDS AND USE THEM
void autonomous (void) {
  moveForwardx(50, 200);
  rotateTheta(thetaOne);
  moveForwardx(30, 200);
  moveClawsIn(100); moveOneBallUp();//move ball inside as(ONLY ONE) well as rotate claws in
  rotateTheta(180);
  moveForwardx(30, 200);
  rotateTheta(120);
  moveForwardx(40, 300);
  rotateTheta(45);
  moveForwardx(30, 200);
  moveOneBallUp();//move ball inside up. ONLY ONE BALL
  rotateTheta(180);
  moveForwardx(30, 200);
  rotateTheta(45);
  moveForwardx(50, 300);
  rotateTheta(45);
  moveForwardx(30,  200);
  moveClawsIn(100); moveOneBallUp();
  RightMotor.rotateFor(90, vex::rotationUnits::deg);
  LeftMotor.rotateFor(-90, vex::rotationUnits::deg);
}


void usercontrol (void) {
  while(1){
//Basic movement controls
    
    //spins each motor forward based on the position of the controller axis
    RightMotor.spin(vex::directionType::fwd, Controller1.Axis2.position()/1.1, vex::velocityUnits::pct);
    LeftMotor.spin(vex::directionType::fwd, Controller1.Axis3.position()/1.1, vex::velocityUnits::pct);
    
    //used to strafe left or right using the middle wheel, using the down arrow button and button B on the controller
    if(Controller1.ButtonDown.pressing()){
      MiddleMotor.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonB.pressing()){
      MiddleMotor.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
    }
    else{
      MiddleMotor.stop(vex::brakeType::brake);
    }


//claw movement
    
    //moves the claws in or out using the right shoulder buttons at the max speed of 127
    if(Controller1.ButtonR2.pressing()){
      rightClaw.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
      leftClaw.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonR1.pressing()){
      rightClaw.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
      leftClaw.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
    }
    else{
      rightClaw.stop(vex::brakeType::brake);
      leftClaw.stop(vex::brakeType::brake);
    }
    

//multi commands
    
    //bring the balls up
    if(Controller1.ButtonL1.pressing()){
      frontMotorBottom.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
      bottomMotorSpin.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
      backMotorTop.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
    }
    
    //bring balls down
    else if(Controller1.ButtonL2.pressing()){
      frontMotorBottom.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
      bottomMotorSpin.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
      backMotorTop.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
    }
    
    //Get rid of ball override function, gets rid of ball in the middle of the bot
    else if(Controller1.ButtonX.pressing()){
      bottomMotorSpin.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
      backMotorTop.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
      vex::task::sleep(500);
      bottomMotorSpin.stop(vex::brakeType::brake);
      backMotorTop.stop(vex::brakeType::brake);
    }
    else{
      frontMotorBottom.stop(vex::brakeType::brake);
      bottomMotorSpin.stop(vex::brakeType::brake);
      backMotorTop.stop(vex::brakeType::brake);
    }


//change calibration of vision sensor to choose if ball is red or blue
    //by clicking the two buttons, we can set the boolean variables to true or false, letting us control what ball we would like to kick out.
    Controller1.ButtonLeft.pressed(setRed);
    Controller1.ButtonRight.pressed(setBlue);
    
    //prints what color ball we are currently using
    if(isBlue)
      Brain.Screen.print("Color Calibrated: Blue");
    else if(isRed){
      Brain.Screen.print("Color Calibrated: Red");
    }


//color sensor to kick ball out
    
    //takes 5 snapshots with the vision sensor, depending on what color we have, 50 milliseconds in between.
    for(int i = 1; i < 5; i++){
      if(isBlue)
        Vision1.takeSnapshot(SIG_BLUE);
      else if(isRed)
        Vision1.takeSnapshot(SIG_RED);
      else{
        return;
      vex::task::sleep(10);
      }
    }
    
    //same code as override function ButtonX, but only will occur if the largest object exists inside of our snapshot.
    if(Vision1.largestObject.exists){
      bottomMotorSpin.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
      backMotorTop.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
      vex::task::sleep(500);
      bottomMotorSpin.stop(vex::brakeType::brake);
      backMotorTop.stop(vex::brakeType::brake);
    }    
    
    //so our bot doesnt blow up to due performing everything as fast as possible
    vex::task::sleep(50);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  //sets code for compitions, pretty self explanatory
  Competition.autonomous( autonomous );
  Competition.drivercontrol(usercontrol);
  
  while(1){
    vex::task::sleep(200);
  }
}
