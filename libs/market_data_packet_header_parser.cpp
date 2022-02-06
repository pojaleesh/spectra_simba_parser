#include "../utils.h"
#include "market_data_packet_header_parser.h"

#include <iostream>

void MarketDataPacketHeaderParser::Parse(std::ifstream& file)
{
    header_.msg_seq_num = Parse32bit(file, order_);
    header_.msg_size = Parse16bit(file, order_);
    header_.msg_flags = Parse16bit(file, order_);
    header_.sending_time = Parse64bit(file, order_);
}

void MarketDataPacketHeaderParser::PrintInfo() const
{
    std::cout << "Message sequence number: " << header_.msg_seq_num << "\n";
    std::cout << "Message size: " << header_.msg_size << "\n";
    std::cout << "Message flags: " << header_.msg_flags << "\n";
    std::cout << "Message sending time: " << header_.sending_time << "\n\n";
}

uint16_t MarketDataPacketHeaderParser::GetFlags()
{
    return header_.msg_flags;
}

Order MarketDataPacketHeaderParser::GetOrder()
{
    return order_;
}

int MarketDataPacketHeaderParser::GetParsedLength() const
{
    return parsed_length_;
}

std::unique_ptr<AbstractParser> CreateMarketDataPacketHeaderParser(
    Order order, int length)
{
    return std::make_unique<MarketDataPacketHeaderParser>(order, length);
}