#pragma once
#include <output.h>

class Display : public Output<float>
{
public:
	static Display& GetInstance();
	bool Write(const float& data) override;

private:
	Display();
};
