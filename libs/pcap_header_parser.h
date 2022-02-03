#pragma once

#include "../types.h"
#include "abstract_parser.h"

class PcapHeaderParser : public AbstractParser {
public:
    PcapHeaderParser(Order order)
        : order_(order)
    { }

    void Parse(std::ifstream& file) override;
    void PrintInfo() override;
    uint32_t GetDataLength();

private:
    void ParseOriginalLength(std::ifstream& file);
    void ParseCapturedLength(std::ifstream& file);
    void ParseTimestampSeconds(std::ifstream& file);
    void ParseTimestampMicroseconds(std::ifstream& file);

    PcapPacketHeader header_;
    Order order_;
};