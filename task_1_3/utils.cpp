#include "utils.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

template <typename T>
inline std::string int_to_hex(T val, size_t width)
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(width) << std::hex << (val|0);
    return ss.str();
}

std::vector<int> ReadBytes(std::ifstream& file, int len)
{
    std::vector<int> result;
    for (int i = 0; i < len; i++) {
        result.push_back(file.get());
    }
    return result;
}

uint32_t Parse32bit(std::ifstream& file, Order order)
{
    std::vector<int> bytes = ReadBytes(file, 4);
    if (order == Order::big_endian) {
        std::reverse(bytes.begin(), bytes.end());
    }
    uint32_t result = int((unsigned char)(bytes[0]) << 24 |
        (unsigned char)(bytes[1]) << 16 |
        (unsigned char)(bytes[2]) << 8 |
        (unsigned char)(bytes[3]));
    return result; 
}

uint16_t Parse16bit(std::ifstream& file, Order order)
{
    std::vector<int> bytes = ReadBytes(file, 2);
    if (order == Order::big_endian) {
        std::reverse(bytes.begin(), bytes.end());
    }
    uint16_t result = int((unsigned char)(bytes[0]) << 8 |
        (unsigned char)(bytes[1]));
    return result; 
}

std::string ConvertToAddress(std::vector<int>::iterator begin,
                             std::vector<int>::iterator end) 
{
    std::string result;
    for (auto it = begin; it != end; it++) {
        result += std::to_string(*it);
        result.push_back('.');
    }
    result.pop_back();
    return result;
}

void SkipBytes(std::ifstream& file, int len)
{
    while (len--) {
        file.get();
    }
}