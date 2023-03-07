#include "Electronics.hpp"
class Filter{
    static double kalmanGain;
    static double uncertaintyEstimate;
    static double valEstimate;
    static double noise;
    static void initKalman(double initVal, double initUncertainty){
        uncertaintyEstimate = 25;
        noise = 5;
        valEstimate = initVal;
        uncertaintyEstimate = initUncertainty;
    }

    
    static double runKalman(double valMes, double uncertaintyMes){
        
        kalmanGain = uncertaintyEstimate/(uncertaintyEstimate+uncertaintyMes);\
        valEstimate = valEstimate + uncertaintyEstimate*(valMes-valEstimate);
        uncertaintyEstimate = (1-kalmanGain)*uncertaintyEstimate;

        valEstimate = valEstimate+(fly.get_torque()-1)*2;
        uncertaintyEstimate = uncertaintyEstimate+noise;
        return valEstimate;
    }

};