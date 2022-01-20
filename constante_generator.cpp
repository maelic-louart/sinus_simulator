#include "sinus_simulator.h"

void constante_generator(hls::stream<bool> &start,hls::stream<bool> &step,hls::stream<int> &constante_fixed,hls::stream<int> &constante_out)
{
	static bool start_tmp=start.read();
	if(start_tmp==1)
	{
		bool step_tmp=step.read();
		static int constante_fixed_tmp=constante_fixed.read();
		if(step_tmp==1)
		{
			constante_out<<constante_fixed_tmp;
		}
	}
}
