#pragma once
#include <vector>

#include "multipoint.h"

#if defined(_MSC_VER)
    //  Microsoft
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#else
    //  do nothing and hope for the best?
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

class EXPORT LinearRegression
{
    double calculateHypothesis(std::vector<double>& explanatory, std::vector<double>& thetas) const;
    double computeErrorForPoints(const std::vector<double>& thetas, const std::vector<MultiPoint>& points);
    std::vector<double> calculateStepGradient(const std::vector<double>& thetas, const std::vector<MultiPoint>& points, double learningRate);
public:

    std::vector<double> calculateParameters(const std::vector<MultiPoint>& points, double learningRate);
    void printThetas(std::vector<double>& thetas) const;

};

