#pragma once
#include <vector>

#include "multipoint.h"

class __declspec(dllexport) LinearRegression
{
    double calculateHypothesis(std::vector<double>& explanatory, std::vector<double>& thetas) const;
    double computeErrorForPoints(const std::vector<double>& thetas, const std::vector<MultiPoint>& points);
    std::vector<double> calculateStepGradient(const std::vector<double>& thetas, const std::vector<MultiPoint>& points, double learningRate);
public:

    std::vector<double> calculateParameters(const std::vector<MultiPoint>& points, double learningRate);
    void printThetas(std::vector<double>& thetas) const;

};

