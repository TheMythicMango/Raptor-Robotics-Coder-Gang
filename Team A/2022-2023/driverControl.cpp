#include "movement.hpp"
#include "pid.hpp"
#include "state.hpp"
#include <cmath>
#include <vector>

double actPwrT = 0;
double tempPowered;
std::vector<double> Movement::drive(std::vector<int> input)
{
  if(input[0] == 0 && input[1]==0) return std::vector<double> {0, 0};

  double ctrX = input[0]/1.27;
  double ctrY = input[1]/1.27;
  double pwrF = fabs(ctrY);
  double pwrT = fabs(ctrX);

  // if(pwrF+pwrT>100) pwrF = 100-pwrT;
  if(pwrF>0){
    double pwrF2 = pwrF*pwrF;
    pwrF = 9.821e-07*pwrF2*pwrF2 - 6.986e-05*pwrF2*pwrF + 0.006751*pwrF2  + 0.03879*pwrF;
    double baseF = 6;
    pwrF*=(100-baseF)/100;
    pwrF+=baseF;
    if(ctrY<0) pwrF *=-1;
  }

  if(pwrT>0){
    double pwrT2 = pwrT*pwrT;
    pwrT = 9.821e-07*pwrT2*pwrT2 - 6.986e-05*pwrT2*pwrT + 0.006751*pwrT2  + 0.03879*pwrT;
    double baseT = 8;
    pwrT*=(100-baseT)/100;
    pwrT+=baseT;
    pwrT *= .8;
    if(pwrT>actPwrT) actPwrT=pwrT*.6+actPwrT*.4;
    else actPwrT=pwrT;
    pwrT = actPwrT;
    if(ctrX<0) pwrT *=-1;
    if(tempPowered<5)pwrT*=.9;
    tempPowered++;
  }
  else{tempPowered = 0;}
  
  double pwrL = pwrF+pwrT;
  double pwrR = pwrF-pwrT;
  
  return std::vector<double> {pwrL*12/100, pwrR*12/100}; // returns left and right motor values to the main class.
};