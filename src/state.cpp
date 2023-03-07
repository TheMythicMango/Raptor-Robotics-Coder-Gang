#include "state.hpp"
#include <ostream>
#include <vector>

bool State::vibrateController = false;
std::vector<std::string> State::outputs = {"test"};
State::State(std::vector<double> pos, std::vector<double> vel, std::vector<double> accel, std::vector<double> volt, std::vector<double> dltRot, std::vector<double> dltRotDr, bool doVoltDrive, double flyVel){
    this->pos = pos;
    this->vel = vel;
    this->accel = accel;
    this->dltRot = dltRot;
    this->dltRotDr = dltRotDr;
    this->voltDrive = volt;
    this->doVoltDrive = doVoltDrive;
    this->turning = false;
    this->flyVel = flyVel;
    this->dltAng = 0;
    // this->outputs = {"test"};
    stateFut = {{0,0},{0,0}};
}
void State::setVel(int index, double value){
    // accel[index] = (vel[index]-value)/dltT;
    vel[index] = value;
    dltRot[index] = value*dltT/wheelCirc;
}