#pragma once

#include "../types.h"
#include "abstract_parser.h"

#include <vector>

class PcapDataParser : public AbstractParser {
public:
    PcapDataParser(int packet_length = 42)      //  Ethernet 2 + IPV4 + UDP
        : packet_length_(packet_length)
    { }

    void Parse(std::ifstream& file) override;
    void PrintInfo() override;
    std::vector<int> GetSimbaPacketData();

private:
    int packet_length_;
    PcapPacketData data_;
    std::vector<int> bytes_;
};