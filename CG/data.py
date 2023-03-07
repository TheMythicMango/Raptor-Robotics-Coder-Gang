import pygame
import sys

# reads line and formats it into [x,y,...]
# returns false if the data is unreadable
initialVals = {}
vals = []
keys = []
def read(file1, j, tm):
    global initialVals
    global vals
    global keys
    string = ""
    doLight = False
    with open(file1) as fl:
        lines = fl.readlines()
        if(j>=len(lines)):
            return True, False
        line = lines[j]
        line = line.split(' ')
        try:
            line[0] = line[0][:-1]
            # line[1]
            for i in range(1,len(line)):
                line[i] = float(line[i])
            if(line[0][0]=='*'):
                if len(vals) == 0:
                    if line[0] in initialVals:
                        vals = list(initialVals.values())
                        keys = list(initialVals.keys())
                    else:
                        initialVals[line[0]] = float(line[1])
                elif line[0] in initialVals:
                    if(len(vals)==len(initialVals)):
                        for integ in range(len(vals)):
                            string = string + " " + str(vals[integ]-initialVals[keys[integ]])
                        file = open("CG/trendData.txt", "a")
                        file.write(string+"\n")
                        file.close()
                        vals = []
                    vals.append(float(line[1]))
                doLight = True
                line[0] = line[0][1:]
                # string = str(tm) + " " + str(float(line[1])-initialPos)+"\n"
                
        except Exception as ex:
            template = "An exception of type {0} occurred. Arguments:\n{1!r}"
            message = template.format(type(ex).__name__, ex.args)
            print(message)
            return False, False
        
        return line, doLight

# returns the index of the first relevant value
def toFirst(file):
    i = 21
    tm = -1
    while tm < 0:
        # will allow the user to exit
        # even if no data comes in
        for event in pygame.event.get():
            if event.type == pygame.QUIT: 
                sys.exit()
        
        i = i+1
        line, trend = read(file, i, tm)
        if(type(line) is bool):
            if(line):
                i = i-1
            continue
        if(line[0]=='time'):
            break
    return i

# adds data to the list and returns the updated list
def addData(file, data, tm, i):
    line, trend = read(file, i, tm)
    i = i+1
    if(type(line) is bool):
        if(line):
            i = i-1
    else:
        key = line[0]
        if (key != 'time'):
            if(key not in data):
                data[key] = {}
            while(tm in data[key]):
                tm+=.00001
            data[key][tm] = line[1:]

            if(trend):
                key = "*"+line[0]+"*"
                if(key not in data):
                    data[key] = {}
                data[key][tm] = line[1:]

        else:
            tm = line[1]
            
    return data, tm, i