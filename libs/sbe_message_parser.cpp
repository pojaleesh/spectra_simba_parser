#include "../utils/utils.h"
#include "bestprices_parser.h"
#include "order_book_snapshot_parser.h"
#include "order_execution_parser.h"
#include "order_update_parser.h"
#include "sbe_message_parser.h"

#include <iostream>

void SBEHeaderParser::Parse(std::ifstream& file)
{
    header_.block_length = Parse16bit(file, order_);
    header_.template_id = Parse16bit(file, order_);
    header_.schema_id = Parse16bit(file, order_);
    header_.version = Parse16bit(file, order_);
}

void SBEHeaderParser::PrintInfo() const
{
    std::cout << "SBE header block length (Длина корневой части): " 
        << header_.block_length << "\n";
    std::cout << "SBE header template id (Идентификатор сообщения): "
       << header_.template_id << " <=> (" << GetMessageId().second << ")\n";
    std::cout << "SBE schema id (Идентификатор схемы сообщений): "
        << header_.schema_id << "\n";
    std::cout << "SBE version (Версия схемы): "
        << header_.version << "\n" << std::endl;
}

std::pair<MsgId, std::string> SBEHeaderParser::GetMessageId() const 
{
    switch (header_.template_id)
    {
        case 1:
            return {MsgId::Hearthbeat, "Hearthbear"};
        case 2:
            return {MsgId::SequenceReset, "SequenceReset"};
        case 3:
            return {MsgId::BestPrices, "BestPrices"};
        case 4:
            return {MsgId::EmptyBook, "EmptyBook"};
        case 5:
            return {MsgId::OrderUpdate, "OrderUpdate"};
        case 6:
            return {MsgId::OrderExecution, "OrderExecution"};
        case 7:
            return {MsgId::OrderBookSnapshot, "OrderBookSnapshot"};
        case 8:
            return {MsgId::SecurityDefinition, "SecurityDefinition"};
        case 9:
            return {MsgId::SecurityStatus, "SecurityStatus"};
        case 10:
            return {MsgId::SecurityDefinitionUpdateReport, "SecurityDefinitionUpdateReport"};
        case 11:
            return {MsgId::TradingSessionStatus, "TradingSessionStatus"};
        case 1000:
            return {MsgId::Logon, "Logon"};
        case 1001:
            return {MsgId::Logout, "Logout"};
        case 1002:
            return {MsgId::MarketDataRequest, "MarketDataRequest"};    
        default:
             break;
    }
    throw 1;
}

int SBEHeaderParser::GetParsedLength() const
{
    return parsed_length_;
}

void SBEParser::Parse(std::ifstream& file) {
    header_parser_->Parse(file);
    auto msg_id = header_parser_->GetMessageId();
    parsed_length_ += 8;
    switch (msg_id.first)
    {
        case MsgId::OrderUpdate:
            root_parser_ = std::make_unique<OrderUpdateParser>(order_);
            break;
        case MsgId::BestPrices:
            root_parser_ = std::make_unique<BestPricesParser>(order_);
            break;
        case MsgId::OrderExecution:
            root_parser_ = std::make_unique<OrderExecutionParser>(order_);
            break;
        case MsgId::OrderBookSnapshot:
            root_parser_ = std::make_unique<OrderBookSnapshotParser>(order_);
            break;
        default:
            break;
    }
    if (root_parser_) {
        root_parser_->Parse(file);
        parsed_length_ += root_parser_->GetParsedLength();
    } else {
        SkipBytes(file, header_parser_->GetRootBlockLength());
        parsed_length_ += header_parser_->GetRootBlockLength();
    }
}

void SBEParser::PrintInfo() const
{
    header_parser_->PrintInfo();
    if (root_parser_ == nullptr) {
        std::cout << "Так как пакет не является: OrderUpdate | OrderExecution | OrderBookSnapshot" 
            << " => не парсим по условию задания\n";
    }
    if (header_parser_->GetMessageId().first == MsgId::OrderUpdate 
        || header_parser_->GetMessageId().first == MsgId::OrderExecution
        || header_parser_->GetMessageId().first == MsgId::OrderBookSnapshot) {
        root_parser_->PrintInfo();
    }
}
    
int SBEParser::GetParsedLength() const
{
    return parsed_length_;
}
