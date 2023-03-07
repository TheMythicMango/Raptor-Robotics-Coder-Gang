#include "Electronics.hpp"
#include "arms.hpp"
#include "cycle.hpp"
#include "movement.hpp"
#include "../dist.cpp"
#include "pros/rtos.hpp"
//high goal and far roller
#ifndef FLYTEST
#define FLYTEST
static void flyRun(State*, int = 20);

static void autonFlyTest(State *state){
    // Resting flyResting(.2, .1, dltT, 5);
    state->pos[2] = Angle::toRad(90);
    now = pros::c::millis();
    targFlyVel = 355;
    bool inAuton = true;
    double iAdder;
    Arms::initFly(0, targFlyVel);
    pros::delay(5);
    now = pros::c::millis();
    // Arms::initFly(state->flyVel, targFlyVel);
    int delay = 6;
    for(int i = 0; i<200; i++){
        cycle(state, inAuton);
    }
    double tempVolt=Arms::getVolts(state->flyVel);
    iAdder = Arms::pidFly.getError();
    // while(true){

    flyRun(state, 25);
    // for(int i = 0; i<20; i++){cycle(state, true);}
    // }
    Arms::initFly(state->flyVel, 0);
    fly.move(0);
    intake.move(0);
}

static bool goFast = false;
static void flyCycle(State *state){
    if(state->flyVel<(targFlyVel-1.5)){
        goFast = true; 
        Arms::setFly(0, 0);
    }
    if(goFast){
        if(state->flyVel > targFlyVel-.2){
            goFast = false;
            Arms::setFly(targFlyVel);
        }
        else fly.move_voltage(12000);
    }
}

static void flyRep(State *state, int extake, int delay){
    intake.move_voltage(12000);
    for(int i = 0; i<extake; i++){flyCycle(state); cycle(state, true);}
    intake.move_voltage(-12000);
    for(int i = 0; i<delay; i++){flyCycle(state); cycle(state, true);}
}

static void flyRun(State *state, int delay){
    flyRep(state, 12, delay);
    flyRep(state, 12, delay);
    flyRep(state, 15, delay-3);
    Arms::setFly(targFlyVel);
}
#endif