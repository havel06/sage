#pragma once

template<typename T1, typename T2>
auto min(const T1& a, const T2& b)
{
	return a < b ? a : b;
}

template<typename T1, typename T2>
auto max(const T1& a, const T2& b)
{
	return a > b ? a : b;
}
