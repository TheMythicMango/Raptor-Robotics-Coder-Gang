#include "movement.hpp"
#include "angle.cpp"
#include <cmath>
#include <cstdio>
#include <string>
#include "dist.cpp"

std::vector<double> startPos = {0,0};
std::vector<double> Movement::targetPos = {0,0};
double targetDist;

double rDecel = .08;
double rAccel = .16;
double maxVelocity = 1;
double buffer = 0;
bool atVelF = false;
void Movement::travelTo(bool inMeters, std::vector<double> targPos, State *state, double accel, double maxVel, double decel, double velF, double buff, double goal){
    if(!inMeters)targPos = {Dist::inToM(targPos[0]), Dist::inToM(targPos[1])};
    double dist = sqrt(pow(state->pos[0]-targPos[0],2)+pow(state->pos[1]-targPos[1],2));
    targetPos = targPos;
    travel(dist, state, accel, maxVel, decel, velF, buff, goal);
    // headingCorrection(targPos, state);
    functionIndex = 8;
}

double velocity;
double prevVelocity;
double traveled;
double velF;
static double goal;
void Movement::travel(double dist, State *state, double accel, double maxVel, double decel, double velFin, double buff, double goalBuff){
    rAccel = accel;
    maxVelocity = maxVel;
    rDecel = decel;
    buffer = buff;
    startPos = {state->pos[0], state->pos[1]};
    velocity = 0;
    prevVelocity = 0;
    targetDist = dist;
    functionIndex = 1;
    traveled = 0;
    velF = velFin;
    atVelF = false;
    goal = goalBuff;
    resetMovePID();
    state->posErr = 1000000;
}

std::vector<double> Movement::_travelTo(State *state){
    return _travel(state, true);
}

static double targetVel;
double accel;
//output in m/s of robot moving
std::vector<double> Movement::_travel(State *state, bool travelTo)
{
    traveled = sqrt(pow(state->pos[0]-startPos[0],2)+pow(state->pos[1]-startPos[1],2));
    double dist = fabs(fabs(targetDist)-fabs(traveled));
    
    state->posErr = dist;
    if(dist<goal){dist = 0; targetVel = 0; accel = 0;}
    else if( dist < buffer || atVelF ){ dist = 0; targetVel = velF; accel = 0;}
    else{
        dist-=buffer;
        double decelVel = sqrt(2*rDecel*dist+velF*velF);
        velocity+=rAccel*dltT;

        accel = rAccel;
        if(decelVel<velocity){ 
            velocity = decelVel; accel = -rDecel;
            if(fabs(getMoveVel(state))<=velF) atVelF = true;  
        }
        else if(velocity>maxVelocity){velocity = maxVelocity; accel = 0;}
        
        targetVel=velocity;
    }
    if(traveled>targetDist){ targetVel*=-1; accel*=-1; }

    prevVelocity = targetVel;
    return {targetVel, accel};
}

//m/s
void Movement::moveVel(State *state, double targVel, double targAccel){
    state->stateFut = {{targVel,targAccel},{targVel, targAccel}};
    functionIndex = 4;
}

// void Movement::headingCorrection(std::vector<double> targPos, State *state){
//     turnTo(targPos, state, .2, .02, .007, 0, .03);
// }
// void Movement::_headingCorrection(std::vector<double> targPos, State *state){
//     double targHeading = Angle::getAng(goalPos[0]-state->pos[0], goalPos[1]-state->pos[1]);
//     double error = Angle::getDist(state->pos[2], targHeading);
//     double velMod = fabs(cos(error));
//     // state->outputs.push_back(std::to_string(Angle::toDeg(targHeading)));
//     // state->outputs.push_back(std::to_string(Angle::toDeg(state->pos[2])));
//     double posErr = state->posErr;
//     std::vector<double> headingState = _turnTo(state);
//     state->posErr = posErr;
//     // if(error<0) turnMod*=-1;
//     double targVel = state->stateFut[0][0];
//     // state->stateFut[0][0] = targVel*velMod+fabs(targVel)*turnMod;
//     state->stateFut[0][0] = targVel*velMod+headingState[0];
//     // state->stateFut[1][0] = targVel*velMod-fabs(targVel)*turnMod;
//     state->stateFut[1][0] = targVel*velMod-headingState[0];
// }