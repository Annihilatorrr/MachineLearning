#pragma once
#include <vector>
#include "definitions.h"
#include "multipoint.h"

class EXPORT LinearRegression
{
    double partialDiff(const MultiPoint& point, const std::vector<double>& thetas, int countOfPoints, int thetaIndex);
    double computeErrorForPoints(const std::vector<double>& thetas, const std::vector<MultiPoint>& points);
    std::vector<double> calculateStepGradient(const std::vector<double>& thetas, const std::vector<MultiPoint>& points, double learningRate);
public:

    std::vector<double> calculateParameters(const std::vector<MultiPoint>& points, double learningRate);
    void printThetas(std::vector<double>& thetas) const;

};

