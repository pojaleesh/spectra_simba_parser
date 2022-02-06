#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#define INT64_NULL (-9223372036854775807LL - 1)
#define DECIMAL5_NULL (9223372036854775807)

enum Order {
    little_endian,
    big_endian,
};

enum ProtocolLength {
    udp_length = 42,
    market_data_packet_header_length = 16,
    incremental_packet_header_length = 12,
    SBE_header_length = 8,
    order_execution_packet_length = 66,
    order_update_packet_length = 42,
    order_book_snapshot_header_length = 19,
    order_book_snapshot_record_length = 49,
    best_prices_header_length=3,
};

enum MsgId {
    Hearthbeat = 1,
    SequenceReset = 2,
    BestPrices = 3,
    EmptyBook = 4,
    OrderUpdate = 5,
    OrderExecution = 6,
    OrderBookSnapshot = 7,
    SecurityDefinition = 8,
    SecurityStatus = 9,
    SecurityDefinitionUpdateReport = 10,
    TradingSessionStatus = 11,
    Logon = 1000,
    Logout = 1001,
    MarketDataRequest = 1002,
};

//  Описание структуры pcap файла я брал с этих источников
//  https://datatracker.ietf.org/doc/html/rfc1761
//  https://tools.ietf.org/id/draft-gharris-opsawg-pcap-00.html

struct PcapGlobalHeader {
    uint32_t magic_number;                          //  identification patter of global header 64 bit 
    uint16_t major_version;                         //  major version 16 bit
    uint16_t minor_version;                         //  minor version 16 bit
    uint32_t reserved_1;                            //  not used field according to rfc 32 bit
    uint32_t reserved_2;                            //  not used field according to rfc 32 bit
    uint32_t snap_len;                              //  indicating the maximum number of octets captured from each packet 32 bit
    uint32_t link_type;                             //  identifying the type of datalink 32 bit
};

struct PcapPacketHeader {
    uint32_t orig_len;                              //  actual length 32 bit
    uint32_t capt_len;                              //  included length 32 bit
    uint32_t ts_sec;                                //  timestamp seconds 32 bit
    uint32_t ts_usec;                               //  timestamp microseconds 32 bit
};

// Считаем что данные в pcap пакете это udp пакет(сказано было вывести просто адреса и порты, я еще чек сумму добавил)
struct PcapPacketData {    
    uint32_t header_check_sum;                      //  header check sum
    std::string destination_address;                //  destination ip  
    uint32_t destination_port;                      //  destination port
    std::string source_address;                     //  source ip
    uint32_t source_port;                           //  source port
};

struct MarketDataPacketHeader {
    uint32_t msg_seq_num;                           //  unique sequence number of packet 32 bit
    uint16_t msg_size;                              //  length of message in bytes 16 bit
    uint16_t msg_flags;                             //  message flags 16 bit
    uint64_t sending_time;                          //  sending time of message 64 bit
};

struct IncrementalPacketHeader {
    uint64_t transaction_time;                      //  transaction time 64 bit        
    uint32_t exchange_trading_session_id;           //  exchange_trading_session_id 32 bit
};

struct SBEHeader {
    uint16_t block_length;                          //  Block length 16 bit
    uint16_t template_id;                           //  TemplateId 16 bit
    uint16_t schema_id;                             //  SchemaId 16 bit
    uint16_t version;                               //  Version 16 bit
};

struct SBEMessage {
    SBEHeader header;                               //  SBE message header
    MsgId msg_id;                                   //  Type of SBE message
};

struct OrderUpdatePacket {
    int64_t md_entry_id;                            //  Bid identifier 64 bit
    int64_t md_entry_px;                             //  Bid price 64 bit 
    int64_t md_entry_size;                          //  Bid volume 64 bit 
    uint64_t md_flags_set;                          //  Bid types 64 bit
    int32_t security_id;                            //  Numeric identifier tool 32 bit.
    uint32_t rpt_seq;                               //  Sequence number of the incremental update 32 bit
    uint8_t md_update_action;                       //  Incremental update type 8 bit
    uint8_t md_entry_type;                          //  Record type 8 bit
};

struct OrderExecutionPacket {
    int64_t md_entry_id;                            //  Bid identifier 64 bit
    int64_t md_entry_px;                            //  Bid price 64 bit
    int64_t md_entry_size;                          //  The remaining quantity in the bid 64 bit.
    int64_t last_px;                                //  Transaction price 64 bit
    int64_t last_qty;                               //  Transaction volume 64 bit
    int64_t trade_id;                               //  Transaction identifier 64 bit
    uint64_t md_flags_set;                          //  Transaction types 64 bit
    int32_t security_id;                            //  Numeric identifier tool 32 bit.
    uint32_t rpt_seq;                               //  Sequence number of the incremental update 32 bit
    uint8_t md_update_action;                       //  Incremental update type 8 bit
    uint8_t md_entry_type;                          //  Record type 8 bit
};

struct OrderBookSnapshotRecord {
    int64_t md_entry_id;                            //  Bid identifier 64 bit
    uint64_t transact_time;                         //  The start time of event processing 64 bit
    int64_t md_entry_px;                            //  Bid price 64 bit
    int64_t md_entry_size;                          //  Bid volume 64 bit
    int64_t trade_id;                               //  Transaction identifier 64 bit
    uint64_t md_flags_set;                          //  Transactions and bid types 64 bit
    uint8_t md_entry_type;                          //  Record type 8 bit
};

struct OrderBookSnapshotPacket {
    int32_t security_id;                            //  Numeric identifier tool 32 bit
    uint32_t last_msg_seq_num_processed;            //  Number of MsgSeqNum 32 bit
    uint32_t rpt_seq;                               //  Number of RptSeq 32 bit
    uint32_t exchange_trading_session_id;           //  Trading session id 32 bit
    uint16_t block_len;                             //  Block length of group 16 bit
    uint8_t group_size;                             //  Group size 8 bit
    std::vector<OrderBookSnapshotRecord> records;   //  All snapshot records records.size() * 49 bits
};