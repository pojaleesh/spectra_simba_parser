#pragma once

#include "abstract_parser.h"
#include "market_data_packet_header_parser.h"
#include "incremental_packet_header_parser.h"
#include "snapshot_packet_parser.h"

class SimbaSpectraDecoder : public AbstractParser {
public:
    SimbaSpectraDecoder(Order order, int length)
        : order_(order)
        , length_(length)
        , market_data_packet_header_parser_(
            std::make_unique<MarketDataPacketHeaderParser>(order, ProtocolLength::market_data_packet_header_length))
        , incremental_packet_parser_(nullptr)
        , snapshot_packet_parser_(nullptr)
        , parsed_length_(0)
    { }
 
    void Parse(std::ifstream& file) override;
    void PrintInfo() const override;
    int GetParsedLength() const override;

private:
    Order order_;
    int length_;
    std::unique_ptr<MarketDataPacketHeaderParser> market_data_packet_header_parser_;
    std::unique_ptr<IncrementalPacketParser> incremental_packet_parser_;
    std::unique_ptr<SnapshotPacketParser> snapshot_packet_parser_;
    int parsed_length_; 
};