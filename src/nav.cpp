#include "nav.hpp"
#include <cmath>
#include <string>
#include <vector>
#include "constants.hpp"
#include "state.hpp"

std::vector<double> Nav::rotate(std::vector<double> X0, double ang)//up is zero
{
    std::vector<double> X;
    X.push_back(X0[0] * cos(-ang) - X0[1]*sin(-ang));
    X.push_back(X0[1] * cos(-ang) + X0[0]*sin(-ang));
    X.push_back(X0[2]+ang);
    return X;
};

std::vector<double> Nav::translate(std::vector<double> X0, std::vector<double> X1, bool reverse)
{
    double i = 1;
    if(reverse){ i = -1; }
    std::vector<double> X;
    X.push_back(X1[0]-X0[0]*i);
    X.push_back(X1[1]-X0[1]*i);
    X.push_back(X1[2]);
    X = rotate(X, -X0[2]*i);
    return X;
}

std::vector<double> Nav::line = {0,0,0};
double Nav::look = 0;
void Nav::pursuit(std::vector<double> followLine, double lookAhead){ //lookAhead should be greater than (dist to line)/2, but less than (dist travelled along line )/2
    Nav::line = followLine;
    Nav::look = lookAhead;
}

double Nav::_pursuit(std::vector<double> Xc){
    std::vector<double> lineT = translate(Xc, line, false); //convert to local coord system

    //slopes of perpendicular lines
    double slopeL=1/tan(lineT[2]);
    double slopeP = -1/slopeL;

    //closest point on line to bot
    double xTarg = (-slopeL*lineT[0]+lineT[1])/(slopeP-slopeL); //ax+b=cx+d   (a-c)x = (d-b)
    double yTarg = slopeP*xTarg;
    if(slopeL== 0){ yTarg = lineT[1]; xTarg = 0; }
    else if(slopeP==0){xTarg = lineT[0]; yTarg = 0;}
    double dist = sqrt(xTarg*xTarg+yTarg*yTarg);

    //point one lookAhead distance from bot on line
    double ang = lineT[2];
    if(dist<look){ double dltD = sqrt(look*look-dist*dist); xTarg+=(dltD*sin(ang)); yTarg+=dltD*cos(ang); }

    double radius = (look*look)/(2*xTarg);
    if(fabs(xTarg) <.0001) radius = 99999999;
    return radius;   
}

std::vector<double> Nav::arc(std::vector<double> X0, std::vector<double> X1)
{
    std::vector<double> X = Nav::translate(X0, X1, false);
    double r = (X[0]*X[0]+X[1]*X[1])/(2*X[0]);
    std::vector<double> Xc;
    Xc.push_back(r);
    Xc.push_back(0);
    Xc.push_back(0);
    Xc = translate(X0, Xc, true);
    Xc[2] = r;
    return Xc;
};

// std::vector<std::vector<double>> Nav::arcX2(std::vector<double> X0, std::vector<double> X2, double r2)
// {
//     X2 = Nav::translate(X0, X2, false);
//     int up = 1;
//     r2 = -fabs(r2);

//     double r1 = (X2[0]*X2[0] + X2[1]*X2[1] + 2*X2[0]*r2*cos(X2[2]) + 2*X2[1]*r2*sin(X2[2]))/(2.0 * (r2*cos(X2[2]) + up*r2 + X2[0]));

//     std::vector<std::vector<double>> Xc;
//     Xc.assign(2, std::vector<double>());

//     Xc[0] = {r1, 0, 0};
//     Xc[0] = translate(X0, Xc[0], true);
//     Xc[0][2] = r1;

//     Xc[1].assign(3, 0);
//     Xc[1][0] = X2[0] + r2*cos(X2[2]);
//     Xc[1][1] = X2[1] - r2*sin(X2[2]);
//     Xc[1][2] = X2[2];
//     Xc[1] = translate(X0, Xc[1], true);
//     Xc[1][2] = r2;
    
//     return Xc;
// };