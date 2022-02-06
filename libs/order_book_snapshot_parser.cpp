#include "../utils/utils.h"
#include "order_book_snapshot_parser.h"

#include <iostream>

static std::unordered_map<uint64_t, std::string> MDFlagsSet {
    {0x1, "Котировочная (Day)"},
    {0x2, "Встречная (IOC)"},
};

static std::unordered_map<char, std::string> MDEntryType {
    {'0', "Bid"},
    {'1', "Ask"},
    {'J', "Empty Book"}
};

void OrderBookSnapshotParser::Parse(std::ifstream& file)
{
    packet_.security_id = Parse32bitSigned(file, order_);
    packet_.last_msg_seq_num_processed = Parse32bit(file, order_);
    packet_.rpt_seq = Parse32bit(file, order_);
    packet_.exchange_trading_session_id = Parse32bit(file, order_);
    packet_.block_len = Parse16bit(file, order_);
    packet_.group_size = Parse8bit(file, order_);
    parsed_length_ += ProtocolLength::order_book_snapshot_header_length;
    for (int i = 0; i < packet_.group_size; i++) {
        OrderBookSnapshotRecord record;
        record.md_entry_id = Parse64bitSigned(file, order_);
        record.transact_time = Parse64bit(file, order_);
        record.md_entry_px = Parse64bitSigned(file, order_);
        record.md_entry_size = Parse64bitSigned(file, order_);
        record.trade_id = Parse64bitSigned(file, order_);
        record.md_flags_set = Parse64bit(file, order_);
        record.md_entry_type = Parse8bit(file, order_);
        packet_.records.push_back(record);
        parsed_length_ += ProtocolLength::order_book_snapshot_record_length;
    }
}

void OrderBookSnapshotParser::PrintInfo() const
{
    std::cout << "Order book snapshot info:\n";
    std::cout << "Security id (Числовой идентификатор инструмента):" 
        << packet_.security_id << "\n";
    std::cout << "LastMsgSeqNumProcessed (Номер последнего отправленного сообщения):" 
        << packet_.last_msg_seq_num_processed << "\n";
    std::cout << "RptSeq (Номер последнего инкрементального обновления):" << 
        packet_.rpt_seq << "\n";
    std::cout << "BlockLen (Размер группы):" << 
        int(packet_.block_len) << "\n";
    std::cout << "Group size (Количество групп):" 
        << int(packet_.group_size) << "\n\n";
    int record_id = 0;
    for (const auto& record : packet_.records) {
        record_id += 1;
        std::cout << "Record #" << record_id << "\n";
        if (record.md_entry_id == INT64_NULL) {
            std::cout << "MD entry id (Идентификатор заявки): null\n";
        } else {
            std::cout << "MD entry id (Идентификатор заявки): "
                << record.md_entry_id << "\n";
        }
        std::cout << "Transact time (Время начала обработки события): "
            << record.transact_time << "\n";
        if (record.md_entry_px == DECIMAL5_NULL) {
            std::cout << "MD entry px (Цена заявки): null\n"; 
        } else {
            std::cout << "MD entry px (Цена заявки): "
                << 0.00001 * record.md_entry_px << "\n";
        }
        if (record.md_entry_size == INT64_NULL) {
            std::cout << "MD entry size (Объем заявки): null\n"; 
        } else {
            std::cout << "MD entry size (Объем заявки): "
                << record.md_entry_size << "\n";
        }
        if (record.trade_id == INT64_NULL) {
            std::cout << "Trade id (Идентификатор сделки): null\n";
        } else {
            std::cout << "Trade id (Идентификатор сделки): "
                << record.trade_id << "\n";
        }
        std::cout << "MD Flags (Типы заявок и сделок): " << record.md_flags_set << "\n";
        int flag_number = 0;
        for (const auto& [flag, name] : MDFlagsSet) {
            if ((flag & record.md_flags_set) == flag) {
                flag_number += 1;
                std::cout << flag_number << ". " << name << "\n";
            }
        }
        if (flag_number == 0) {
            std::cout << "Никаких флагов в MD Flags\n";
        }
        std::cout << "MD entry type (Тип записи): " 
            << MDEntryType[record.md_entry_type] << "\n" << std::endl;
    }
}

int OrderBookSnapshotParser::GetParsedLength() const
{
    return parsed_length_;
}