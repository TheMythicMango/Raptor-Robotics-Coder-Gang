#include "pid.hpp"
#include "state.hpp"
#include <string>

double PID::run(double val, double targetVal)
{
    double error = targetVal - val;
    double out = error * p; // p

    int size = 3;
    errors.push_back(error); // d
    if ((int)errors.size() > size)
        errors.erase(errors.begin());
    double dout = (errors.front() - errors.back())/size;
    out += dout*d;

    errorSum += error*i*dltT; // i
    if(errorSum>limI) errorSum=limI;
    if(errorSum<-limI) errorSum = -limI; 

    if(doDamp&&!firstTime) damp(error);
    if(below!=(val<targetVal)){
        below = !below;
        if(val>targetVal) errorSum*=tbh;
        else errorSum/=tbh;
        tbh=pow(tbh, tbhM);
        firstTime = false;
    }

    if(val<targetVal-BBtol){ out+=BB; errorSum+=BBk*dltT;}
    if(val>targetVal+BBtol){ out-=BB; errorSum-=BBkm*dltT; }

    out += errorSum;
    return out;
}

void PID::setError(double errorSum){this->errorSum = errorSum;}
double PID::getError(){return errorSum;}
PID::PID(double error0, double p, double i, double d, double initI, double limI, double tbh, double tbhMod, double BB, double BBtol, double BBk, double BBkm, bool doDamp){
    if(error0>0){
        this->isNegative = true;
        this->below = true;
    }
    else{
        this->isNegative = false;
        this->below = false;
    }
    this->p = p;
    this->i = i;
    this->d = d;
    this->limI = fabs(limI);
    this->tbh = tbh;
    
    this->tbhM = tbhMod;
    this->errorSum = initI;
    this->BB = BB;
    this->BBtol = BBtol;
    this->BBk = BBk;
    this->BBkm = BBkm;
    this->doDamp = doDamp;
    this->firstTime = true;
}

// PIDBB::PIDBB(PID *pid, double plus, double minus, double tolerance, double iMod):
//     pid(pid), min(fabs(minus)), plus(fabs(plus)), tol(tolerance), iMod(fabs(iMod)){}

// double PIDBB::runB(double val, double target){
//     double out = 0;
//     if(val<target-tol){ out=plus; pid->errorSum+=iMod*dltT;}
//     if(val>target+tol){ out=-min; pid->errorSum-=iMod*dltT; }
//     out+=pid->run(val, target);
//     // std::cout <<PID::PID;
//     return out;
// }

double prevErr;
void PID::damp(double error){
    if((error<0)!=isNegative){
        isNegative = !isNegative;
        if(firstTime){ prevErr = errorSum; firstTime = false; return;}
        else{errorSum = (prevErr+errorSum)/2; prevErr = errorSum;}
    }
}