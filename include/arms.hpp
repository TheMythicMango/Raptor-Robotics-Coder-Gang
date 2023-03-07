#ifndef BOTARMS
#define BOTARMS

#include <iostream>
#include <vector>
#include "pros/vision.h"
// #include "state.hpp"
#include "pid.hpp"
#include "Electronics.hpp"

class Arms
{
    static float targetVel;
    static float voltMod;
public:
    static pros::vision_color_code_t rollerCode;
    static PID pidFly;
    static void initFly(float actVel, float targVel, float I = 0);
    static void initFlyFast(float actVel, float targVel, float I = 0);
    static void setFly(float vel, float I = 0);
    static void launchVel(float actVel);//returns voltage
    static float getVolts(float vel);
    // static void launchGoal(double dist);
    // static void intakeVel(double vel, State *state);
    static bool rollerTo(State *state, bool red); // true: red, false: blue

};

#endif