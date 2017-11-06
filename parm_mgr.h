// Copyright 2017 - Robert J. Erickson
#pragma once
#include <map>
#include "cast_string.h"
#include "flags.h"

namespace GEO {

class ParmManager
{
	enum OptionFlags {
		NOARG=0,
		HIDDEN=1,
		MULTI_VALUE=2,
		IS_SPECIFIED=3,
	};
	struct OptionSpec {
		std::string m_tag;
		CastString m_default; 
		Flags32 m_flags; 
		CastStringVec m_values; 
		OptionSpec(const std::string &tag) : m_tag(tag) {}
		OptionSpec(const std::string &tag, const std::string &dflt) : m_tag(tag), m_default(dflt) {}
		void noArg(bool x) {m_flags(NOARG, x);}
		bool noArg() const {return m_flags(NOARG);}
		void hidden(bool x) {m_flags(HIDDEN, x);}
		bool hidden() const {return m_flags(HIDDEN);}
		bool multiValue() const {return m_flags(MULTI_VALUE);}
		void isSpecified(bool x) {m_flags(IS_SPECIFIED, x);}
		bool isSpecified() const {return m_flags(IS_SPECIFIED);}
		void addValue(const std::string &s) {m_values.push_back(s);}
		const CastString &value() {
			if (m_values.empty()) {
				return m_default; 
			} else {
				return m_values.back();
			}
		}
		CastStringVec &values() {return m_values;}
	private:
		void multiValue(bool x) {m_flags(MULTI_VALUE, x);}
	}; 

	using OptionMap = std::map<std::string, OptionSpec>; 
	OptionMap m_options; 
	std::string m_exePath; 
	CastStringVec m_nonTagArgs; 
public:
	ParmManager(); 
	virtual ~ParmManager() {}

	OptionSpec &addOption(const std::string &tag); 
	OptionSpec &addOption(const std::string &tag, const std::string &dflt); 
	OptionSpec &addOption(const std::string &tag, const std::string &dflt, bool noArg); 
	OptionSpec *getOption(const std::string &tag); 
	const CastString &value(const std::string &tag) {return getOption(tag)->value();}
	const CastStringVec &values(const std::string &tag) {return getOption(tag)->values();}
	bool isSpecified(const std::string &tag) {return getOption(tag)->isSpecified();}

	void parseArgs(int argc, char **argv); 
	CastStringVec &nonTagArgs() {return m_nonTagArgs;}
	const std::string &exePath() {return m_exePath;}
};


}
