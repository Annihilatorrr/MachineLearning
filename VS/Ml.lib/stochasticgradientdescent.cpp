#include "stochasticgradientdescent.h"

std::vector<double> StochasticGradientDescent::calculateParameters(const std::vector<MultiPoint>& points, double learningRate)
{
    // initial thetas are zeros, count of thetas is 1 more than point dimension
    // for example: y = th0 + x1*th1 + x2*th2
    std::vector<double> thetas(points[0].getDimension() + 1);
    RandomGenerator rnd;
    const auto lastIndexOfPoints = points.size() - 1;
    double lastError{};
    double eps{};
    do
    {
        const auto pointIndex = rnd.generateRandomInRange(0u, lastIndexOfPoints);
        thetas = calculateGradients(thetas, points[pointIndex], learningRate);
        const double currentError = computeError(thetas, points[pointIndex]);
        eps = std::abs(currentError - lastError);
        lastError = currentError;
    }
    while (eps > 0.0000001);
    return thetas;
}

std::vector<double> StochasticGradientDescent::calculateGradients(const std::vector<double>& thetas,
                                                                   const MultiPoint& point, double learningRate)
{
    std::vector<double> gradients(thetas.size(), 0.0);

    const int countOfPoints = 1;

    int thetaIndex{};
    for (auto& gradient : gradients)
    {
        const auto partDiff = partialDiff(point, thetas, countOfPoints, thetaIndex);
        gradient += partDiff;
        ++thetaIndex;
    }
    int gradientIndex{};
    for (auto& gradient : gradients)
    {
        gradient = thetas[gradientIndex] - learningRate * gradient;
        ++gradientIndex;
    }

    return gradients;
}

double StochasticGradientDescent::computeError(const std::vector<double>& thetas, const MultiPoint& point)
{
    double totalError = 0;
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
    return totalError;
}

double StochasticGradientDescent::partialDiff(const MultiPoint& point, const std::vector<double>& thetas, int countOfPoints, int thetaIndex)
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
