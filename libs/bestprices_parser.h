#pragma once

#include "abstract_parser.h"
#include "../types.h"
#include "bestprices_parser.h"

#include <memory>
#include <vector>

// Так как размер BestPrices изначально не известен, то этот парсер просто нужен
// для того, чтобы прочитать  NoMDEntries и скипнуть ненужные байты
class BestPricesParser : public AbstractParser {
public:
    BestPricesParser(Order order)
        : order_(order)
        , parsed_length_(0)
    { }
 
    void Parse(std::ifstream& file) override;
    void PrintInfo() const override;
    int GetParsedLength() const override;

private:
    Order order_;
    int parsed_length_;
};
