#pragma once
#include "multipoint.h"
#include "definitions.h"

class EXPORT GradientDescent
{
    static double partialDiff(const MultiPoint& point, const std::vector<double>& thetas, int countOfPoints, int thetaIndex);
    static double computeError(const std::vector<double>& thetas, const std::vector<MultiPoint>& points);
    static std::vector<double> calculateGradients(const std::vector<double>& thetas, const std::vector<MultiPoint>& points, double learningRate);
public:
    static std::vector<double> calculateParameters(const std::vector<MultiPoint>& points, double learningRate);
};

