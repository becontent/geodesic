// Copyright 2017 - Robert J. Erickson
#include "sudoku.h"
#include "gtest/gtest.h"

using namespace std; 
namespace GEO {
/// SudokuArray
SudokuArray::SudokuArray() :
m_array(gridSize(), FlagVec(gridSize(), Flags64(defaultFlagVal())))
{	}

SudokuArray::FlagPVec SudokuArray::row(int r)
{
	FlagPVec rval(gridSize()); 
	for (int i=0; i<gridSize(); ++i) {
		rval[i] = &m_array[r][i]; 
	}
	return rval; 
}

SudokuArray::FlagPVec SudokuArray::col(int c)
{
	FlagPVec rval(gridSize()); 
	for (int i=0; i<gridSize(); ++i) {
		rval[i] = &m_array[i][c]; 
	}
	return rval; 
}
SudokuArray::FlagPVec SudokuArray::group(int row, int col)
{
	FlagPVec rval;
	rval.reserve(gridSize()); 
	int startRow = row * m_groupSize; 
	int endRow = startRow + m_groupSize; 
	int startCol = col * m_groupSize; 
	int endCol = startCol + m_groupSize; 
	for (int i=startRow; i<endRow; ++i) {
		for (int j=startCol; j<endCol; ++j) {
			rval.push_back(&m_array[i][j]); 
		}
	}
	return rval; 
}
void SudokuArray::init()
{
	for (int i=0; i<gridSize(); ++i) {
		for (int j=0; j<gridSize(); ++j) {
			for (int v=0; v<gridSize(); ++v) {
				m_array[i][j](v, true); 
			}
		}
	}
}
void SudokuArray::assign(int row, int col, int val)
{
	auto &f = m_array[row][col];
	f.clear(); 
	f(val, true); 
}
void SudokuArray::clear(int row, int col)
{
	m_array[row][col] = defaultFlagVal(); 
}
unsigned long long SudokuArray::defaultFlagVal()
{
	unsigned long long v = 0; 
	v = ~v; 
	v >>= 64 - gridSize(); 
	return v; 
}
void SudokuArray::clear(int row, int col, int val)
{
	auto &f = m_array[row][col];
	f(val, false); 
}

Flags64 &SudokuArray::operator()(int row, int col) 
{
	return m_array[row][col]; 
}

// +------------ + ----------- + ----------- +
// | 123 123 123 | 123 123 123 | 123 123 123 |
// | 456 456 456 | 456 456 456 | 456 456 456 |
// | 789 789 789 | 789 789 789 | 789 789 789 |
// |             |             |             |
// | 123 123 123 | 123 123 123 | 123 123 123 |
// | 456 456 456 | 456 456 456 | 456 456 456 |
// | 789 789 789 | 789 789 789 | 789 789 789 |
// |             |             |             |
// | 123 123 123 | 123 123 123 | 123 123 123 |
// | 456 456 456 | 456 456 456 | 456 456 456 |
// | 789 789 789 | 789 789 789 | 789 789 789 |
// + ----------- + ----------- + ----------- +
// | 123 123 123 | 123 123 123 | 123 123 123 |
// | 456 456 456 | 456 456 456 | 456 456 456 |
// | 789 789 789 | 789 789 789 | 789 789 789 |
// |             |             |             |
// | 123 123 123 | 123 123 123 | 123 123 123 |
// | 456 456 456 | 456 456 456 | 456 456 456 |
// | 789 789 789 | 789 789 789 | 789 789 789 |
// |             |             |             |
// | 123 123 123 | 123 123 123 | 123 123 123 |
// | 456 456 456 | 456 456 456 | 456 456 456 |
// | 789 789 789 | 789 789 789 | 789 789 789 |
// + ----------- + ----------- + ----------- +
// | 123 123 123 | 123 123 123 | 123 123 123 |
// | 456 456 456 | 456 456 456 | 456 456 456 |
// | 789 789 789 | 789 789 789 | 789 789 789 |
// |             |             |             |
// | 123 123 123 | 123 123 123 | 123 123 123 |
// | 456 456 456 | 456 456 456 | 456 456 456 |
// | 789 789 789 | 789 789 789 | 789 789 789 |
// |             |             |             |
// | 123 123 123 | 123 123 123 | 123 123 123 |
// | 456 456 456 | 456 456 456 | 456 456 456 |
// | 789 789 789 | 789 789 789 | 789 789 789 |
// + ----------- + ----------- + ----------- +
void SudokuArray::dump()
{
	auto dumpGroupSep = [this]()
	{
		for (int i=0; i<groupSize(); ++i) {
			cout << "+-"; 
			for (int j=0; j<groupSize(); ++j) {
				for (int v=0; v<groupSize(); ++v) {
					cout << "-"; 
				}
				cout << "-"; 
			}
		}
		cout << "+" << endl; 
	}; 
	auto dumpValSep = [this]()
	{
		for (int i=0; i<groupSize(); ++i) {
			cout << "| "; 
			for (int j=0; j<groupSize(); ++j) {
				for (int v=0; v<groupSize(); ++v) {
					cout << " "; 
				}
				cout << " "; 
			}
		}
		cout << "|" << endl; 
	};
	auto dumpValRow = [this](int row, int valStart)
	{
		int col = 0; 
		for (int i=0; i<groupSize(); ++i) {
			cout << "| "; 
			for (int j=0; j<groupSize(); ++j) {
				for (int v=0; v<groupSize(); ++v) {
					int val = valStart + v; 
					bool set = m_array[row][col](val); 
					if (set) {
						cout << val + 1; 
					} else {
						cout << "."; 
					}
				}
				cout << " "; 
				++col; 
			}
		}
		cout << "|" << endl; 
	};

	dumpGroupSep(); 
	int row = 0; 
	for (int gy=0; gy<groupSize(); ++gy) {
		for (int gRow=0; gRow<groupSize(); ++gRow) {
			if (gRow)
				dumpValSep(); 
			for (int vRow=0; vRow<gridSize(); vRow += groupSize()) {
				dumpValRow(row, vRow); 
			}
			++row; 
		}
		dumpGroupSep(); 
	}
}

TEST(SudokuArray, Basic)
{
	SudokuArray arr; 
	for (int i=0; i<arr.gridSize(); ++i) {
		arr.assign(i, i, i); 
		Flags64 f; 
		f(i, true); 
		EXPECT_EQ(f, arr(i,i)); 
	}
	arr.assign(3, 1, 3); 
	Flags64 f; 
	f(3, true); 
	EXPECT_EQ(f, arr(3,1)); 
	arr.clear(3, 1); 
	Flags64 f2(0x1ff); 
	EXPECT_EQ(f2, arr(3,1)); 
}
TEST(SudokuArray, Groups)
{
	SudokuArray arr; 
	for (int i=0; i<arr.gridSize(); ++i) {
		int col = (i+1) % arr.gridSize(); 
		arr.assign(i, col, i); 
	}
	Flags64 dfltFlag(0x1ff); 
	auto testGroup = [dfltFlag](SudokuArray::FlagPVec &grp, int expVal=-1)
	{
		int cnt = 0; 
		for (auto *f : grp) {
			if (*f != dfltFlag) {
				++cnt; 
				if (expVal >= 0) 
					EXPECT_TRUE((*f)(expVal)); 
			}
		}
		return cnt; 
	}; 
	//arr.dump(); 
	for (int i=0; i<arr.gridSize(); ++i) {
		auto row = arr.row(i);
		int cnt = testGroup(row, i); 
		EXPECT_EQ(1, cnt); 
		auto col = arr.col((i+1) % arr.gridSize()); 
		cnt = testGroup(col, i); 
		EXPECT_EQ(1, cnt); 
	}
	auto grp = arr.group(0, 0); 
	int cnt = testGroup(grp); 
	EXPECT_EQ(2, cnt); 
}

}
