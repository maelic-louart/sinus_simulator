#include "sinus_simulator.h"




void addition(hls::stream<int> &signal,hls::stream<int> &constant,hls::stream<int> &sum_1)
{
	int signal_tmp=signal.read();
	int constant_tmp=constant.read();
	int sum_tmp=signal_tmp+constant_tmp;
	sum_1<<sum_tmp;
}

