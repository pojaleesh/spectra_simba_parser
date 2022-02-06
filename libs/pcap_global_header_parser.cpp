#include "../utils/utils.h"
#include "pcap_global_header_parser.h"

#include <iostream>

Order PcapGlobalHeaderParser::GetOrder()
{
    return order_;
}

void PcapGlobalHeaderParser::ParseOrder(std::ifstream& file)
{
    std::vector<int> bytes = ReadBytes(file, 4);
    if (bytes[0] != 0xd4) {
        order_ = Order::little_endian;
    } else {
        order_ = Order::big_endian;
    }
}

void PcapGlobalHeaderParser::ParseMajorVersion(std::ifstream& file)
{
    header_.major_version = Parse16bit(file, order_);
}

void PcapGlobalHeaderParser::ParseMinorVersion(std::ifstream& file)
{
    header_.minor_version = Parse16bit(file, order_);
}

void PcapGlobalHeaderParser::ParseSnapLen(std::ifstream &file)
{
    header_.snap_len = Parse32bit(file, order_); 
}

void PcapGlobalHeaderParser::ParseLinkType(std::ifstream& file)
{
    header_.link_type = Parse32bit(file, order_);
}

void PcapGlobalHeaderParser::Parse(std::ifstream& file)
{
    ParseOrder(file);
    ParseMajorVersion(file); 
    ParseMinorVersion(file);
    SkipBytes(file, 8);                         //  skip reserved_1, reserved_2 fields
    ParseSnapLen(file);
    ParseLinkType(file);
}

void PcapGlobalHeaderParser::PrintInfo() const
{
    std::cout << "Pcap global header info:\n";
    if (order_ == Order::big_endian) {
        std::cout << "Order: big-endian\n";
    } else {
        std::cout << "Order: little-endian\n";
    }
    std::cout << "Major version: " << header_.major_version << "\n";
    std::cout << "Minor version: " << header_.minor_version << "\n";
    std::cout << "Snap len: " << header_.snap_len << "\n";
    std::cout << "Link type: " << header_.link_type << "\n\n"; 
}

int PcapGlobalHeaderParser::GetParsedLength() const
{
    return parsed_length_;
}