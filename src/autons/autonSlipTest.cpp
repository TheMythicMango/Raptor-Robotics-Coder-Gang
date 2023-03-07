#include "Electronics.hpp"
#include "arms.hpp"
#include "cycle.hpp"
#include "movement.hpp"
#include "../dist.cpp"
#include "pros/rtos.hpp"
#include "autonFlyTest.cpp"


// static void launchHigh(State *state, int delay = 6);
static void autonSlipTest(State *state){
    targFlyVel = 352;
    pros::delay(1);
    intake.move(0);
    now = pros::c::millis();
    Arms::initFly(0, 0);
    cycle(state, true);
    state->pos = {0,0,0};

    for(int i = 0; i<10; i++){
        Movement::travel(Dist::inToM(24), state,.12,.06,.006);
        intake.move(-12000);
        while(!Movement::restingMove.isRested(state->posErr)){cycle(state, true);}

        Movement::turnToA(pi, state);
        while(!Movement::restingTurn.isRested(state->posErr)){cycle(state, true);}

        Movement::travel(Dist::inToM(24), state, .06, .06, .003);
        intake.move(-12000);
        while(!Movement::restingMove.isRested(state->posErr)){cycle(state, true);}

        Movement::turnToA(0, state);
        while(!Movement::restingTurn.isRested(state->posErr)){cycle(state, true);}
    }
}