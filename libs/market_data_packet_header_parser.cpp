#include "../utils.h"
#include "market_data_packet_header_parser.h"

#include <iostream>

void MarketDataPacketHeaderParser::Parse(std::ifstream& file)
{
    header_.msg_seq_num = Parse32bit(file);
    header_.msg_size = Parse16bit(file);
    header_.msg_flags = Parse16bit(file);
    header_.sending_time = Parse64bit(file);
}

void MarketDataPacketHeaderParser::PrintInfo()
{
    std::cout << "Message sequence number: " << header_.msg_seq_num << "\n";
    std::cout << "Message size: " << header_.msg_size << "\n";
    std::cout << "Message flags: " << header_.msg_flags << "\n";
    std::cout << "Message sending time: " << header_.sending_time << "\n\n";
}