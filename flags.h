// Copyright 2017 - Robert J. Erickson
#pragma once

namespace GEO {

template<typename T>
class TFlags {
	T m_flags = 0; 
public:
	TFlags() {}
	TFlags(T x) : m_flags(x) {}
	virtual ~TFlags() {}

	bool operator()(int x) const {return 1 & (m_flags >> x);}
	void operator()(int x, bool y) {
		if (y) {
			m_flags |= T(1) << x;
		} else {
			m_flags &= ~(T(1) << x); 
		}
	}
	T flags() const {return m_flags;}
	void clear() {m_flags = 0;}
	bool operator==(const TFlags &x) const {return m_flags == x.m_flags;}
	bool operator!=(const TFlags &x) const {return m_flags != x.m_flags;}
	void operator=(T x) {m_flags = x;}
}; 

using Flags64 = TFlags<unsigned long long>;
using Flags32 = TFlags<unsigned int>; 

} // namespace
