#pragma once
#include "main.h"
#include "pros/imu.hpp"
#include "pros/optical.hpp"

extern pros::Controller master;
// extern pros::Controller reporter;
// Motor(port, gearset(2=blue), reverse?, encoder units(0=deg))

extern pros::Motor left_mtr3;
extern pros::Motor left_mtr;
extern pros::Motor left_mtr2;

extern pros::Motor right_mtr3;
extern pros::Motor right_mtr;
extern pros::Motor right_mtr2;

extern pros::Motor fly;
extern pros::Motor intake;

extern pros::IMU inert;
extern pros::IMU inert2;

extern pros::Optical optic;

extern pros::ADIEncoder perp_enc;
// extern pros::ADIEncoder right_enc;
extern pros::ADIEncoder par_enc;

extern pros::Rotation rot; //flywheel rotation sensor

extern pros::ADIDigitalOut angler;
extern pros::ADIDigitalOut expansion;
// extern pros::ADIDigitalOut expansion2;

extern pros::Vision vision; //camera