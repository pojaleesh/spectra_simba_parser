#pragma once

#include "types.h"

#include <fstream>
#include <vector>

std::vector<int> ReadBytes(std::ifstream& file, int len);

std::string ConvertToAddress(std::vector<int>::iterator begin,
                             std::vector<int>::iterator end);

uint8_t Parse8bit(std::ifstream& file, Order order = Order::little_endian);

uint16_t Parse16bit(std::ifstream& file, Order order = Order::little_endian);

uint32_t Parse32bit(std::ifstream& file, Order order = Order::little_endian);

uint64_t Parse64bit(std::ifstream& file, Order order = Order::little_endian);

int8_t Parse8bitSigned(std::ifstream& file, Order order = Order::little_endian);

int16_t Parse16bitSigned(std::ifstream& file, Order order = Order::little_endian);

int32_t Parse32bitSigned(std::ifstream& file, Order order = Order::little_endian);

int64_t Parse64bitSigned(std::ifstream& file, Order order = Order::little_endian);

void SkipBytes(std::ifstream& file, int len);

template <typename T>
inline std::string int_to_hex(T val, size_t width=sizeof(T)*2);