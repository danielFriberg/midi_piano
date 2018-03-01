#pragma once

#include <string>
#include <algorithm>
#include <bitset>

bool is_positive_int(const std::string& s);

// splits bitset<32> into bytes divided by spaces and the divider char
std::string spliceBitset32(std::bitset<32> bits, char dividerChar = '|');