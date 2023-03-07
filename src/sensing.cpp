#include "sensing.hpp"
//#define _USE_MATH_DEFINES
// #include <cmath>
// #include "math.h"
#include <cmath>
#include <cstdio>
#include <ostream>
#include "angle.cpp"

// const double pi = acos(-1);
void Sense::getPos(State* state)
{
    std::vector<double> odomOut = odom((state->dltRot[0])*360, state->dltRot[2]*360, state->dltAng, state->pos[2]);
    
    state->pos[0] += odomOut[0];
    state->pos[1] += odomOut[1];
    // std::cout << odomOut[2];
    state->pos[2] += odomOut[2];
    state->pos[2] = fmod(state->pos[2], twoPi);
    if(state->pos[2]<0) state->pos[2]+=twoPi;
}

std::vector<double> Sense::odom(double rotPar, double rotPerp, double dltAng, double ang)
{
    double dltPar = (Angle::toRad(rotPar)) * wheelRadiusOd;
    double dltPerp = -Angle::toRad(rotPerp) * wheelRadiusOd;
    double dltX, dltY;
    if (dltAng == 0)
    {
        dltX = dltPerp;
        dltY = dltPar;
    }
    else
    {
        dltX = 2 * sin(dltAng / 2) * (dltPerp / dltAng + CWheelOffset);                         //chordLength = 2r sin(theta/2)
        dltY = 2 * sin(dltAng / 2) * (dltPar / dltAng + 0);                                     //r = dist/theta
    }

    // shift to global positions. positive = counterclockwise
    double angM = -ang - dltAng / 2;
    double outX = dltX * cos(angM) - dltY * sin(angM);
    double outY = dltX * sin(angM) + dltY * cos(angM);
    return {outX, outY, dltAng};
}

double Sense::heading(double ang){
    ang=Angle::toRad(ang);
    if(ang>pi) ang-=twoPi;
    return ang;
}