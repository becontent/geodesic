// Copyright 2017 - Robert J. Erickson

#include <iostream>
#include "parm_mgr.h"
#include "error.h"

using namespace std; 
namespace GEO {
ParmManager::ParmManager()
{}

ParmManager::OptionSpec &ParmManager::addOption(const string &tag)
{
	auto p = m_options.emplace(tag, OptionSpec(tag)); 
	OptionSpec &rval = p.first->second; 
	return rval; 
}
ParmManager::OptionSpec &ParmManager::addOption(const string &tag, const string &dflt)
{
	auto p = m_options.emplace(tag, OptionSpec(tag, dflt)); 
	OptionSpec &rval = p.first->second; 
	return rval; 
}
ParmManager::OptionSpec &ParmManager::addOption(const string &tag, const string &dflt, bool noArg)
{
	auto p = m_options.emplace(tag, OptionSpec(tag, dflt)); 
	OptionSpec &rval = p.first->second; 
	rval.noArg(noArg); 
	return rval; 
}
void ParmManager::parseArgs(int argc, char ** argv)
{
	m_exePath = argv[0]; 
	for (int i=1; i<argc; ++i) {
		CastString s = argv[i]; 
		auto it = m_options.find(s); 
		if (it == m_options.end()) {
			m_nonTagArgs.push_back(s); 
		} else {
			OptionSpec &spec = it->second; 
			spec.isSpecified(true); 
			if (! spec.noArg()) {
				++i; 
				if (i < argc) {
					CastString val = argv[i]; 
					spec.addValue(val); 
				} else {
					error(Msg("Expecting value after %s") %spec.m_tag); 
				}
			}
		}
	}
}

ParmManager::OptionSpec *ParmManager::getOption(const string &tag)
{
	auto it = m_options.find(tag); 
	if (it == m_options.end()) {
		return nullptr;
	} else {
		return &it->second; 
	}
}

}