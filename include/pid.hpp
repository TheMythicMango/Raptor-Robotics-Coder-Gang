#ifndef PIDCONTROL
#define PIDCONTROL

#include <cmath>
#include <vector>
#include "state.hpp"


class PID{
protected:
    double p;
    double i;
    double d;
    double f;
    double tbh;
    double tbhM;
    bool mirror;
    double limI;
    bool below;
    bool firstTime;
    bool isNegative;
    double BB, BBtol, BBk, BBkm;
    std::vector<double> errors; 
    void damp(double error);
public:
    bool doDamp;
    double errorSum;
    //@param tbh between 0 and 1. multiplies I by param when crosses to above and divides when crosses to below
    //@param tbhM between 0 and 1. Raises tbh to the power of tbhM. Meant to slowly dampen tbh to 1.

    PID(double error0, double p, double i, double d, double initI = 0, double limI = 1e+10, double tbh = 1, double tbhM = 1,double BB =0, double BBtol=0, double BBk=0, double bbkM=-1, bool doDamp = true);
    // void PIDBB(PID, double min, double max, double tolerance, double iMod);
    double run(double val, double target);
    void setError(double i);
    double getError();
};

class PIDBB{
    PID *pid;
    double min, plus, tol, iMod;
public:
    PIDBB(PID *pid, double plus, double minus, double tolerance=0, double iMod = 0);
    double runB(double val, double target);
};

#endif