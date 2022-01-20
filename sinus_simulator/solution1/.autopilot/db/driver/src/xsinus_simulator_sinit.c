// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xsinus_simulator.h"

extern XSinus_simulator_Config XSinus_simulator_ConfigTable[];

XSinus_simulator_Config *XSinus_simulator_LookupConfig(u16 DeviceId) {
	XSinus_simulator_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XSINUS_SIMULATOR_NUM_INSTANCES; Index++) {
		if (XSinus_simulator_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XSinus_simulator_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XSinus_simulator_Initialize(XSinus_simulator *InstancePtr, u16 DeviceId) {
	XSinus_simulator_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XSinus_simulator_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XSinus_simulator_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

