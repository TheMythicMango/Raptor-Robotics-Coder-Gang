#include "vex.h"

brain Brain;

//motors
motor LeftFront = motor(PORT1, ratio18_1);
motor LeftBack = motor(PORT10, ratio18_1);
motor RightFront = motor(PORT11,ratio18_1);
motor RightBackk = motor(PORT20, ratio18_1);

//Sensors
encoder EncoderLeft = encoder(Brain.ThreeWirePort.C);
encoder EncoderRight = encoder(Brain.ThreeWirePort.E);
encoder EncoderBack = encoder(Brain.ThreeWirePort.G);

//distances from tracker wheels to center of bot
float rWidth = 0; 
float lWidth = 0; 
float bLength = 0;

//ratios of omni wheel trackers: inches/degrees
float rightWheelRatio = 0;
float leftWheelRatio = 0;
float backWheelRatio = 0;

//vars for delta encoder values
float previousL = 0;
float previousR = 0;
float previousB = 0;

//position variables
float previousOrientationRadians = 0;
float previousGlobalX = 0;
float previousGlobalY = 0;
float absoluteOrientationRadians = 0;
float absoluteOrientationDegrees = 0;

//need to figure these out
//Constants for Motion Control, where "P" is proportional and "D" is derivative.
float turnP = 1.2;
float driveP = 6;
float turnD = 20;
float driveD = 40;
float turnMax = 40;
float driveMax = 60;
float errorMarginBase = 1;
float errorMarginTurnDeg = 0.5;

//reference x and y
float localX = 0;
float localY = 0;

//difference in wheels
float deltaLeft = 0;
float deltaRight = 0;
float deltaBack = 0;

//absolute position
float absoluteGlobalX = 0;
float absoluteGlobalY = 0;

//pi
float pi = 3.14159265359;

//encoder values
float currentLeft = 0;
float currentRight = 0;
float currentBack = 0;

float reduceAngle0to360( float angleDeg ) { //Takes an input angle in degrees and converts it to a positive angle value below 360.
  while(!(angleDeg >= 0 && angleDeg < 360)) {
    if( angleDeg < 0 ) { angleDeg += 360; }
    if(angleDeg >= 360) { angleDeg -= 360; }
  }
  return(angleDeg);
}

float reduceAngleMinus180to180( float angleDeg ) { //Takes an input angle in degrees and converts it to an angle between -180 and 180.
  while(!(angleDeg >= -180 && angleDeg < 180)) {
    if( angleDeg < -180 ) { angleDeg += 360; }
    if(angleDeg >= 180) { angleDeg -= 360; }
  }
  return(angleDeg);
}

void setDriveVelocity( float LFSpeed, float LBSpeed, float RBSpeed, float RFSpeed) {
  LeftFront.spin(directionType::fwd, LFSpeed, velocityUnits::pct);
  LeftBack.spin(directionType::fwd, LBSpeed, velocityUnits::pct);
  RightBackk.spin(directionType::fwd, RBSpeed, velocityUnits::pct);
  RightFront.spin(directionType::fwd, RFSpeed, velocityUnits::pct);
}

void setDriveVoltage( float LFSpeed, float LBSpeed, float RBSpeed, float RFSpeed) {
  LeftFront.spin(directionType::fwd, LFSpeed, voltageUnits::volt);
  LeftBack.spin(directionType::fwd, LBSpeed, voltageUnits::volt);
  RightBackk.spin(directionType::fwd, RBSpeed, voltageUnits::volt);
  RightFront.spin(directionType::fwd, RFSpeed, voltageUnits::volt);
}

void driveHold( void ) {
  LeftFront.stop(brakeType::hold);
  LeftBack.stop(brakeType::hold);
  RightBackk.stop(brakeType::hold);
  RightFront.stop(brakeType::hold);
}

void updateEncoders() { //Calculates the change in encoder values from the last cycle.
    currentLeft = (EncoderLeft.rotation(rotationUnits::deg))*(leftWheelRatio); 
    currentRight = (EncoderRight.rotation(rotationUnits::deg))*(rightWheelRatio); 
    currentBack = (EncoderBack.rotation(rotationUnits::deg))*(backWheelRatio); 

    deltaLeft = currentLeft - previousL; 
    deltaRight = currentRight - previousR;
    deltaBack = currentBack - previousB;

    previousL = currentLeft;
    previousR = currentRight;
    previousB = currentBack; 
}

