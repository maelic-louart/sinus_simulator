#include "sinus_simulator.h"


int main()
{

	hls::stream<bool> start_sinus("start_sinus");
	hls::stream<bool> start_constante("start_constante");
	hls::stream<bool> step_sinus("step_sinus");
	hls::stream<bool> step_constante("step_constante");
	hls::stream<int> constante_fixed("constante_fixed");
	hls::stream<int> signal_sinus("signal_sinus");
	hls::stream<int> sum("sum");
	hls::stream<ap_uint<8>> n_simu_strm("n_strm");
	hls::stream<ap_uint<8>> n_simu_ref_strm("n_ref_strm");

	hls::stream<int> signal_tmp("signal_tmp");
	hls::stream<int> const_tmp("const_tmp");

	int signal_sinus_tmp=0;
	int sum_tmp=0;

	start_sinus<<1;
	start_constante<<1;
	constante_fixed<<3;

	int err=0;
	int nb_simu=10;

	for (int i=0;i<nb_simu;i++)
	{
		step_sinus<<1;
		step_constante<<1;
		sinus_simulator(start_sinus,start_constante,step_sinus,step_constante,constante_fixed,signal_sinus,sum);
		signal_sinus_tmp=signal_sinus.read();
		sum_tmp=sum.read();
		cout << "signal_sinus =" << signal_sinus_tmp <<endl;
		cout << "sum =" << sum_tmp << endl;
	}
	return err;
}

