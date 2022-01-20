// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XSINUS_SIMULATOR_H
#define XSINUS_SIMULATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xsinus_simulator_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XSinus_simulator_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XSinus_simulator;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XSinus_simulator_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XSinus_simulator_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XSinus_simulator_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XSinus_simulator_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XSinus_simulator_Initialize(XSinus_simulator *InstancePtr, u16 DeviceId);
XSinus_simulator_Config* XSinus_simulator_LookupConfig(u16 DeviceId);
int XSinus_simulator_CfgInitialize(XSinus_simulator *InstancePtr, XSinus_simulator_Config *ConfigPtr);
#else
int XSinus_simulator_Initialize(XSinus_simulator *InstancePtr, const char* InstanceName);
int XSinus_simulator_Release(XSinus_simulator *InstancePtr);
#endif

void XSinus_simulator_Start(XSinus_simulator *InstancePtr);
u32 XSinus_simulator_IsDone(XSinus_simulator *InstancePtr);
u32 XSinus_simulator_IsIdle(XSinus_simulator *InstancePtr);
u32 XSinus_simulator_IsReady(XSinus_simulator *InstancePtr);
void XSinus_simulator_EnableAutoRestart(XSinus_simulator *InstancePtr);
void XSinus_simulator_DisableAutoRestart(XSinus_simulator *InstancePtr);


void XSinus_simulator_InterruptGlobalEnable(XSinus_simulator *InstancePtr);
void XSinus_simulator_InterruptGlobalDisable(XSinus_simulator *InstancePtr);
void XSinus_simulator_InterruptEnable(XSinus_simulator *InstancePtr, u32 Mask);
void XSinus_simulator_InterruptDisable(XSinus_simulator *InstancePtr, u32 Mask);
void XSinus_simulator_InterruptClear(XSinus_simulator *InstancePtr, u32 Mask);
u32 XSinus_simulator_InterruptGetEnabled(XSinus_simulator *InstancePtr);
u32 XSinus_simulator_InterruptGetStatus(XSinus_simulator *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
