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
                points.push_back(MultiPoint(-2.92 - 3.0 * i + 3.0 * j + 0.6 * k,
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
std::vector<std::vector<Banknote>> splitBy(std::vector<Banknote>& objects, ptrToDbl field, double referenceValue)
{
    std::vector<std::vector<Banknote>> splits(2);
    for (auto& b : objects)
    {
        if (b.*field < referenceValue)
        {
            splits[0].push_back(b);
        }
        else
        {
            splits[1].push_back(b);
        }
    }
    return splits;
}

struct Spliter
{
    double gini = 99.0;
    double refVal;
};
void testDesicionTree(std::vector<Banknote>& records)
{
    using ptrToDoubleSplitter = std::tuple<std::vector<Banknote>, std::vector<Banknote>>(std::vector<Banknote>&, ptrToDbl, double);
    std::vector<ptrToDbl> attributes;
    attributes.push_back(&Banknote::varianceOfWavelet);
    attributes.push_back(&Banknote::skewnessOfWavelet);
    attributes.push_back(&Banknote::kurtosisOfWavelet);
    attributes.push_back(&Banknote::entropyOfImage);

    std::cout << std::endl;
    std::map<int, Spliter> giniMap{ {0, {99, 99}}, {1, {99, 99}}, {2, {99, 99}}, {3, {99, 99}} };
    int splitterIndex{};
    const double countOfLessLeft = std::count_if(records.begin(), records.end(), [](const auto& b) {return b.varianceOfWavelet <= 0.3299; });
    const auto recordsSize = records.size();
    for (const auto& attr : attributes)
    {
        for (const auto& record: records)
        {
            double giniParent{};

            if (record.*attr >=0.32 && record.*attr < 0.33)
            {
                int r = 0;
            }
            auto splittedResult = splitBy(records, attr, record.*attr);
            for (const auto& group : splittedResult)
            {
                double score{};
                auto groupSize = !group.empty() ? group.size() : 0;
                std::vector<int>classValues{ 0, 1 };
                for (const auto classValue : classValues)
                {
                    const double countOfGivenClassElements = std::count_if(group.begin(), group.end(), [&](const auto& b) {return b.classification == classValue; });
                    if (groupSize)
                    {
                        double p = (countOfGivenClassElements / groupSize);
                        score += (p * p);
                    }
                }

                giniParent += (1 - score) * groupSize / recordsSize;
            }
            
            if (giniMap[splitterIndex].gini > giniParent)
            {
                giniMap[splitterIndex].gini = giniParent;
                giniMap[splitterIndex].refVal = record.*attr;
            }
        }
        ++splitterIndex;
    }
    auto min = *std::min_element(giniMap.begin(), giniMap.end(), [](const auto& l, const auto& r) { return l.second.gini < r.second.gini; });
    std::cout << "Splitter x[" << min.first << "] <= " << min.second.refVal;
    auto finalSplitResult = splitBy(records, attributes[min.first], min.second.refVal);
    std::cout << " (" << finalSplitResult[0].size() << ", " << finalSplitResult[1].size() << " ) : " << min.second.gini << std::endl;
    if (min.second.gini < 0.1)
    {
        std::cout << "The end\n";
        return;
    }
    testDesicionTree(finalSplitResult[0]);
    testDesicionTree(finalSplitResult[1]);
}

int main()
{
    testLinearRegressionGradientDescent();
    //testLinearRegressionStochasticGradientDescent();
    //auto recordsX = readData("data_banknote_authentication.txt");
    //testDesicionTree(recordsX);
    return 0;
}
