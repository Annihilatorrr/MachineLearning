import singleplot
import numpy as np

def basic_demo():
    plt = singleplot.SinglePlot()
    plt.plotXY([1, 2, 3, 4], [5, 6, 7, 8], color="red")
    plt.setXLabel("x", fontsize=15, color="green")
    plt.setYLabel("y", fontsize=15, color="green")
    plt.show()

def sin_demo():
    plt = singleplot.SinglePlot()
    plt.set_title("Hello, sine")
    x = np.linspace(0,10, num=50)
    plt.plotXY(x, np.sin(x), color="red", label='sine curve')
    plt.setXLabel("x", fontsize=15, color="green")
    plt.setYLabel("y=sin(x)", fontsize=15, color="green")
    plt.display_legend()
    plt.show()

def sin_cos_demo():
    plt = singleplot.SinglePlot()
    plt.set_title("Hello, sine")
    x = np.linspace(0,10, num=50)
    plt.plotXY(x, np.sin(x), color="red", label='sine curve')
    plt.plotXY(x, np.cos(x), color="red", label='sine curve')
    plt.setXLabel("x", fontsize=15, color="green")
    plt.setYLabel("y=sin(x)", fontsize=15, color="green")
    plt.display_legend()
    plt.show()

def ticks_demo():
    plt = singleplot.SinglePlot()
    x = np.linspace(0,10, num=50)
    plt.plotXY(x, np.sin(x), color="red")
    plt.setXLabel("x", fontsize=15, color="green")
    plt.setYLabel("y=sin(x)", fontsize=15, color="green")
    plt.setYTicks(color='red', labelcolor='red', labelsize='xx-large')
    plt.show()

def figure_demo():
    plt = singleplot.SinglePlot()
    fig = plt.createFigure(0.1,0.1,0.8,.8, title="random axes")
    fig.axes[0].set_xlabel("xBig", fontsize=15, color="green")
    fig.axes[0].set_ylabel("yBig", fontsize=15, color="green")
    ax = plt.addAxisToFigure(fig, 0.6,0.6,0.2,0.2)
    ax.set_xlabel("xSmall", fontsize=15, color="green")
    ax.set_ylabel("ySmall", fontsize=15, color="green")
    plt.show()

def main():
    #basic_demo()
    #sin_demo()
    #ticks_demo()
    #sin_cos_demo()
    figure_demo()
if (__name__ == "__main__"):
    main()
