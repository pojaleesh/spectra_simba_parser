#include "../utils.h"
#include "incremental_packet_header_parser.h"

#include <iostream>

void IncrementalPacketHeaderParser::Parse(std::ifstream& file)
{
    //std::cout << "-------IncrementalPacketHeaderParser--------\n"; 
    header_.transaction_time = Parse64bit(file, order_);
    header_.exchange_trading_session_id = Parse32bit(file, order_);
    parsed_length_ += 12;
    //std::cout << "-------IncrementalPacketHeaderParser--------\n" << std::endl; 
}

void IncrementalPacketHeaderParser::PrintInfo() const
{
    std::cout << "Transaction time: " << header_.transaction_time << "\n";
    if (header_.exchange_trading_session_id == 0xffffffff) {
        std::cout << "Exchange trading session id: NULL\n";
    } else {
        std::cout << "Exchange trading session id: " << header_.exchange_trading_session_id << "\n";
    }
}

int IncrementalPacketHeaderParser::GetParsedLength() const
{
    return parsed_length_;
}

void IncrementalPacketParser::Parse(std::ifstream& file)
{
    header_parser_.Parse(file);
    length_ -= 12;
    while (length_ > 0) {
        SBEParser sbe_parser(order_);
        sbe_parser.Parse(file);
        length_ -= sbe_parser.GetParsedLength();
        sbe_messages_.push_back(std::move(sbe_parser));
    }
    std::cout << length_ << "\n";
    SkipBytes(file, length_);
}

void IncrementalPacketParser::PrintInfo() const
{
    header_parser_.PrintInfo();
    for (const auto& message : sbe_messages_) {
        message.PrintInfo();
    }
}

int IncrementalPacketParser::GetParsedLength() const
{
    return parsed_length_;
}