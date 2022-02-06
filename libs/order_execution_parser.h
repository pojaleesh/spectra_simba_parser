#pragma once

#include "../utils/utils.h"
#include "abstract_parser.h"

class OrderExecutionParser : public AbstractParser {
public:
    OrderExecutionParser(Order order)
        : order_(order)
        , parsed_length_(0)
    { }

    void Parse(std::ifstream& file) override;
    void PrintInfo() const override;
    int GetParsedLength() const override;

private:
    Order order_;
    OrderExecutionPacket packet_;
    int parsed_length_; 
};