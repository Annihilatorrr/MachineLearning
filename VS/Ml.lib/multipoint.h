#pragma once
#include <utility>
#include <vector>

class MultiPoint
{
    double m_y = 0.0;
    std::vector<double> m_xs;
public:

   MultiPoint(double y, std::vector<double> xs):m_y(y), m_xs(std::move(xs)){}

    void setY(double y) { m_y = y; }
    void setXs(const std::vector<double>& xs) { m_xs = xs; }

    double getY() const { return m_y; }
    const std::vector<double>& getXs() const { return m_xs; }
    size_t getDimension() const { return m_xs.size() + 1; }
};
