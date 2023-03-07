#include <vector>
#include "math.h"

class profiles{
    class profile{
        double dist, initVel, accel, maxVel, decel, finalVel;
        double traveled, remaining;
        double vel;
        profile(double dist, double initVel, double accel, double maxVel, double decel, double finalVel):
        dist(dist), accel(accel), maxVel(maxVel), decel(decel), finalVel(finalVel){
            traveled = 0;
            vel = initVel;
        }
        
        double accelTemp;
        double prevVel;
        double slowingDist;
        double slowingVel;
        std::vector<double> getTargState(double dltT){
            remaining = dist-traveled;
            slowingDist = (finalVel*finalVel - vel*vel) / (-2*decel);
            prevVel = vel;
            if(vel<maxVel){
                vel+=accel*dltT;
                if(vel>maxVel){
                    accelTemp = (maxVel-prevVel)/dltT;
                    vel = maxVel;
                }
            }
            if(slowingDist>remaining+vel*dltT){
                vel=prevVel;
                slowingVel = sqrt(2*decel*remaining + finalVel*finalVel);
                if(vel>slowingVel){vel = slowingVel;}
                accelTemp = (vel-prevVel);
            }
            
            dist = dist + vel*dltT + .5*accelTemp*dltT*dltT;
            return{dist, vel, accelTemp};
        }
    };

    std::vector<profile> motions;
    
};