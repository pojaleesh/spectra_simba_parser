#pragma once

#include <fstream>

class AbstractParser {
public:
    virtual void Parse(std::ifstream& file) = 0;
    virtual void PrintInfo() = 0;
    virtual ~AbstractParser() = default;
};