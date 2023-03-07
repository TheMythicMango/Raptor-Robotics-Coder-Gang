#include <vector>
#ifndef CONSTANTS4AUTON
#define CONSTANTS4AUTON

static double fieldWidth = 140.2;

static double posRollC = 29.4;
static double posRollF = 111;
 
static std::vector<double> posHighGoalLT{10,44};
static std::vector<double> posHighGoalLB{44,10};
static std::vector<double> posHighGoalRT{fieldWidth-44,fieldWidth-10};
static std::vector<double> posHighGoalRB{fieldWidth-10,fieldWidth-44};
 
 
static std::vector<double> posHighGoalL{17.78,17.78};
static std::vector<double> posHighGoalR{fieldWidth-16.2,fieldWidth-16.2};
 
static std::vector<double> pos1D{11.30,fieldWidth-11.3};
static std::vector<double> pos2D{23.08,fieldWidth-23.08};
static std::vector<double> pos3D{34.86,fieldWidth-34.86};
static std::vector<double> pos4D{46.64,fieldWidth-46.64};
static std::vector<double> pos5D{58.42,fieldWidth-58.42};
static std::vector<double> pos6D{fieldWidth-58.42,58.42};
static std::vector<double> pos7D{fieldWidth-46.64,46.64};
static std::vector<double> pos8D{fieldWidth-34.86,34.86};
static std::vector<double> pos9D{fieldWidth-23.08,23.08};
static std::vector<double>pos10D{fieldWidth-11.30,11.3};
 
 
static std::vector<double> pos1DR{58.42, 105.35};
static std::vector<double> pos2DR{70.20, 93.77};
static std::vector<double> pos3DR{81.99, 81.99};
static std::vector<double> pos4DR{105.35,58.42};
 
static std::vector<double> pos4DL{fieldWidth-58.42, fieldWidth-105.35};
static std::vector<double> pos3DL{fieldWidth-70.20, fieldWidth-93.77};
static std::vector<double> pos2DL{fieldWidth-81.99, fieldWidth-81.99};
static std::vector<double> pos1DL{fieldWidth-105.35,fieldWidth-58.42};

static std::vector<double> pos1WR{fieldWidth-50.58, 114.18};
static std::vector<double> pos2WR{fieldWidth-50.58, 105.35};
static std::vector<double> pos3WR{fieldWidth-50.58, 96.52};
static std::vector<double> pos4WR{96.52, 89.83};
static std::vector<double> pos5WR{105.35,89.83};
static std::vector<double> pos6WR{114.18,89.83}; 

static std::vector<double> pos1WL{fieldWidth-114.18,fieldWidth-89.83};
static std::vector<double> pos2WL{fieldWidth-105.35,fieldWidth-89.83};
static std::vector<double> pos3WL{fieldWidth-96.52, fieldWidth-89.83};
static std::vector<double> pos4WL{50.58, fieldWidth-96.52};
static std::vector<double> pos5WL{50.58, fieldWidth-105.35};
static std::vector<double> pos6WL{50.58, fieldWidth-114.18}; 
#endif