import pygame
from pygame import gfxdraw
from ._tools import colGen, modPos #uses some of the math tools

# creates a graph with each point represented by a circle with
# a radius proportional to the third number by the refRad 
def multCircleGraph(self, data, refRad):
    for dat in data:
        circleGraph(self, data[dat], refRad)
def circleGraph(self, data, refRad):
    color = self.lineCol
    if(data is None): return
    for dat in data:
        
        if(type(data) is dict):
            pos = [dat, data[dat][0]]
        elif type(data) is tuple:
            pos = [0,0]
        else:
            pos = data[dat][0:2]
        try:
            rad = data[dat][2]/refRad
        except:
            # print("wrong data (_graph.py circleGraph)")
            rad = .05
        # print(pos)
        if(rad<0):
            rad*=-1
        bounds = self.bounds["def"]
        rad = rad*(self.size[0])/(bounds[0][1]-bounds[0][0])
        pos = modPos(self, pos, self.bounds["def"])
        try: 
            color = self.lineCol[dat]
        except:
            color = (128,128,128)
        if(rad<2):
            pygame.draw.line(self.surf, color, pos, pos)
        else:
            pygame.draw.circle(self.surf, color, pos, rad)

# determines wether there's one or more than one line to be drawn
def graph(self):
    data = self.data
    if type(data) is dict:
        multGraph(self, data)
    else:
        oneGraph(self, data)
            
# if there's one, then it just graphs that one
def oneGraph(self, data):
    _graph(data, self.bounds, self.lineCol)

# otherwise it has to do some more work
def multGraph(self, data):
    # setting up so that the selected line is drawn
    # on top so that it can be more easily seen.
    passed = False
    modKeys = list(data.keys())
    modKeys.append(self.selected)

    # loops through and graphs each variable
    for dat in modKeys:
        if(dat == self.selected and not passed):
            passed = True
            continue
        color = self.lineCol[dat]
        if(dat in self.bounds):
            bounds = self.bounds[dat]
        else:
            bounds = self.bounds["def"]
        
        _graph(self, data[dat], bounds, color)

# creates the lines to represent each variable
# data is the data being passed in either as:
# x1: y1, x2: y2 (dictionary) or [[x,y],[x2,y2]] (array)
# bounds are the range of values that the array should be 
# able to hold.
def _graph(self, data, bounds, lineCol):
    # modifies the bounds based on if a value is outside
    # of the bounds. If the bounds are flexible, then it
    # makes it so the bounds will encompass the variable,
    # if the bounds are rigid, then the line isn't drawn
    def modBounds(dim, x):
        x = float(x)
        if(self.flexBounds[dim]):
            if(x>bounds[dim][1]):
                bounds[dim][1] = x
            elif(x<bounds[dim][0]):
                bounds[dim][0] = x
        elif(x<bounds[dim][0] or x>bounds[dim][1]):
            return False
        return True
    
    if(len(data)<1):
        return
    # if the data is in a dict, the individual values 
    # are converted to arrays, {x: y} -> [x,y]
    if(type(data) is dict): 
        x = list(data.keys())[0]
        if(len(data[x])>0):
            data0 = [x, data[x][0]]
        else:
            data0 = [x,0]
    else:
        data0 = data[0]
    start = modPos(self, data0, bounds)
    out = False

    # loops through coords within variable
    for pos in data:
        if(type(data) is dict):
            if(len(data[x])>0):
                pos = [pos, data[pos][0]]
            else:
                pos = [x,0]
                
        b1 = modBounds(0,pos[0])
        b2 = modBounds(1, pos[1])
        pos = modPos(self, pos, bounds)

        # draws line from the previous point to the current one
        # only if both of them are within the bounds.
        if( b1 and b2 and (not out) and pos>start):
            pygame.draw.aaline(self.surf, lineCol, start, pos)
        elif b1 and b2:
            out = False
        else: 
            out = True
        start = pos

    
