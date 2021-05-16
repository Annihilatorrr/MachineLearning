#include "gradientdescent.h"

std::vector<double> GradientDescent::calculateGradients(const std::vector<double>& thetas, const std::vector<MultiPoint>& points, double learningRate)
{
    std::vector<double> gradient(thetas.size(), 0.0);

    const int countOfPoints = points.size();
    for (const auto& point : points)
    {
        int thetaIndex{};
        for (auto& partDerivative : gradient)
        {
            partDerivative += partialDiffWithRespectToTheta(point, thetas, countOfPoints, thetaIndex);
            ++thetaIndex;
        }
    }
    int partDerivativeIndex{};
    for (auto& partDerivative : gradient)
    {
        // minus because we need to go in the direction where loss function has minimum
        partDerivative = thetas[partDerivativeIndex] - learningRate * partDerivative;
        ++partDerivativeIndex;
    }

    return gradient;
}

double GradientDescent::computeError(const std::vector<double>& thetas, const std::vector<MultiPoint>& points)
{
    double totalError = 0;
    for (const auto& point : points)
    {
        const double realY = point.getY();
        double calculatedY{};
        const auto& xValues = point.getXs();
        unsigned int index{};
        for (auto x : xValues)
        {
            calculatedY += (index > 0) ? thetas[index] * x : thetas[index];
            ++index;
        }
        totalError += (realY - calculatedY) * (realY - calculatedY);
    }
    return totalError / points.size();
}

double GradientDescent::partialDiffWithRespectToTheta(const MultiPoint& point, const std::vector<double>& thetas, int countOfPoints, int thetaIndex)
{
    const auto& xVars = point.getXs();
    const int countOfThetasHavingX = xVars.size();

    //(y - theta0 - theta1*x1 - ... - thetaN*xN)
    double diffValue = point.getY() - thetas[0];

    for (int i = 0; i < countOfThetasHavingX; ++i)
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

std::vector<double> GradientDescent::calculateParameters(const std::vector<MultiPoint>& points, double learningRate)
{
    // initial thetas are zeros, count of thetas is dimension
    // for example: y = th0 + x1*th1 + x2*th2. Here Point dimension is 3
    std::vector<double> thetas(points[0].getDimension());

    double lastError{};
    static int i = 0;
    double eps{};
    do
    {
        i++;
        thetas = calculateGradients(thetas, points, learningRate);
        const double currentError = computeError(thetas, points);
        eps = std::abs(currentError - lastError);

        lastError = currentError;
    }
    while (eps > 0.0000001);
    return thetas;
}
