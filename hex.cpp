/*
Author Joshua Jackson z1855047
Assignment 3

This file contains the implementation of hex class methods
*/

#ifndef HEX_CPP
#define HEX_CPP

#include "hex.h"

/**
* Returns the hex value as a string
*
* @param i Hex value to be converted
* 
* @return Hex value as a string
**/
std::string hex::to_hex8(uint8_t i) {
	std::ostringstream os;
	os << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint16_t>(i);

	return os.str();
}

/**
* Returns the hex value as a string
*
* @param i Hex value to be converted
* 
* @return Hex value as a string
**/
std::string hex::to_hex32(uint32_t i) {
	std::ostringstream os;
	os << std::hex << std::setfill('0') << std::setw(8) << i;

	return os.str();
}

/**
* Returns the hex value as a string
*
* @param i Hex value to be converted
* 
* @return Hex value as a string with "0x" appended to front
**/
std::string hex::to_hex0x32(uint32_t i) {
	return std::string("0x")+to_hex32(i);
}

#endif
