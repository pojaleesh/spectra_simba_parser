#pragma once

#include <string>

//  Описание структуры pcap файла я брал с этих источников
//  https://datatracker.ietf.org/doc/html/rfc1761
//  https://tools.ietf.org/id/draft-gharris-opsawg-pcap-00.html

struct pcap_global_header {
    uint32_t magic_number;              //  identification patter of global header 64 bit 
    uint16_t major_version;             //  major version of pcap packet 16 bit
    uint16_t minor_version;             //  minor version of pcap packet 16 bit
    uint32_t reserved_1;                //  not used field according to rfc of pcap packet 32 bit
    uint32_t reserved_2;                //  not used field according to rfc of pcap packet 32 bit
    uint32_t snap_len;                  //  indicating the maximum number of octets captured from each packet of pcap packet 32 bit
    uint32_t link_type;                 //  identifying the type of datalink of pcap packet 32 bit
};

struct pcap_packet_header {
    uint32_t orig_len;                  //  actual length of packet 32 bit
    uint32_t capt_len;                  //  included length of packet 32 bit
    uint32_t ts_sec;                    //  timestamp seconds of packet 32 bit
    uint32_t ts_usec;                   //  timestamp microseconds of packet 32 bit
};

// Считаем что данные в pcap пакете это udp пакет(сказано было вывести просто адреса и порты, я еще чек сумму добавил)
struct pcap_packet_data {    
    uint32_t header_check_sum;          //  header check sum
    std::string destination_address;    //  destination ip  
    uint32_t destination_port;          //  destination port
    std::string source_address;         //  source ip
    uint32_t source_port;               //  source port
};

struct pcap_packet {
    pcap_packet_header header;
    pcap_packet_data data;
};

enum Order {
    little_endian,
    big_endian,
};