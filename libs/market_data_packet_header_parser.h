#pragma once

#include "../utils/types.h"
#include "abstract_parser.h"

#include <memory>

class MarketDataPacketHeaderParser : public AbstractParser {
public:
    MarketDataPacketHeaderParser(Order order, int length)
        : order_(order)
        , length_(length)
        , parsed_length_(0)
    { }

    void Parse(std::ifstream& file) override;
    void PrintInfo() const override;
    int GetParsedLength() const override;
    uint16_t GetFlags();    
    Order GetOrder();

private:
    Order order_;
    int length_;
    MarketDataPacketHeader header_;
    int parsed_length_;
};

std::unique_ptr<AbstractParser> CreateMarketDataPacketHeaderParser(
    Order order_, int length);