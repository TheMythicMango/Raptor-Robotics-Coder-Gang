#include <cstring>
#include "Electronics.hpp"
#ifndef DIAGNOSTICS
#define DIAGNOSTICS
class Diagnostics{
public:
    static std::vector<std::string> motorHealth();
    // static void odom(State *state);
    static std::vector<std::string> flywheel(State *state);
    static void roller();
    static void powerMonitor();
    // static void pistons(State *state);
};
#endif