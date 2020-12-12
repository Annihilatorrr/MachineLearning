#include "linearregression.h"

#include <iostream>
#include <vector>
double LinearRegression::computeErrorForPoints(const std::vector<double>& thetas, const std::vector<MultiPoint>& points)
{
    double totalError = 0;
    for (const auto& point : points)
    {
        double diff = point.getY();
        const auto& xValues = point.getXs();
        unsigned int index{};
        for (auto x : xValues)
        {
            if (index > 0)
            {
                diff -= thetas[index] * x;
            }
            else
            {
                diff -= (thetas[index]);
            }
            ++index;
        }
        totalError += diff * diff;
    }
    return totalError / points.size();
}

double LinearRegression::partialDiff(const MultiPoint& point, const std::vector<double>& thetas, int countOfPoints, int thetaIndex)
{
    const auto& xVars = point.getXs();
    const int dimension = xVars.size();

    //(y - theta0 - theta1*x1 - ... - thetaN*xN)
    double diffValue = point.getY() - thetas[0];

    for (int i = 0; i < dimension; ++i)
    {
        diffValue -= thetas[i + 1] * xVars[i];
    }

    // multiple by 1 for partial diff theta0 or by x_i if partial diff theta_i
    if (thetaIndex != 0)
    {
        diffValue *= xVars[thetaIndex - 1];
    }

    return diffValue * (-2.0 / countOfPoints);
}
std::vector<double> LinearRegression::calculateStepGradient(const std::vector<double>& thetas, const std::vector<MultiPoint>& points, double learningRate)
{
    std::vector<double> gradientOfThetaList(thetas.size(), 0.0);

    const int countOfPoints = points.size();
    for (const auto& point : points)
    {
        int thetaIndex{};
        for (auto& gradientOfTheta : gradientOfThetaList)
        {
            auto partDiff = partialDiff(point, thetas, countOfPoints, thetaIndex);
            gradientOfTheta += partDiff;
            ++thetaIndex;
        }
    }
    int gradientIndex{};
    for (auto& gradient : gradientOfThetaList)
    {
        gradient = thetas[gradientIndex] - learningRate * gradient;
        ++gradientIndex;
    }

    return gradientOfThetaList;
}
std::vector<double> LinearRegression::calculateParameters(const std::vector<MultiPoint>& points, double learningRate)
{
    // initial thetas are zeros, count of thetas is 1 more than point dimension
    // for example: y = th0 + x1*th1 + x2*th2
    std::vector<double> thetas(points[0].getDimension() + 1);

    double lastError{};
    static int i = 0;
    do
    {
        i++;
        thetas = calculateStepGradient(thetas, points, learningRate);
        const double currentError = computeErrorForPoints(thetas, points);
        const double eps = std::abs(currentError - lastError);
        
        if (eps < 0.0000001)
        {
            break;
        }

        lastError = currentError;

    } while (true);
    return thetas;
}

void LinearRegression::printThetas(std::vector<double>& thetas) const
{
    for (auto theta : thetas)
    {
        std::cout << theta << " ";
    }
    std::cout << std::endl;
}
