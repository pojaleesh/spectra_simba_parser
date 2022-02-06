#include "../utils/utils.h"
#include "pcap_data_parser.h"

#include <iostream>

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

void PcapDataParser::PrintInfo() const
{
    std::cout << "Pcap data parser(udp) info:\n";
    std::cout << "Header check sum: "
        << data_.header_check_sum << "\n";
    std::cout << "Source address: "
        << data_.source_address << " -> "
        << "Destination address: "
        << data_.destination_address << "\n";
    std::cout << "Source port: "
        << data_.source_port << "\n";
    std::cout << "Destination port: "
        << data_.destination_port << "\n\n";
}

int PcapDataParser::GetParsedLength() const
{
    return parsed_length_;
}