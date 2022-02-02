#include "pcap_parser.h"
#include "utils.h"

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

void PcapGlobalHeaderParser::PrintInfo()
{
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

uint32_t PcapHeaderParser::GetDataLength()
{
    // TODO случай когда capt_len != orig_len, то есть пакет был поврежден
    return header_.capt_len;
}

void PcapHeaderParser::ParseOriginalLength(std::ifstream& input_file)
{
    header_.orig_len = Parse32bit(input_file, order_); 
}

void PcapHeaderParser::ParseCapturedLength(std::ifstream& input_file)
{
    header_.capt_len = Parse32bit(input_file, order_); 
}

void PcapHeaderParser::ParseTimestampSeconds(std::ifstream& input_file)
{
    header_.ts_sec = Parse32bit(input_file, order_);
}

void PcapHeaderParser::ParseTimestampMicroseconds(std::ifstream& input_file)
{
    header_.ts_usec = Parse32bit(input_file, order_);
}

void PcapHeaderParser::Parse(std::ifstream& file)
{
    ParseTimestampSeconds(file);
    ParseTimestampMicroseconds(file);
    ParseCapturedLength(file);
    ParseOriginalLength(file);
}

void PcapHeaderParser::PrintInfo()
{
    std::cout << "Original length: " << header_.orig_len << '\n';
    std::cout << "Captured length: " << header_.capt_len << '\n';
    std::cout << "Timestamp seconds: " << header_.ts_sec << '\n';
    std::cout << "Timestamp microseconds: " << header_.ts_usec << '\n';
}

void PcapDataParser::Parse(std::ifstream& file)
{
    std::vector<int> bytes = ReadBytes(file, packet_length_);
    data_.header_check_sum = ((unsigned char)(bytes[24]) << 8) | 
        (unsigned char)(bytes[25]);
    data_.source_address = ConvertToAddress(bytes.begin() + 26, bytes.begin() + 30);
    data_.destination_address = ConvertToAddress(bytes.begin() + 30, bytes.begin() + 34);
    data_.source_port =  ((unsigned char)(bytes[34]) << 8) | 
        (unsigned char)(bytes[35]);
    data_.destination_port = ((unsigned char)(bytes[36]) << 8) | 
        (unsigned char)(bytes[37]);
}

void PcapDataParser::PrintInfo()
{
    std::cout << "Header check sum: " << data_.header_check_sum << "\n";
    std::cout << "Source address: " << data_.source_address << " -> " << "Destination address: " << data_.destination_address << "\n";
    std::cout << "Source port: " << data_.source_port << "\n";
    std::cout << "Destination port: " << data_.destination_port << "\n\n";
}