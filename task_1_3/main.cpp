#include "pcap_parser.h"

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

        PcapHeaderParser header_parser(global_header_parser.GetOrder());
        header_parser.Parse(file);
        PcapDataParser data_parser(header_parser.GetDataLength());
        data_parser.Parse(file);

        std::cout << "Packet number: " << packet_number << "\n";
        header_parser.PrintInfo();
        data_parser.PrintInfo();
    }

    return 0;
}