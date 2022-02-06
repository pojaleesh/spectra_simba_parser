#pragma once

#include "../utils/types.h"
#include "abstract_parser.h"

#include <vector>

class PcapDataParser : public AbstractParser {
public:
    PcapDataParser(int packet_length = 42)      //  Ethernet 2 + IPV4 + UDP
        : packet_length_(packet_length)
        , parsed_length_(0)
    { }

    void Parse(std::ifstream& file) override;
    void PrintInfo() const override;
    int GetParsedLength() const override;

private:
    int packet_length_;
    PcapPacketData data_;
    int parsed_length_;
};