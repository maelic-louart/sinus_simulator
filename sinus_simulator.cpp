#include "sinus_simulator.h"

void sinus_simulator(hls::stream<bool> &start_sinus,hls::stream<bool> &start_constante,hls::stream<bool> &step_sinus,hls::stream<bool> &step_constante,hls::stream<int> &constante_fixed,hls::stream<int> &signal_sinus,hls::stream<int> &sum)
{

#pragma HLS interface axis port=start_sinus
#pragma HLS INTERFACE axis port=start_constante
#pragma HLS INTERFACE axis port=step_sinus
#pragma HLS INTERFACE axis port=step_constante
#pragma HLS INTERFACE axis port=constante_fixed
#pragma HLS INTERFACE axis port=signal_sinus
#pragma HLS INTERFACE axis port=sum
#pragma HLS INTERFACE s_axilite port=return bundle=control

#pragma HLS DATAFLOW


	hls::stream<int> signal_tmp("signal_tmp");
	hls::stream<int> const_tmp("const_tmp");

	sinus(start_sinus,step_sinus,signal_tmp,signal_sinus);
	constante_generator(start_constante,step_constante,constante_fixed,const_tmp);
	addition(signal_tmp,const_tmp,sum);

}

