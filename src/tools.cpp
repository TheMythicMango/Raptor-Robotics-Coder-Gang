#include "math.h"

#ifndef ROBOTTOOLS
#define ROBOTTOOLS
class Resting{
private:
    float timeForRest;
    float tolForRest;
    float timeResting = 0;
    float timePerFrame;
    float exitTime;
    float timeRunning = 0;

public:
    Resting(float timeForRest, float toleranceForRest, float timePerFrame, float exitTime = 0) : 
    timeForRest(timeForRest), tolForRest(toleranceForRest), 
    timePerFrame(timePerFrame), exitTime(exitTime){}

    bool isRested(double error){
        timeRunning+=timePerFrame;

        if(fabs(error)<tolForRest) timeResting += timePerFrame;
        else timeResting = 0;

        if(timeResting>=timeForRest){timeResting = 0; timeRunning = 0; return true;}
        if(exitTime!=0 && timeRunning>exitTime){timeResting = 0; timeRunning = 0;return true; }
        return false;
    }
};

#endif