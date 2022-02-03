#pragma once

#include "abstract_parser.h"
#include "../types.h"

#include <vector>

class MarketDataPacketHeaderParser : public AbstractParser {
public:
    MarketDataPacketHeaderParser(std::vector<int> bytes)
        : bytes_(bytes)
    { }

    void Parse(std::ifstream& file) override;
    void PrintInfo() override;

private:
    std::vector<int> bytes_;
    MarketDataPacketHeader header_;
};