#include "../utils.h"
#include "sbe_message_parser.h"
#include "simba_spectra_decoder.h"

#include <iostream>

void SimbaSpectraDecoder::Parse(std::ifstream& file)
{
    market_data_packet_header_parser_->Parse(file);
    length_ -= 16;
    auto msg_flags = market_data_packet_header_parser_->GetFlags();
    if ((msg_flags & 0x8) == 0x8) {
        //std::cout << "Here" << "\n";
        incremental_packet_parser_ = std::make_unique<IncrementalPacketParser>(
            order_, length_);
        incremental_packet_parser_->Parse(file);
    } else {    
        snapshot_packet_parser_ = std::make_unique<SnapshotPacketParser>(
            order_, length_
        );
        snapshot_packet_parser_->Parse(file);
        length_ -= snapshot_packet_parser_->GetParsedLength();
        SkipBytes(file, length_);
    }
}

void SimbaSpectraDecoder::PrintInfo() const
{
    market_data_packet_header_parser_->PrintInfo();
    if (incremental_packet_parser_) {
        incremental_packet_parser_->PrintInfo();
    } else {
        snapshot_packet_parser_->PrintInfo();
    }
}

int SimbaSpectraDecoder::GetParsedLength() const
{
    return parsed_length_;
}