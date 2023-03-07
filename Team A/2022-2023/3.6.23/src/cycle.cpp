#include "cycle.hpp"
#include "Electronics.hpp"
#include "movement.hpp"
#include "pros/colors.h"
#include <cmath>
#include <cstddef>
#include <string>
#include <sys/_stdint.h>
#include <vector>
#include "dist.cpp"
#include "angle.cpp"

static std::shared_ptr<graphy::AsyncGrapher> grapher(new graphy::AsyncGrapher("Flywheel Velocity vs. Time"));

static void senseUpdate(State *state){
	// ***flag
	state->dltRot = {0,0,0,0};
	state->dltRot[0] = par_enc.get_value()/360.0;//(left_mtr.get_position()+left_mtr2.get_position()+left_mtr3.get_position())/5  /360.0;
	state->dltRot[1] = (right_mtr.get_position()+right_mtr2.get_position()+right_mtr3.get_position())/5  /360.0;
	state->dltRot[2] = perp_enc.get_value()/360.0;
	// state->dltRot[3] = 
	state->dltAng = ( Sense::heading(inert.get_heading())*.989 + Sense::heading(inert2.get_heading())*1.01 )/2;
  	// left_enc.reset(); right_enc.reset(); //
	perp_enc.reset(); par_enc.reset();
	left_mtr.tare_position();left_mtr2.tare_position();left_mtr3.tare_position();
	right_mtr.tare_position();right_mtr2.tare_position();right_mtr3.tare_position();
	inert.tare_heading(); inert2.tare_heading();
}

static int i = 0;

static int prevI;
void initCycle(){
	grapher->addDataType("vel", COLOR_YELLOW);grapher->addDataType("targVel", COLOR_GREEN_YELLOW);grapher->addDataType("voltage", COLOR_RED);grapher->addDataType("current", COLOR_PINK);
	// grapher->addDataType("output0", COLOR_BLUE);
	// grapher->addDataType("tempL", COLOR_GREEN_YELLOW);grapher->addDataType("targR", COLOR_RED);grapher->addDataType("actR", COLOR_ORANGE);grapher->addDataType("currentR", COLOR_POWDER_BLUE);grapher->addDataType("-currentR", COLOR_LIGHT_GREEN);

// Start grapher task
	grapher->startTask();
}

