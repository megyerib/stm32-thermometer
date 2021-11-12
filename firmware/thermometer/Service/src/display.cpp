#include <display.h>
#include <seven_seg.h>

#define DIGIT_L    0b00011100
#define DIGIT_H    0b01101110

static const digit_t decimals[10] =
{
	[0] = DIGIT_0,
	[1] = DIGIT_1,
	[2] = DIGIT_2,
	[3] = DIGIT_3,
	[4] = DIGIT_4,
	[5] = DIGIT_5,
	[6] = DIGIT_6,
	[7] = DIGIT_7,
	[8] = DIGIT_8,
	[9] = DIGIT_9,
};

Display::Display()
{

}

Display& Display::GetInstance()
{
	static Display instance;
	return instance;
}

bool Display::Write(const float& data)
{
	// Transform data to a fix point decimal with rounding
	int32_t sign = data < 0 ? -1 : 1;
	int32_t intval = (int32_t)((10 * data * sign) + 0.5f);
	intval *= sign;

	digit_t digits[3];

	if (intval <= -995)         // x < -99 (too low)  ->   _L_
	{
		digits[0] = DIGIT_NONE;
		digits[1] = DIGIT_L;
		digits[2] = DIGIT_NONE;
	}
	else if (intval <= -100)    // -99 <= x <= -10    ->   -XX
	{
		digits[0] = DIGIT_MINUS;
		intval *= -1;

		digits[1] = decimals[intval / 100 % 10];
		digits[2] = decimals[intval /  10 % 10];
	}
	else if (intval < 0)        // -10 < x < 0        ->   -X.X
	{
		digits[0] = DIGIT_MINUS;
		intval *= -1;

		digits[1] = decimals[intval / 10 % 10] | DIGIT_POINT;
		digits[2] = decimals[intval % 10];
	}
	else if (intval < 100)      // 0 <= x < 10        ->   _X.X
	{
		digits[0] = DIGIT_NONE;
		digits[1] = decimals[intval / 10 % 10] | DIGIT_POINT;
		digits[2] = decimals[intval % 10];
	}
	else if (intval < 1000)     // 10 <= x < 100      ->   XX.X
	{
		digits[0] = decimals[intval / 100 % 10];
		digits[1] = decimals[intval / 10 % 10] | DIGIT_POINT;
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
		digits[0] = DIGIT_NONE;
		digits[1] = DIGIT_H;
		digits[2] = DIGIT_NONE;
	}

	// Write to display
	SevenSeg::GetInstance().Write(digits);

	// Return
	return false;
}
