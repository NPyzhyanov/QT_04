#ifndef MEASURE_H
#define MEASURE_H

#include <vector>
#include <string>

namespace Measure
{

struct Unit
{
    std::string name;
    double conversion_rate;
};

struct Quantity
{
    std::string name;
    std::vector<Unit> units;
};

}

#endif // MEASURE_H
