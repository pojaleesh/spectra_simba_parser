#include "order_execution_parser.h"

#include <iostream>

static std::unordered_map<uint64_t, std::string> MDFlagsSet = {
    {0x1, "Сделка по котировочной заявке"},
    {0x2, "Сделка по встречной (IOC) заявке"},
    {0x4, "Внесистемная сделка, включая адресные, сделки по ногам, сделки RFS"},
    {0x1000, "Признак последней записи в транзакции матчинга"},
    {0x80000, "Сделка по заявке Fill-or-kill"},
    {0x4000000, "Адресная ссылка"},
    {0x8000000, "Сделка по связке. Ставится у операций по ногам связки"},
    {0x20000000000, "Активная сторона в сделке. Заявка, приведшая к сделке при добавлении в стакан"},
    {0x40000000000, "Пассивная сторона в сделке. Заявка из стакана, участвующая в сделке"},
    {0x200000000000, "Сделка по синтетической заявке"},
    {0x400000000000,  "Сделка из системы RFS"}
};

static std::unordered_map<uint8_t, std::string> MDUpdateAction {
    {1, "Change"},
    {2, "Delete"}
};

static std::unordered_map<char, std::string> MDEntryType {
    {'0', "Bid"},
    {'1', "Ask"}
};

void OrderExecutionParser::Parse(std::ifstream& file)
{
    packet_.md_entry_id = Parse64bitSigned(file, order_);
    packet_.md_entry_px = Parse64bitSigned(file, order_);
    packet_.md_entry_size = Parse64bit(file, order_);
    packet_.last_px = Parse64bitSigned(file, order_);
    packet_.last_qty = Parse64bitSigned(file, order_);
    packet_.trade_id = Parse64bitSigned(file, order_);
    packet_.md_flags_set = Parse64bit(file, order_);
    packet_.security_id = Parse32bitSigned(file, order_);
    packet_.rpt_seq = Parse32bit(file, order_);
    packet_.md_update_action = Parse8bit(file, order_);
    packet_.md_entry_type = Parse8bit(file, order_);
    parsed_length_ += ProtocolLength::order_execution_packet_length;
}

void OrderExecutionParser::PrintInfo() const
{

    std::cout << "MD entry id (Идентификатор заявки): "
        << packet_.md_entry_id << "\n";
    if (packet_.md_entry_px == DECIMAL5_NULL) {
        std::cout << "MD entry px (Цена заявки): null" << "\n";
    } else {
        std::cout << "MD entry px (Цена заявки): "
            << 0.00001 * packet_.md_entry_px << "\n";
    }
    if (packet_.md_entry_size == INT64_NULL) {
        std::cout << "MD entry size (Объем заявки): null" << "\n";
    } else {
        std::cout << "MD entry size (Объем заявки): "
            << packet_.md_entry_size << "\n";
    }
    std::cout << "Last px (Цена сделки): "
        << 0.00001 * packet_.last_px << "\n";
    std::cout << "Last qty (Объем сделки): "
        << packet_.last_qty << "\n";
    std::cout << "Trade id (Идентификатор сделки): "
        << packet_.trade_id << "\n";
    std::cout << "MD Flags (Типы заявок, битовая маска): " 
        << packet_.md_flags_set << "\n";

    int flag_number = 0;
    for (const auto& [flag, name] : MDFlagsSet) {
        if ((flag & packet_.md_flags_set) == flag) {
            flag_number += 1;
            std::cout << flag_number << ". " << name << "\n";
        }
    }
    if (!flag_number) {
        std::cout << "Никаких флагов в MD Flags" << "\n";
    }

    std::cout << "Security id (Числовой идентификатор инструмента.): " 
        << packet_.security_id << "\n";
    std::cout << "RptSeq (Порядковый номер инкрементального обновления.): " 
        << packet_.rpt_seq << "\n";
    std::cout << "MD Update action (Тип инкрементального обновления): " 
        << MDUpdateAction[packet_.md_update_action] << "\n";
    std::cout << "MD entry type (Тип записи): " 
        << MDEntryType[packet_.md_entry_type] << "\n" << std::endl;
}

int OrderExecutionParser::GetParsedLength() const
{
    return parsed_length_;
}