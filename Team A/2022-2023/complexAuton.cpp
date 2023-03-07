#include "movement.hpp"
#include "state.hpp"
#include "nav.hpp"
#include <cmath>
#include <vector>
#include "angle.cpp"
#include "dist.cpp"
std::vector<double> targetPos2;

std::vector<double> stateF;
bool rev;
void Movement::pursue(bool inMeters, State *state, std::vector<double> finalState, double lookAhead, double reverse, double accel, double maxVel, double decel){
    if(!inMeters){ finalState[0] = Dist::inToM(finalState[0]); finalState[1] = Dist::inToM(finalState[1]);}
    if(finalState.size()<3){finalState.push_back( Angle::getAng(finalState[0]-(state->pos[0]+lookAhead/3*sin(state->pos[2])), finalState[1]-(state->pos[1]+lookAhead/3*cos(state->pos[2]))) );}
    if(reverse) finalState[2] += pi;
    Nav::pursuit(finalState, lookAhead);
    stateF = finalState;
    rev = reverse;
    travelTo(true, finalState, state, accel, maxVel, decel);
    functionIndex = 9;
}

void Movement::_pursue(State* state){
    double r = Nav::_pursuit(state->pos);
    std::vector<double> move = _travelTo(state);
    double leftVel, rightVel;

    double diffDr = (r+botWidth/2)/(r-botWidth/2);
    if(r > 999999) diffDr = 1;
    double sqrtDr = pow(diffDr, .1);
    if(fabs(diffDr)>1){
        leftVel = move[0]/sqrtDr;
        rightVel = move[0]/(diffDr*sqrtDr);
    }
    else {
        leftVel = move[0]*sqrtDr*diffDr;
        rightVel = move[0]*sqrtDr;
    }
    int m = 1;
    if(rev) m = -1;
    state->stateFut = {{leftVel*m,move[1]*m},{rightVel*m, move[1]*m}};
}
// void Movement::routeTo(std::vector<double> pos, State *state){
//     targetPos2 = pos;
//     turnTo(pos, state);
//     travelTo(pos, state);
//     functionIndex = 2;
// }
// void Movement::_routeTo(State *state){
//     std::vector<double> outTurn = _turnTo(state);
//     double turnErr = state->posErr;
//     std::vector<double> outLin = _travelTo(state);
//     outTurn[0]*=botWidth/4;
//     outTurn[1]*=botWidth/4;
//     // std::vector<double> outLin = _travelTo(state);
//     // if(fabs(outLin[0])+fabs(outTurn[0]) > 12) {
//     //     outLin[0] = 12-fabs(outTurn[0]);
//     //     if(outLin[1]<0) outLin[0] *=-1;
//     //     outLin[1] = outLin[0];
//     // }
//     state->posErr = sqrt(pow(state->pos[0]-targetPos2[0],2)+pow(state->pos[1]-targetPos2[1],2));
//     if(turnErr<.5){
//         double ratio = 1-(turnErr/.5);
//         std::printf("outTurn: %.2f\n", outTurn[0]);
//         setVel(state, outLin[0]*ratio+outTurn[0], outLin[1]*ratio+outTurn[1], outLin[0]*ratio-outTurn[0], outLin[1]*ratio-outTurn[1]);
//     }
//     else setVel(state, outTurn[0], outTurn[1], -outTurn[0], -outTurn[1]);
//     functionIndex=2;
// }