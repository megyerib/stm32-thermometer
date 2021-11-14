#include "client_connection.h"
#include <cstdio>

const size_t BUF_SIZE = 30;

ClientConnection::ClientConnection(Transmitter& transmitter) : transmitter(transmitter)
{

}

bool ClientConnection::Write(const app_state_t& state)
{
	int temp_int = state.temperature * 10.0 + 0.5;
	int thr_int  = state.threshold * 10.0 + 0.5;

	static char buf[BUF_SIZE]; // TODO make own buffer for UART

	int len = sprintf(buf, "TEMP%+03d%+03d\n", temp_int, thr_int);

	return transmitter.Transmit(buf, len);
}
