#include "Electronics.hpp"
#include "arms.hpp"
#include "cycle.hpp"
#include "movement.hpp"
#include "../dist.cpp"
#include "pros/rtos.hpp"
#include "autonFlyTest.cpp"
#include "../ConstantsAuton.cpp"


// static void launchHigh(State *state, int delay = 6);
static void autonTest(State *state){
    int rollerTime = 25;
    double rollerDist = -360*.65;
    targFlyVel = 376;
    pros::delay(1);
    intake.move(0);
    now = pros::c::millis();
    Arms::initFly(0, targFlyVel);
    cycle(state, true);
    cycle(state, true);
    state->pos = {Dist::inToM(12*7+1.75),Dist::inToM(13.925),pi/2};

    Movement::travelTo(false,{posRollF-5, 14}, state);
    intake.move(-12000);
    while(!Movement::restingMove.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false,{122.63, 122.63}, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    //@roller 1
    Movement::moveVel(state, -.02);
    for(int i = 0; i<30; i++){cycle(state, true);}
    Movement::rest(state);
    intake.move_relative(rollerDist, 600);
    for(int i = 0; i<rollerTime; i++){cycle(state, true);}
    intake.move(0);

    Movement::travel(Dist::inToM(3), state);
    while(!Movement::restingMoveQ.isRested(state->posErr/1.5)){cycle(state, true);}

    Movement::turnTo(false,{126.63, 122.63}, state);
    while(!Movement::restingTurn.isRested(state->posErr)){cycle(state, true);}

    //@fire 1
    Movement::rest(state);
    while(state->flyVel<targFlyVel-1){
        cycle(state, true);
    }
    flyRun(state, 25);
    intake.move(0);
    targFlyVel = 352.5;
    angler.set_value(false);
    Arms::setFly(targFlyVel);

    Movement::turnTo(false, {pos2DL[0]-3, pos2DL[1]+3}, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}
    intake.move(-127);

    Movement::pursue(false, state, {pos2DL[0]-3, pos2DL[1]+3});
    while(!Movement::restingMove.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false,{122.63, 122.63}, state);
    while(!Movement::restingTurn.isRested(state->posErr/1.2)){cycle(state, true);}

    Movement::rest(state);
    flyRun(state, 25);
    intake.move(0);
    targFlyVel = 270;
    angler.set_value(false);
    Arms::setFly(targFlyVel);
    intake.move(0);

    // Movement::turnTo(false,{13, posRollF-7}, state);
    // while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    // intake.move(127);
    // Movement::travelTo(false, {13, posRollF-7}, state);
    // while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    // Movement::turnToA(90,state);
    // while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    // //@roller 2
    // Movement::moveVel(state, -.02);
    // for(int i = 0; i<20; i++){cycle(state, true);}
    // Movement::rest(state);
    // intake.move_relative(rollerDist, 600);
    // for(int i = 0; i<rollerTime; i++){cycle(state, true);}
    // intake.move(0);

    Movement::rest(state);
    intake.move(0);
    Arms::initFly(0,0);
    return;

}