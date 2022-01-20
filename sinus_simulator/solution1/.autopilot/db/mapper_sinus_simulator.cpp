#include <systemc>
#include <vector>
#include <iostream>
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_fixed.h"
using namespace std;
using namespace sc_dt;
class AESL_RUNTIME_BC {
  public:
    AESL_RUNTIME_BC(const char* name) {
      file_token.open( name);
      if (!file_token.good()) {
        cout << "Failed to open tv file " << name << endl;
        exit (1);
      }
      file_token >> mName;//[[[runtime]]]
    }
    ~AESL_RUNTIME_BC() {
      file_token.close();
    }
    int read_size () {
      int size = 0;
      file_token >> mName;//[[transaction]]
      file_token >> mName;//transaction number
      file_token >> mName;//pop_size
      size = atoi(mName.c_str());
      file_token >> mName;//[[/transaction]]
      return size;
    }
  public:
    fstream file_token;
    string mName;
};
unsigned int ap_apatb_start_sinus_V_cap_bc;
static AESL_RUNTIME_BC __xlx_start_sinus_V_size_Reader("../tv/stream_size/stream_size_in_start_sinus_V.dat");
unsigned int ap_apatb_start_constante_V_cap_bc;
static AESL_RUNTIME_BC __xlx_start_constante_V_size_Reader("../tv/stream_size/stream_size_in_start_constante_V.dat");
unsigned int ap_apatb_step_sinus_V_cap_bc;
static AESL_RUNTIME_BC __xlx_step_sinus_V_size_Reader("../tv/stream_size/stream_size_in_step_sinus_V.dat");
unsigned int ap_apatb_step_constante_V_cap_bc;
static AESL_RUNTIME_BC __xlx_step_constante_V_size_Reader("../tv/stream_size/stream_size_in_step_constante_V.dat");
unsigned int ap_apatb_constante_fixed_V_cap_bc;
static AESL_RUNTIME_BC __xlx_constante_fixed_V_size_Reader("../tv/stream_size/stream_size_in_constante_fixed_V.dat");
unsigned int ap_apatb_signal_sinus_V_cap_bc;
static AESL_RUNTIME_BC __xlx_signal_sinus_V_size_Reader("../tv/stream_size/stream_size_out_signal_sinus_V.dat");
unsigned int ap_apatb_sum_V_cap_bc;
static AESL_RUNTIME_BC __xlx_sum_V_size_Reader("../tv/stream_size/stream_size_out_sum_V.dat");
extern "C" void sinus_simulator(char*, char*, char*, char*, int*, int*, int*);
extern "C" void apatb_sinus_simulator_hw(volatile void * __xlx_apatb_param_start_sinus, volatile void * __xlx_apatb_param_start_constante, volatile void * __xlx_apatb_param_step_sinus, volatile void * __xlx_apatb_param_step_constante, volatile void * __xlx_apatb_param_constante_fixed, volatile void * __xlx_apatb_param_signal_sinus, volatile void * __xlx_apatb_param_sum) {
  // collect __xlx_start_sinus_tmp_vec
  unsigned __xlx_start_sinus_V_tmp_Count = 0;
  unsigned __xlx_start_sinus_V_read_Size = __xlx_start_sinus_V_size_Reader.read_size();
  vector<char> __xlx_start_sinus_tmp_vec;
  while (!((hls::stream<char>*)__xlx_apatb_param_start_sinus)->empty() && __xlx_start_sinus_V_tmp_Count < __xlx_start_sinus_V_read_Size) {
    __xlx_start_sinus_tmp_vec.push_back(((hls::stream<char>*)__xlx_apatb_param_start_sinus)->read());
    __xlx_start_sinus_V_tmp_Count++;
  }
  ap_apatb_start_sinus_V_cap_bc = __xlx_start_sinus_tmp_vec.size();
  // store input buffer
  char* __xlx_start_sinus_input_buffer= new char[__xlx_start_sinus_tmp_vec.size()];
  for (int i = 0; i < __xlx_start_sinus_tmp_vec.size(); ++i) {
    __xlx_start_sinus_input_buffer[i] = __xlx_start_sinus_tmp_vec[i];
  }
  // collect __xlx_start_constante_tmp_vec
  unsigned __xlx_start_constante_V_tmp_Count = 0;
  unsigned __xlx_start_constante_V_read_Size = __xlx_start_constante_V_size_Reader.read_size();
  vector<char> __xlx_start_constante_tmp_vec;
  while (!((hls::stream<char>*)__xlx_apatb_param_start_constante)->empty() && __xlx_start_constante_V_tmp_Count < __xlx_start_constante_V_read_Size) {
    __xlx_start_constante_tmp_vec.push_back(((hls::stream<char>*)__xlx_apatb_param_start_constante)->read());
    __xlx_start_constante_V_tmp_Count++;
  }
  ap_apatb_start_constante_V_cap_bc = __xlx_start_constante_tmp_vec.size();
  // store input buffer
  char* __xlx_start_constante_input_buffer= new char[__xlx_start_constante_tmp_vec.size()];
  for (int i = 0; i < __xlx_start_constante_tmp_vec.size(); ++i) {
    __xlx_start_constante_input_buffer[i] = __xlx_start_constante_tmp_vec[i];
  }
  // collect __xlx_step_sinus_tmp_vec
  unsigned __xlx_step_sinus_V_tmp_Count = 0;
  unsigned __xlx_step_sinus_V_read_Size = __xlx_step_sinus_V_size_Reader.read_size();
  vector<char> __xlx_step_sinus_tmp_vec;
  while (!((hls::stream<char>*)__xlx_apatb_param_step_sinus)->empty() && __xlx_step_sinus_V_tmp_Count < __xlx_step_sinus_V_read_Size) {
    __xlx_step_sinus_tmp_vec.push_back(((hls::stream<char>*)__xlx_apatb_param_step_sinus)->read());
    __xlx_step_sinus_V_tmp_Count++;
  }
  ap_apatb_step_sinus_V_cap_bc = __xlx_step_sinus_tmp_vec.size();
  // store input buffer
  char* __xlx_step_sinus_input_buffer= new char[__xlx_step_sinus_tmp_vec.size()];
  for (int i = 0; i < __xlx_step_sinus_tmp_vec.size(); ++i) {
    __xlx_step_sinus_input_buffer[i] = __xlx_step_sinus_tmp_vec[i];
  }
  // collect __xlx_step_constante_tmp_vec
  unsigned __xlx_step_constante_V_tmp_Count = 0;
  unsigned __xlx_step_constante_V_read_Size = __xlx_step_constante_V_size_Reader.read_size();
  vector<char> __xlx_step_constante_tmp_vec;
  while (!((hls::stream<char>*)__xlx_apatb_param_step_constante)->empty() && __xlx_step_constante_V_tmp_Count < __xlx_step_constante_V_read_Size) {
    __xlx_step_constante_tmp_vec.push_back(((hls::stream<char>*)__xlx_apatb_param_step_constante)->read());
    __xlx_step_constante_V_tmp_Count++;
  }
  ap_apatb_step_constante_V_cap_bc = __xlx_step_constante_tmp_vec.size();
  // store input buffer
  char* __xlx_step_constante_input_buffer= new char[__xlx_step_constante_tmp_vec.size()];
  for (int i = 0; i < __xlx_step_constante_tmp_vec.size(); ++i) {
    __xlx_step_constante_input_buffer[i] = __xlx_step_constante_tmp_vec[i];
  }
  // collect __xlx_constante_fixed_tmp_vec
  unsigned __xlx_constante_fixed_V_tmp_Count = 0;
  unsigned __xlx_constante_fixed_V_read_Size = __xlx_constante_fixed_V_size_Reader.read_size();
  vector<int> __xlx_constante_fixed_tmp_vec;
  while (!((hls::stream<int>*)__xlx_apatb_param_constante_fixed)->empty() && __xlx_constante_fixed_V_tmp_Count < __xlx_constante_fixed_V_read_Size) {
    __xlx_constante_fixed_tmp_vec.push_back(((hls::stream<int>*)__xlx_apatb_param_constante_fixed)->read());
    __xlx_constante_fixed_V_tmp_Count++;
  }
  ap_apatb_constante_fixed_V_cap_bc = __xlx_constante_fixed_tmp_vec.size();
  // store input buffer
  int* __xlx_constante_fixed_input_buffer= new int[__xlx_constante_fixed_tmp_vec.size()];
  for (int i = 0; i < __xlx_constante_fixed_tmp_vec.size(); ++i) {
    __xlx_constante_fixed_input_buffer[i] = __xlx_constante_fixed_tmp_vec[i];
  }
  //Create input buffer for signal_sinus
  ap_apatb_signal_sinus_V_cap_bc = __xlx_signal_sinus_V_size_Reader.read_size();
  int* __xlx_signal_sinus_input_buffer= new int[ap_apatb_signal_sinus_V_cap_bc];
  //Create input buffer for sum
  ap_apatb_sum_V_cap_bc = __xlx_sum_V_size_Reader.read_size();
  int* __xlx_sum_input_buffer= new int[ap_apatb_sum_V_cap_bc];
  // DUT call
  sinus_simulator(__xlx_start_sinus_input_buffer, __xlx_start_constante_input_buffer, __xlx_step_sinus_input_buffer, __xlx_step_constante_input_buffer, __xlx_constante_fixed_input_buffer, __xlx_signal_sinus_input_buffer, __xlx_sum_input_buffer);
  for (unsigned i = 0; i <ap_apatb_signal_sinus_V_cap_bc; ++i)
    ((hls::stream<int>*)__xlx_apatb_param_signal_sinus)->write(__xlx_signal_sinus_input_buffer[i]);
  for (unsigned i = 0; i <ap_apatb_sum_V_cap_bc; ++i)
    ((hls::stream<int>*)__xlx_apatb_param_sum)->write(__xlx_sum_input_buffer[i]);
}
