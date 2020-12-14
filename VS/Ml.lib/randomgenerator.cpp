#include "randomgenerator.h"

RandomGenerator::RandomGenerator(): _mt(_rd())
{
}

double RandomGenerator::generateRandomInRange(double from, double to)
{
    std::uniform_real_distribution<double> dist(from, to);
    return dist(_mt);
}

unsigned RandomGenerator::generateRandomInRange(unsigned from, unsigned to)
{
    std::uniform_int_distribution<unsigned> dist(from, to);
    return dist(_mt);
}
