#ifndef REFERENCEBOOK_H
#define REFERENCEBOOK_H

#include <vector>
#include "measure.h"

namespace ReferenceBook
{

const std::vector<Measure::Quantity> reference_book{
    {"Длина", {
            {"метр", 1.0}, {"дюйм", 0.0254}, {"морская миля", 1852.0}
        }},
    {"Масса", {
            {"килограмм", 1.0}, {"фунт", 0.45359237}, {"тройская унция", 0.0311034768}
        }},
    {"Энергия", {
            {"джоуль", 1.0}, {"ватт-час", 3600.0}, {"калория", 4.1868}
        }}
};

}

#endif // REFERENCEBOOK_H
