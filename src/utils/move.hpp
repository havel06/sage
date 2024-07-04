#pragma once

template<typename T>
T&& move(T& a)
{
	return (T&&)a;
}
