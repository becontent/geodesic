// Copyright 2017 - Robert J. Erickson
#pragma once
#include <vector>
#include "utilities/flags.h"

namespace GEO {

class SudokuArray {
public:
	using FlagPVec = std::vector<Flags64*>; 
private:
	using FlagVec = std::vector<Flags64>; 
	const int m_groupSize = 3; 
	std::vector<FlagVec > m_array; 
public:
	SudokuArray(); 
	SudokuArray(const SudokuArray &from) :
	m_array(from.m_array)
	{	}

	FlagPVec row(int row); 
	FlagPVec col(int col); 
	FlagPVec group(int row, int col); 
	void assign(int row, int col, int val); 
	void clear(int row, int col, int val); 
	void clear(int row, int col); 
	Flags64 &operator()(int row, int col); 
	void dump(); 
	int gridSize() {return m_groupSize * m_groupSize; }
	int groupSize() {return m_groupSize;}
private:
	void init(); 
	unsigned long long defaultFlagVal(); 
}; 

} // namespace
