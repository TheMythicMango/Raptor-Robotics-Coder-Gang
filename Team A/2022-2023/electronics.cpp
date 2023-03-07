#include "Electronics.hpp"
#include "main.h"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"
pros::Controller master(pros::E_CONTROLLER_MASTER);
// pros::Controller reporter(pros::E_CONTROLLER_PARTNER);
// Motor(port, gearset(2=blue), reverse?, encoder units(0=deg))

pros::Motor left_mtr(17, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);//top - in degrees
pros::Motor left_mtr2(19, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);//in degrees
pros::Motor left_mtr3(20, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);//in degrees

pros::Motor right_mtr(11, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);//top - in degrees
pros::Motor right_mtr2(12, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);//in degrees
pros::Motor right_mtr3(13, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);//in degrees

pros::Motor intake(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor fly(1, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);//250 rpm

pros::Optical optic(5);
pros::Rotation rot(6);

pros::IMU inert(9);//
pros::IMU inert2(10);


pros::ADIEncoder perp_enc(7, 8, true);
pros::ADIEncoder par_enc(3, 4, true);

pros::ADIDigitalOut angler(2);
pros::ADIDigitalOut expansion(5);
// pros::ADIDigitalOut expansion2(5);

pros::Vision vision(21, pros::E_VISION_ZERO_CENTER);