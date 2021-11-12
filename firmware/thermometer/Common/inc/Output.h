#pragma once
#include <cstdint>

// TODO checklist for output classes

#define OUTPUT_WRITE_OK  0

template <typename T>
class Output
{
public:
	virtual int32_t Write(const T& data) = 0;
};
