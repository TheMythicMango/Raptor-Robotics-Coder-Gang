// #include "Electronics.hpp"
#include "movement.hpp"
#include "pid.hpp"
#include "state.hpp"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include "angle.cpp"

int Movement::functionIndex = 0;

Resting Movement::restingMove(.075,.005, dltT, 4);
Resting Movement::restingTurn(.075, .015, dltT, 2);

Resting Movement::restingMoveQ(.024,.007, dltT, 2);
Resting Movement::restingTurnQ(.075, .022, dltT, 1.2);

PID Movement::leftVelPID(0,0,0,0);
PID Movement::rightVelPID(0,0,0,0);

PID Movement::leftPIDXL(0,0,0,0);//(.2, 0, 0, 0,4,.5,1,0,0,4,4, false);
PID Movement::rightPIDXL(0,0,0,0);//(.2, 0, 0, 0,4,.5,1,0,0,4,4, false);

void Movement::resetMovePID(){
    leftVelPID = PID (0,0, 0, 0, 0,.5,1,1,0,0,6,6, true);
    rightVelPID = PID(0,0, 0, 0, 0,.5,1,1,0,0,6,6, true);
    leftPIDXL = PID (0,0, 0, 0, 0,1,1,1,0,0,2,2, false);
    rightPIDXL = PID(0,0, 0, 0, 0,1,1,1,0,0,2,2, false); 
}

//m/s
double Movement::getMoveVel(State *state){
    return (state->vel[0]+state->vel[1])/RWheelToMotor;
}
//rad/s
double Movement::getTurnVel(State *state){
    return (state->vel[0]-state->vel[1])/(RWheelToMotor*(botWidth));
}

double velk = 1.7;
double out;
double actVel;
//@output in rpm
double Movement::velL(State *state, double dltT){
    double targetVel = state->stateFut.at(0).at(0);
    // targetVel+=state->stateFut.at(0).at(1)*dltT;
    // state->stateFut.at(0).at(0) = targetVel;
    targetVel=(targetVel*RWheelToMotor);

    state->stateFut.at(0).at(0)+=state->stateFut.at(0).at(1)*dltT;
    return targetVel;
}

//@output in rpm
double Movement::velR(State *state, double dltT){
    double targetVel = state->stateFut.at(1).at(0);
    // targetVel+=state->stateFut.at(1).at(1)*dltT;
    // state->stateFut.at(1).at(0) = targetVel;
    targetVel=(targetVel*RWheelToMotor);

    state->stateFut.at(1).at(0)+=state->stateFut.at(1).at(1)*dltT;
    return targetVel;
}

//rpm
double Movement::accelL(State *state){
    double targetAccel = state->stateFut.at(0).at(1);
    targetAccel=(targetAccel*RWheelToMotor);

    return targetAccel;
}
//rpm
double Movement::accelR(State *state){
    double targetAccel = state->stateFut.at(1).at(1);
    targetAccel=(targetAccel*RWheelToMotor);

    return targetAccel;
}

void Movement::setVel(State *state, double velL, double accelL, double velR, double accelR){
    state->stateFut = {{velL,accelL},{velR, accelR}};
    functionIndex = 4;
}


void Movement::rest(State *state){
    state->voltDrive = {0,0};
    moveVel(state, 0);
    functionIndex = 6;
}

std::vector<double> output = {0,0};
void Movement::tick(State *state){
    state->doVoltDrive = true;
    state->turning = false;
    switch (functionIndex) {
    case 1:
        state->doVoltDrive = false;
        output = _travel(state);
        moveVel(state, output[0], output[1]);
        functionIndex = 1;
        break;
    // case 2:
    //     _routeTo(state);
    //     state->doVoltDrive = false;
    //     break;
    case 3:
        state->doVoltDrive = false;
        output = _turn(state);
        turnVel(state, output[0], output[1]);
        state->turning = true;
        functionIndex = 3;
        break;
    case 4:
        state->doVoltDrive = false;
        break;
    case 6:
        break;
    case 7:
        state->doVoltDrive = false;
        output = _turnTo(state);
        turnVel(state, output[0], output[1]);
        state->turning = true;
        functionIndex = 7;
        break;
    case 8:
        state->doVoltDrive = false;
        output = _travelTo(state);
        moveVel(state, output[0], output[1]);
        // _headingCorrection(targetPos, state);
        functionIndex = 8;
        break;
    case 9:
        _pursue(state);
        state->doVoltDrive = false;
        functionIndex = 9;
    default:
        break;
    }
    
}