// Copyright 2017 - Robert J. Erickson
#include "cast_string.h"

using namespace std; 
namespace GEO {

CastString::CastString()
{	}
CastString::CastString(const std::string &s) :
string(s)
{	}
CastString &CastString::operator=(const char *s) {*this = CastString(s); return *this;}
CastString &CastString::operator=(char x) {*this = to_string(x); return *this;}
CastString &CastString::operator=(int x) {*this = to_string(x); return *this;}
CastString &CastString::operator=(long x) {*this = to_string(x); return *this;}
CastString &CastString::operator=(long long x) {*this = to_string(x); return *this;}
CastString &CastString::operator=(unsigned char x) {*this = to_string(x); return *this;}
CastString &CastString::operator=(unsigned int x) {*this = to_string(x); return *this;}
CastString &CastString::operator=(unsigned long x) {*this = to_string(x); return *this;}
CastString &CastString::operator=(unsigned long long x) {*this = to_string(x); return *this;}
CastString &CastString::operator=(float x) {*this = to_string(x); return *this;}
CastString &CastString::operator=(double x) {*this = to_string(x); return *this;}

CastString::operator char () 			const {return char(stoi(*this));} 
CastString::operator int () 			const {return stoi(*this);} 
CastString::operator long () 			const {return stol(*this);} 
CastString::operator long long () 		const {return stoll(*this);} 
CastString::operator unsigned char () 	const {return (unsigned char)(stoul(*this));} 
CastString::operator unsigned int () 	const {return stoul(*this);} 
CastString::operator unsigned long () 	const {return stoul(*this);} 
CastString::operator unsigned long long () const {return stoull(*this);} 
CastString::operator float () 			const {return stof(*this);} 
CastString::operator double () 			const {return stod(*this);} 


}
