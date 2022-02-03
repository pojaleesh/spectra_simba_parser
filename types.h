#pragma once

#include <string>

//  Описание структуры pcap файла я брал с этих источников
//  https://datatracker.ietf.org/doc/html/rfc1761
//  https://tools.ietf.org/id/draft-gharris-opsawg-pcap-00.html

struct PcapGlobalHeader {
    uint32_t magic_number;              //  identification patter of global header 64 bit 
    uint16_t major_version;             //  major version of pcap packet 16 bit
    uint16_t minor_version;             //  minor version of pcap packet 16 bit
    uint32_t reserved_1;                //  not used field according to rfc of pcap packet 32 bit
    uint32_t reserved_2;                //  not used field according to rfc of pcap packet 32 bit
    uint32_t snap_len;                  //  indicating the maximum number of octets captured from each packet of pcap packet 32 bit
    uint32_t link_type;                 //  identifying the type of datalink of pcap packet 32 bit
};

struct PcapPacketHeader {
    uint32_t orig_len;                  //  actual length of packet 32 bit
    uint32_t capt_len;                  //  included length of packet 32 bit
    uint32_t ts_sec;                    //  timestamp seconds of packet 32 bit
    uint32_t ts_usec;                   //  timestamp microseconds of packet 32 bit
};

// Считаем что данные в pcap пакете это udp пакет(сказано было вывести просто адреса и порты, я еще чек сумму добавил)
struct PcapPacketData {    
    uint32_t header_check_sum;          //  header check sum
    std::string destination_address;    //  destination ip  
    uint32_t destination_port;          //  destination port
    std::string source_address;         //  source ip
    uint32_t source_port;               //  source port
};

struct pcap_packet {
    PcapPacketHeader header;
    PcapPacketData data;
};

enum Order {
    little_endian,
    big_endian,
};

struct MarketDataPacketHeader {
    uint32_t msg_seq_num;               //  unique sequence number of packet 32 bit
    uint16_t msg_size;                  //  length of message in bytes 16 bit
    uint16_t msg_flags;                 //  message flags 16 bit
    uint64_t sending_time;              //  sending time of message 64 bit
};