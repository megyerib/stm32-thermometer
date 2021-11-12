#include <alarm_sound.h>
#include <square_wave.h>
#include <buzzer.h>

const square_wave_t wave_on  = {true, 55.0f, 0.5f};
const square_wave_t wave_off = {false, 55.0f, 0.0f};

AlarmSound& AlarmSound::GetInstance()
{
	static AlarmSound instance;
	return instance;
}

AlarmSound::AlarmSound() : Periodic(500)
{

}

bool AlarmSound::Write(const bool& on)
{
	enable = on;
	state = on;

	Buzzer& buzzer = Buzzer::GetInstance();

	return buzzer.Write(state ? wave_on : wave_off);
}

void AlarmSound::Cyclic()
{
	if(!enable) {
		return;
	}

	state = !state;

	Buzzer& buzzer = Buzzer::GetInstance();
	buzzer.Write(state ? wave_on : wave_off);
}
