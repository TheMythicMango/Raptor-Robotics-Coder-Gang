#include "Electronics.hpp"
#include "arms.hpp"
#include "cycle.hpp"
#include "dist.cpp"
#include "movement.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <string>
#include "ConstantsAuton.cpp"

static void driver(State *state){
	state->pos = {Dist::inToM(12*7+1.75),Dist::inToM(15.5),pi/2};
	now = pros::c::millis();
	Movement::rest(state);
    targFlyVel = 280;
	
    bool pressedexpansion = false;
    bool pressedAngler = false;
    bool pressedLaunch = false;
	fly.move_voltage(0);
	bool inAuton = false;
	bool doRollerMacro = false;
	bool doRollerP = false;
	bool rollerMacro = false;
	int i = 0;
	int prevIExp = -100;
	int prevITurret = -100;
	double tempTune = 0;
	expansion.set_value(false);
	Arms::initFly(0,0);
	while(1){
		//drive
		state->voltDrive = Movement::drive({master.get_analog(ANALOG_RIGHT_X), master.get_analog(ANALOG_LEFT_Y)});
		if(fabs(master.get_analog(ANALOG_LEFT_X))>70){state->voltDrive = {master.get_analog(ANALOG_LEFT_X)/40.0, master.get_analog(ANALOG_LEFT_X)/-40.0};}

		// if(doRollerMacro){ doRollerMacro = !Arms::rollerTo(state, ON_RED);}
		cycle(state, inAuton);

		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
			if(targFlyVel<=280) targFlyVel = 310;
			else targFlyVel = 270;
		}

		//@flywheel
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
			pressedLaunch=!pressedLaunch;
			if(pressedLaunch) Arms::initFly(0, state->flyVel);
			else Arms::initFly(0, 0);
		}
		if(pressedLaunch){Arms::setFly(targFlyVel);}

		// Arms::launchVel(state->flyVel);

		if(state->flyVel>targFlyVel-5&&targFlyVel<targFlyVel+10 ){
			state->vibrateController =true;
		}
		else state->vibrateController = false;
		if(!pressedLaunch){ if(fabs(state->flyVel)>10) fly.move_voltage(0); else fly.move_voltage(0);}
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
			targFlyVel+=master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)/100.0;
			state->outputs.push_back(std::to_string(targFlyVel));
		}

		//@intake
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){ intake.move_voltage(-12000); doRollerMacro = false;}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
			intake.move_voltage(12000);
			doRollerMacro = false;
			if(pressedLaunch){
				Arms::setFly(0);
				fly.set_current_limit(2500);
				fly.move_voltage(12000);
			}
		}
		else{
			intake.move_voltage(0);
			// if(prevIIntake+5>i){ if(vision.get_by_size(0).height>150&&!Arms::rollerTo(state, ON_RED)) doRollerMacro = true; }
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
			tempTune+=master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)/10000.0;
			// state->outputs.push_back("tune: "+std::to_string(tempTune));
		}
		// if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
		// 	rollerMacro = !rollerMacro;
		// }
		// if(rollerMacro){
		// 	rollerMacro = Arms::rollerTo(state, true);
		// }

		//@turret @turn
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
			if(prevITurret+15>i){
				// Movement::pursue(false, state, {0,0});
				// Movement::travelTo({0,0}, state);
				// Movement::travel(-1, state, .11, .05, .005, .004, .005, .003);
				Movement::turnToA(0, state);
				do{ cycle(state, inAuton); if(master.get_digital_new_press(DIGITAL_Y)){break;} } while(!Movement::restingTurn.isRested(state->posErr));
				// Movement::pursue(false, state, {0,0});
				// do{ cycle(state, inAuton); if(master.get_digital_new_press(DIGITAL_Y)){break;} } while(!Movement::restingMoveQ.isRested(state->posErr));
				master.rumble(".");
				Movement::rest(state);
			}
			else{ prevITurret = i; }
		}
		if(master.get_digital_new_press(DIGITAL_UP)){
			// pressedexpansion = !pressedexpansion; expansion.set_value(pressedexpansion);
			expansion.set_value(true);
			// else prevIExp = i;
		}

		//@indexer
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){ pressedAngler=!pressedAngler;}

		// if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
		// 	left_mtr.set_brake_mode  (pros::E_MOTOR_BRAKE_BRAKE);
		// 	left_mtr2.set_brake_mode (pros::E_MOTOR_BRAKE_BRAKE);
		// 	left_mtr3.set_brake_mode (pros::E_MOTOR_BRAKE_BRAKE);
		// 	right_mtr.set_brake_mode (pros::E_MOTOR_BRAKE_BRAKE);
		// 	right_mtr2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
		// 	right_mtr3.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
		// }
		// if(pressedAngler) flyVel = 270;
		// else flyVel = 270;
		angler.set_value(pressedAngler);
		i++;
	}
}