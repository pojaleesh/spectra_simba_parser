#pragma once

#include "../utils/types.h"
#include "abstract_parser.h"
#include "sbe_message_parser.h"

#include <memory>
#include <vector>

class IncrementalPacketHeaderParser : public AbstractParser {
public:
    IncrementalPacketHeaderParser(Order order)
        : order_(order)
        , parsed_length_(0)
    { }
 
    void Parse(std::ifstream& file) override;
    void PrintInfo() const override;
    int GetParsedLength() const override;

private:
    Order order_;
    IncrementalPacketHeader header_;
    int parsed_length_;
};

class IncrementalPacketParser : public AbstractParser {
public:
    IncrementalPacketParser(Order order, int length)
        : order_(order)
        , length_(length)
        , header_parser_(order)
        , parsed_length_(0)
    { }

    void Parse(std::ifstream& file) override;
    void PrintInfo() const override;
    int GetParsedLength() const override;

private:
    Order order_;
    int length_;
    IncrementalPacketHeaderParser header_parser_;
    std::vector<SBEParser> sbe_messages_;
    int parsed_length_;
};