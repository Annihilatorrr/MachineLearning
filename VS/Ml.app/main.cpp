#include <iomanip>
#include <iostream>


#include "../Ml.lib/gradientdescent.h"
#include <stochasticgradientdescent.h>
#include <linearregression.h>


void testLinearRegressionGradientDescent()
{
    LinearRegression<GradientDescent> lr;
    std::vector<MultiPoint> points;

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            for (int k = 0; k < 10; ++k)
            {
                points.push_back(MultiPoint(static_cast<double>(2.4 + 3.3 * i + 3.7 * j + 0.6 * k),
                    { static_cast<double>(i), static_cast<double>(j), static_cast<double>(k) }));
            }
        }
    }
    auto th = lr.calculateParameters(points, 0.0001);

    int thetaIndex{};
    std::cout << "Gradient descent test:" << std::endl;
    std::cout << "Initial values: 2.4 3.3 3.7 0.6" << std::endl;
    std::cout << "Calculated values:" << std::endl;
    for (const auto& grad : th)
    {
        std::cout << std::setw(14) << "theta #" << thetaIndex++;
    }
    std::cout << std::endl;

    for (const auto& grad : th)
    {
        std::cout << std::setw(15) << grad;
    }
    std::cout << std::endl << std::endl;

}

void testLinearRegressionStochasticGradientDescent()
{
    LinearRegression<StochasticGradientDescent> lr;
    std::vector<MultiPoint> points;

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            for (int k = 0; k < 10; ++k)
            {
                points.push_back(MultiPoint(static_cast<double>(2.4 + 3.3 * i + 3.7 * j + 0.6 * k),
                    { static_cast<double>(i), static_cast<double>(j), static_cast<double>(k) }));
            }
        }
    }
    auto th = lr.calculateParameters(points, 0.0001);

    int thetaIndex{};

    std::cout << "Stochastic gradient descent test:" << std::endl;
    std::cout << "Initial values: 2.4 3.3 3.7 0.6" << std::endl;
    std::cout << "Calculated values:" << std::endl;
    for (const auto& grad : th)
    {
        std::cout << std::setw(14) << "theta #" << thetaIndex++;
    }
    std::cout << std::endl;

    for (const auto& grad : th)
    {
        std::cout << std::setw(15) << grad;
    }
    std::cout << std::endl << std::endl;

}

int main()
{
    testLinearRegressionGradientDescent();
    testLinearRegressionStochasticGradientDescent();

    return 0;
}
