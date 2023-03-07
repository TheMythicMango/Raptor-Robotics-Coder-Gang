import pygame
from pygame import gfxdraw #import gfxdraw for anti-aliased graphics

# main file of class
# the purpose is to make creating graphs as simple and 
# powerful as possible
class graphics:
    fontSz = 15 #size of font in text 
    
    # initializes parameters for a specific graph
    def __init__(self, surf, size, off, bounds, backCol = False,
                lineCol = (255,255,255),
                flexBounds = [True, False], doKey = True):
        self.size = size #size of graph
        self.off = off #position of top-left corner of graph
        # surface that graph is on (a required part of pygame drawing)
        self.surf = surf
        self.bounds = bounds #the range of the data within the graph
        self.backCol = backCol
        self.lineCol = lineCol
        #wether the bounds can be adjusted based on data outside of current bounds
        self.flexBounds = flexBounds
        self.selected = None #which parameter is selected, and will be highlited
        self.doKey = doKey #id the graph should have a label for each line
        self.colI = 0 #ensuring that each graph gets a unique color

        # processing the inputs for later convenience
        if(type(self.lineCol) is not dict):
            self.lineCol = {'def': self.lineCol}
        if(type(self.bounds) is not dict):
            self.bounds = {'def': self.bounds}
        if(type(self.doKey) is not dict):
            self.doKey = {'def': self.doKey}

    # detects what key was clicked
    def select(self, pos, keys):
        pos = [pos[0]-self.off[0], pos[1]-self.off[1]]
        if self.selected == None:
            if -1<pos[0] < 150:
                if -1<pos[1]<len(keys)*graphics.fontSz:
                    self.selected = keys[pos[1]//graphics.fontSz]
        else: 
            self.selected = None
        return -1<pos[0]<self.size[0] and -1<pos[1]<self.size[1]

    # creates the key which shows what each colored line represents
    def key(self, tm):
        data = self.data
        i = 0
        for dat in data:
            if((dat in self.doKey and self.doKey[dat]) or 
                    (dat not in self.doKey and self.doKey['def'])):
                text = dat+': '
                try:
                    text = text+"{:07.2f}".format(data[dat][tm][0])
                except:
                    print("data doesn't contain a value for: " + dat + " at this index")
                backCol = self.lineCol[dat]
                pos = [self.off[0], self.off[1]+i*graphics.fontSz]
                self.write(text, pos, backCol)
                i=i+1

    # writes text to screen at given position
    def write(self, text, pos, backCol):
        if((backCol[0]+backCol[1]+backCol[2])/3 < 128):
            textCol = (255,255,255)
        else:
            textCol = (0,0,0)
        font = pygame.font.SysFont('notomono', graphics.fontSz-3)
        text = font.render(text, True, textCol, backCol)            
        textRect = text.get_rect()
        textRect.topleft = pos
        self.surf.blit(text, textRect)

    # draws the background and pre-processes data
    def backGround(self, data):
        self.data = data
        for dat in data:
            if(dat not in self.lineCol):
                self.lineCol[dat] = self.colGen(self.colI)
                self.colI = (self.colI+1)
        pygame.draw.rect(self.surf, self.backCol, pygame.Rect(self.off, self.size))

    # displays the position of the selected line at the current moment, 
    # and at the time the mouse is hovering over if possible
    # will also return the mouse position relative to the graph
    def highlight(self):
        data = self.data
        mPos = pygame.mouse.get_pos()

        # identifies mouse position relative to the graph
        if(self.selected in self.bounds):
            bounds = self.bounds[self.selected]
        else:
            bounds = self.bounds["def"]
        pos = self.revPos(mPos, bounds)
        tm = pos[0]

        # writes the latest value of the selected variable to the screen
        if(self.selected is not None):
            times = list(data[self.selected].keys())
            text = 'tm: ' + "{:06.2f}".format(times[-1]) + ' '+self.selected + ': '
            text = text + "{:07.2f}".format(data[self.selected][times[-1]][0])
            posT = [self.off[0], self.off[1]+self.size[1]-graphics.fontSz]
            self.write(text, posT, self.backCol)
        else:
            times = list(data[list(data.keys())[0]].keys())

        # identifies the time value in the graph closest to the one chosen
        i = 1
        if(len(times)>1):
            while times[i]<tm:
                i = i+1
                if(i>=len(times)):
                    i=i-1
                    break
            tm1 = times[i-1]
            tm2 = times[i]
            if(abs(tm-tm1)<abs(tm-tm2)):
                tm = tm1
            else:
                tm = tm2
        else:
            tm = times[0]

        # escapes early if the mouse it outside the range of the graph or there is no selected value
        if(pos[0]<bounds[0][0] or pos[0]>bounds[0][1] or pos[1]<bounds[1][0] or pos[1]>bounds[1][1] or self.selected is None):
            return tm, pos[1]
        
        # writes the value of the selected variable at the time the mouse is hovering over on the screen
        text = 'tm: ' + "{:06.2f}".format(tm) + ' '+self.selected + ': ' + "{:07.2f}".format(data[self.selected][tm][0])
        self.write(text, mPos, self.backCol)

        # and draws a small circle to indicate that position
        center0 = tm, data[self.selected][tm][0]
        center = self.modPos(center0, bounds)
        try:
            pygame.gfxdraw.circle(self.surf, int(center[0]), int(center[1]), 3, self.lineCol[self.selected])
        except:
            print('invalid Data')
        return center0

    # imports the other functions for the graphing app from other files
    from ._graph import graph, circleGraph, multCircleGraph # this file contains the code for drawing the data
    from ._tools import colGen, modPos, revPos, rect #this file contains the math tools used