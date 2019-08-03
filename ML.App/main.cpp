// ML.App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <linearregression.h>
#include "csv.h"
#include <iterator>

std::vector<double> getY(std::vector<double>& xVals)
{
    std::vector<double> y;
    for (auto x : xVals)
    {
        y.push_back(x * 2 + 4);
    }
    return y;
}

int main()
{
    //io::CSVReader<5> in("data.csv");
    //in.read_header(io::ignore_extra_column, "", "TV","radio", "newspaper", "sales");
    //std::string vendor; int size; double speed;
    //while (in.read_row(vendor, size, speed)) {
    //    // do stuff with the data
    //}
    std::ifstream input("data.csv");
    if (!input.is_open()) return 1;


    std::string s;
    std::getline(input, s);
    std::vector<double> yVals;// { 1, 2, 3, 4, 5, 6 };
    std::vector<std::vector<double>> xVals;// { 1, 2, 3, 4, 5, 6 };

    while (std::getline(input, s))
    {
        std::stringstream ss(s);
        std::string str;

        double undefindeColumn;
        ss >> undefindeColumn;

        std::getline(ss, str, ',');
        double tv;
        ss >> tv;

        std::getline(ss, str, ',');
        double radio;
        ss >> radio;
        
        std::getline(ss, str, ',');
        double newspapers;
        ss >> newspapers;

        std::getline(ss, str, ',');
        double sales;
        ss >> sales;

        yVals.push_back(sales);
        xVals.push_back({tv, radio, newspapers});
    }

    LinearRegression lr;
    lr.fit(xVals, yVals);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
