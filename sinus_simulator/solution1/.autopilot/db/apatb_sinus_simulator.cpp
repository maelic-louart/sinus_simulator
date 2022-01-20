#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_start_sinus_V "../tv/cdatafile/c.sinus_simulator.autotvin_start_sinus_V.dat"
#define AUTOTB_TVOUT_start_sinus_V "../tv/cdatafile/c.sinus_simulator.autotvout_start_sinus_V.dat"
#define WRAPC_STREAM_SIZE_IN_start_sinus_V "../tv/stream_size/stream_size_in_start_sinus_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_start_sinus_V "../tv/stream_size/stream_ingress_status_start_sinus_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_start_constante_V "../tv/cdatafile/c.sinus_simulator.autotvin_start_constante_V.dat"
#define AUTOTB_TVOUT_start_constante_V "../tv/cdatafile/c.sinus_simulator.autotvout_start_constante_V.dat"
#define WRAPC_STREAM_SIZE_IN_start_constante_V "../tv/stream_size/stream_size_in_start_constante_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_start_constante_V "../tv/stream_size/stream_ingress_status_start_constante_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_step_sinus_V "../tv/cdatafile/c.sinus_simulator.autotvin_step_sinus_V.dat"
#define AUTOTB_TVOUT_step_sinus_V "../tv/cdatafile/c.sinus_simulator.autotvout_step_sinus_V.dat"
#define WRAPC_STREAM_SIZE_IN_step_sinus_V "../tv/stream_size/stream_size_in_step_sinus_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_step_sinus_V "../tv/stream_size/stream_ingress_status_step_sinus_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_step_constante_V "../tv/cdatafile/c.sinus_simulator.autotvin_step_constante_V.dat"
#define AUTOTB_TVOUT_step_constante_V "../tv/cdatafile/c.sinus_simulator.autotvout_step_constante_V.dat"
#define WRAPC_STREAM_SIZE_IN_step_constante_V "../tv/stream_size/stream_size_in_step_constante_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_step_constante_V "../tv/stream_size/stream_ingress_status_step_constante_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_constante_fixed_V "../tv/cdatafile/c.sinus_simulator.autotvin_constante_fixed_V.dat"
#define AUTOTB_TVOUT_constante_fixed_V "../tv/cdatafile/c.sinus_simulator.autotvout_constante_fixed_V.dat"
#define WRAPC_STREAM_SIZE_IN_constante_fixed_V "../tv/stream_size/stream_size_in_constante_fixed_V.dat"
#define WRAPC_STREAM_INGRESS_STATUS_constante_fixed_V "../tv/stream_size/stream_ingress_status_constante_fixed_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_signal_sinus_V "../tv/cdatafile/c.sinus_simulator.autotvin_signal_sinus_V.dat"
#define AUTOTB_TVOUT_signal_sinus_V "../tv/cdatafile/c.sinus_simulator.autotvout_signal_sinus_V.dat"
#define WRAPC_STREAM_SIZE_OUT_signal_sinus_V "../tv/stream_size/stream_size_out_signal_sinus_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_signal_sinus_V "../tv/stream_size/stream_egress_status_signal_sinus_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_sum_V "../tv/cdatafile/c.sinus_simulator.autotvin_sum_V.dat"
#define AUTOTB_TVOUT_sum_V "../tv/cdatafile/c.sinus_simulator.autotvout_sum_V.dat"
#define WRAPC_STREAM_SIZE_OUT_sum_V "../tv/stream_size/stream_size_out_sum_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_sum_V "../tv/stream_size/stream_egress_status_sum_V.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_start_sinus_V "../tv/rtldatafile/rtl.sinus_simulator.autotvout_start_sinus_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_start_constante_V "../tv/rtldatafile/rtl.sinus_simulator.autotvout_start_constante_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_step_sinus_V "../tv/rtldatafile/rtl.sinus_simulator.autotvout_step_sinus_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_step_constante_V "../tv/rtldatafile/rtl.sinus_simulator.autotvout_step_constante_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_constante_fixed_V "../tv/rtldatafile/rtl.sinus_simulator.autotvout_constante_fixed_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_signal_sinus_V "../tv/rtldatafile/rtl.sinus_simulator.autotvout_signal_sinus_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_sum_V "../tv/rtldatafile/rtl.sinus_simulator.autotvout_sum_V.dat"

