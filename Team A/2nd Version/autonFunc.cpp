#include "vex.h"
#import "odomfunc.cpp"

using namespace vex;

//taken from benBots for a test. Essentially goes in a square 3 times while rotatings
void test_odometry(void){
  driveReset(0, 0, 0);
  turnSlide(0, 24, -90, driveMax, turnMax, 0, driveP, turnP, driveD, turnD, errorMarginBase, errorMarginTurnDeg);
  turnSlide(24, 24, 180, driveMax, turnMax, 0, driveP, turnP, driveD, turnD, errorMarginBase, errorMarginTurnDeg);
  turnSlide(24, 0, 90, driveMax, turnMax, 0, driveP, turnP, driveD, turnD, errorMarginBase, errorMarginTurnDeg);
  turnSlide(0, 0, 0, driveMax, turnMax, 0, driveP, turnP, driveD, turnD, errorMarginBase, errorMarginTurnDeg);
  turnSlide(0, 24, -90, driveMax, turnMax, 0, driveP, turnP, driveD, turnD, errorMarginBase, errorMarginTurnDeg);
  turnSlide(24, 24, 180, driveMax, turnMax, 0, driveP, turnP, driveD, turnD, errorMarginBase, errorMarginTurnDeg);
  turnSlide(24, 0, 90, driveMax, turnMax, 0, driveP, turnP, driveD, turnD, errorMarginBase, errorMarginTurnDeg);
  turnSlide(0, 0, 0, driveMax, turnMax, 0, driveP, turnP, driveD, turnD, errorMarginBase, errorMarginTurnDeg);
  turnSlide(0, 24, -90, driveMax, turnMax, 0, driveP, turnP, driveD, turnD, errorMarginBase, errorMarginTurnDeg);
  turnSlide(24, 24, 180, driveMax, turnMax, 0, driveP, turnP, driveD, turnD, errorMarginBase, errorMarginTurnDeg);
  turnSlide(24, 0, 90, driveMax, turnMax, 0, driveP, turnP, driveD, turnD, errorMarginBase, errorMarginTurnDeg);
  turnSlide(0, 0, 0, driveMax, turnMax, 0, driveP, turnP, driveD, turnD, errorMarginBase, errorMarginTurnDeg);
}
