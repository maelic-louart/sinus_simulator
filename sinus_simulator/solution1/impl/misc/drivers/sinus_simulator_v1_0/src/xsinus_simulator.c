// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xsinus_simulator.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XSinus_simulator_CfgInitialize(XSinus_simulator *InstancePtr, XSinus_simulator_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XSinus_simulator_Start(XSinus_simulator *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSinus_simulator_ReadReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_AP_CTRL) & 0x80;
    XSinus_simulator_WriteReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XSinus_simulator_IsDone(XSinus_simulator *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSinus_simulator_ReadReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XSinus_simulator_IsIdle(XSinus_simulator *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSinus_simulator_ReadReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XSinus_simulator_IsReady(XSinus_simulator *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSinus_simulator_ReadReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XSinus_simulator_EnableAutoRestart(XSinus_simulator *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSinus_simulator_WriteReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XSinus_simulator_DisableAutoRestart(XSinus_simulator *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSinus_simulator_WriteReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_AP_CTRL, 0);
}

void XSinus_simulator_InterruptGlobalEnable(XSinus_simulator *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSinus_simulator_WriteReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_GIE, 1);
}

void XSinus_simulator_InterruptGlobalDisable(XSinus_simulator *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSinus_simulator_WriteReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_GIE, 0);
}

void XSinus_simulator_InterruptEnable(XSinus_simulator *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XSinus_simulator_ReadReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_IER);
    XSinus_simulator_WriteReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_IER, Register | Mask);
}

void XSinus_simulator_InterruptDisable(XSinus_simulator *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XSinus_simulator_ReadReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_IER);
    XSinus_simulator_WriteReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_IER, Register & (~Mask));
}

void XSinus_simulator_InterruptClear(XSinus_simulator *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSinus_simulator_WriteReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_ISR, Mask);
}

u32 XSinus_simulator_InterruptGetEnabled(XSinus_simulator *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XSinus_simulator_ReadReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_IER);
}

u32 XSinus_simulator_InterruptGetStatus(XSinus_simulator *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XSinus_simulator_ReadReg(InstancePtr->Control_BaseAddress, XSINUS_SIMULATOR_CONTROL_ADDR_ISR);
}

