/*
Author Joshua Jackson z1855047
Assignment 3

This file contains the #include statements and declarations for the memory class
*/

#ifndef MEM_H
#define MEM_H

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

class memory
{
public:
	memory(uint32_t s);
	~memory();

	bool check_illegal(uint32_t addr) const;
	uint32_t get_size() const;
	uint8_t get8(uint32_t addr) const;
	uint16_t get16(uint32_t addr) const;
	uint32_t get32(uint32_t addr) const;
	
	int32_t get8_sx(uint32_t addr) const;
	int32_t get16_sx(uint32_t addr) const;
	int32_t get32_sx(uint32_t addr) const;

	void set8(uint32_t addr, uint8_t val);
	void set16(uint32_t addr, uint16_t val);
	void set32(uint32_t addr, uint32_t val);

	void dump() const;

	bool load_file(const std::string &fname);

private:
	std::vector<uint8_t> mem;
};

#endif
