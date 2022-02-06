#pragma once

#include "../utils/types.h"
#include "abstract_parser.h"

#include <memory>

class SBEHeaderParser : public AbstractParser {
public:
    SBEHeaderParser(Order order)
        : order_(order)
        , parsed_length_(0)
    { }

    void Parse(std::ifstream& file) override;
    void PrintInfo() const override;
    int GetParsedLength() const override;
    std::pair<MsgId, std::string> GetMessageId() const;
    int GetRootBlockLength() { return header_.block_length; }

private:
    Order order_;
    SBEHeader header_;
    int parsed_length_;
};

class SBEParser : public AbstractParser {
public:
    SBEParser(Order order)
        : order_(order)
        , header_parser_(std::make_unique<SBEHeaderParser>(order))
        , root_parser_(nullptr)
        , parsed_length_(0)
    { }

    void Parse(std::ifstream& file) override;
    void PrintInfo() const override;
    int GetParsedLength() const override;
private:
    Order order_;
    std::unique_ptr<SBEHeaderParser> header_parser_;
    std::unique_ptr<AbstractParser> root_parser_;
    int parsed_length_;
};