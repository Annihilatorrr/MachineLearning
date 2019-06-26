import matplotlib.pyplot as plt
import numpy as np
import matplotlib.mlab as mlab
import math
from scipy.stats import norm

def init_matplotlib():
    plt.style.use('ggplot')
    plt.rcParams['figure.figsize'] = (12, 9)

def calculate_likelihood(x, mu, sigma): 
    n = len(x)  
    likelihood = -n/2.0 * np.log(2 * np.pi) - n/2.0 * math.log(sigma**2 ) - 1/(2*sigma**2) * sum([(x_i - mu)**2 for x_i in x ])

    return likelihood

def estimate_gaussian_parameters_from_data(data):
    return data.mean(), data.std()

def predict_parameters(data):
    mu = np.mean(data)
    sigma = 0
    #for i in data:
     #   sigma += (mu - i)**2
    #sigma /= len(data)
    sigma = np.sum((mu - data)**2)/len(data);
    return (mu, sigma)


def main():
    init_matplotlib()
    fig, axes = plt.subplots(ncols=2, nrows=2)
    countOfSamples = 1000
    plot_margin = 0.01
    
    mu = 0
    sigma = 2
    
    x_values = np.linspace(mu - 3*sigma, mu + 3*sigma, 1000)
    y_values_1 = mlab.normpdf(x_values, mu, sigma)
    axes[0][0].plot(x_values, y_values_1)
    axes[0][0].set_title("Generated by mlab.normpdf from matplotlib.mlab")
    axes[0][0].margins(plot_margin)
    
    y_values_2 = norm.pdf(x_values, mu, sigma)
    axes[0][1].plot(x_values, y_values_2)
    axes[0][1].set_title("Generated by norm.pdf from scipy.stats ")
    axes[0][1].margins(plot_margin)

    random_data = np.random.normal(mu, sigma, 1000)
    count, bins, ignored =  axes[1][0].hist(random_data, bins=20, density=True)
    axes[1][0].set_title("Generated by np.random.normal and hist ")
    axes[1][0].margins(plot_margin)

    l11 = calculate_likelihood(y_values_1, mu, sigma)
    l12 = calculate_likelihood_cycle_for(y_values_1, mu, sigma)
    l21 = calculate_likelihood(y_values_2, mu, sigma)
    l22 = calculate_likelihood_cycle_for(y_values_2, mu, sigma)
    estimated_mu, estimated_sigma = estimate_gaussian_parameters_from_data(random_data)
    l11 = calculate_likelihood(y_values_1, estimated_mu, estimated_sigma)
    likelihoods={}
    #mu1, sigma1 = predict_parameters(y2)
    #lkl = -len(x)/2*(np.log1p(2*np.pi)+np.log1p(sigma1**2))-1/(2*(sigma1**2))*np.sum((y2-mu1)**2)
    #predict_parameters(y1)
    for expAv in np.arange(float(mu-3), float(mu+3), 0.5):
        for dev in np.arange(0.5, sigma+3, 0.5):
            lh = calculate_likelihood(random_data, expAv, dev)
            print("mu=", expAv, "sigma=", dev, "likelihood=",lh)
            likelihoods[lh] = (expAv, dev)
            
    maxLh = max(s for s in likelihoods)
    print(maxLh, likelihoods[maxLh][0], likelihoods[maxLh][1])
    #axes[1][1].plot(x)
    #axes[1][1].plot(bins, 1/(sigma * np.sqrt(2*np.pi)) *
    #           np.exp( - (bins - mu)**2 / (2 * sigma**2) ),
    #     linewidth=2, color='r')

    #axes[1][1].set_title("Generated from bins by Gauss distr")
    #axes[1][1].margins(plot_margin)
    fig.tight_layout()
    plt.show()

if (__name__ == "__main__"):
    main()