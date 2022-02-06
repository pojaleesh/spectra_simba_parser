#include "libs/market_data_packet_header_parser.h"
#include "libs/pcap_data_parser.h"
#include "libs/pcap_global_header_parser.h"
#include "libs/pcap_header_parser.h"
#include "libs/simba_spectra_decoder.h"

#include <iostream>
#include <cassert>

int main(int argc, char *argv[]) {
    std::string file_name = argv[1];
    
    int packet_count = std::stoi(argv[2]);
    assert(packet_count > 0);
    
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
        PcapDataParser pcap_data_parser(ProtocolLength::udp_length);
        pcap_data_parser.Parse(file);

        std::cout << "--------------Packet number: " << packet_number << "--------------\n";
        pcap_header_parser.PrintInfo();
        pcap_data_parser.PrintInfo();

        SimbaSpectraDecoder simba_spectra_decoder(
           global_header_parser.GetOrder(),
           pcap_header_parser.GetDataLength() - 42);
        simba_spectra_decoder.Parse(file);
        simba_spectra_decoder.PrintInfo(); 
        
        if (packet_number == packet_count) {
           return 0;
        }
    }

    return 0;
}
