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
#define DT 1.00000000000000000e+00f
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
#define spikeCount_neuron1 glbSpkCntneuron1[0]
#define spike_neuron1 glbSpkneuron1
#define glbSpkShiftneuron1 0

EXPORT_VAR unsigned int* glbSpkCntneuron1;
EXPORT_VAR unsigned int* glbSpkneuron1;
EXPORT_VAR scalar* inputneuron1;
EXPORT_VAR scalar* Vmemneuron1;
EXPORT_VAR scalar* scaleValneuron1;
#define spikeCount_neuron2 glbSpkCntneuron2[0]
#define spike_neuron2 glbSpkneuron2
#define glbSpkShiftneuron2 0

EXPORT_VAR unsigned int* glbSpkCntneuron2;
EXPORT_VAR unsigned int* glbSpkneuron2;
EXPORT_VAR scalar* inputneuron2;
EXPORT_VAR scalar* Vmemneuron2;
EXPORT_VAR scalar* scaleValneuron2;

// ------------------------------------------------------------------------
// custom update variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// pre and postsynaptic variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// synapse variables
// ------------------------------------------------------------------------

EXPORT_FUNC void pushneuron1SpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullneuron1SpikesFromDevice();
EXPORT_FUNC void pushneuron1CurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullneuron1CurrentSpikesFromDevice();
EXPORT_FUNC unsigned int* getneuron1CurrentSpikes(unsigned int batch = 0); 
EXPORT_FUNC unsigned int& getneuron1CurrentSpikeCount(unsigned int batch = 0); 
EXPORT_FUNC void pushinputneuron1ToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullinputneuron1FromDevice();
EXPORT_FUNC void pushCurrentinputneuron1ToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentinputneuron1FromDevice();
EXPORT_FUNC scalar* getCurrentinputneuron1(unsigned int batch = 0); 
EXPORT_FUNC void pushVmemneuron1ToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullVmemneuron1FromDevice();
EXPORT_FUNC void pushCurrentVmemneuron1ToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentVmemneuron1FromDevice();
EXPORT_FUNC scalar* getCurrentVmemneuron1(unsigned int batch = 0); 
EXPORT_FUNC void pushscaleValneuron1ToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullscaleValneuron1FromDevice();
EXPORT_FUNC void pushCurrentscaleValneuron1ToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentscaleValneuron1FromDevice();
EXPORT_FUNC scalar* getCurrentscaleValneuron1(unsigned int batch = 0); 
EXPORT_FUNC void pushneuron1StateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullneuron1StateFromDevice();
EXPORT_FUNC void pushneuron2SpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullneuron2SpikesFromDevice();
EXPORT_FUNC void pushneuron2CurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullneuron2CurrentSpikesFromDevice();
EXPORT_FUNC unsigned int* getneuron2CurrentSpikes(unsigned int batch = 0); 
EXPORT_FUNC unsigned int& getneuron2CurrentSpikeCount(unsigned int batch = 0); 
EXPORT_FUNC void pushinputneuron2ToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullinputneuron2FromDevice();
EXPORT_FUNC void pushCurrentinputneuron2ToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentinputneuron2FromDevice();
EXPORT_FUNC scalar* getCurrentinputneuron2(unsigned int batch = 0); 
EXPORT_FUNC void pushVmemneuron2ToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullVmemneuron2FromDevice();
EXPORT_FUNC void pushCurrentVmemneuron2ToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentVmemneuron2FromDevice();
EXPORT_FUNC scalar* getCurrentVmemneuron2(unsigned int batch = 0); 
EXPORT_FUNC void pushscaleValneuron2ToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullscaleValneuron2FromDevice();
EXPORT_FUNC void pushCurrentscaleValneuron2ToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentscaleValneuron2FromDevice();
EXPORT_FUNC scalar* getCurrentscaleValneuron2(unsigned int batch = 0); 
EXPORT_FUNC void pushneuron2StateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullneuron2StateFromDevice();
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
