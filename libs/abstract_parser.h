#pragma once

#include <fstream>

class AbstractParser {
public:
    virtual void Parse(std::ifstream& file) = 0;
    virtual void PrintInfo() const = 0;
    virtual int GetParsedLength() const = 0;
    virtual ~AbstractParser() = default;
};