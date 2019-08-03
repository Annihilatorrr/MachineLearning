#pragma once
#include <vector>
#include <iostream>

class __declspec(dllexport) LinearRegression
{
    void printThetas(std::vector<double> thetas)
    {
        for(auto theta: thetas)
        {
            std::cout << theta << " ";
        }
        std::cout << std::endl;
    }

    double calculateError(std::vector<std::vector<double>> explanatory, std::vector<double> yReal, std::vector<double> coefficients)
    {
        if (!coefficients.empty())
        {
            double error{};
            for (int observationIndex = 0; observationIndex < yReal.size(); ++observationIndex)
            {
                double yPredicted = coefficients[0]; // constant
                for (int j = 1; j < coefficients.size(); ++j)
                {
                    yPredicted += coefficients[j] * explanatory[observationIndex][j - 1];
                }
                error = error + (yReal[observationIndex] - yPredicted)*(yReal[observationIndex] - yPredicted)/ yReal.size();
            }
            return error;
        }
        return -1;
    }
public:
    LinearRegression();
    ~LinearRegression();

    double calculateHypothesis(std::vector<double> explanatory, std::vector<double> thetas)
    {
        double hyp{};
        for (int i = 0; i < thetas.size(); ++i)
        {
            if (i > 0)
            {
                hyp += explanatory[i - 1] * thetas[i];
            }
            else
            {
                hyp = thetas[i];
            }
        }

        return hyp;
    }

    void fit(std::vector<std::vector<double>> explanatory, std::vector<double> y)
    {
        double alpha = .001;
        std::vector<double> thetas(explanatory[0].size() + 1, 0);
        int iterations = 50000;
        double lastError{};
        double currentError{};
        do
        {
            lastError = currentError;
            for (auto observationNumber = 0; observationNumber < y.size(); ++observationNumber)
            {
                auto hyp = calculateHypothesis(explanatory[observationNumber], thetas);
                thetas[0] -= alpha / y.size() * (hyp - y[observationNumber]);
                for (int i = 0; i < thetas.size(); ++i)
                {
                    if (i > 0)
                    {
                        thetas[i] -= alpha / y.size() * (hyp - y[observationNumber])*explanatory[observationNumber][i - 1];
                    }
                    else
                    {
                        thetas[i] -= alpha / y.size() * (hyp - y[observationNumber]);
                    }
                }
            }
            currentError = calculateError(explanatory, y, thetas);
            if (iterations % 1000 == 0)
            {
                printThetas(thetas);
                std::cout << "Error: " << currentError << std::endl;
            }
        } while (fabs(currentError - lastError) > 0.00001);
        printThetas(thetas);
    }

};

