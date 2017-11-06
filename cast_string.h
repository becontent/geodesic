// Copyright 2017 - Robert J. Erickson
#pragma once
#include <string>
#include <vector> 

namespace GEO {

class CastString : public std::string
{
public:
	CastString(); 
	CastString(const std::string &s); 

	CastString &operator=(const char *s); 
	CastString &operator=(char x); 
	CastString &operator=(int x); 
	CastString &operator=(long x); 
	CastString &operator=(long long x); 
	CastString &operator=(unsigned char x); 
	CastString &operator=(unsigned int x); 
	CastString &operator=(unsigned long x); 
	CastString &operator=(unsigned long long x); 
	CastString &operator=(float x); 
	CastString &operator=(double x); 

	operator char () const; 
	operator int () const; 
	operator long () const; 
	operator long long () const; 
	operator unsigned char () const; 
	operator unsigned int () const; 
	operator unsigned long () const; 
	operator unsigned long long () const; 
	operator float () const; 
	operator double () const; 

};
using CastStringVec = std::vector<CastString>; 
}
