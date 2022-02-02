#include <alarm_sound.h>
#include <buzzer.h>
#include <square_wave.h>

const square_wave_t wave_on  = {true, 440.0f, 0.5f};
const square_wave_t wave_off = {false, 440.0f, 0.0f};

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
	if(on && !enable) { // Turning the alarm on
		state = false;
	}

	enable = on;

	Buzzer& buzzer = Buzzer::GetInstance();

	return buzzer.Write(state ? wave_on : wave_off);
}

void AlarmSound::PeriodicFunction()
{
	if(enable) {
		state = !state;
	} else {
		state = false;
	}

	Buzzer& buzzer = Buzzer::GetInstance();
	buzzer.Write(state ? wave_on : wave_off);
}
