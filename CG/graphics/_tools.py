import math

# generates a color based on the input value. 
# There should theoretically be 4^3=64 unique colors generated.
# more than enough for my needs
def colGen(self, i):
    x = 64
    y = x*11
    i = y*i+y
    return (i%255, ((i/255)*x)%255, (i/pow(255, 2)*x)%255)

# adjusts coordinate from a graphs local system to the global system
def modPos(self, val, bounds):
    rnge = [
        (bounds[0][1]-bounds[0][0]),
        (bounds[1][1]-bounds[1][0])
    ]
    if(rnge[0] == 0 or rnge[1] == 0):
        return [0,0]
    return [
        ((val[0]-bounds[0][0]) * self.size[0]/rnge[0])+self.off[0] ,
        (-(val[1]-bounds[1][0]) * self.size[1]/rnge[1])+self.off[1] + self.size[1]
    ]

# adjusts from global to local coordinates
def revPos(self, val, bounds):
    rnge = [
        (bounds[0][1]-bounds[0][0]),
        (bounds[1][1]-bounds[1][0])
    ]
    return [
        (val[0]-self.off[0])*rnge[0]/self.size[0] + bounds[0][0],
        -(val[1]-self.off[1]-self.size[1])*rnge[1]/self.size[1] + bounds[1][0]
    ]

# draws a rectangle at the position and rotation given
def rect(self, pos, ang, width, height, col):
    ang = -ang
    s = math.sin(ang)
    c = math.cos(ang)
    width = width/2
    height = height/2
    coords = [
        [width*c - height*s + pos[0], width*s + height*c + pos[1]],
        [-width*c - height*s + pos[0], -width*s + height*c + pos[1]],
        [-width*c + height*s + pos[0], -width*s - height*c + pos[1]],
        [width*c + height*s + pos[0], width*s - height*c + pos[1]]
    ]
    coords.append(coords[0])
    return coords