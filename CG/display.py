# importing necessary libraries. The graphics run off of pygame

from curses import raw
from data import read, toFirst, addData #these are some functions made to reduce the size of this file
#this is my custom graphing library which allows for easy creation and management of different graphs
from graphics.graphics import graphics 
import sys, pygame
from graphics.dpad import modDpad
import math

# initializing variables and pygame
rawData = {} #this will hold a dictionary with data from data.txt organized: [variable][time][value]
# trendData = {} #same idea for specific data;
firstTmTD = None

pygame.init()
fps = 20
size = 800,700
screen = pygame.display.set_mode(size)
f = open("./CG/controlInput.txt", "w")
f.write("0\n0");
f.close()
i = toFirst("CG/data.txt") #finds the first index of time
i2 = 0;
tm = read("CG/data.txt", i, 0)[1] #reads the time at the first index
tm2 = 0
isSelected = False
doScrub = False
selectedPos = [0,0]

# sets the minimum and maximum values to be displayed
# [[x-min, x-max], [y-min, y-max]]
bounds = {
    'def': [[0,20],[-100,100]],
    'ang': [[0,20],[0.0, 10]],
    'ang2': [[0,20],[-3.14,3.14]],
    'posX': [[0,20],[0,3.566]],
    'posY': [[0,20],[0,3.566]],
    'accelX':[[0,20], [-5,5]],
    'accelY':[[0,20], [-5,5]]
}

# defines the parameters of the graphs I want on the screen
# screen: what window it shows on, size: of the graph, off: offset from top left of screen, 
# bounds: range within the graph, flexBounds: should the bounds increase if a number larger 
# than the current bounds is included, should the graph have a key

# the rawGraph displays the 'rawData' coming in from data.txt
rawGraph = graphics(screen, size = [800,150], off = [0,0], bounds = bounds, backCol = (230,230,230),
                    flexBounds=[True, False], doKey = {'def': True, 'line': False})
# trendGraph = graphics(screen, size = [400,150], off = [400,0], bounds = [[0,20],[-100,100]], backCol= (0,0,100), 
                    # flexBounds=[True, True], doKey={'def': True})
# the state graph displays the current position and rotation of the bot at a specific point in time
stateGraph = graphics(  screen, size = [550, 550], off = [125, 150], bounds = [[0,4], [0,4]], 
                        backCol = (240,240,240), flexBounds = [False, False], doKey=False, lineCol={1: (128,128,0)})
dPad = graphics(  screen, size = [100, 100], off = [670, 570], bounds = [[-127,127], [-127,127]], 
                        backCol = (240,240,240), flexBounds = [False, False], doKey=False, lineCol={1: (128,128,0)})

stateData = {} #the rawData for the state graph

while True:
    if(fps is not None):
        pygame.time.Clock().tick(fps) #sets a framerate
    for k in range(2):
        pTm = tm
        j = 0
        
        while tm == pTm and j < 20:# loops until 'tm' changes or if no change is happening, 100 times
            j = j+1
            rawData, tm, i = addData("CG/data.txt", rawData, tm, i) #adds new data to 'rawData'
            # trendData, tm2, i2 = addData("CG/trendData.txt", trendData, tm2, i2)
            if(firstTmTD is None):
                firstTmTD = tm2
        screen.fill((255,255,255))

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            f = open("./CG/controlInput.txt", "w")
            f.write("close");
            f.close
            sys.exit()
        if event.type == pygame.MOUSEBUTTONUP: #checks if moused clicked one of the key words.
            pos = pygame.mouse.get_pos()
            bRaw = rawGraph.select(pos, list(rawData.keys())) #if it did, then that one is marked as selected
            isSelected = not isSelected
            doScrub = isSelected and bRaw and (rawGraph.selected is None) #otherwise doScrub is set to True

    # draws line at current tm, or mouse tm if doing scrub
    # scrub is where the mouse position is related to the time value on the state graph
    if(doScrub and selectedPos):
        selTm = selectedPos[0]
    else:
        selTm  = pTm
    rawData['line'] = [selTm,rawGraph.bounds['def'][1][0]],[selTm, rawGraph.bounds['def'][1][1]]

    # set the position of the bot on 'stateGraph'
    try:
        circleDat = {1: rawData['circle1'][selTm], 2: rawData['circle2'][selTm]}
    except:
        circleDat = None
    
    bots = ['']
    for k in range(10):
        if(('posX'+str(i)) in rawData):
            bots.append(str(i))
    for bot in bots:
        try:
            botPos = [rawData['posX'+bot][selTm][0], rawData['posY'+bot][selTm][0]]
            botAng = rawData['ang'+bot][selTm][0]
        except:
            botPos = [2,2]
            botAng = 0
        
        # draw the bot on 'stateGraph'
        stateData['bot'+bot] =  stateGraph.rect(botPos, botAng, .10, .10, (0,0,0))
        stateData['line'] = [[0,0], [4,4]]
        frontPos = [botPos[0]+.05*math.sin(botAng), botPos[1]+.05*math.cos(botAng)]
        stateData['front'+bot] = stateGraph.rect(frontPos, botAng, 0, .10, (255, 255, 0))

    # graphs the background of the graphs
    # the data on the graphs
    # and the key for 'rawGraph'
    if(len(rawData)>0):
        rawGraph.backGround(rawData)
        rawGraph.key(selTm)
        selectedPos = rawGraph.highlight() #outputs mos pos relative to bounds
        rawGraph.graph()
        stateGraph.backGround(stateData)
        stateGraph.graph()
        stateGraph.circleGraph(circleDat, 1)
        dPad.backGround(stateData)
        # trendGraph.backGround(trendData)
        # trendGraph.circleGraph(trendData["inputR"], 1)
    f = open("./CG/controlInput.txt", "w")
    if not pygame.mouse.get_pressed()[0]:
        padCircles = {1: [0,0,127], 2: [0,0,10]}
    else:
        mousePos = dPad.revPos(pygame.mouse.get_pos(), dPad.bounds['def'])
        padPos = modDpad(mousePos[0], mousePos[1])
        padPos.append(10)
        padCircles = {1: [0,0,127], 2: padPos}
    dPad.circleGraph(padCircles, 1)

    mousePos = stateGraph.revPos(pygame.mouse.get_pos(), stateGraph.bounds['def'])
    try:
        f.write(str(padPos[0]) + '\n' + str(padPos[1]))
    except:
        randomVariableName = 1
    f.close()

    pygame.display.flip()