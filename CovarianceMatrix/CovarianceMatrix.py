import numpy as np
import matplotlib.pyplot as plt

def cov(x, y):
    xbar, ybar = x.mean(), y.mean()
    return np.sum((x - xbar)*(y - ybar))/(len(x) - 1)

# Covariance matrix
def cov_mat(X):
    return np.array([[cov(X[0], X[0]), cov(X[0], X[1])], \
                     [cov(X[1], X[0]), cov(X[1], X[1])]])

def main():

    plt.style.use('ggplot')
    plt.rcParams['figure.figsize'] = (12, 12)
    fig, axes = plt.subplots(ncols=2, nrows=2)

    plt.axis('equal')
    # Normal distributed x and y vector with mean 0 and standard deviation 1
    x = np.random.normal(0, 3, 2000)
    y = np.random.normal(0, 1, 2000)
    X = np.vstack((x, y)).T
    print(cov_mat(X.T))
    axes[0][0].scatter(X[:, 0], X[:, 1])
    axes[0][0].set_xlim([-10,10])
    axes[0][0].set_ylim([-10,10])
    plt.title('Generated Data')
    plt.axis('equal');
    plt.show()


if (__name__ == "__main__"):
    main()
