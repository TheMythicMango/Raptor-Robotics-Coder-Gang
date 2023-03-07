#include "diagnostics.hpp"
#include "Electronics.hpp"
#include <string>
#include <vector>
std::vector<std::string> Diagnostics::flywheel(State *state){
    std::vector<std::string> str;
    str.push_back("trgt: " + std::to_string((int)targFlyVel)+" spd: "+std::to_string((int) state->flyVel)+"    ");
    str.push_back("temp: "+std::to_string((int) fly.get_temperature()*9/5+32)+" hot: " + (fly.is_over_temp()?"y":"n"));
    str.push_back("d: "+std::to_string(-1.7));
    return str;
}
std::vector<std::string> Diagnostics::motorHealth(){
    std::vector<std::string> str;
    int tempR = ((right_mtr.get_temperature()+right_mtr2.get_temperature()+right_mtr3.get_temperature())/3.0)*9.0/5.0+32;
    int tempL = ((left_mtr.get_temperature()+left_mtr2.get_temperature()+left_mtr3.get_temperature())/3.0)*9.0/5.0+32;
    str.push_back(std::to_string(tempR)+" "+std::to_string(tempL));
    std::string disconnected = "";
    if((right_mtr.get_flags() & 1)==1){disconnected+="2 ";}
    if((right_mtr2.get_flags() & 1)==1){disconnected+="3 ";}
    if((right_mtr3.get_flags() & 1)==1){disconnected+="4 ";}
    if(rot.get_velocity()>1e8){disconnected+="6 ";}
    if((intake.get_flags()&1)==1){disconnected+="10 ";}
    if((fly.get_flags() & 1)==1){disconnected+="11 ";}
    if((left_mtr.get_flags() & 1)==1){disconnected+="15 ";}
    if((left_mtr2.get_flags() & 1)==1){disconnected+="19 ";}
    if((left_mtr3.get_flags() & 1)==1){disconnected+="20 ";}
    if(disconnected.length()==0 && errno==19){disconnected+="threewire";}
    str.push_back(disconnected);
    errno=0;
    return str;
}