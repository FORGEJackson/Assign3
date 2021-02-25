/*
Author Joshua Jackson z1855047
Assignment 3

This file contains the implementation of memory class methods
*/

#ifndef MEM_CPP
#define MEM_CPP

#include "hex.h"
#include "memory.h"

/**
* Constructor for memory class
*
* This constructor sets the memory size, rounded up to the nearest 16 bytes
*
* @param siz Unsigned integer containing the size of memory to allocate
**/
memory::memory(uint32_t siz) {
	siz = (siz+15)&0xfffffff0; //round the length up, mod-16

	mem.resize(siz, 0xa5);
}

/**
* Destructor for memory
**/
memory::~memory() {

}

/**
* Checks if a given address is within the memory range
*
* Compares the given address to memory::get_size()
* 
* @param i unsigned integer containing the address to be checked
*
* @return Returns true if address is out of range, otherwise returns false
**/
bool memory::check_illegal(uint32_t i) const {
	if(i > memory::get_size()) {
		std::cout << "WARNING: Address out of range: " << hex::to_hex0x32(i) << std::endl;
		return true;
	}
	else {
		return false;
	}
}

/**
* Returns the size of mem
*
* @return Returns an unsigned int containing the size of mem
**/
uint32_t memory::get_size() const {
	return mem.size();
}

/**
* Retrieve selected byte from mem
*
* Check to see if the given addr is in your mem by calling check_illegal(). If addr is in
* the valid range then return the value of the byte from your simulated memory at the given
* address. If addr is not in the valid range then return zero to the caller.
*
* @param addr The address of the byte to be retrieved
*
* @return The byte at the given address
**/
uint8_t memory::get8(uint32_t addr) const {
	if(!memory::check_illegal(addr)) {
		return mem[addr];
	}
	else {
		return 0;
	}
}

/**
* Retrieves the two bytes at the given address
*
* This function must call your get8() function twice to get two bytes and then combine them
* in little-endian1 order to create a 16-bit return value
*
* @param addr Address of bytes to be retrieved
*
* @return The two bytes at the given address
**/
uint16_t memory::get16(uint32_t addr) const {
	uint8_t secondHalf = get8(addr);
	uint8_t firstHalf = get8(addr + 1);
	return ((uint16_t)firstHalf << 8) | secondHalf;
}

/**
* Retrieves the four bytes at the given address
*
* This function must call your get16() function twice to get four bytes and then combine them
* in little-endian1 order to create a 32-bit return value
*
* @param addr Address of bytes to be retrieved
*
* @return The four bytes at the given address
**/
uint32_t memory::get32(uint32_t addr) const {
	uint16_t secondHalf = get16(addr);
	uint16_t firstHalf = get16(addr + 2);
	return ((uint32_t)firstHalf << 16) | secondHalf; 
}

/**
* Calls get8() and returns the sign extended value as a 32-bit integer
*
* @param addr Address of bytes to be retrieved
*
* @return The byte at the given address, sign extended to 32 bits
**/
int32_t memory::get8_sx(uint32_t addr) const {
	return (int32_t)memory::get8(addr);
}

/**
* Calls get16() and returns the sign extended value as a 32-bit integer
*
* @param addr Address of bytes to be retrieved
*
* @return The bytes at the given address, sign extended to 32 bits
**/
int32_t memory::get16_sx(uint32_t addr) const {
	return (int32_t)memory::get16(addr);
}

/**
* Calls get32() and returns the sign extended value as a 32-bit integer
*
* @param addr Address of bytes to be retrieved
*
* @return The bytes at the given address, converted to a signed integer
**/
int32_t memory::get32_sx(uint32_t addr) const {
	return memory::get32(addr);
}

/**
* Sets the byte at addr to val
*
* This function will call check_illegal() to verify the the addr argument is valid. If addr is
* valid then set the byte in the simulated memory at that address to the given val. If addr is
* not valid then discard the data and return to the callera
*
* @param addr Address of byte to be changed
* @param val New value for the given byte
**/
void memory::set8(uint32_t addr, uint8_t val) {
	if (!memory::check_illegal(addr)) {
		mem[addr] = val;
	}
}

/**
* Calls set8() twice to store the two bytes in little-endian order
*
* @param addr Address of bytes to be changed
* @param val New value for the given bytes
**/
void memory::set16(uint32_t addr, uint16_t val) {
	uint8_t firstHalf = (uint8_t)((val & 0xFF00) >> 8);
	uint8_t secondHalf = (uint8_t)(val & 0x00FF);
	memory::set8(addr + 1, firstHalf);
	memory::set8(addr, secondHalf);
}

/**
* Calls set16() twice to store the four bytes in little-endian order
*
* @param addr Address of bytes to be changed
* @param val New value for the given bytes
**/
void memory::set32(uint32_t addr, uint32_t val) {
	uint16_t firstHalf = (uint16_t)((val & 0xFFFF0000) >> 16);
	uint16_t secondHalf = (uint16_t)(val & 0x0000FFFF);
	memory::set16(addr + 2, firstHalf);
	memory::set16(addr, secondHalf); 
}

/**
* Dumps the memory contents to std::cout
*
* Dump the entire contents of your simulated memory in hex with the corresponding ASCII
* characters on the right exactly, space-for-space in the format shown in the output section
* of the handout
**/
void memory::dump() const {
	std::string endline = "";
	for (uint32_t addr = 0; addr < get_size() ; ++addr) {
		if (addr % 16 == 0)
			std::cout << std::hex << std::setfill('0') << std::setw(8) << addr << ": ";
		
		std::cout << hex::to_hex8(get8(addr)) << " ";
		
		uint8_t ch = get8(addr);
		ch = isprint(ch) ? ch : '.';
		endline += ch;
			
		if (addr % 16 == 7)
			std::cout << " ";

		if (addr % 16 == 15) {
			std::cout << "*" << endline << "*" << std::endl;
			endline.clear();
		}
	}
}

/**
* Opens file in binary mode and reads contents into memory
**/
bool memory::load_file(const std::string &fname) {
	std::ifstream infile(fname, std::ios::in|std::ios::binary);

	if (infile.is_open()) {
		uint8_t i;
		infile >> std::noskipws;
		for (uint32_t addr = 0; infile >> i; ++addr) {
			if (memory::check_illegal(addr)) {
				std::cerr << "Program too big." << std::endl;
				return false;
			}
			set8(addr, i);
		}
		return true;
	}
	else {
		std::cerr << "Can't open file '" << fname << "' for reading." << std::endl;
		return false;
	} 
}

#endif
