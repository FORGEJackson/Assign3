/*
Author Joshua Jackson z1855047
Assignment 3

This file contains the #include statements and declarations for the hex class
*/

#ifndef HEX_H
#define HEX_H

#include <string>
#include <sstream>
#include <iomanip>

class hex
{
public:
	static std::string to_hex8(uint8_t i);
	static std::string to_hex32(uint32_t i);
	static std::string to_hex0x32(uint32_t i);
};

#endif
