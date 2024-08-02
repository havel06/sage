#pragma once

#include "utils/log.hpp"
#include <raylib/raylib.h>

class Profiling_Timer
{
public:
	Profiling_Timer(const char* name)
	{
		m_name = name;
		m_time_begin = GetTime();
	}
	~Profiling_Timer()
	{
		const float diff = GetTime() - m_time_begin;
		SG_DEBUG("PROFILE: \"%s\" took %f ms.", m_name, diff * 1000);
	}
private:
	const char* m_name;
	float m_time_begin;
};


#define SG_PROFILE_SCOPE_LINE(name, line) \
	Profiling_Timer _profiler##line(name);

#define SG_PROFILE_SCOPE(name) SG_PROFILE_SCOPE_LINE(name, __LINE__)
