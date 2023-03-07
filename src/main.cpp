#include "main.h"
#include "Electronics.hpp"
#include "cycle.hpp"
// #include "autons/autonSkimTest.cpp"
// #include "autons/autonMid6Near.cpp"
// #include "autonFlyTest.cpp"
#include "autons/autonTest.cpp"
// #include "autonSkillsTest.cpp"
#include "driverRun.cpp"
#include "diagnostics.hpp"
#include "arms.hpp"
#include "movement.hpp"
#include "pid.hpp"
#include "state.hpp"
#include <cmath>
#include <limits>
#include <ostream>
#include <string>
#include <vector>
#include <cstring>
// #include "fireGoose3.c"

State state;

// keep under a few seconds
bool ON_RED = true;
bool ON_ROLLER = true;
void redOrBlue(){
	ON_RED = !ON_RED;
	// if(onRedSide){
	// 	pros::screen::print(pros::E_TEXT_MEDIUM, 1, "on red");
	// }
	// else pros::screen::print(pros::E_TEXT_MEDIUM, 1, "on blue");
	// if(ON_RED) pros::screen::set_pen(COLOR_BLUE);
	// else pros::screen::set_pen(COLOR_RED);
	// pros::screen::fill_rect(10, 10, 90, 90);
}
// bool ON_ROLLER = false;
void closeOrFar(){
	ON_ROLLER = !ON_ROLLER;
	// if(ON_ROLLER){
	// 	pros::lcd::print( 6, "                      on roller     ");
	// }
	// else pros::lcd::print( 6, "                      off roller     ");
}
void initialize()
{
	initCycle();
	pros::lcd::initialize();
	expansion.set_value(false);
	master.clear();
	std::printf("*start*");
	std::cout << std::flush;
	inert.reset();
	inert2.reset();
	int i = 0;
	while(i++<120||inert.is_calibrating()||inert2.is_calibrating()||inert.get_heading()==INFINITY||inert2.get_heading()==INFINITY){pros::delay(dltT*1000);}
	state.pos = {0,0,0};
}

// between auton and driver. and after driver
void disabled() {fly.move_voltage(0);}

// after initialize, before auton. Stops when comp started.
void competition_initialize() {}



/* can call from other functions for testing purposes
 *if robot disabled, auton stops, will start from beginning when reenabled */
void autonomous(){autonTest(&state);}

// similar to auton. Runs after initialize when not in comp mode.

void opcontrol(){
	driver(&state);
}


