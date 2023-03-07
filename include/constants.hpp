#include <cmath>
#include <sys/_stdint.h>
#include <vector>
#ifndef Constants
#define Constants

    extern bool ON_RED;
    static uint32_t now;
    extern bool ON_ROLLER; 
    extern double targFlyVel;
    extern const double pi;
    extern const double twoPi;
    extern const double pi180;

    extern const double botWidth; //meters
    extern const double botLength; //meters
    extern const std::vector<double> initialPosition; //x in meters, y in meters, rad

    extern const double RWheelToMotor;
    const double rpm_to_radps = 2*pi/60;
    extern const double Kemf;
    extern const double Ktorque;

    extern const double resistance;

    //adjust one to fix angle drift(bigger R = turn left), adjust both to fix scale(bigger = percieved move farther)
    extern const double wheelRadiusOd; // inches to meters
    extern const double wheelRadiusDr; // inches to meters
    extern const double wheelCirc;
    extern const double wheelCircDr;//in meters
    extern const double MaxRawTorque;
    extern const double mass; // lbs to kg

   //adjust to fix turning amount (bigger = smaller turn perceived)
    extern const double leftOffset; //meters //.2
    extern const double rightOffset; //meters //.195
    extern const double CWheelOffset; //meters
    
    extern const double length; //meters
    extern const double dltT; //seconds
    extern const double rotInert;
    extern const double dragMech;
    extern const double Rdrift;
    extern const double numMotors;
    
#endif