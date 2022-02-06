#include "../utils.h"
#include "pcap_header_parser.h"

#include <iostream>

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

void PcapHeaderParser::PrintInfo() const
{
    std::cout << "Original length: " << header_.orig_len << '\n';
    std::cout << "Captured length: " << header_.capt_len << '\n';
    std::cout << "Timestamp seconds: " << header_.ts_sec << '\n';
    std::cout << "Timestamp microseconds: " << header_.ts_usec << '\n';
}

int PcapHeaderParser::GetParsedLength() const
{
    return parsed_length_;
}