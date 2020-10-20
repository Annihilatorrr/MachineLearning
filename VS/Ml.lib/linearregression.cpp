#include "linearregression.h"

#include <iostream>
#include <vector>
double LinearRegression::computeErrorForPoints(const std::vector<double>& thetas, const std::vector<MultiPoint>& points)
{
    double totalError = 0;
    for (const auto& point : points)
    {
        double diff = point.getY();
        int index{};
        for (auto x : point.getXs())
        {
            if (index)
                diff -= thetas[index] * x;
            else
                diff -= (thetas[index]);
            ++index;
        }
        totalError += diff * diff;
    }
    return totalError / points.size();
}

double partialDiff(const MultiPoint& point, const std::vector<double>& thetas, int n, int thetaIndex)
{
    const auto& xVars = point.getXs();
    const int dimension = xVars.size();

    //(y - theta0 - theta1*x1 - ... - thetaN*xN)
    double diffValue = point.getY() - thetas[0] * (1.0);

    for (int i = 0; i < dimension; ++i)
    {
        diffValue -= thetas[i + 1] * xVars[i];
    }

    // multiple by 1 for partial diff theta0 or by x_i if partial diff theta_i
    diffValue *= thetaIndex != 0 ? xVars[thetaIndex - 1] : 1;

    return diffValue * (-2.0 / n);
}
std::vector<double> LinearRegression::calculateStepGradient(const std::vector<double>& thetas, const std::vector<MultiPoint>& points, double learningRate)
{
    std::vector<double> gradientOfThetaList(thetas.size());

    // double multiplier = 1.0/points.size(); // 2.0 is here for the sake of optimization, it comes from derivative of squared variable

    int n = points.size();
    for (const auto& point : points)
    {
        int thetaIndex{};
        for (auto& gradientOfTheta : gradientOfThetaList)
        {
            auto partDiff = partialDiff(point, thetas, n, thetaIndex);
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

    //qDebug() << "==============";
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
        double currentError = computeErrorForPoints(thetas, points);
        double error = abs(currentError - lastError);
        //qDebug() << "error" << error << thetas;
        if (error < 0.0000001)
            break;

        lastError = currentError;

        //if (!(i % 10000))
        //{
        //    for (const auto& grad : thetas)
        //    {
        //        std::cout << grad << " ";
        //    }
        //    std::cout << std::endl;
        //}

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