class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  start_sinus_V_depth = 0;
  start_constante_V_depth = 0;
  step_sinus_V_depth = 0;
  step_constante_V_depth = 0;
  constante_fixed_V_depth = 0;
  signal_sinus_V_depth = 0;
  sum_V_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{start_sinus_V " << start_sinus_V_depth << "}\n";
  total_list << "{start_constante_V " << start_constante_V_depth << "}\n";
  total_list << "{step_sinus_V " << step_sinus_V_depth << "}\n";
  total_list << "{step_constante_V " << step_constante_V_depth << "}\n";
  total_list << "{constante_fixed_V " << constante_fixed_V_depth << "}\n";
  total_list << "{signal_sinus_V " << signal_sinus_V_depth << "}\n";
  total_list << "{sum_V " << sum_V_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int start_sinus_V_depth;
    int start_constante_V_depth;
    int step_sinus_V_depth;
    int step_constante_V_depth;
    int constante_fixed_V_depth;
    int signal_sinus_V_depth;
    int sum_V_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};

static void RTLOutputCheckAndReplacement(std::string &AESL_token, std::string PortName) {
  bool no_x = false;
  bool err = false;

  no_x = false;
  // search and replace 'X' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('X', 0);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
  no_x = false;
  // search and replace 'x' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('x', 2);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
}
extern "C" void sinus_simulator_hw_stub_wrapper(volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *);

extern "C" void apatb_sinus_simulator_hw(volatile void * __xlx_apatb_param_start_sinus, volatile void * __xlx_apatb_param_start_constante, volatile void * __xlx_apatb_param_step_sinus, volatile void * __xlx_apatb_param_step_constante, volatile void * __xlx_apatb_param_constante_fixed, volatile void * __xlx_apatb_param_signal_sinus, volatile void * __xlx_apatb_param_sum) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;long __xlx_apatb_param_start_sinus_V_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_start_sinus_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_start_sinus_V_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_start_sinus_V_stream_buf_final_size; ++i)((hls::stream<char>*)__xlx_apatb_param_start_sinus)->read();
long __xlx_apatb_param_start_constante_V_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_start_constante_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_start_constante_V_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_start_constante_V_stream_buf_final_size; ++i)((hls::stream<char>*)__xlx_apatb_param_start_constante)->read();
long __xlx_apatb_param_step_sinus_V_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_step_sinus_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_step_sinus_V_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_step_sinus_V_stream_buf_final_size; ++i)((hls::stream<char>*)__xlx_apatb_param_step_sinus)->read();
long __xlx_apatb_param_step_constante_V_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_step_constante_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_step_constante_V_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_step_constante_V_stream_buf_final_size; ++i)((hls::stream<char>*)__xlx_apatb_param_step_constante)->read();
long __xlx_apatb_param_constante_fixed_V_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_constante_fixed_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_constante_fixed_V_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_constante_fixed_V_stream_buf_final_size; ++i)((hls::stream<int>*)__xlx_apatb_param_constante_fixed)->read();
long __xlx_apatb_param_signal_sinus_V_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_OUT_signal_sinus_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_signal_sinus_V_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_signal_sinus_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > signal_sinus_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "signal_sinus_V");
  
            // push token into output port buffer
            if (AESL_token != "") {
              signal_sinus_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {for (int j = 0, e = i; j != e; ++j) {
int xlx_stream_elt;

            ((int*)&xlx_stream_elt)[0] = signal_sinus_V_pc_buffer[j].to_int64();
          ((hls::stream<int>*)__xlx_apatb_param_signal_sinus)->write(xlx_stream_elt);
}
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  long __xlx_apatb_param_sum_V_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_OUT_sum_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_sum_V_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_sum_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > sum_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "sum_V");
  
            // push token into output port buffer
            if (AESL_token != "") {
              sum_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {for (int j = 0, e = i; j != e; ++j) {
int xlx_stream_elt;

            ((int*)&xlx_stream_elt)[0] = sum_V_pc_buffer[j].to_int64();
          ((hls::stream<int>*)__xlx_apatb_param_sum)->write(xlx_stream_elt);
}
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static AESL_FILE_HANDLER aesl_fh;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
//start_sinus_V
aesl_fh.touch(AUTOTB_TVIN_start_sinus_V);
aesl_fh.touch(AUTOTB_TVOUT_start_sinus_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_start_sinus_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_start_sinus_V);
//start_constante_V
aesl_fh.touch(AUTOTB_TVIN_start_constante_V);
aesl_fh.touch(AUTOTB_TVOUT_start_constante_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_start_constante_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_start_constante_V);
//step_sinus_V
aesl_fh.touch(AUTOTB_TVIN_step_sinus_V);
aesl_fh.touch(AUTOTB_TVOUT_step_sinus_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_step_sinus_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_step_sinus_V);
//step_constante_V
aesl_fh.touch(AUTOTB_TVIN_step_constante_V);
aesl_fh.touch(AUTOTB_TVOUT_step_constante_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_step_constante_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_step_constante_V);
//constante_fixed_V
aesl_fh.touch(AUTOTB_TVIN_constante_fixed_V);
aesl_fh.touch(AUTOTB_TVOUT_constante_fixed_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_constante_fixed_V);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_constante_fixed_V);
//signal_sinus_V
aesl_fh.touch(AUTOTB_TVIN_signal_sinus_V);
aesl_fh.touch(AUTOTB_TVOUT_signal_sinus_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_signal_sinus_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_signal_sinus_V);
//sum_V
aesl_fh.touch(AUTOTB_TVIN_sum_V);
aesl_fh.touch(AUTOTB_TVOUT_sum_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_sum_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_sum_V);
CodeState = DUMP_INPUTS;
std::vector<char> __xlx_apatb_param_start_sinus_stream_buf;
{
  while (!((hls::stream<char>*)__xlx_apatb_param_start_sinus)->empty())
    __xlx_apatb_param_start_sinus_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_start_sinus)->read());
  for (int i = 0; i < __xlx_apatb_param_start_sinus_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_start_sinus)->write(__xlx_apatb_param_start_sinus_stream_buf[i]);
  }
