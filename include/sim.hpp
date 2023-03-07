#include <cmath>
#include "constants.hpp"
#include <vector>
#include "state.hpp"
#ifndef SIM
#define SIM
class Simulate
{
    // static const double RMotorLoss;
    // static const double REMF;
    // static const double drag;
    // static const double wheelRadius;
    // static const double mass;
    // static const double width;
    // static const double length;
    // static const double dltT;
    // static const double rotInert;

public:
    static void step(State* state);
};
#endif