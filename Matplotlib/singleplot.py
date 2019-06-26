import matplotlib
import matplotlib.pyplot as plt
import numpy as np

class SinglePlot(object):
    def plotXY(self, xList, yList, **kwargs):
        plt.plot(xList, yList, **kwargs)

    def plotY(self, yList, **kwargs):
        plt.plot(yList, **kwargs)

    def show(self):
        plt.show()

    def setXLabel(self, text, **kwargs):
        plt.xlabel(text, **kwargs)

    def setYLabel(self, text, **kwargs):
        plt.ylabel(text, **kwargs)
    
    def set_title(self, text, **kwargs):
        plt.title(text, **kwargs)

    def display_legend(self, **kwargs):
        plt.legend(**kwargs)

    def setYTicks(self, **kwargs):
        plt.tick_params(axis='y', **kwargs)

    def setXLim(self, fromValue, toValue):
        plt.xlim(fromValue, toValue)

    def createFigure(self, *axes, title):
        fig = plt.figure()
        ax = fig.add_axes(list(axes))
        ax.set_title(title)
        return fig

    def addAxisToFigure(self, fig, *axes):
        ax = fig.add_axes(list(axes))
        return ax