long __xlx_apatb_param_start_sinus_stream_buf_size = ((hls::stream<char>*)__xlx_apatb_param_start_sinus)->size();
std::vector<char> __xlx_apatb_param_start_constante_stream_buf;
{
  while (!((hls::stream<char>*)__xlx_apatb_param_start_constante)->empty())
    __xlx_apatb_param_start_constante_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_start_constante)->read());
  for (int i = 0; i < __xlx_apatb_param_start_constante_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_start_constante)->write(__xlx_apatb_param_start_constante_stream_buf[i]);
  }
long __xlx_apatb_param_start_constante_stream_buf_size = ((hls::stream<char>*)__xlx_apatb_param_start_constante)->size();
std::vector<char> __xlx_apatb_param_step_sinus_stream_buf;
{
  while (!((hls::stream<char>*)__xlx_apatb_param_step_sinus)->empty())
    __xlx_apatb_param_step_sinus_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_step_sinus)->read());
  for (int i = 0; i < __xlx_apatb_param_step_sinus_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_step_sinus)->write(__xlx_apatb_param_step_sinus_stream_buf[i]);
  }
long __xlx_apatb_param_step_sinus_stream_buf_size = ((hls::stream<char>*)__xlx_apatb_param_step_sinus)->size();
std::vector<char> __xlx_apatb_param_step_constante_stream_buf;
{
  while (!((hls::stream<char>*)__xlx_apatb_param_step_constante)->empty())
    __xlx_apatb_param_step_constante_stream_buf.push_back(((hls::stream<char>*)__xlx_apatb_param_step_constante)->read());
  for (int i = 0; i < __xlx_apatb_param_step_constante_stream_buf.size(); ++i)
    ((hls::stream<char>*)__xlx_apatb_param_step_constante)->write(__xlx_apatb_param_step_constante_stream_buf[i]);
  }
