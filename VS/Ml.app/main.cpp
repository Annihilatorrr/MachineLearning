#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "../Ml.lib/gradientdescent.h"
#include <stochasticgradientdescent.h>
#include <linearregression.h>
#include <map>

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

struct Banknote
{
    double varianceOfWavelet;
    double skewnessOfWavelet;
    double kurtosisOfWavelet;
    double entropyOfImage;
    int classification;
};

std::vector<Banknote> readData(const char* fileName)
{
    std::ifstream in(fileName);
    std::vector<Banknote> banknotes;
    if (in.is_open())
    {
        std::string line;
        while (std::getline(in, line))
        {
            Banknote banknote{};
            std::istringstream s(line);
            std::string field;
            std::getline(s, field, ',');
            banknote.varianceOfWavelet = std::stod(field);
            std::getline(s, field, ',');
            banknote.skewnessOfWavelet = std::stod(field);
            std::getline(s, field, ',');
            banknote.kurtosisOfWavelet = std::stod(field);
            std::getline(s, field, ',');
            banknote.entropyOfImage = std::stod(field);
            std::getline(s, field, ',');
            banknote.classification = std::stoi(field);
            banknotes.push_back(banknote);
        }
    }
    return banknotes;
}

typedef double Banknote::* ptrToDbl;
std::tuple<std::vector<Banknote>, std::vector<Banknote>> splitBy(std::vector<Banknote>& objects, ptrToDbl field, double referenceValue)
{
    std::vector<Banknote> first;
    std::vector<Banknote> second;
    for (auto& b : objects)
    {
        if (b.*field < referenceValue)
        {
            first.push_back(b);
        }
        else
        {
            second.push_back(b);
        }
    }
    return { first, second };
}

struct Spliter
{
    double gini;
    double refVal;
};
void testDesicionTree(std::vector<Banknote>& records)
{
    using ptrToDoubleSplitter = std::tuple<std::vector<Banknote>, std::vector<Banknote>>(std::vector<Banknote>&, ptrToDbl, double);
    std::vector<ptrToDbl> splitters;
    splitters.push_back(&Banknote::varianceOfWavelet);
    splitters.push_back(&Banknote::skewnessOfWavelet);
    splitters.push_back(&Banknote::kurtosisOfWavelet);
    splitters.push_back(&Banknote::entropyOfImage);

    
    
    std::cout << "====================" << std::endl;
    std::cout << "varianceOfWavelet" << std::endl;
    std::cout << "skewnessOfWavelet" << std::endl;
    std::cout << "kurtosisOfWavelet" << std::endl;
    std::cout << "entropyOfImage" << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << std::endl;
    std::map<int, Spliter> giniMap{ {0, {99, 99}}, {1, {99, 99}}, {2, {99, 99}}, {3, {99, 99}} };
    int splitterIndex{};
    const double countOfLessLeft = std::count_if(records.begin(), records.end(), [](const auto& b) {return b.varianceOfWavelet <= 0.3299; });
    for (const auto& splitter : splitters)
    {
        for (const auto rec: records)
        {
            double giniParent{};
            std::vector<int>classValues{ 0, 1 };

            auto result = splitBy(records, splitter, rec.*splitter);
            auto& left = std::get<0>(result);
            auto& right = std::get<1>(result);

            if (rec.*splitter >=0.32 && rec.*splitter < 0.33)
            {
                int r = 0;
            }

            double giniLeft{};
            const auto leftSize = !left.empty() ? left.size() : 0;
            const double countOf0Left = std::count_if(left.begin(), left.end(), [](const auto& b) {return b.classification == 0; });
            const double countOf1Left = left.size() - countOf0Left;
            if (leftSize)
            {
                double p0 = (countOf0Left / leftSize);
                double p1 = (countOf1Left / leftSize);
                giniLeft = 1.0 - (p0*p0 + p1*p1);
                giniParent += giniLeft * leftSize / records.size();
            }

            double giniRight{};
            const auto rightSize = !right.empty() ? right.size() : 0;
            const double countOf0Right = std::count_if(right.begin(), right.end(), [](const auto& b) {return b.classification == 0; });
            const double countOf1Right = right.size() - countOf0Right;

            if (rightSize)
            {
                double p0 = (countOf0Right / rightSize);
                double p1 = (countOf1Right / rightSize);
                giniRight = 1.0 - (p0*p0 - p1*p1);
                giniParent += giniRight * rightSize / records.size();
            }

            //std::cout << "totalLeft: " << left.size() << ", 0: " << countOf0Left << ", 1: " << countOf1Left << "| ";
            //std::cout << "totalRight: " << right.size() << ", 0: " << countOf0Right << ", 1: " << countOf1Right << std::endl;
            if (giniMap[splitterIndex].gini > giniParent)
            {
                giniMap[splitterIndex].gini = giniParent;
                giniMap[splitterIndex].refVal = rec.*splitter;
                //std::cout << "splitterIndex: " << splitterIndex << ", Gini parent: " << giniParent << " Gini left: " << giniLeft << " Gini right: " << giniRight << " Value: " << rec.*splitter <<  std::endl;
            }
        }
        ++splitterIndex;
    }
    auto min = *std::min_element(giniMap.begin(), giniMap.end(), [](const auto& l, const auto& r) { return l.second.gini < r.second.gini; });
    std::cout << "The best splitter # " << min.first << " at value " << min.second.refVal;
    if (min.second.gini < 0.22)
    {
        std::cout << "The end\n";
        return;
    }
    auto result2 = splitBy(records, splitters[min.first], min.second.refVal);
    testDesicionTree(std::get<0>(result2));
    testDesicionTree(std::get<1>(result2));
}

int main()
{
    //testLinearRegressionGradientDescent();
    //testLinearRegressionStochasticGradientDescent();
    auto recordsX = readData("data_banknote_authentication.txt");
    testDesicionTree(recordsX);
    return 0;
}
