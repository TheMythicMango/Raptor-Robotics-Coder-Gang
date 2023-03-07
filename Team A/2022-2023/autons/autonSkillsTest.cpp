#include "Electronics.hpp"
#include "arms.hpp"
#include "cycle.hpp"
#include "movement.hpp"
#include "../dist.cpp"
#include "pros/rtos.hpp"
#include "autonFlyTest.cpp"
#include "../ConstantsAuton.cpp"


// static void launchHigh(State *state, int delay = 6);
static int rollerTime = 28;
static double rollerDist = -360*1.25;
static void autonSkillsTest(State *state){
    targFlyVel = 376;
    pros::delay(1);
    intake.move(0);
    now = pros::c::millis();
    Arms::initFly(0, targFlyVel);
    cycle(state, true);
    cycle(state, true);
    state->pos = {Dist::inToM(12*7+1.75),Dist::inToM(13.925),pi/2};

    //4 seconds
    Movement::turnToA(Angle::toRad(83), state, .3, .25, .07, .015, .015);
    while(!Movement::restingTurn.isRested(state->posErr)){cycle(state, true);}

    Movement::travel(Dist::inToM(25), state);
    intake.move(-12000);
    while(!Movement::restingMove.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false,{126.63, 122.63}, state);
    while(!Movement::restingTurn.isRested(state->posErr)){cycle(state, true);}

    //@fire 1
    Movement::rest(state);
    intake.move(0);
    while(state->flyVel<targFlyVel-1){
        cycle(state, true);
    }
    flyRun(state, 30);
    targFlyVel = 280;
    angler.set_value(true);
    Arms::setFly(targFlyVel);

    //@roller 1
    Movement::moveVel(state, -.02);
    for(int i = 0; i<40; i++){cycle(state, true);}
    Movement::rest(state);
    intake.move_relative(rollerDist, 600);
    for(int i = 0; i<rollerTime; i++){cycle(state, true);}
    intake.move(0);

    Movement::travel(Dist::inToM(3), state);
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false, {pos8D[0]+2, pos8D[1]}, state);
    while(!Movement::restingTurnQ.isRested(state->posErr/1.5)){cycle(state, true);}

    Movement::travel(Dist::inToM(12), state, .13, .06, .016, .004, .005, .003);
    intake.move(0);
    while(!Movement::restingMoveQ.isRested(state->posErr/2)){cycle(state, true);}

    Movement::travel(Dist::inToM(16), state, .11, .01, .005, .004);
    intake.move(-12000);
    while(!Movement::restingMove.isRested(state->posErr)){cycle(state, true);}

    Movement::turnToA(Angle::toRad(-90), state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    intake.move(0);
    Movement::travel(Dist::inToM(-25), state);
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    //@roller2
    Movement::moveVel(state, -.015);
    for(int i = 0; i<30; i++){cycle(state, true);}
    Movement::rest(state);
    intake.move_relative(rollerDist, 600);
    for(int i = 0; i<rollerTime; i++){cycle(state, true);}
    intake.move(0);

    Movement::travel(Dist::inToM(3), state);
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false, posHighGoalLB, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}
    Movement::pursue(false,state, {posHighGoalLB[0], posHighGoalLB[1]}, .3);
    while(!Movement::restingMove.isRested(state->posErr/2.0)){cycle(state, true);}

    Movement::turnTo(false, {posHighGoalL[0], posHighGoalL[1]-3}, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    //@fire 2
    Movement::rest(state);
    Arms::setFly(600);
    intake.move(127);
    for(int i = 0; i<60; i++){cycle(state, true);}
    intake.move(0);
    angler.set_value(false);
    targFlyVel = 310;
    Arms::setFly(targFlyVel);

    Movement::turnToA(Angle::toRad(-95), state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    Movement::travel(Dist::inToM(-52), state);
    while(state->posErr>.01){cycle(state, true);}

    Movement::turnTo(false, pos2DL, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}
    
    intake.move(-127);
    Movement::pursue(false,state, pos2DL, .3);
    while(!Movement::restingMoveQ.isRested(state->posErr*1.4)){cycle(state, true);}

    Movement::turnTo(false, posHighGoalL, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    //@fire 3
    Movement::rest(state);
    flyRun(state, 15);
    intake.move(0);
    angler.set_value(true);
    targFlyVel = 280;
    Arms::setFly(targFlyVel);

    Movement::turnTo(false, {pos2WL[0]-4, pos2WL[1]+1.5}, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    intake.move(-128);
    Movement::pursue(false,state, {11,pos1WL[1]+2}, .3);
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}    

    Movement::turnToA(Angle::toRad(180), state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}
    intake.move(0);

    Movement::travelTo(false, {posHighGoalLT[0], posHighGoalLT[1]-3}, state);
    while(!Movement::restingMove.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false, {posHighGoalL[0]-3, posHighGoalL[1]}, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    //@fire 4
    Movement::rest(state);
    Arms::setFly(600);
    intake.move(127);
    for(int i = 0; i<60; i++){cycle(state, true);}
    intake.move(0);
    angler.set_value(false);
    targFlyVel = 320;
    Arms::setFly(targFlyVel);

    Movement::turnToA(Angle::toRad(186), state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    Movement::pursue(false,  state, {13, posRollF-10}, .5, true);
    while(!Movement::restingMove.isRested(state->posErr)){cycle(state, true);}

    Movement::turnToA(Angle::toRad(90), state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    //@roller 3
    Movement::moveVel(state, -.02);
    for(int i = 0; i<45; i++){cycle(state, true);}
    Movement::rest(state);
    intake.move_relative(rollerDist, 600);
    for(int i = 0; i<rollerTime; i++){cycle(state, true);}
    intake.move(0);

    Movement::travel(Dist::inToM(3), state, .11, .01, .005);
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false, {posRollC+6, fieldWidth-18}, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}
    intake.move(-127); 

    Movement::travelTo(false, {posRollC+6, fieldWidth-18}, state);
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    Movement::turnToA(Angle::toRad(185), state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}
    Movement::rest(state);
    intake.move(127);
    for(int i = 0; i<30; i++){cycle(state, true);}
    intake.move(0);

    //@roller 4
    Movement::moveVel(state, -.02);
    for(int i = 0; i<30; i++){cycle(state, true);}
    Movement::rest(state);
    intake.move_relative(rollerDist, 600);
    for(int i = 0; i<rollerTime; i++){cycle(state, true);}
    intake.move(0);
    angler.set_value(false);

    Movement::travel(Dist::inToM(3), state);
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false, pos3DR, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}
    intake.move(-127);

    Movement::pursue(false,state, pos3DR);
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false, {posHighGoalR[0]+2, posHighGoalR[1]}, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    //@fire 5
    Movement::rest(state);
    flyRun(state, 15);
    intake.move(0);
    angler.set_value(false);
    targFlyVel = 270;
    Arms::setFly(targFlyVel);

/*
    Movement::turnTo(false, {pos5WR[0]+4, pos5WR[1]}, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    intake.move(-128);
    Movement::pursue(false,state, {fieldWidth-11,pos6WR[1]-2}, .3);
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}    

    Movement::turnToA(Angle::toRad(0), state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}
    intake.move(0);

    Movement::travelTo(false, {posHighGoalRT[0], posHighGoalRT[1]+3}, state);
    while(!Movement::restingMove.isRested(state->posErr)){cycle(state, true);}

    Movement::turnTo(false, posHighGoalR, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    //@fire 6
    Movement::rest(state);
    Arms::setFly(600);
    intake.move(127);
    for(int i = 0; i<60; i++){cycle(state, true);}
    intake.move(0);
    angler.set_value(false);
    Arms::setFly(280);
*/

    Movement::turnTo(false, {pos9D[0]+4, pos9D[1]-4}, state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    Movement::travelTo(false, {pos9D[0]+4, pos9D[1]-4}, state);
    while(!Movement::restingMoveQ.isRested(state->posErr)){cycle(state, true);}

    Movement::turnToA(Angle::toRad(-45), state);
    while(!Movement::restingTurnQ.isRested(state->posErr)){cycle(state, true);}

    expansion.set_value(true);

    Movement::rest(state);
    intake.move(0);
    Arms::initFly(0,0);
}


