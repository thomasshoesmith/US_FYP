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
#define spikeCount_conv2d_1_nrn glbSpkCntconv2d_1_nrn[0]
#define spike_conv2d_1_nrn glbSpkconv2d_1_nrn
#define glbSpkShiftconv2d_1_nrn 0

EXPORT_VAR unsigned int* glbSpkCntconv2d_1_nrn;
EXPORT_VAR unsigned int* glbSpkconv2d_1_nrn;
EXPORT_VAR scalar* Fxconv2d_1_nrn;
EXPORT_VAR scalar* Vmemconv2d_1_nrn;
#define spikeCount_conv2d_input_nrn glbSpkCntconv2d_input_nrn[0]
#define spike_conv2d_input_nrn glbSpkconv2d_input_nrn
#define glbSpkShiftconv2d_input_nrn 0

EXPORT_VAR unsigned int* glbSpkCntconv2d_input_nrn;
EXPORT_VAR unsigned int* glbSpkconv2d_input_nrn;
EXPORT_VAR scalar* inputconv2d_input_nrn;
EXPORT_VAR scalar* Vmemconv2d_input_nrn;
#define spikeCount_conv2d_nrn glbSpkCntconv2d_nrn[0]
#define spike_conv2d_nrn glbSpkconv2d_nrn
#define glbSpkShiftconv2d_nrn 0

EXPORT_VAR unsigned int* glbSpkCntconv2d_nrn;
EXPORT_VAR unsigned int* glbSpkconv2d_nrn;
EXPORT_VAR scalar* Fxconv2d_nrn;
EXPORT_VAR scalar* Vmemconv2d_nrn;
#define spikeCount_dense_1_nrn glbSpkCntdense_1_nrn[0]
#define spike_dense_1_nrn glbSpkdense_1_nrn
#define glbSpkShiftdense_1_nrn 0

EXPORT_VAR unsigned int* glbSpkCntdense_1_nrn;
EXPORT_VAR unsigned int* glbSpkdense_1_nrn;
EXPORT_VAR scalar* Fxdense_1_nrn;
EXPORT_VAR scalar* Vmemdense_1_nrn;
#define spikeCount_dense_2_nrn glbSpkCntdense_2_nrn[0]
#define spike_dense_2_nrn glbSpkdense_2_nrn
#define glbSpkShiftdense_2_nrn 0

EXPORT_VAR unsigned int* glbSpkCntdense_2_nrn;
EXPORT_VAR unsigned int* glbSpkdense_2_nrn;
EXPORT_VAR scalar* Fxdense_2_nrn;
EXPORT_VAR scalar* Vmemdense_2_nrn;
#define spikeCount_dense_nrn glbSpkCntdense_nrn[0]
#define spike_dense_nrn glbSpkdense_nrn
#define glbSpkShiftdense_nrn 0

EXPORT_VAR unsigned int* glbSpkCntdense_nrn;
EXPORT_VAR unsigned int* glbSpkdense_nrn;
EXPORT_VAR scalar* Fxdense_nrn;
EXPORT_VAR scalar* Vmemdense_nrn;

// ------------------------------------------------------------------------
// custom update variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// pre and postsynaptic variables
// ------------------------------------------------------------------------
EXPORT_VAR float* inSynconv2d_to_conv2d_1_syn;
EXPORT_VAR float* inSynconv2d_input_to_conv2d_syn;
EXPORT_VAR float* inSyndense_to_dense_1_syn;
EXPORT_VAR float* inSyndense_1_to_dense_2_syn;
EXPORT_VAR float* inSynconv2d_1_to_dense_syn;

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------
EXPORT_VAR const unsigned int maxRowLengthconv2d_input_to_conv2d_syn;
EXPORT_VAR unsigned int* rowLengthconv2d_input_to_conv2d_syn;
EXPORT_VAR uint32_t* indconv2d_input_to_conv2d_syn;
EXPORT_VAR const unsigned int maxRowLengthconv2d_to_conv2d_1_syn;
EXPORT_VAR unsigned int* rowLengthconv2d_to_conv2d_1_syn;
EXPORT_VAR uint32_t* indconv2d_to_conv2d_1_syn;

// ------------------------------------------------------------------------
// synapse variables
// ------------------------------------------------------------------------
EXPORT_VAR scalar* weightsgconv2d_1_to_dense_syn;
EXPORT_VAR scalar* gconv2d_input_to_conv2d_syn;
EXPORT_VAR scalar* kernelgconv2d_input_to_conv2d_syn;
EXPORT_VAR scalar* gconv2d_to_conv2d_1_syn;
EXPORT_VAR scalar* kernelgconv2d_to_conv2d_1_syn;
EXPORT_VAR scalar* gdense_1_to_dense_2_syn;
EXPORT_VAR scalar* gdense_to_dense_1_syn;

