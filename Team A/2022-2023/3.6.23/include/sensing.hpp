#ifndef SENSING
#define SENSING
#include <iostream>
#include <cmath>
#include <vector>
#include "state.hpp"
#include "constants.hpp"
class Sense
{

public:
    static void getPos(State* state);
    static std::vector<double> odom(double rotPar, double rotPerp, double dltAng, double ang);
    static double heading(double dltAng);
};
#endif