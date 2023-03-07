import numpy
import matplotlib.pyplot as plt
from sklearn.metrics import r2_score

degree = 4
file = "CG/trendData.txt"
firstTmTD = None
data = numpy.loadtxt(file)
x,y = data[:,0], data[:,1]

mymodel = numpy.poly1d(numpy.polyfit(x,y,degree))

myline = numpy.linspace(0,4, 100)

plt.scatter(x, y)
plt.plot(myline, mymodel(myline))

print("r-squared: " + str(r2_score(y, mymodel(x))))
print(numpy.poly1d(mymodel))
# print(mymodel.coef)
plt.show()

