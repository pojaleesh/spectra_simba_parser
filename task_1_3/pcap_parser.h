#pragma once

#include "types.h"

#include <algorithm>
#include <fstream>
#include <memory>
#include <vector>

class AbstractParser {
public:
    virtual void Parse(std::ifstream& file) = 0;
    virtual void PrintInfo() = 0;
    virtual ~AbstractParser() = default;
};

class PcapGlobalHeaderParser : public AbstractParser {
public:
    void Parse(std::ifstream& file) override;
    void PrintInfo() override;
    Order GetOrder();

private:
    void ParseOrder(std::ifstream& file);
    void ParseMajorVersion(std::ifstream& file);
    void ParseMinorVersion(std::ifstream& file);
    void ParseSnapLen(std::ifstream& file);
    void ParseLinkType(std::ifstream& file);

    Order order_;
    pcap_global_header header_;
};

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

    pcap_packet_header header_;
    Order order_;
};

class PcapDataParser : public AbstractParser {
public:
    PcapDataParser(int packet_length)
        : packet_length_(packet_length)
    { }

    void Parse(std::ifstream& file) override;
    void PrintInfo() override;

private:
    int packet_length_;
    pcap_packet_data data_;
};