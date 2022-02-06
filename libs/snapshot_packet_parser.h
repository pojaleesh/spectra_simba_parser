#pragma once

#include "abstract_parser.h"
#include "../types.h"
#include "sbe_message_parser.h"

class SnapshotPacketParser : public AbstractParser {
public:
    SnapshotPacketParser(Order order, int length)
        : order_(order)
        , length_(length)
        , sbe_message_(order_)
        , parsed_length_(0)
    { }

    void Parse(std::ifstream& file) override;
    void PrintInfo() const override;
    int GetParsedLength() const override;

private:
    Order order_;
    int length_;
    SBEParser sbe_message_;
    int parsed_length_;
};