#include "libs/market_data_packet_header_parser.h"
#include "libs/pcap_data_parser.h"
#include "libs/pcap_global_header_parser.h"
#include "libs/pcap_header_parser.h"

#include <iostream>

int main(int argc, char *argv[]) {
    std::string file_name = argv[1];
    std::ifstream file(file_name, std::ios::in | std::ios::out | std::ios::binary);
    
    PcapGlobalHeaderParser global_header_parser;
    global_header_parser.Parse(file);
    global_header_parser.PrintInfo();

    int packet_number = 0;
    while (true) {
        if (file.eof()) {
            break;
        }
        packet_number += 1;

        PcapHeaderParser pcap_header_parser(global_header_parser.GetOrder());
        pcap_header_parser.Parse(file);
        PcapDataParser pcap_data_parser(pcap_header_parser.GetDataLength());
        pcap_data_parser.Parse(file);

        std::cout << "Packet number: " << packet_number << "\n";
        pcap_header_parser.PrintInfo();
        pcap_data_parser.PrintInfo();
        
        // MarketDataPacketHeaderParser market_data_packet_header_parser(
        //    pcap_data_parser.GetSimbaPacketData());
        // market_data_packet_header_parser.PrintInfo();

        // if (packet_number == 1) {
        //     return 0;
        // }
    }

    return 0;
}