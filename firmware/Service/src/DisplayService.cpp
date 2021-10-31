#include "DisplayService.h"

#define DIGIT_L    0b00011100
#define DIGIT_H    0b01101110

static const Digit7Seg decimals[10] =
{
	[0] = {.byte = DIGIT_0},
	[1] = {.byte = DIGIT_1},
	[2] = {.byte = DIGIT_2},
	[3] = {.byte = DIGIT_3},
	[4] = {.byte = DIGIT_4},
	[5] = {.byte = DIGIT_5},
	[6] = {.byte = DIGIT_6},
	[7] = {.byte = DIGIT_7},
	[8] = {.byte = DIGIT_8},
	[9] = {.byte = DIGIT_9},
};

DisplayService::DisplayService()
{
	PortInit();
}

DisplayService* DisplayService::GetInstance()
{
	static DisplayService instance;
	return &instance;
}

int32_t DisplayService::Write(const float& data)
{
	// Transform data to a fix point decimal with rounding
	int32_t sign = data < 0 ? -1 : 1;
	int32_t intval = (int32_t)((10 * data * sign) + 0.5f);
	intval *= sign;

	Digit7Seg digits[3];

	if (intval <= -995)         // x < -99 (too low)  ->   _L_
	{
		digits[0].byte = DIGIT_NONE;
		digits[1].byte = DIGIT_L;
		digits[2].byte = DIGIT_NONE;
	}
	else if (intval <= -100)    // -99 <= x <= -10    ->   -XX
	{
		digits[0].byte = DIGIT_MINUS;
		intval *= -1;

		digits[1] = decimals[intval / 100 % 10];
		digits[2] = decimals[intval /  10 % 10];
	}
	else if (intval < 0)        // -10 < x < 0        ->   -X.X
	{
		digits[0].byte = DIGIT_MINUS;
		intval *= -1;

		digits[1].byte = decimals[intval / 10 % 10].byte | DIGIT_POINT;
		digits[2] = decimals[intval % 10];
	}
	else if (intval < 100)      // 0 <= x < 10        ->   _X.X
	{
		digits[0].byte = DIGIT_NONE;
		digits[1].byte = decimals[intval / 10 % 10].byte | DIGIT_POINT;
		digits[2] = decimals[intval % 10];
	}
	else if (intval < 1000)     // 10 <= x < 100      ->   XX.X
	{
		digits[0] = decimals[intval / 100 % 10];
		digits[1].byte = decimals[intval / 10 % 10].byte | DIGIT_POINT;
		digits[2] = decimals[intval % 10];
	}
	else if (intval < 10000)    // 100 <= x < 1000    ->   XXX
	{
		digits[0] = decimals[intval / 1000 % 10];
		digits[1] = decimals[intval /  100 % 10];
		digits[2] = decimals[intval /   10 % 10];
	}
	else                        // 1000 <= x          ->   _H_
	{
		digits[0].byte = DIGIT_NONE;
		digits[1].byte = DIGIT_H;
		digits[2].byte = DIGIT_NONE;
	}

	// Write to display
	for (int i = 0; i < 3; i++)
	{
		digit[i]->Write(digits[i]);
	}

	// Return
	return OUTPUT_WRITE_OK;
}
