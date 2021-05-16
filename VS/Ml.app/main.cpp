#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../Ml.lib/gradientdescent.h"
#include <stochasticgradientdescent.h>
#include <linearregression.h>

//template <typename T>
//bool read_tuple_element(std::istream& in, T& value) {
//    in >> value;
//    return true;
//}
//
//template <typename Tuple, std::size_t... I>
//void read_tuple_elements(std::istream& in, Tuple& value, std::index_sequence<I...>)
//{
//    std::initializer_list<bool>{ read_tuple_element(in, std::get<I>(value))... };
//}
//  
//template <typename ...Targs> class SimpleCSVParser {
//    std::tuple<Targs...> SimpleCSVParser<Targs...>::iterator::operator*() {
//        std::istringstream in(cur);
//        in.imbue(std::locale(std::locale(), new commasep)); // for comma separation
//        std::tuple<Targs...> t;
//        read_tuple_elements(in, t, std::make_index_sequence<sizeof...(Targs)>{});
//        if (in) { // you may want to check if all data was consumed by adding && in.eof()
//            // now do something with the filled t;
//        }
//        else {
//            // the value could *not* successfully be read: somehow deal with that
//        }
//    }
//};

void testLinearRegressionGradientDescent()
{
    LinearRegression<GradientDescent> lr;
    std::vector<MultiPoint> points;

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            for (int k = 0; k < 10; ++k)
            {
                points.push_back(MultiPoint(2.4 + 3.3 * i + 3.7 * j + 0.6 * k,
                    { static_cast<double>(i), static_cast<double>(j), static_cast<double>(k) }));
            }
        }
    }
    auto th = lr.calculateParameters(points, 0.0001);

    int thetaIndex{};
    std::cout << "Gradient descent test:" << std::endl;
    std::cout << "Initial values: 2.4 3.3 3.7 0.6" << std::endl;
    std::cout << "Calculated values:" << std::endl;
    for (const auto& grad : th)
    {
        std::cout << std::setw(14) << "theta #" << thetaIndex++;
    }
    std::cout << std::endl;

    for (const auto& grad : th)
    {
        std::cout << std::setw(15) << grad;
    }
    std::cout << std::endl << std::endl;

}

void testLinearRegressionStochasticGradientDescent()
{
    LinearRegression<StochasticGradientDescent> lr;
    std::vector<MultiPoint> points;

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            for (int k = 0; k < 10; ++k)
            {
                points.push_back(MultiPoint(static_cast<double>(2.4 + 3.3 * i + 3.7 * j + 0.6 * k),
                    { static_cast<double>(i), static_cast<double>(j), static_cast<double>(k) }));
            }
        }
    }
    auto th = lr.calculateParameters(points, 0.0001);

    int thetaIndex{};

    std::cout << "Stochastic gradient descent test:" << std::endl;
    std::cout << "Initial values: 2.4 3.3 3.7 0.6" << std::endl;
    std::cout << "Calculated values:" << std::endl;
    for (const auto& grad : th)
    {
        std::cout << std::setw(14) << "theta #" << thetaIndex++;
    }
    std::cout << std::endl;

    for (const auto& grad : th)
    {
        std::cout << std::setw(15) << grad;
    }
    std::cout << std::endl << std::endl;

}

void testDesicionTree()
{
    std::ifstream in("data_banknote_authentication.txt");
    if (in.is_open())
    {
        std::string line;
        while (std::getline(in, line))
        {
            std::istringstream s(line);
            std::string field;
            while (std::getline(s, field, ','))
            {
                
            }
        }
    }
}

int main()
{
    testLinearRegressionGradientDescent();
    testLinearRegressionStochasticGradientDescent();
    testDesicionTree();
    return 0;
}
