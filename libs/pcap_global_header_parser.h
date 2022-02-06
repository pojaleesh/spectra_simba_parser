#pragma once

#include "abstract_parser.h"
#include "../types.h"

class PcapGlobalHeaderParser : public AbstractParser {
public:
    void Parse(std::ifstream& file) override;
    void PrintInfo() const override;
    int GetParsedLength() const override;
    Order GetOrder();

private:
    void ParseOrder(std::ifstream& file);
    void ParseMajorVersion(std::ifstream& file);
    void ParseMinorVersion(std::ifstream& file);
    void ParseSnapLen(std::ifstream& file);
    void ParseLinkType(std::ifstream& file);

    Order order_;
    PcapGlobalHeader header_;
    int parsed_length_{};
};