#include "stdafx.h"

#include "utils.h"


bool is_positive_int(const std::string& s) {
	return !s.empty() && std::find_if(begin(s), end(s),
		[](char c) {return !isdigit(c); }) == end(s);
}

std::string spliceBitset32(std::bitset<32> bits, char dividerChar) {
	std::string result;
	std::string divider = "   ";
	divider[1] = dividerChar;
	for (int i = 0; i < 8; i++) result += bits[i] ? '1' : '0';
	result += divider;
	for (int i = 8; i < 16; i++) result += bits[i] ? '1' : '0';
	result += divider;
	for (int i = 16; i < 24; i++) result += bits[i] ? '1' : '0';
	result += divider;
	for (int i = 24; i < 32; i++) result += bits[i] ? '1' : '0';
	std::reverse(begin(result), end(result));
	return result;
}