EXPORT_FUNC void pushconv2d_1_nrnSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullconv2d_1_nrnSpikesFromDevice();
EXPORT_FUNC void pushconv2d_1_nrnCurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullconv2d_1_nrnCurrentSpikesFromDevice();
EXPORT_FUNC unsigned int* getconv2d_1_nrnCurrentSpikes(unsigned int batch = 0); 
EXPORT_FUNC unsigned int& getconv2d_1_nrnCurrentSpikeCount(unsigned int batch = 0); 
EXPORT_FUNC void pushFxconv2d_1_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullFxconv2d_1_nrnFromDevice();
EXPORT_FUNC void pushCurrentFxconv2d_1_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentFxconv2d_1_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentFxconv2d_1_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushVmemconv2d_1_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullVmemconv2d_1_nrnFromDevice();
EXPORT_FUNC void pushCurrentVmemconv2d_1_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentVmemconv2d_1_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentVmemconv2d_1_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushconv2d_1_nrnStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullconv2d_1_nrnStateFromDevice();
EXPORT_FUNC void pushconv2d_input_nrnSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullconv2d_input_nrnSpikesFromDevice();
EXPORT_FUNC void pushconv2d_input_nrnCurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullconv2d_input_nrnCurrentSpikesFromDevice();
EXPORT_FUNC unsigned int* getconv2d_input_nrnCurrentSpikes(unsigned int batch = 0); 
EXPORT_FUNC unsigned int& getconv2d_input_nrnCurrentSpikeCount(unsigned int batch = 0); 
EXPORT_FUNC void pushinputconv2d_input_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullinputconv2d_input_nrnFromDevice();
EXPORT_FUNC void pushCurrentinputconv2d_input_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentinputconv2d_input_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentinputconv2d_input_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushVmemconv2d_input_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullVmemconv2d_input_nrnFromDevice();
EXPORT_FUNC void pushCurrentVmemconv2d_input_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentVmemconv2d_input_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentVmemconv2d_input_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushconv2d_input_nrnStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullconv2d_input_nrnStateFromDevice();
EXPORT_FUNC void pushconv2d_nrnSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullconv2d_nrnSpikesFromDevice();
EXPORT_FUNC void pushconv2d_nrnCurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullconv2d_nrnCurrentSpikesFromDevice();
EXPORT_FUNC unsigned int* getconv2d_nrnCurrentSpikes(unsigned int batch = 0); 
EXPORT_FUNC unsigned int& getconv2d_nrnCurrentSpikeCount(unsigned int batch = 0); 
EXPORT_FUNC void pushFxconv2d_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullFxconv2d_nrnFromDevice();
EXPORT_FUNC void pushCurrentFxconv2d_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentFxconv2d_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentFxconv2d_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushVmemconv2d_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullVmemconv2d_nrnFromDevice();
EXPORT_FUNC void pushCurrentVmemconv2d_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentVmemconv2d_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentVmemconv2d_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushconv2d_nrnStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullconv2d_nrnStateFromDevice();
EXPORT_FUNC void pushdense_1_nrnSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_1_nrnSpikesFromDevice();
EXPORT_FUNC void pushdense_1_nrnCurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_1_nrnCurrentSpikesFromDevice();
EXPORT_FUNC unsigned int* getdense_1_nrnCurrentSpikes(unsigned int batch = 0); 
EXPORT_FUNC unsigned int& getdense_1_nrnCurrentSpikeCount(unsigned int batch = 0); 
EXPORT_FUNC void pushFxdense_1_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullFxdense_1_nrnFromDevice();
EXPORT_FUNC void pushCurrentFxdense_1_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentFxdense_1_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentFxdense_1_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushVmemdense_1_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullVmemdense_1_nrnFromDevice();
EXPORT_FUNC void pushCurrentVmemdense_1_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentVmemdense_1_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentVmemdense_1_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushdense_1_nrnStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_1_nrnStateFromDevice();
EXPORT_FUNC void pushdense_2_nrnSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_2_nrnSpikesFromDevice();
EXPORT_FUNC void pushdense_2_nrnCurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_2_nrnCurrentSpikesFromDevice();
EXPORT_FUNC unsigned int* getdense_2_nrnCurrentSpikes(unsigned int batch = 0); 
EXPORT_FUNC unsigned int& getdense_2_nrnCurrentSpikeCount(unsigned int batch = 0); 
EXPORT_FUNC void pushFxdense_2_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullFxdense_2_nrnFromDevice();
EXPORT_FUNC void pushCurrentFxdense_2_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentFxdense_2_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentFxdense_2_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushVmemdense_2_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullVmemdense_2_nrnFromDevice();
EXPORT_FUNC void pushCurrentVmemdense_2_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentVmemdense_2_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentVmemdense_2_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushdense_2_nrnStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_2_nrnStateFromDevice();
EXPORT_FUNC void pushdense_nrnSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_nrnSpikesFromDevice();
EXPORT_FUNC void pushdense_nrnCurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_nrnCurrentSpikesFromDevice();
EXPORT_FUNC unsigned int* getdense_nrnCurrentSpikes(unsigned int batch = 0); 
EXPORT_FUNC unsigned int& getdense_nrnCurrentSpikeCount(unsigned int batch = 0); 
EXPORT_FUNC void pushFxdense_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullFxdense_nrnFromDevice();
EXPORT_FUNC void pushCurrentFxdense_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentFxdense_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentFxdense_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushVmemdense_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullVmemdense_nrnFromDevice();
EXPORT_FUNC void pushCurrentVmemdense_nrnToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullCurrentVmemdense_nrnFromDevice();
EXPORT_FUNC scalar* getCurrentVmemdense_nrn(unsigned int batch = 0); 
EXPORT_FUNC void pushdense_nrnStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_nrnStateFromDevice();
EXPORT_FUNC void pushconv2d_input_to_conv2d_synConnectivityToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullconv2d_input_to_conv2d_synConnectivityFromDevice();
EXPORT_FUNC void pushconv2d_to_conv2d_1_synConnectivityToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullconv2d_to_conv2d_1_synConnectivityFromDevice();
EXPORT_FUNC void allocateweightsgconv2d_1_to_dense_syn(unsigned int count);
EXPORT_FUNC void freeweightsgconv2d_1_to_dense_syn();
EXPORT_FUNC void pushweightsgconv2d_1_to_dense_synToDevice(unsigned int count);
EXPORT_FUNC void pullweightsgconv2d_1_to_dense_synFromDevice(unsigned int count);
EXPORT_FUNC void pushinSynconv2d_1_to_dense_synToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullinSynconv2d_1_to_dense_synFromDevice();
EXPORT_FUNC void pushconv2d_1_to_dense_synStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullconv2d_1_to_dense_synStateFromDevice();
EXPORT_FUNC void pushgconv2d_input_to_conv2d_synToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullgconv2d_input_to_conv2d_synFromDevice();
EXPORT_FUNC void allocatekernelgconv2d_input_to_conv2d_syn(unsigned int count);
EXPORT_FUNC void freekernelgconv2d_input_to_conv2d_syn();
EXPORT_FUNC void pushkernelgconv2d_input_to_conv2d_synToDevice(unsigned int count);
EXPORT_FUNC void pullkernelgconv2d_input_to_conv2d_synFromDevice(unsigned int count);
EXPORT_FUNC void pushinSynconv2d_input_to_conv2d_synToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullinSynconv2d_input_to_conv2d_synFromDevice();
EXPORT_FUNC void pushconv2d_input_to_conv2d_synStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullconv2d_input_to_conv2d_synStateFromDevice();
EXPORT_FUNC void pushgconv2d_to_conv2d_1_synToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullgconv2d_to_conv2d_1_synFromDevice();
EXPORT_FUNC void allocatekernelgconv2d_to_conv2d_1_syn(unsigned int count);
EXPORT_FUNC void freekernelgconv2d_to_conv2d_1_syn();
EXPORT_FUNC void pushkernelgconv2d_to_conv2d_1_synToDevice(unsigned int count);
EXPORT_FUNC void pullkernelgconv2d_to_conv2d_1_synFromDevice(unsigned int count);
EXPORT_FUNC void pushinSynconv2d_to_conv2d_1_synToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullinSynconv2d_to_conv2d_1_synFromDevice();
EXPORT_FUNC void pushconv2d_to_conv2d_1_synStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullconv2d_to_conv2d_1_synStateFromDevice();
EXPORT_FUNC void pushgdense_1_to_dense_2_synToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullgdense_1_to_dense_2_synFromDevice();
EXPORT_FUNC void pushinSyndense_1_to_dense_2_synToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullinSyndense_1_to_dense_2_synFromDevice();
EXPORT_FUNC void pushdense_1_to_dense_2_synStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_1_to_dense_2_synStateFromDevice();
EXPORT_FUNC void pushgdense_to_dense_1_synToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullgdense_to_dense_1_synFromDevice();
EXPORT_FUNC void pushinSyndense_to_dense_1_synToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullinSyndense_to_dense_1_synFromDevice();
EXPORT_FUNC void pushdense_to_dense_1_synStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulldense_to_dense_1_synStateFromDevice();
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
