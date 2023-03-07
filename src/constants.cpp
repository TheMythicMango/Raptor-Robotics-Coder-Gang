#include <cmath>
#include <vector>
#include "constants.hpp"
double targFlyVel = 290;

const double pi = acos(-1);
const double twoPi = 2*pi;
const double pi180 = pi/180.0;

const double botWidth = 0.3; //meters
const double botLength = .2; //meters
// const double fieldWidth = 3.61;//meterss
const std::vector<double> initialPosition = {0,0,0}; //x in meters, y in meters, rad
// static const std::vector<double> goalPos = {0,0}; //meters
// const std::vector<double> goalPos = {fieldWidth-.45, fieldWidth-.45};

const double RWheelToMotor = 5.0*60.0/(3.0*wheelCircDr);//(rpm)/(m/s)
const double Kemf = 6.68;
const double Ktorque = .198;
// const double Ktorque2 = .50633;

const double resistance = 3.84; //

//adjust one to fix angle drift(bigger R = turn left), adjust both to fix scale(bigger = percieved move farther)
const double wheelRadiusOd = (2.75/2)*.0254*1.00727; // inches to meters
const double wheelRadiusDr = (3.25/2)*.0254*1.00727; // inches to meters
const double wheelCirc = wheelRadiusOd*twoPi;
const double wheelCircDr = wheelRadiusDr*twoPi;
const double MaxRawTorque = 2.1/36.0;
const double mass = 20/2.205; // lbs to kg

//adjust to fix turning amount (bigger = smaller turn perceived)
const double leftOffset = .305/2;//.0968; //meters //.2
const double rightOffset = .3/2;//.0968; //meters //.195
const double CWheelOffset = .143; //meters

const double length = .20; //meters
const double dltT = .025; //seconds
const double rotInert = (1.0 / 12.0) * mass * (std::pow(botWidth, 2) + std::pow(length, 2));
// const double maxVel = (3600/RWheelToMotor)*wheelCirc;
const double dragMech = 0.1;
const double Rdrift = 0;
const double numMotors = 1;