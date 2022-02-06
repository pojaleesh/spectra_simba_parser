compile:
	g++ -std=c++17 -fsanitize=address utils/utils.cpp main.cpp libs/pcap_data_parser.cpp libs/pcap_header_parser.cpp libs/pcap_global_header_parser.cpp libs/market_data_packet_header_parser.cpp libs/simba_spectra_decoder.cpp libs/incremental_packet_header_parser.cpp libs/sbe_message_parser.cpp libs/order_update_parser.cpp libs/bestprices_parser.cpp libs/order_execution_parser.cpp libs/snapshot_packet_parser.cpp libs/order_book_snapshot_parser.cpp 
run:
	./a.out file.txt > res.txt
clean:
	rm res.txt a.out
