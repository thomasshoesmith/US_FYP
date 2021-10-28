#pragma once
#ifdef BUILDING_GENERATED_CODE
#define EXPORT_VAR __declspec(dllexport) extern
#define EXPORT_FUNC __declspec(dllexport)
#else
#define EXPORT_VAR __declspec(dllimport) extern
#define EXPORT_FUNC __declspec(dllimport)
#endif
// Standard C++ includes
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

// Standard C includes
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#define DT 1.00000000000000006e-01f
typedef float scalar;
#define SCALAR_MIN 1.175494351e-38f
#define SCALAR_MAX 3.402823466e+38f

#define TIME_MIN 1.175494351e-38f
#define TIME_MAX 3.402823466e+38f

// ------------------------------------------------------------------------
// bit tool macros
#define B(x,i) ((x) & (0x80000000 >> (i))) //!< Extract the bit at the specified position i from x
#define setB(x,i) x= ((x) | (0x80000000 >> (i))) //!< Set the bit at the specified position i in x to 1
#define delB(x,i) x= ((x) & (~(0x80000000 >> (i)))) //!< Set the bit at the specified position i in x to 0

extern "C" {
// ------------------------------------------------------------------------
// global variables
// ------------------------------------------------------------------------
EXPORT_VAR unsigned long long iT;
EXPORT_VAR float t;

// ------------------------------------------------------------------------
// timers
// ------------------------------------------------------------------------
EXPORT_VAR double initTime;
EXPORT_VAR double initSparseTime;
EXPORT_VAR double neuronUpdateTime;
EXPORT_VAR double presynapticUpdateTime;
EXPORT_VAR double postsynapticUpdateTime;
EXPORT_VAR double synapseDynamicsTime;
// ------------------------------------------------------------------------
// local neuron groups
// ------------------------------------------------------------------------
#define spikeCount_Pop glbSpkCntPop[0]
#define spike_Pop glbSpkPop
#define glbSpkShiftPop 0

EXPORT_VAR unsigned int* glbSpkCntPop;
EXPORT_VAR unsigned int* glbSpkPop;
EXPORT_VAR scalar* VPop;
EXPORT_VAR scalar* UPop;
EXPORT_VAR scalar* aPop;
EXPORT_VAR scalar* bPop;
EXPORT_VAR scalar* cPop;
EXPORT_VAR scalar* dPop;
// current source variables

// ------------------------------------------------------------------------
// custom update variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// postsynaptic variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// synapse variables
// ------------------------------------------------------------------------

EXPORT_FUNC void pushPopSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullPopSpikesFromDevice();
EXPORT_FUNC void pushPopCurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullPopCurrentSpikesFromDevice();
EXPORT_FUNC unsigned int* getPopCurrentSpikes(unsigned int batch = 0); 
EXPORT_FUNC unsigned int& getPopCurrentSpikeCount(unsigned int batch = 0); 
EXPORT_FUNC void pushVPopToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullVPopFromDevice();
EXPORT_FUNC void pushCurrentVPopToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentVPopFromDevice();
EXPORT_FUNC scalar* getCurrentVPop(unsigned int batch = 0); 
EXPORT_FUNC void pushUPopToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullUPopFromDevice();
EXPORT_FUNC void pushCurrentUPopToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentUPopFromDevice();
EXPORT_FUNC scalar* getCurrentUPop(unsigned int batch = 0); 
EXPORT_FUNC void pushaPopToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullaPopFromDevice();
EXPORT_FUNC void pushCurrentaPopToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentaPopFromDevice();
EXPORT_FUNC scalar* getCurrentaPop(unsigned int batch = 0); 
EXPORT_FUNC void pushbPopToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullbPopFromDevice();
EXPORT_FUNC void pushCurrentbPopToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentbPopFromDevice();
EXPORT_FUNC scalar* getCurrentbPop(unsigned int batch = 0); 
EXPORT_FUNC void pushcPopToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullcPopFromDevice();
EXPORT_FUNC void pushCurrentcPopToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentcPopFromDevice();
EXPORT_FUNC scalar* getCurrentcPop(unsigned int batch = 0); 
EXPORT_FUNC void pushdPopToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldPopFromDevice();
EXPORT_FUNC void pushCurrentdPopToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentdPopFromDevice();
EXPORT_FUNC scalar* getCurrentdPop(unsigned int batch = 0); 
EXPORT_FUNC void pushPopStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullPopStateFromDevice();
EXPORT_FUNC void pushCSStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCSStateFromDevice();
// Runner functions
EXPORT_FUNC void copyStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void copyConnectivityToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void copyStateFromDevice();
EXPORT_FUNC void copyCurrentSpikesFromDevice();
EXPORT_FUNC void copyCurrentSpikeEventsFromDevice();
EXPORT_FUNC void allocateMem();
EXPORT_FUNC void freeMem();
EXPORT_FUNC size_t getFreeDeviceMemBytes();
EXPORT_FUNC void stepTime();

// Functions generated by backend
EXPORT_FUNC void updateNeurons(float t); 
EXPORT_FUNC void updateSynapses(float t);
EXPORT_FUNC void initialize();
EXPORT_FUNC void initializeSparse();
}  // extern "C"