static double voltL = 0, voltR = 0;
static double prevVoltL = 0, prevVoltR = 0;
static std::vector<double> prevVel = {0,0,0};
static std::vector<double> currentVel = {0,0,0};
double dltPosMid;
double prevFlyVel;
double currentFLyVel;
void cycle(State *state, bool inAuton){
	currentFLyVel = rot.get_velocity()/(36.0);
	state->flyVel = (prevFlyVel + currentFLyVel)/2;
	prevFlyVel = currentFLyVel;
	dltPosMid = 0;
  	senseUpdate(state);
	Sense::getPos(state);
	dltPosMid+=state->dltRot[2];
	Arms::launchVel(state->flyVel);
	for(int j = 0; j<2; j++){
		pros::delay(dltT*1000/3);
		senseUpdate(state);
		Sense::getPos(state);
		dltPosMid+=state->dltRot[2];
		state->flyVel = state->flyVel*.8 + fly.get_actual_velocity()*.2;
		Arms::launchVel(state->flyVel);
	}

	currentVel = {
		(left_mtr.get_actual_velocity()+left_mtr2.get_actual_velocity()+left_mtr3.get_actual_velocity())/3.0,
		(right_mtr.get_actual_velocity()+right_mtr2.get_actual_velocity()+right_mtr3.get_actual_velocity())/3.0,
		dltPosMid/dltT
	};
	for(int k = 0; k<3; k++){
		state->vel.at(k) = currentVel.at(k)/2 + prevVel.at(k)/2;
		currentVel.at(k) = prevVel.at(k);
	}
  	
	

	//if(inAuton)

	Movement::tick(state);

	if(state->doVoltDrive){
		left_mtr.move_voltage(state->voltDrive[0]*1000);
		left_mtr2.move_voltage(state->voltDrive[0]*1000);
		left_mtr3.move_voltage(state->voltDrive[0]*1000);
		right_mtr.move_voltage(state->voltDrive[1]*1000);
		right_mtr2.move_voltage(state->voltDrive[1]*1000);
		right_mtr3.move_voltage(state->voltDrive[1]*1000);
	}
	else {
		int n = 1;
		for(int i = 0; i<n; i++){
			double velL = Movement::velL(state, dltT/n);//rad/s of motor
			double accelL = Movement::accelL(state);
			voltL = Movement::leftVelPID.run(state->vel[0]*2*pi/60, velL)+Movement::leftPIDXL.run(state->vel[0]*2*pi/60, velL);
			prevVoltL = voltL;

			double tempL = 0;
			if(state->turning){
				tempL += fabs(velL)/2.55 + 1.4;
				if(velL<0)tempL*=-1;
				if((velL>0) == (accelL>0)) tempL += accelL/15.5;
				else tempL += accelL/.7;
			}
			else{
				tempL += fabs(velL)/3.08 + 1.0;
				if(velL<0)tempL*=-1;
				if((velL>0) == (accelL>0)) tempL += accelL/11;
				else tempL += accelL/.9;
			}
			
			
			if(velL!=0) voltL+=tempL;
			left_mtr.move_voltage(voltL*1000);
			left_mtr2.move_voltage(voltL*1000);
			left_mtr3.move_voltage(voltL*1000);

			double velR = Movement::velR(state, dltT/n);
			if (fabs(velL+velR)<.001) {voltR=-voltL;}
			else{ 
				double accelR = Movement::accelR(state);
				voltR = Movement::rightVelPID.run(state->vel[1]*2*pi/60, velR)+Movement::rightPIDXL.run(state->vel[1]*2*pi/60, velR);
				prevVoltR = voltR;

				double tempR = 0;
				tempR+=fabs(velR)/3.08 + 1.0;
				if(velR<0)tempR*=-1;
				if((velR>0) == (accelR>0)) tempR += accelR/11;
				else tempR += accelR/.9;
				
				if(velR!=0) voltR+=tempR;
			}
			right_mtr.move_voltage(voltR*1000);
			right_mtr2.move_voltage(voltR*1000);
			right_mtr3.move_voltage(voltR*1000);

			//@movement output
			// grapher->update("targR", fabs(velR/30));grapher->update("actR", fabs(state->vel[1]*2*pi/60/30));grapher->update("currentR", right_mtr.get_current_draw()/2500.0);grapher->update("-currentR", -right_mtr.get_current_draw()/2500.0);
			// state->outputs.push_back("velR: " + std::to_string(velR));
			// grapher->update("output0", std::stod(state->outputs[0]));
		}
	}
	
	int wait = 3;
	if(i%wait==0){
		//@flywheel output
		// state->outputs.push_back("0");
		grapher->update("vel", state->flyVel/600); grapher->update("targVel", targFlyVel/600);grapher->update("voltage", fly.get_voltage()/12000.0);grapher->update("current", fly.get_current_draw()/2500.0);//grapher->update("output0", std::stod(state->outputs[0]));
	
		state->outputs.push_back("x: "+std::to_string((int) Dist::mToIn(state->pos[0]*10)) + "y: "+std::to_string((int)Dist::mToIn(state->pos[1]*10))+"     ");
		state->outputs.push_back("ang: "+std::to_string(Angle::toDeg(state->pos[2]))+"    ");
		if(!state->outputs.empty()){
			int length = state->outputs.size();
			int index = (i/wait)%length;
			master.print(index, 0, state->outputs.at(index).c_str());
		}
		// reporter.print(1, 0, "error: %s", strerror(errno));
		// reporter.print(2,0,"flyVel: %.3f", flyVel);
		// std::cout << "time: " << i*dltT << "\n" << "posX: " << state->pos[0] << "\n" << "posY: " << state->pos[1] << "\n" << "ang: " << state->pos[2] << "\n";
		std::cout <<std::flush;
	}
	else if(state->vibrateController){master.rumble(".");}
	i++;

	state->outputs.clear();
	pros::c::task_delay_until(&now, dltT*1000);
}
