#pragma once
#include <cstdint>

template <typename T>
class Input
{
public:
	virtual bool Read(T& data) = 0;
};
