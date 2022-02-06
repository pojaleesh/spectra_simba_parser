#include "../utils/types.h"
#include "order_update_parser.h"

#include <iostream>

static std::unordered_map<uint64_t, std::string> MDFlagsSet = {
    {0x1, "Котировочная (Day)"},
    {0x2, "Встречная (IOC)"},
    {0x4, "Внесистемная заявка"},
    {0x1000, "Признак последней записи в транзакции матчинга"},
    {0x80000, "Заявка Fill-or-Kill"},
    {0x100000, "Запись является результатом перемещения заявки"},
    {0x200000, "Запись является результатом удаления заявки"},
    {0x400000, "Запись является результатом группового удаления заявок"},
    {0x4000000, "Признак адресной заявки"},
    {0x8000000, "Признак заявки по связке"},
    {0x20000000, "Признак удаления остатка заявки по причине кросс-сделки"},
    {0x100000000, "Запись является результатом отмены заявок сервисом Cancel on Disconnect"},
    {0x200000000000, "Признак синтетической заявки"},
    {0x400000000000, "Заявка из системы RFS"} 
};

static std::unordered_map<uint8_t, std::string> MDUpdateAction {
    {0, "New"},
    {2, "Delete"}
};

static std::unordered_map<char, std::string> MDEntryType {
    {'0', "Bid"},
    {'1', "Ask"}
};

void OrderUpdateParser::Parse(std::ifstream& file)
{
    packet_.md_entry_id = Parse64bitSigned(file, order_);
    packet_.md_entry_px = Parse64bitSigned(file, order_);
    packet_.md_entry_size = Parse64bit(file, order_);
    packet_.md_flags_set = Parse64bit(file, order_);
    packet_.security_id = Parse32bitSigned(file, order_);
    packet_.rpt_seq = Parse32bit(file, order_);
    packet_.md_update_action = Parse8bit(file, order_);
    packet_.md_entry_type = Parse8bit(file, order_);
    parsed_length_ += ProtocolLength::order_update_packet_length;
}

void OrderUpdateParser::PrintInfo() const
{
    std::cout << "MD entry id (Идентификатор заявки): "
        << packet_.md_entry_id << "\n";
    std::cout << "MD entry px (Цена заявки): "
        << 0.00001 * packet_.md_entry_px << "\n";
    std::cout << "MD entry size (Объем заявки): "
        << packet_.md_entry_size << "\n";
    std::cout << "MD Flags (Типы заявок, битовая маска): "
        << packet_.md_flags_set << "\n";

    int flag_number = 0;
    for (const auto& [flag, name] : MDFlagsSet) {
        if ((flag & packet_.md_flags_set) == flag) {
            flag_number += 1;
            std::cout << flag_number << ". " << name << "\n";
        }
    }
    if (flag_number == 0) {
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

int OrderUpdateParser::GetParsedLength() const
{
    return parsed_length_;
}