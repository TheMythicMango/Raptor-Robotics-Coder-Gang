#include "Electronics.hpp"
#include "arms.hpp"
#include "cycle.hpp"
#include "movement.hpp"
#include "../dist.cpp"
#include "pros/rtos.hpp"
#include "autonFlyTest.cpp"
#include "../ConstantsAuton.cpp"


// static void launchHigh(State *state, int delay = 6);
static void autonSkimTest(State *state){
    int rollerTime = 20;
    double rollerDist = -360*.65;
    targFlyVel = 350;
    pros::delay(1);
    intake.move(0);
    now = pros::c::millis();
    Arms::initFly(0, targFlyVel);
    cycle(state, true);
    state->pos = {Dist::inToM(13.75),Dist::inToM(12*5+1.925),pi/2};

    Movement::turnTo(false, pos2DL, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    Movement::pursue(false, state, pos2DL);
    intake.move(-12000);
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false,{122.63, 122.63}, state);
    while(!Movement::restingTurn.isRested(state->posErr)){cycle(state, true);}

    intake.move(0);
    Movement::rest(state);
    for(int i =0; i<10; i++){cycle(state, true);}
    flyRun(state, 30);
    intake.move(-12000);
    targFlyVel = 380;
    Arms::setFly(targFlyVel);

    // Arms::initFly(0,0);
    // intake.move(0);
    // return;

    Movement::turnTo(false, {pos2WL[0]-6,pos2WL[1]}, state);
    while(!Movement::restingTurnQ.isRested(state->posErr/2)){cycle(state, true);}

    Movement::pursue(false, state, {pos1WL[0]-11,pos1WL[1]+2});
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false,{122.63, 122.63}, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    Movement::travel(Dist::inToM(20), state);
    while(!Movement::restingMove.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false,{122.63, 122.63}, state);
    while(!Movement::restingTurn.isRested(state->posErr)){cycle(state, true);}


    intake.move(0);
    for(int i =0; i<10; i++){
        cycle(state, true);
    }
    Movement::rest(state);
    flyRun(state, 30);
    intake.move(0);
    targFlyVel = 270;
    Arms::setFly(targFlyVel);

    // Movement::turnTo(false, {13, posRollF-7}, state);
    // while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    // Movement::travelTo(false, {13, posRollF-7} ,state);
    // while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    // Movement::turnToA(Angle::toRad(90), state);
    // while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    // Movement::moveVel(state, -.02);
    // for(int i = 0; i<30; i++){cycle(state, true);}
    // Movement::rest(state);
    // intake.move_relative(rollerDist, 600);
    // for(int i = 0; i<rollerTime; i++){cycle(state, true);}
    // intake.move(0);

    intake.move(0);
    Movement::rest(state);

}


