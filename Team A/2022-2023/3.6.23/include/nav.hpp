#include <cmath>
#include <bits/stdc++.h>
#include <vector>

#ifndef NAVIGATION
#define NAVIGATION
class Nav
{
public:
    static std::vector<double> line;
    static double look;
    
    static std::vector<double> rotate(std::vector<double>, double);
    static std::vector<double>translate(std::vector<double>, std::vector<double>, bool);
    static std::vector<double> arc(std::vector<double>, std::vector<double>);
    static std::vector<std::vector<double>> arcX2(std::vector<double>, std::vector<double>, double);

    static void pursuit(std::vector<double> line, double lookAhead);
    static double _pursuit(std::vector<double> Xcurrent);
};
#endif