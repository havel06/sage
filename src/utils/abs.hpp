#pragma once

template<typename T>
T abs(T value)
{
	return (value >= 0) ? value : -value;
}
