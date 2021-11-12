#pragma once
#include <cstdint>

template <typename T>
class Output
{
public:
	virtual bool Write(const T& data) = 0;
};