void updatePosition() { //Approximates the motion of the robot as an arc, and updates its position accordingly
    absoluteOrientationRadians = (currentLeft-currentRight)/(rWidth + lWidth); 

    absoluteOrientationDegrees = reduceAngle0to360(absoluteOrientationRadians*(180/pi)); 

    float deltaA = (deltaLeft-deltaRight)/(rWidth + lWidth); //Change in angle.

    //Calulates coordinates relative to the chord of the robot's arc.
    if (deltaA == 0) { //Prevents divide by zero error.
        localX = deltaBack;
        localY = deltaRight;
    } else {
        localX = (2*sin(deltaA/2))*((deltaBack/deltaA)+bLength); 
        localY = (2*sin(deltaA/2))*((deltaRight/deltaA)+rWidth);
    }

    float localPolarAngle = 0;
    float localPolarLength = 0;

    //Caluclates polar coordinates.
    if (localX == 0 && localY == 0){ //Prevents two zeros from being passed to atan2.
        localPolarAngle = 0;
        localPolarLength = 0;
    } else {
        localPolarAngle = atan2(localY, localX); 
        localPolarLength = sqrt(pow(localX, 2) + pow(localY, 2)); 
    }

    //Converts polar coordinates to global coordinates.
    float globalPolarLength = localPolarLength; 
    float globalPolarAngle = localPolarAngle - previousOrientationRadians - (deltaA/2);

    float globalX = globalPolarLength*cos(globalPolarAngle); 
    float globalY = globalPolarLength*sin(globalPolarAngle); 

    //Calulates absolute position and orientation.
    absoluteGlobalX = previousGlobalX + globalX; 
    absoluteGlobalY = previousGlobalY + globalY; 

    previousGlobalX = absoluteGlobalX;
    previousGlobalY = absoluteGlobalY;

    //Sets up the previous orientation for deltas.
    previousOrientationRadians = absoluteOrientationRadians;
}

int positionTrack() { //Background thread used to position track full time.
  while(1){
    updateEncoders();
    updatePosition();

    Brain.Screen.printAt(1, 20, "Absolute X: %f Inches", absoluteGlobalX);
    Brain.Screen.printAt(1, 40, "Absolute Y: %f Inches", absoluteGlobalY);
    Brain.Screen.printAt(1, 60, "Absolute Rotation: %f Radians, %f Degrees", absoluteOrientationRadians, absoluteOrientationDegrees);
    Brain.Screen.printAt(1, 80, "Left Wheel: %f Inches, %f Degrees", currentLeft, EncoderLeft.rotation(vex::rotationUnits::deg));
    Brain.Screen.printAt(1, 100, "Right Wheel: %f Inches, %f Degrees", currentRight, EncoderRight.rotation(vex::rotationUnits::deg));
    Brain.Screen.printAt(1, 120, "Back Wheel: %f Inches, %f Degrees", currentBack, EncoderBack.rotation(vex::rotationUnits::deg));
  }
}

void driveReset(float X, float Y, float OrientationDeg) { //Tells the robot its position on the field at the beginning of a match.
  EncoderRight.setRotation(0, rotationUnits::deg);
  EncoderLeft.setRotation((rWidth+lWidth)*(pi/180)*(OrientationDeg)/(leftWheelRatio), rotationUnits::deg);
  EncoderBack.setRotation(0, rotationUnits::deg);

  previousL = 0;
  previousR = 0;
  previousB = 0;

  updateEncoders();
  updatePosition();

  previousGlobalX = 0;
  previousGlobalY = 0;

  previousGlobalX = X;
  previousGlobalY = Y;
}