long __xlx_apatb_param_step_constante_stream_buf_size = ((hls::stream<char>*)__xlx_apatb_param_step_constante)->size();
std::vector<int> __xlx_apatb_param_constante_fixed_stream_buf;
{
  while (!((hls::stream<int>*)__xlx_apatb_param_constante_fixed)->empty())
    __xlx_apatb_param_constante_fixed_stream_buf.push_back(((hls::stream<int>*)__xlx_apatb_param_constante_fixed)->read());
  for (int i = 0; i < __xlx_apatb_param_constante_fixed_stream_buf.size(); ++i)
    ((hls::stream<int>*)__xlx_apatb_param_constante_fixed)->write(__xlx_apatb_param_constante_fixed_stream_buf[i]);
  }
long __xlx_apatb_param_constante_fixed_stream_buf_size = ((hls::stream<int>*)__xlx_apatb_param_constante_fixed)->size();
std::vector<int> __xlx_apatb_param_signal_sinus_stream_buf;
long __xlx_apatb_param_signal_sinus_stream_buf_size = ((hls::stream<int>*)__xlx_apatb_param_signal_sinus)->size();
std::vector<int> __xlx_apatb_param_sum_stream_buf;
long __xlx_apatb_param_sum_stream_buf_size = ((hls::stream<int>*)__xlx_apatb_param_sum)->size();
CodeState = CALL_C_DUT;
sinus_simulator_hw_stub_wrapper(__xlx_apatb_param_start_sinus, __xlx_apatb_param_start_constante, __xlx_apatb_param_step_sinus, __xlx_apatb_param_step_constante, __xlx_apatb_param_constante_fixed, __xlx_apatb_param_signal_sinus, __xlx_apatb_param_sum);
CodeState = DUMP_OUTPUTS;
long __xlx_apatb_param_start_sinus_stream_buf_final_size = __xlx_apatb_param_start_sinus_stream_buf_size - ((hls::stream<char>*)__xlx_apatb_param_start_sinus)->size();
// print start_sinus_V Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_start_sinus_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_start_sinus_stream_buf_final_size; j != e; ++j) {
sc_bv<8> __xlx_tmp_lv_hw;
sc_bv<8> __xlx_tmp_lv;
__xlx_tmp_lv = ((char*)&__xlx_apatb_param_start_sinus_stream_buf[j])[0];
__xlx_tmp_lv_hw = __xlx_tmp_lv;

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv_hw.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_start_sinus_V, __xlx_sprintf_buffer.data()); 
  }

  tcl_file.set_num(__xlx_apatb_param_start_sinus_stream_buf_final_size, &tcl_file.start_sinus_V_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_start_sinus_V, __xlx_sprintf_buffer.data());
}

// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_start_sinus_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_start_sinus_stream_buf_final_size > 0) {
  long start_sinus_V_stream_ingress_size = __xlx_apatb_param_start_sinus_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", start_sinus_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_start_sinus_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_start_sinus_stream_buf_final_size; j != e; j++) {
    start_sinus_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", start_sinus_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_start_sinus_V, __xlx_sprintf_buffer.data());
  }
} else {
  long start_sinus_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", start_sinus_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_start_sinus_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_start_sinus_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_start_sinus_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_start_sinus_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_start_sinus_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_start_sinus_V, __xlx_sprintf_buffer.data());
}long __xlx_apatb_param_start_constante_stream_buf_final_size = __xlx_apatb_param_start_constante_stream_buf_size - ((hls::stream<char>*)__xlx_apatb_param_start_constante)->size();
// print start_constante_V Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_start_constante_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_start_constante_stream_buf_final_size; j != e; ++j) {
sc_bv<8> __xlx_tmp_lv_hw;
sc_bv<8> __xlx_tmp_lv;
__xlx_tmp_lv = ((char*)&__xlx_apatb_param_start_constante_stream_buf[j])[0];
__xlx_tmp_lv_hw = __xlx_tmp_lv;

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv_hw.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_start_constante_V, __xlx_sprintf_buffer.data()); 
  }

  tcl_file.set_num(__xlx_apatb_param_start_constante_stream_buf_final_size, &tcl_file.start_constante_V_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_start_constante_V, __xlx_sprintf_buffer.data());
}

// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_start_constante_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_start_constante_stream_buf_final_size > 0) {
  long start_constante_V_stream_ingress_size = __xlx_apatb_param_start_constante_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", start_constante_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_start_constante_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_start_constante_stream_buf_final_size; j != e; j++) {
    start_constante_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", start_constante_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_start_constante_V, __xlx_sprintf_buffer.data());
  }
} else {
  long start_constante_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", start_constante_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_start_constante_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_start_constante_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_start_constante_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_start_constante_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_start_constante_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_start_constante_V, __xlx_sprintf_buffer.data());
}long __xlx_apatb_param_step_sinus_stream_buf_final_size = __xlx_apatb_param_step_sinus_stream_buf_size - ((hls::stream<char>*)__xlx_apatb_param_step_sinus)->size();
// print step_sinus_V Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_step_sinus_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_step_sinus_stream_buf_final_size; j != e; ++j) {
sc_bv<8> __xlx_tmp_lv_hw;
sc_bv<8> __xlx_tmp_lv;
__xlx_tmp_lv = ((char*)&__xlx_apatb_param_step_sinus_stream_buf[j])[0];
__xlx_tmp_lv_hw = __xlx_tmp_lv;

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv_hw.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_step_sinus_V, __xlx_sprintf_buffer.data()); 
  }

  tcl_file.set_num(__xlx_apatb_param_step_sinus_stream_buf_final_size, &tcl_file.step_sinus_V_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_step_sinus_V, __xlx_sprintf_buffer.data());
}

// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_step_sinus_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_step_sinus_stream_buf_final_size > 0) {
  long step_sinus_V_stream_ingress_size = __xlx_apatb_param_step_sinus_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", step_sinus_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_step_sinus_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_step_sinus_stream_buf_final_size; j != e; j++) {
    step_sinus_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", step_sinus_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_step_sinus_V, __xlx_sprintf_buffer.data());
  }
} else {
  long step_sinus_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", step_sinus_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_step_sinus_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_step_sinus_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_step_sinus_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_step_sinus_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_step_sinus_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_step_sinus_V, __xlx_sprintf_buffer.data());
}long __xlx_apatb_param_step_constante_stream_buf_final_size = __xlx_apatb_param_step_constante_stream_buf_size - ((hls::stream<char>*)__xlx_apatb_param_step_constante)->size();
// print step_constante_V Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_step_constante_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_step_constante_stream_buf_final_size; j != e; ++j) {
sc_bv<8> __xlx_tmp_lv_hw;
sc_bv<8> __xlx_tmp_lv;
__xlx_tmp_lv = ((char*)&__xlx_apatb_param_step_constante_stream_buf[j])[0];
__xlx_tmp_lv_hw = __xlx_tmp_lv;

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv_hw.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_step_constante_V, __xlx_sprintf_buffer.data()); 
  }

  tcl_file.set_num(__xlx_apatb_param_step_constante_stream_buf_final_size, &tcl_file.step_constante_V_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_step_constante_V, __xlx_sprintf_buffer.data());
}

// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_step_constante_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_step_constante_stream_buf_final_size > 0) {
  long step_constante_V_stream_ingress_size = __xlx_apatb_param_step_constante_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", step_constante_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_step_constante_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_step_constante_stream_buf_final_size; j != e; j++) {
    step_constante_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", step_constante_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_step_constante_V, __xlx_sprintf_buffer.data());
  }
} else {
  long step_constante_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", step_constante_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_step_constante_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_step_constante_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_step_constante_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_step_constante_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_step_constante_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_step_constante_V, __xlx_sprintf_buffer.data());
}long __xlx_apatb_param_constante_fixed_stream_buf_final_size = __xlx_apatb_param_constante_fixed_stream_buf_size - ((hls::stream<int>*)__xlx_apatb_param_constante_fixed)->size();
// print constante_fixed_V Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_constante_fixed_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_constante_fixed_stream_buf_final_size; j != e; ++j) {
sc_bv<32> __xlx_tmp_lv_hw;
sc_bv<32> __xlx_tmp_lv;
__xlx_tmp_lv = ((int*)&__xlx_apatb_param_constante_fixed_stream_buf[j])[0];
__xlx_tmp_lv_hw = __xlx_tmp_lv;

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv_hw.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_constante_fixed_V, __xlx_sprintf_buffer.data()); 
  }

  tcl_file.set_num(__xlx_apatb_param_constante_fixed_stream_buf_final_size, &tcl_file.constante_fixed_V_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_constante_fixed_V, __xlx_sprintf_buffer.data());
}

