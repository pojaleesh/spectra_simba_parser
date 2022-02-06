#include "../utils/utils.h"
#include "market_data_packet_header_parser.h"

#include <iostream>

static std::unordered_map<uint16_t, std::pair<std::string, std::string>> FlagsSet = {
    {0x1, {"LastFragment 1", "LastFragment 0"}},
    {0x2, {"StartOfSnapshot 1", "StartOfSnaphot 0"}},
    {0x4, {"EndOfSnapshot 1", "EndOfSnapshot 0"}},
    {0x8, {"IncrementalPacket 1", "SnapShotPacket 1"}},
    {0x10, {"PossDupFlag 1", "PossDupFlag 0"}}
};

void MarketDataPacketHeaderParser::Parse(std::ifstream& file)
{
    header_.msg_seq_num = Parse32bit(file, order_);
    header_.msg_size = Parse16bit(file, order_);
    header_.msg_flags = Parse16bit(file, order_);
    header_.sending_time = Parse64bit(file, order_);
    parsed_length_ += ProtocolLength::market_data_packet_header_length;
}

void MarketDataPacketHeaderParser::PrintInfo() const
{
    std::cout << "Market data packet header info:\n";
    std::cout << "Message sequence number: " << header_.msg_seq_num << "\n";
    std::cout << "Message size: " << header_.msg_size << "\n";
    std::cout << "Message flags: " << header_.msg_flags << " <=>\n";

    int flag_number = 0;
    for (const auto& [flag, meanings] : FlagsSet) {
        flag_number += 1;
        if (header_.msg_flags & flag) {
            std::cout << flag_number << "." << meanings.first << "\n";
        } else {
            std::cout << flag_number << "." << meanings.second << "\n";
        }
    }

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
    Order order)
{
    return std::make_unique<MarketDataPacketHeaderParser>(order);
}