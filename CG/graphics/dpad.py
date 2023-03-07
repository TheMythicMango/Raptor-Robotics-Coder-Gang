from math import sqrt

def modDpad(x,y):
    l = sqrt(pow(x,2.0)+pow(y,2.0))
    if(l>127):
        x = x*127.0/l
        y = y*127.0/l
        l=127
    return [x,y]
