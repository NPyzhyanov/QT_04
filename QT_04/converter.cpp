#include "converter.h"
#include "referencebook.h"

Converter::Converter()
{
    reference_book = &ReferenceBook::reference_book;
}


std::string Converter::get_quantity_name(const unsigned int quantity_order_number)
{
    return (reference_book->at(quantity_order_number)).name;
}


std::vector<std::string> Converter::get_units_names(const unsigned int quantity_order_number)
{
    std::vector<std::string> output;
    std::vector<Measure::Unit> units = reference_book->at(quantity_order_number).units;
    for (auto unit : units)
    {
        output.push_back(unit.name);
    }
    return output;
}


double Converter::get_conversion_rate(const unsigned int quantity_order_number, const unsigned int source_unit_order_number, const unsigned int destination_unit_order_number)
{
    double source_to_base_conversion_rate = (reference_book->at(quantity_order_number).units).at(source_unit_order_number).conversion_rate;
    double destination_to_base_conversion_rate = (reference_book->at(quantity_order_number).units).at(destination_unit_order_number).conversion_rate;
    
    return source_to_base_conversion_rate / destination_to_base_conversion_rate;
}


Converter::~Converter()
{
    reference_book = nullptr;
}
