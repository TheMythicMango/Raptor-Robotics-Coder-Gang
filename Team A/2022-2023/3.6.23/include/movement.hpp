#ifndef MOVEMENT
#define MOVEMENT

#include <iostream>
#include <cmath>
#include <vector>
// #include "angle.hpp"
#include "state.hpp"
#include "pid.hpp"
#include "../src/tools.cpp"

//#include "sensing.hpp"
class Movement
{
public:
    static PID leftVelPID;
    static PID rightVelPID;
    static PID leftPIDXL;
    static PID rightPIDXL;

    static Resting restingTurn;
    static Resting restingTurnQ;
    static Resting restingMove;
    static Resting restingMoveQ;
    
    static void resetMovePID();
    static int functionIndex;
    static std::vector<double> targetPos;

    // driverControl.cpp
    static std::vector<double> move(double, double);
    static std::vector<double> drive(std::vector<int>);

    //                                                                              .11, .05, .005, .004, .005, .003
    static void travel(double dist,                                  State *state, double accel = .11, double maxVel = .05, double decel = .005, double velF = .004, double buff = .005, double goal = .003);
    static void travelTo(bool inMeters, std::vector<double> goalPos, State *state, double accel = .11, double maxVel = .05, double decel = .005, double velF = .004, double buff = .005, double goal = .003);
    static void headingCorrection(std::vector<double> targPos, State *state);
    static void _headingCorrection(std::vector<double> targPos, State *state);

    //.6, .25, .027, .015, .015, .015
    static void turn               (double ang, State *state, double accel = .6, double maxVel = .25, double decel = .027, double velF = .015, double buff = .015, double goal = .015);
    static void turnToA            (double ang, State *state, double accel = .6, double maxVel = .25, double decel = .027, double velF = .015, double buff = .015, double goal = .015);
    static void turnTo(bool inMeters, std::vector<double> pos, State *state, double accel = .5, double maxVel = .25, double decel = .07, double velF = .03, double buff = .015, double goal = .015);
    
    //complexAuton
    // static void routeTo(std::vector<double> pos, State*);

    static void pursue(bool inMeters, State *state, std::vector<double> finalState, double lookAhead = .3, double reverse = false, double = .12, double = .06, double = .006);
    static void _pursue(State* state);

    static void turnVel(State *, double targVel, double targAccel=0);
    static void moveVel(State *, double targVel, double targAccel=0);

    //autonManagement
    static void tick(State *state);
    static void rest(State *state);
    static double velL(State *state, double dltTime = dltT);
    static double accelL(State *state);
    static double accelR(State *state);
    static double velR(State *state, double dltTime = dltT);
    static double getTurnVel(State *state);
    static double getMoveVel(State *state);
    static void setVel(State *state, double velL, double accelL, double velR, double accelR);

private:
    //autonLinear
    static std::vector<double> _travel(State *, bool travelTo = false);
    static std::vector<double> _travelTo(State *state);

    //autonTurn
    static void _turnSet(double accel, double maxVel, double decel, double velF, double buff, double goal);
    static std::vector<double> _turn(State *);
    static std::vector<double> _turnTo(State *state);

    //complexAuton
    // static void _routeTo(State *state);
    
    //autonManagement
    static double _velL(State *state);
    static double _velR(State *state);
};

#endif