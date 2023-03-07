#include "movement.hpp"
#include "angle.cpp"
#include <cstdio>
#include "dist.cpp"

double targetAng=0;
double targetVelT=0;
bool atFinalVelT;
void Movement::turn(double ang, State *state, double accel, double maxVel, double decel, double velFT, double buff, double goal ){
    targetAng = ang+state->pos[2];
    _turnSet(accel, maxVel, decel, velFT, buff, goal);
    state->posErr = 1000000;
}
void Movement::turnToA(double ang, State *state, double accel, double maxVel, double decel, double velFT, double buff, double goal){
    targetAng = fmod(ang, twoPi);
    _turnSet(accel, maxVel, decel, velFT, buff, goal);
    state->posErr = 1000000;
}
void Movement::turnTo(bool inMeters, std::vector<double> pos, State *state, double accel, double maxVel, double decel, double velFT, double buff, double goal){
    if(!inMeters)pos = {Dist::inToM(pos[0]), Dist::inToM(pos[1])};
    targetPos = pos;
    targetAng = atan((pos[0]-state->pos[0]) / (pos[1]-state->pos[1]));
    if ((pos[1]-state->pos[1]) < 0)
    {
        targetAng += pi;
    }
    _turnSet(accel, maxVel, decel, velFT, buff, goal);
    functionIndex = 7;
    state->posErr = 1000000;
}

double accelT;
double decelT;
double maxVelT;
double bufferT;
double velFT;
double goalT;
void Movement::_turnSet(double accel, double maxVel, double decel, double velF, double buff, double goal){
    targetAng = fmod(targetAng, twoPi);
    if (targetAng < 0)
    {
        targetAng += twoPi;
    }
    accelT = accel;
    decelT = decel;
    maxVelT = maxVel;
    bufferT = buff;
    targetVelT = 0;
    functionIndex = 3;
    velFT = velF;
    atFinalVelT = false;
    goalT = goal;
    resetMovePID();
}

std::vector<double> Movement::_turnTo(State *state){
    targetAng = atan((targetPos[0]-state->pos[0]) / (targetPos[1]-state->pos[1]));
    if ((targetPos[1]-state->pos[1]) < 0)
    {
        targetAng += pi;
    }
    if (targetAng < 0)
    {
        targetAng += twoPi;
    }
    if(fabs(Angle::getDist(targetAng, state->pos[2]))>pi/2){
        if(sqrt(pow(targetPos[0]-state->pos[0], 2)+pow(targetPos[1]-state->pos[1], 2))<.5){
            targetAng+=pi;
            fmod(targetAng, twoPi);
        }
    }
    return _turn(state);
}

//output in rad/s of robot spinning
std::vector<double> Movement::_turn(State *state){
    std::cout << targetAng;
    double ang = state->pos[2];
    if (ang < 0)
    {
        ang += twoPi;
    }
    if(fabs(ang-targetAng)>pi){
        if(ang<targetAng){
            ang+=twoPi;
        }
        else{
            ang-=twoPi;
        }
    }
    double dist = fabs(targetAng-ang);
    double out, accel;
    state->posErr = dist;
    if(dist<goalT){ out = 0; accel = 0; }
    else{
        if(dist<bufferT) dist = 0;
        else dist-=bufferT;
        double velDecel = sqrt(2*decelT*dist + velFT*velFT);
        out = fabs(targetVelT);
        out+=accelT*dltT;

        accel = accelT;
        if(out>velDecel){ 
            out = velDecel; accel = -decelT; 
            if(fabs(getTurnVel(state))<=velFT){atFinalVelT = true;}
        }
        if(out >maxVelT){ out = maxVelT; accel = 0;}
        if(atFinalVelT){accel = 0; out=velFT;}
        
        if(targetAng<ang){ out*=-1; accel *=-1;}
    }
    targetVelT=out;
    return {targetVelT, accel};
}

//@return output in m/s
void Movement::turnVel(State *state, double targVel, double targAccel){
    targVel*=(botWidth/2);
    targAccel*=(botWidth/2);
    state->stateFut = {{targVel,targAccel},{-targVel, -targAccel}};
    functionIndex = 4;
}