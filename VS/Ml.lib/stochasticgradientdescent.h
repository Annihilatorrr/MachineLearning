#pragma once
#include <vector>

#include "multipoint.h"
#include "definitions.h"
#include "randomgenerator.h"

class EXPORT StochasticGradientDescent
{
    static std::vector<double> calculateGradients(const std::vector<double>& thetas, const MultiPoint& point, double learningRate);
    static double computeError(const std::vector<double>& thetas, const MultiPoint& point);
    static double partialDiff(const MultiPoint& point, const std::vector<double>& thetas, int countOfPoints, int thetaIndex);
public:
    static std::vector<double> calculateParameters(const std::vector<MultiPoint>& points, double learningRate);
};

