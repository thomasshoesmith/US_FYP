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
EXPORT_VAR std::uniform_real_distribution<float> standardUniformDistribution;
EXPORT_VAR std::normal_distribution<float> standardNormalDistribution;
EXPORT_VAR std::exponential_distribution<float> standardExponentialDistribution;

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
EXPORT_VAR std::mt19937 hostRNG;

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
#define spikeCount_dense_1_nrn glbSpkCntdense_1_nrn[0]
#define spike_dense_1_nrn glbSpkdense_1_nrn
#define glbSpkShiftdense_1_nrn 0

EXPORT_VAR unsigned int* glbSpkCntdense_1_nrn;
EXPORT_VAR unsigned int* glbSpkdense_1_nrn;
EXPORT_VAR scalar* Vmemdense_1_nrn;
EXPORT_VAR unsigned int* nSpkdense_1_nrn;
EXPORT_VAR scalar Vthrdense_1_nrn;
#define spikeCount_dense_nrn glbSpkCntdense_nrn[0]
#define spike_dense_nrn glbSpkdense_nrn
#define glbSpkShiftdense_nrn 0

EXPORT_VAR unsigned int* glbSpkCntdense_nrn;
EXPORT_VAR unsigned int* glbSpkdense_nrn;
EXPORT_VAR scalar* Vmemdense_nrn;
EXPORT_VAR unsigned int* nSpkdense_nrn;
EXPORT_VAR scalar Vthrdense_nrn;
#define spikeCount_flatten_input_nrn glbSpkCntflatten_input_nrn[0]
#define spike_flatten_input_nrn glbSpkflatten_input_nrn
#define glbSpkShiftflatten_input_nrn 0

EXPORT_VAR unsigned int* glbSpkCntflatten_input_nrn;
EXPORT_VAR unsigned int* glbSpkflatten_input_nrn;
EXPORT_VAR scalar* inputflatten_input_nrn;

// ------------------------------------------------------------------------
// custom update variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// pre and postsynaptic variables
// ------------------------------------------------------------------------
EXPORT_VAR float* inSyndense_to_dense_1_syn;
EXPORT_VAR float* inSynflatten_input_to_dense_syn;

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// synapse variables
// ------------------------------------------------------------------------
EXPORT_VAR scalar* gdense_to_dense_1_syn;
EXPORT_VAR scalar* gflatten_input_to_dense_syn;

EXPORT_FUNC void pushdense_1_nrnSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_1_nrnSpikesFromDevice();
EXPORT_FUNC void pushdense_1_nrnCurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_1_nrnCurrentSpikesFromDevice();
EXPORT_FUNC unsigned int* getdense_1_nrnCurrentSpikes(unsigned int batch = 0); 
EXPORT_FUNC unsigned int& getdense_1_nrnCurrentSpikeCount(unsigned int batch = 0); 
EXPORT_FUNC void pushVmemdense_1_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullVmemdense_1_nrnFromDevice();
EXPORT_FUNC void pushCurrentVmemdense_1_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentVmemdense_1_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentVmemdense_1_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushnSpkdense_1_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullnSpkdense_1_nrnFromDevice();
EXPORT_FUNC void pushCurrentnSpkdense_1_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentnSpkdense_1_nrnFromDevice();
EXPORT_FUNC unsigned int* getCurrentnSpkdense_1_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushdense_1_nrnStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_1_nrnStateFromDevice();
EXPORT_FUNC void pushdense_nrnSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_nrnSpikesFromDevice();
EXPORT_FUNC void pushdense_nrnCurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_nrnCurrentSpikesFromDevice();
EXPORT_FUNC unsigned int* getdense_nrnCurrentSpikes(unsigned int batch = 0); 
EXPORT_FUNC unsigned int& getdense_nrnCurrentSpikeCount(unsigned int batch = 0); 
EXPORT_FUNC void pushVmemdense_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullVmemdense_nrnFromDevice();
EXPORT_FUNC void pushCurrentVmemdense_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentVmemdense_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentVmemdense_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushnSpkdense_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullnSpkdense_nrnFromDevice();
EXPORT_FUNC void pushCurrentnSpkdense_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentnSpkdense_nrnFromDevice();
EXPORT_FUNC unsigned int* getCurrentnSpkdense_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushdense_nrnStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_nrnStateFromDevice();
EXPORT_FUNC void pushflatten_input_nrnSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullflatten_input_nrnSpikesFromDevice();
EXPORT_FUNC void pushflatten_input_nrnCurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullflatten_input_nrnCurrentSpikesFromDevice();
EXPORT_FUNC unsigned int* getflatten_input_nrnCurrentSpikes(unsigned int batch = 0); 
EXPORT_FUNC unsigned int& getflatten_input_nrnCurrentSpikeCount(unsigned int batch = 0); 
EXPORT_FUNC void pushinputflatten_input_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullinputflatten_input_nrnFromDevice();
EXPORT_FUNC void pushCurrentinputflatten_input_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentinputflatten_input_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentinputflatten_input_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushflatten_input_nrnStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullflatten_input_nrnStateFromDevice();
EXPORT_FUNC void pushgdense_to_dense_1_synToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullgdense_to_dense_1_synFromDevice();
EXPORT_FUNC void pushinSyndense_to_dense_1_synToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullinSyndense_to_dense_1_synFromDevice();
EXPORT_FUNC void pushdense_to_dense_1_synStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_to_dense_1_synStateFromDevice();
EXPORT_FUNC void pushgflatten_input_to_dense_synToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullgflatten_input_to_dense_synFromDevice();
EXPORT_FUNC void pushinSynflatten_input_to_dense_synToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullinSynflatten_input_to_dense_synFromDevice();
EXPORT_FUNC void pushflatten_input_to_dense_synStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullflatten_input_to_dense_synStateFromDevice();
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
