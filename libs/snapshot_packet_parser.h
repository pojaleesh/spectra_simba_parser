#pragma once

#include "../utils/types.h"
#include "abstract_parser.h"
#include "sbe_message_parser.h"

class SnapshotPacketParser : public AbstractParser {
public:
    SnapshotPacketParser(Order order)
        : order_(order)
        , sbe_message_(order_)
        , parsed_length_(0)
    { }

    void Parse(std::ifstream& file) override;
    void PrintInfo() const override;
    int GetParsedLength() const override;

private:
    Order order_;
    SBEParser sbe_message_;
    int parsed_length_;
};