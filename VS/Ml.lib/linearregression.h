#pragma once
#include <vector>
#include <iostream>
#include "definitions.h"
#include "multipoint.h"

template <typename GRAD> class EXPORT LinearRegression
{
public:

    std::vector<double> calculateParameters(const std::vector<MultiPoint>& points, double learningRate)
    {
        return GRAD::calculateParameters(points, learningRate);
    }

    void printThetas(std::vector<double>& thetas) const
    {
        for (auto theta : thetas)
        {
            std::cout << theta << " ";
        }
        std::cout << std::endl;
    }

};

