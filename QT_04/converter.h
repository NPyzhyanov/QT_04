#ifndef CONVERTER_H
#define CONVERTER_H

#include <vector>
#include <string>

#include "measure.h"

class Converter
{
public:
    Converter();
    ~Converter();
    
    std::string get_quantity_name(const unsigned int quantity_order_number);
    std::vector<std::string> get_units_names(const unsigned int quantity_order_number);
    double get_conversion_rate(const unsigned int quantity_order_number, const unsigned int source_unit_order_number, const unsigned int destination_unit_order_number);
    
private:
    const std::vector<Measure::Quantity>* reference_book;
    
};

#endif // CONVERTER_H