void turnSlide(float endX, float endY, float endRotationDeg, float maxDriveValue, float maxTurnValue, float timeoutMsec, float drivePValue, float turnPValue, float driveDValue, float turnDValue, float driveErrorMargin, float turnErrorMarginDeg) {

  //Using a PD controller, simultaneously turns and drives to a point.

  endRotationDeg = reduceAngle0to360(endRotationDeg);

  float turnError = reduceAngleMinus180to180(endRotationDeg - absoluteOrientationDegrees);
  float driveError = sqrt(pow((endX - absoluteGlobalX), 2) + pow((endY - absoluteGlobalY), 2)); //Drive error is the absolute distance from the tracking center to the desired point, calculated using the Pythagorean Theorem.

  float deltaTurnError = 0;
  float deltaDriveError = 0;

  float prevTurnError = turnError;
  float prevDriveError = driveError;
  
  while( ((reduceAngleMinus180to180(turnError)) > turnErrorMarginDeg || (reduceAngleMinus180to180(turnError)) < -turnErrorMarginDeg || driveError > driveErrorMargin || driveError < -driveErrorMargin) && Brain.timer(timeUnits::msec) < timeoutMsec){
    turnError = reduceAngleMinus180to180(endRotationDeg - absoluteOrientationDegrees);
    driveError = sqrt(pow((endX - absoluteGlobalX), 2) + pow((endY - absoluteGlobalY), 2)); //Absolute distance from the tracking center to the desired point.

    deltaTurnError = turnError - prevTurnError;
    deltaDriveError = driveError - prevDriveError;

    float finalTurn = turnError*turnPValue - deltaTurnError*turnDValue; //Final value to pass to the motor, taking P and D loops into account.
    float finalDrive = driveError*drivePValue - deltaDriveError*driveDValue; //Final drive value to pass to the motor, taking P and D loops into account.

    prevTurnError = turnError;
    prevDriveError = driveError;

    //Prevents large values from being passed.
    if( finalTurn > maxTurnValue ) {
      finalTurn = maxTurnValue;
    }
    if( finalTurn < -maxTurnValue) {
      finalTurn = -maxTurnValue;
    }
    if( finalDrive > maxDriveValue ) {
      finalDrive = maxDriveValue;
    }
    if( finalDrive < -maxDriveValue ) {
      finalDrive = -maxDriveValue;
    }
    setDriveVelocity(
      finalDrive*(cos(absoluteOrientationRadians + atan2(endY - absoluteGlobalY, endX - absoluteGlobalX) - pi/4)) + finalTurn, // The robot uses trigonometry to determine the ideal value to pass to a motor
      finalDrive*(cos(3*pi/4-atan2(endY - absoluteGlobalY, endX - absoluteGlobalX)-absoluteOrientationRadians))+finalTurn,     // given each wheel's 45 degree offset. This value for the drive is then added
      finalDrive*(cos(absoluteOrientationRadians + atan2(endY - absoluteGlobalY, endX - absoluteGlobalX) - pi/4)) - finalTurn, // to the value for turning, which is negative on the right side of the bot.
      finalDrive*(cos(3*pi/4-atan2(endY - absoluteGlobalY, endX - absoluteGlobalX)-absoluteOrientationRadians))-finalTurn
    );

    task::sleep(5); //Changing this sleep time results in derivative values being thrown off.
  }
  driveHold();
}

void calibratePositionTrackers(void){
  Brain.Screen.clearScreen();
  while(not(Brain.Screen.pressing())){
    Brain.Screen.printAt(1, 20, "Move the robot forward 96 inches. Tap to begin. ");
  }
  while(Brain.Screen.pressing()){ }

  driveReset(0, 0, 0);
  Brain.Screen.clearScreen();
  while(not(Brain.Screen.pressing())){
    Brain.Screen.printAt(1, 20, "Move the robot forward 96 inches. Tap to end.");
  }
  while(Brain.Screen.pressing()){ }
  float leftwheelratio = 96/EncoderLeft.rotation(vex::rotationUnits::deg);
  float rightwheelratio = 96/EncoderRight.rotation(vex::rotationUnits::deg);

  Brain.Screen.clearScreen();
  while(not(Brain.Screen.pressing())){
    Brain.Screen.printAt(1, 20, "Move the robot right 96 inches. Tap to begin. ");
  }
  while(Brain.Screen.pressing()){ }

  driveReset(0, 0, 0);
  Brain.Screen.clearScreen();
  while(not(Brain.Screen.pressing())){
    Brain.Screen.printAt(1, 20, "Move the robot right 96 inches. Tap to end.");
  }
  while(Brain.Screen.pressing()){ }
  float backwheelratio = 96/EncoderBack.rotation(vex::rotationUnits::deg);

  Brain.Screen.clearScreen();
  while(not(Brain.Screen.pressing())){
    Brain.Screen.printAt(1, 20, "Spin the robot clockwise four times. Tap to begin. ");
  }
  while(Brain.Screen.pressing()){ }

  driveReset(0, 0, 0);
  Brain.Screen.clearScreen();
  while(not(Brain.Screen.pressing())){
    Brain.Screen.printAt(1, 20, "Spin the robot clockwise four times. Tap to end.");
  }
  while(Brain.Screen.pressing()){ }
  float drivedistance = ((EncoderLeft.rotation(rotationUnits::deg))*(leftwheelratio)-(EncoderRight.rotation(rotationUnits::deg))*(rightwheelratio))/(16*pi);

  Brain.Screen.clearScreen();
  while(not(Brain.Screen.pressing())){
    Brain.Screen.printAt(1, 20, "lWheelRatio: %f", leftwheelratio);
    Brain.Screen.printAt(1, 40, "rWheelRatio: %f", rightwheelratio);
    Brain.Screen.printAt(1, 60, "bWheelRatio: %f", backwheelratio);
    Brain.Screen.printAt(1, 80, "Drive Distance (all): %f", drivedistance);
  }
  while(Brain.Screen.pressing()){ }
}