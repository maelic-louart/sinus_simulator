#ifndef SINUS_SIMULATOR_H_
#define SINUS_SIMULATOR_H_

#include <iostream>
#include <iomanip>
#include <ap_fixed.h>
#include <ap_int.h>
#include <hls_stream.h>
using namespace std;

// size of the table than contains the sinus and cosinus values
#define DATA_SIZE 256

//const int cos_table[DATA_SIZE/4+1] = {1,0.9997,0.9988,0.99729,0.99518,0.99248,0.98918,0.98528,0.98079,0.9757,0.97003,0.96378,0.95694,0.94953,0.94154,0.93299,0.92388,0.91421,0.90399,0.89322,0.88192,0.87009,0.85773,0.84485,0.83147,0.81758,0.80321,0.78835,0.77301,0.75721,0.74095,0.72425,0.70711,0.68954,0.67156,0.65317,0.63439,0.61523,0.5957,0.57581,0.55557,0.535,0.5141,0.4929,0.4714,0.44961,0.42756,0.40524,0.38268,0.3599,0.33689,0.31368,0.29028,0.26671,0.24298,0.2191,0.19509,0.17096,0.14673,0.12241,0.098017,0.073565,0.049068,0.024541,0.0};
const int cos_table[DATA_SIZE/4+1] = {128,127,127,127,127,127,126,126,125,124,124,123,122,121,120,119,118,117,115,114,112,111,109,108,106,104,102,100,98,96,94,92,90,88,85,83,81,78,76,73,71,68,65,63,60,57,54,51,48,46,43,40,37,34,31,28,24,21,18,15,12,9,6,3,0};
//const int sin_table[DATA_SIZE/4+1] = {0,0.024541,0.049068,0.073565,0.098017,0.12241,0.14673,0.17096,0.19509,0.2191,0.24298,0.26671,0.29028,0.31368,0.33689,0.3599,0.38268,0.40524,0.42756,0.44961,0.4714,0.4929,0.5141,0.535,0.55557,0.57581,0.5957,0.61523,0.63439,0.65317,0.67156,0.68954,0.70711,0.72425,0.74095,0.75721,0.77301,0.78835,0.80321,0.81758,0.83147,0.84485,0.85773,0.87009,0.88192,0.89322,0.90399,0.91421,0.92388,0.93299,0.94154,0.94953,0.95694,0.96378,0.97003,0.9757,0.98079,0.98528,0.98918,0.99248,0.99518,0.99729,0.9988,0.9997,1};
const int sin_table[DATA_SIZE/4+1] = {0,3,6,9,12,15,18,21,24,28,31,34,37,40,43,46,48,51,54,57,60,63,65,68,71,73,76,78,81,83,85,88,90,92,94,96,98,100,102,104,106,108,109,111,112,114,115,117,118,119,120,121,122,123,124,124,125,126,126,127,127,127,127,127,128};

int cos_lookup (int n);
int sin_lookup (int n);
void sinus(hls::stream<bool> &start,hls::stream<bool> &step,hls::stream<int> &signal_1,hls::stream<int> &signal_2);
void addition(hls::stream<int> &signal,hls::stream<int> &constant,hls::stream<int> &sum_1);
void constante_generator(hls::stream<bool> &start,hls::stream<bool> &step,hls::stream<int> &constante_fixed,hls::stream<int> &constante_out);
void sinus_simulator(hls::stream<bool> &start_sinus,hls::stream<bool> &start_constante,hls::stream<bool> &step_sinus,hls::stream<bool> &step_constante,hls::stream<int> &constante_fixed,hls::stream<int> &signal_sinus,hls::stream<int> &sum);

#endif
