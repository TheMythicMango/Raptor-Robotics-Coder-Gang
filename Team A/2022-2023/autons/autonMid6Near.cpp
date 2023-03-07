#include "Electronics.hpp"
#include "arms.hpp"
#include "cycle.hpp"
#include "movement.hpp"
#include "../dist.cpp"
#include "pros/rtos.hpp"
#include "autonFlyTest.cpp"
#include "../ConstantsAuton.cpp"


// static void launchHigh(State *state, int delay = 6);
static void autonMid6Near(State *state){
    int rollerTime = 20;
    double rollerDist = -360*.65;
    targFlyVel = 355;
    pros::delay(1);
    intake.move(0);
    now = pros::c::millis();
    Arms::initFly(0, targFlyVel);
    cycle(state, true);
    state->pos = {Dist::inToM(13.75),Dist::inToM(12*5+1.925),pi/2};;

    //4 seconds
    Movement::turnTo(false, {pos1DL[0]+13, pos1DL[1]-13}, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    Movement::travelTo(false, {pos1DL[0]+13, pos1DL[1]-13}, state);
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false,{126.63, 122.63}, state);
    while(!Movement::restingTurn.isRested(state->posErr)){cycle(state, true);}

    Movement::rest(state);
    while(state->flyVel<targFlyVel-1){
        cycle(state, true);
    }

    flyRep(state, 12, 20);
    flyRep(state, 15, 7);
    Arms::setFly(targFlyVel);
    intake.move(0);
    targFlyVel = 360;
    Arms::setFly(targFlyVel);

    // Arms::initFly(0,0);
    // intake.move(0);
    // return;

    Movement::turnToA(Angle::toRad(-45), state);
    while(!Movement::restingTurnQ.isRested(state->posErr/2)){cycle(state, true);}

    Movement::travel(Dist::inToM(12), state, .13, .06, .03, .004, .005, .003);
    intake.move(0);
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    Movement::travel(Dist::inToM(17), state, .11, .04, .005, .004);
    intake.move(-12000);
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false,{122.63, 118.63}, state);
    while(!Movement::restingTurn.isRested(state->posErr/1.2)){cycle(state, true);}


    intake.move(0);
    for(int i =0; i<10; i++){
        cycle(state, true);
    }
    Movement::rest(state);
    flyRep(state, 10, 20);
    flyRep(state, 10, 20);
    flyRep(state, 15, 7);
    intake.move(0);
    targFlyVel = 270;
    Arms::setFly(targFlyVel);

    Movement::turnToA(Angle::toRad(135), state);
    while(!Movement::restingTurnQ.isRested(state->posErr/1.5)){cycle(state, true);}

    Movement::travel(Dist::inToM(-18) ,state);
    while(!Movement::restingMoveQ.isRested(state->posErr/1.5)){cycle(state, true);}

    Movement::turnToA(Angle::toRad(83), state);
    while(!Movement::restingTurnQ.isRested(state->posErr/2.5)){cycle(state, true);}

    Movement::moveVel(state, -.02);
    for(int i = 0; i<25; i++){cycle(state, true);}
    Movement::rest(state);
    intake.move_relative(rollerDist, 600);
    for(int i = 0; i<rollerTime; i++){cycle(state, true);}
    intake.move(0);

    intake.move(0);
    Movement::rest(state);

}


