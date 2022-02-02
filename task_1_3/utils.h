#pragma once

#include "types.h"

#include <fstream>
#include <vector>

std::vector<int> ReadBytes(std::ifstream& file, int len);

std::string ConvertToAddress(std::vector<int>::iterator begin,
                             std::vector<int>::iterator end);

uint16_t Parse16bit(std::ifstream& file, Order order);

uint32_t Parse32bit(std::ifstream& file, Order order);

void SkipBytes(std::ifstream& file, int len);

template <typename T>
inline std::string int_to_hex(T val, size_t width=sizeof(T)*2);