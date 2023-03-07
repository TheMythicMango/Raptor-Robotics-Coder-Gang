#include "sim.hpp"
#include <vector>

void Simulate::step(State* state)
{
    std::vector<double> current = {0,0};
    std::vector<double> sumVolt = {0,0};
    std::vector<double> trq = {0,0};
    for(int i = 0; i<2; i++){
        double velM = (state->vel[i]/wheelCirc)*60/(RWheelToMotor/6);
        double voltage = (state->voltDrive[i]-velM/Kemf);
        double current = voltage/resistance;
        if(current>2.5) current = 2.5;
        else if (current<-2.5) {current = -2.5; }
        trq[i] = current*Ktorque*numMotors*(RWheelToMotor/6);
        // sumVolt[i] = state->voltDrive[i] - *Kemf;
        // if(fabs(sumVolt[i])<1.75) sumVolt[i]=0;
        // else if(sumVolt[i]>0) sumVolt[i]-=1.75;
        // else sumVolt[i]+=1.75;
        // current[i] = sumVolt[i]/resistance;
        // if(current[i]>1) current[i] = 1;
        // else if(current[i]<-1) current[i] = -1;
        
        // trq[i] = current[i]*MaxRawTorque*numMotors*RWheelToMotor/2.5;
        // if(state->vel[i]>.1){
        //     trq[i]-=dragMech;
        // }
        // else if(state->vel[i]<-.1){
        //     trq[i]+=dragMech;
        // }
    }

    double forceLin = (trq[0] + trq[1]) / wheelRadiusOd;
    double trqRot = ((trq[0] - trq[1]) / wheelRadiusOd) * (botWidth / 2);
    double accelLin = forceLin / mass;
    double accelRot = trqRot / rotInert;

    double dltAng = ((state->vel[0]-state->vel[1])/botWidth + accelRot * dltT) * dltT;

    state->accel[0] = (accelLin + accelRot * (botWidth / 2)) + state->vel[2] * -sin(dltAng)/dltT*Rdrift;//left
    state->accel[1] = (accelLin - accelRot * (botWidth / 2)) + state->vel[2] * -sin(dltAng)/dltT*Rdrift;//right
    state->accel[2] = ((state->vel[0] + state->vel[1]) / 2) * sin(dltAng) * Rdrift/dltT;//mid
    
    for(int i = 0; i<2; i++){
        // if( fabs(state->vel[i]+state->accel[i]*dltT) > maxVel ) {
        //     int x = 1;
        //     if(state->vel[i]+state->accel[i]*dltT < 0) x= -1;
        //     state->accel[i] = x*maxVel - state->vel[i] ;
        // }

        state->setVel(i, state->vel[i] + state->accel[i]*dltT);

    }
    state->setVel(2, state->vel[2] + state->accel[2]*dltT);
    state->dltRot[2]=dltAng*CWheelOffset/wheelCirc;
}