// dump stream ingress status to file
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_constante_fixed_V, __xlx_sprintf_buffer.data());
  if (__xlx_apatb_param_constante_fixed_stream_buf_final_size > 0) {
  long constante_fixed_V_stream_ingress_size = __xlx_apatb_param_constante_fixed_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", constante_fixed_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_constante_fixed_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_constante_fixed_stream_buf_final_size; j != e; j++) {
    constante_fixed_V_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", constante_fixed_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_constante_fixed_V, __xlx_sprintf_buffer.data());
  }
} else {
  long constante_fixed_V_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", constante_fixed_V_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_constante_fixed_V, __xlx_sprintf_buffer.data());
}

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_constante_fixed_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_constante_fixed_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_constante_fixed_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_constante_fixed_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_IN_constante_fixed_V, __xlx_sprintf_buffer.data());
}long __xlx_apatb_param_signal_sinus_stream_buf_final_size = ((hls::stream<int>*)__xlx_apatb_param_signal_sinus)->size() - __xlx_apatb_param_signal_sinus_stream_buf_size;
{
  while (!((hls::stream<int>*)__xlx_apatb_param_signal_sinus)->empty())
    __xlx_apatb_param_signal_sinus_stream_buf.push_back(((hls::stream<int>*)__xlx_apatb_param_signal_sinus)->read());
  for (int i = 0; i < __xlx_apatb_param_signal_sinus_stream_buf.size(); ++i)
    ((hls::stream<int>*)__xlx_apatb_param_signal_sinus)->write(__xlx_apatb_param_signal_sinus_stream_buf[i]);
  }
// print signal_sinus_V Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_signal_sinus_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_signal_sinus_stream_buf_final_size; j != e; ++j) {
sc_bv<32> __xlx_tmp_lv = ((int*)&__xlx_apatb_param_signal_sinus_stream_buf[__xlx_apatb_param_signal_sinus_stream_buf_size+j])[0];

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVOUT_signal_sinus_V, __xlx_sprintf_buffer.data()); 
  }

  tcl_file.set_num(__xlx_apatb_param_signal_sinus_stream_buf_final_size, &tcl_file.signal_sinus_V_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_signal_sinus_V, __xlx_sprintf_buffer.data());
}
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_signal_sinus_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_signal_sinus_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_signal_sinus_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_signal_sinus_V, __xlx_sprintf_buffer.data());
}long __xlx_apatb_param_sum_stream_buf_final_size = ((hls::stream<int>*)__xlx_apatb_param_sum)->size() - __xlx_apatb_param_sum_stream_buf_size;
{
  while (!((hls::stream<int>*)__xlx_apatb_param_sum)->empty())
    __xlx_apatb_param_sum_stream_buf.push_back(((hls::stream<int>*)__xlx_apatb_param_sum)->read());
  for (int i = 0; i < __xlx_apatb_param_sum_stream_buf.size(); ++i)
    ((hls::stream<int>*)__xlx_apatb_param_sum)->write(__xlx_apatb_param_sum_stream_buf[i]);
  }
// print sum_V Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_sum_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_sum_stream_buf_final_size; j != e; ++j) {
sc_bv<32> __xlx_tmp_lv = ((int*)&__xlx_apatb_param_sum_stream_buf[__xlx_apatb_param_sum_stream_buf_size+j])[0];

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVOUT_sum_V, __xlx_sprintf_buffer.data()); 
  }

  tcl_file.set_num(__xlx_apatb_param_sum_stream_buf_final_size, &tcl_file.sum_V_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_sum_V, __xlx_sprintf_buffer.data());
}
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_sum_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_sum_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_sum_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_sum_V, __xlx_sprintf_buffer.data());
}CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
