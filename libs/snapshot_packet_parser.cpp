#include "../utils/utils.h"
#include "snapshot_packet_parser.h"

#include <iostream>

int SnapshotPacketParser::GetParsedLength() const
{
    return parsed_length_;
}

void SnapshotPacketParser::Parse(std::ifstream& file)
{
    sbe_message_.Parse(file);
    parsed_length_ += sbe_message_.GetParsedLength();
}

void SnapshotPacketParser::PrintInfo() const
{
    sbe_message_.PrintInfo();
}