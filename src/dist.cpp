#ifndef DISTANCECONVERSION
#define DISTANCECONVERSION
class Dist{
public:
    static double inToM(double in){
        return in*.0254;
    }
    static double mToIn(double m){
        return m/.0254;
    }
};
#endif