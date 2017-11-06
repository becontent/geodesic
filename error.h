// Copyright 2017 - Robert J. Erickson
#pragma once

#include <exception> 
#include <ostream> 
#include <iostream> 
#include <sstream> 
#include "boost/format.hpp"

namespace GEO {

struct Exception : 
	public std::exception
{
	std::string m_msg; 
	Exception(const std::string &msg) : m_msg(msg) {	}
	const char* what(){return m_msg.c_str();}
};

using Msg=boost::format; 
struct Error 
{
	Error(Msg &fmt) {
		throwError(str(fmt)); 
	}
private:
	void throwError(const std::string &s)
	{
		std::cout << s << std::endl; 
		throw Exception(s); 
	}
};

inline void error(Msg &fmt) 
{
	Error tmp(fmt); 
}
inline void error(const std::string &s) {
	error(Msg(s)); 
}
inline void okIf(bool condition, Msg &fmt) 
{
	if (! condition)
		Error tmp(fmt); 
}
inline void okIf(bool condition, const std::string &s) 
{
	okIf(condition, Msg(s)); 
}

} // namespace
