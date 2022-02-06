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

uint64_t Parse64bit(std::ifstream& file, Order order)
{
    std::vector<int> bytes = ReadBytes(file, 8);
    if (order == Order::big_endian) {
        std::reverse(bytes.begin(), bytes.end());
    }
    uint64_t result = static_cast<uint64_t>(bytes[0]) << 56 |
        static_cast<uint64_t>(bytes[1]) << 48 |
        static_cast<uint64_t>(bytes[2]) << 40 |
        static_cast<uint64_t>(bytes[3]) << 32 |
        static_cast<uint64_t>(bytes[4]) << 24 |
        static_cast<uint64_t>(bytes[5]) << 16 |
        static_cast<uint64_t>(bytes[6]) << 8 |
        static_cast<uint64_t>(bytes[7]);
    return result;
}

int64_t Parse64bitSigned(std::ifstream& file, Order order)
{
    std::vector<int> bytes = ReadBytes(file, 8);
    if (order == Order::big_endian) {
        std::reverse(bytes.begin(), bytes.end());
    }
    int64_t result = static_cast<int64_t>(bytes[0]) << 56 |
        static_cast<int64_t>(bytes[1]) << 48 |
        static_cast<int64_t>(bytes[2]) << 40 |
        static_cast<int64_t>(bytes[3]) << 32 |
        static_cast<int64_t>(bytes[4]) << 24 |
        static_cast<int64_t>(bytes[5]) << 16 |
        static_cast<int64_t>(bytes[6]) << 8 |
        static_cast<int64_t>(bytes[7]);
    return result;
}

uint32_t Parse32bit(std::ifstream& file, Order order)
{
    std::vector<int> bytes = ReadBytes(file, 4);
    if (order == Order::big_endian) {
        std::reverse(bytes.begin(), bytes.end());
    }
    uint32_t result = static_cast<uint32_t>(bytes[0]) << 24 |
        static_cast<uint32_t>(bytes[1]) << 16 |
        static_cast<uint32_t>(bytes[2]) << 8 |
        static_cast<uint32_t>(bytes[3]);
    return result; 
}

int32_t Parse32bitSigned(std::ifstream& file, Order order)
{
    std::vector<int> bytes = ReadBytes(file, 4);
    if (order == Order::big_endian) {
        std::reverse(bytes.begin(), bytes.end());
    }
    int32_t result = static_cast<int32_t>(bytes[0]) << 24 |
        static_cast<int32_t>(bytes[1]) << 16 |
        static_cast<int32_t>(bytes[2]) << 8 |
        static_cast<int32_t>(bytes[3]);
    return result; 
}

uint16_t Parse16bit(std::ifstream& file, Order order)
{
    std::vector<int> bytes = ReadBytes(file, 2);
    if (order == Order::big_endian) {
        std::reverse(bytes.begin(), bytes.end());
    }
    uint16_t result = static_cast<uint16_t>(bytes[0]) << 8 |
        static_cast<uint16_t>(bytes[1]);
    return result; 
}

int16_t Parse16bitSigned(std::ifstream& file, Order order)
{
    std::vector<int> bytes = ReadBytes(file, 2);
    if (order == Order::big_endian) {
        std::reverse(bytes.begin(), bytes.end());
    }
    int16_t result = static_cast<int16_t>(bytes[0]) << 8 |
        static_cast<int16_t>(bytes[1]);
    return result; 
}

uint8_t Parse8bit(std::ifstream& file, Order order)
{
    uint8_t result = static_cast<uint8_t>(file.get());
    return result;
}

int8_t Parse8bitSigned(std::ifstream& file, Order order)
{
    int8_t result = static_cast<int8_t>(file.get());
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
