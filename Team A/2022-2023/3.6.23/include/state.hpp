#ifndef STATE
#define STATE

#include <iostream>
#include <cmath>
#include <vector>
#include "constants.hpp"
class State
{
public:
    std::vector<double> pos;//0 x, 1 y, 2 ang
    std::vector<double> vel;//in rpm 0 left, 1 right,  2 perpendicular
    std::vector<double> velWheels;//{left, right}
    std::vector<double> dltRot;
    std::vector<double> dltRotDr;
    std::vector<double> accel;
    std::vector<std::vector<double>> stateFut;//target vel and how it should change
    //{{velL,accelL},{velR, accelR}}
    std::vector<double> voltDrive;//0 is left, 1 is right
    static std::vector<std::string> outputs;
    double dltAng;

    static bool vibrateController;
    double flyVel;
    bool doVoltDrive;
    bool turning;
    double posErr = 100;
    State(std::vector<double> pos = initialPosition, std::vector<double> vel = {0,0,0}, std::vector<double> accel = {0,0,0}, std::vector<double> volt = {0,0}, std::vector<double> dltRot = {0, 0, 0}, std::vector<double> dltRotDr = {0, 0, 0}, bool doVoltDrive = true, double flyvel = 0);
    State(const State &old); //copy constructor so that states can be cloned appropriately.

    void setVel(int index, double value);
};

#endif