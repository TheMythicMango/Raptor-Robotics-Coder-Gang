#include <cmath>
#include "constants.hpp"
#ifndef ANGLECALC
#define ANGLECALC
class Angle{
public:
    static double getAng(double x, double y){//0 to 2*Pi
        double ang = atan(x/y);
        if(y<0) ang+=pi;
        ang = fmod(ang, 2*pi);
        if (ang < 0)
        {
            ang += twoPi;
        }
        return ang;
    }
    static double getDist(double ang1, double ang2){//-pi to pi
        double angDist = ang2-ang1;
        if(fabs(angDist)>pi){
            if(ang1>ang2) ang1-=twoPi;
            else ang2-=twoPi;
            angDist = ang2-ang1;
        }
        return angDist;
    }
    static double toRad(double degrees){
        return degrees*pi180;
    }
    static double toDeg(double radians){
        return radians*180.0/pi;
    }
};
#endif