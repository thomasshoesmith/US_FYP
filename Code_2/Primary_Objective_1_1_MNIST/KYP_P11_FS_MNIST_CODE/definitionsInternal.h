#pragma once
#include "definitions.h"

#define SUPPORT_CODE_FUNC inline
using std::min;
using std::max;
#include <intrin.h>

int inline gennCLZ(unsigned int value) {
    unsigned long leadingZero = 0;
    if( _BitScanReverse(&leadingZero, value)) {
        return 31 - leadingZero;
    }
    else {
        return 32;
    }
}

// ------------------------------------------------------------------------
// merged group structures
// ------------------------------------------------------------------------
extern "C" {
// ------------------------------------------------------------------------
// global variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// timers
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// merged group arrays for host initialisation
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// local neuron groups
// ------------------------------------------------------------------------

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

// ------------------------------------------------------------------------
// copying merged group structures to device
// ------------------------------------------------------------------------
EXPORT_FUNC void pushMergedNeuronInitGroup0ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* Fx, scalar* Vmem, float* inSynInSyn0, unsigned int numNeurons);
EXPORT_FUNC void pushMergedNeuronInitGroup1ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* input, scalar* Vmem, unsigned int numNeurons);
EXPORT_FUNC void pushMergedSynapseConnectivityInitGroup0ToDevice(unsigned int idx, unsigned int* rowLength, uint32_t* ind, scalar* g, scalar* kernelg, unsigned int rowStride, unsigned int numSrcNeurons, unsigned int numTrgNeurons);
EXPORT_FUNC void pushMergedSynapseConnectivityInit0kernelgToDevice(unsigned int idx, scalar* value);
EXPORT_FUNC void pushMergedSynapseConnectivityInitGroup1ToDevice(unsigned int idx, unsigned int* rowLength, uint32_t* ind, scalar* g, scalar* kernelg, unsigned int rowStride, unsigned int numSrcNeurons, unsigned int numTrgNeurons);
EXPORT_FUNC void pushMergedSynapseConnectivityInit1kernelgToDevice(unsigned int idx, scalar* value);
EXPORT_FUNC void pushMergedNeuronUpdateGroup0ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* input, scalar* Vmem, unsigned int numNeurons);
EXPORT_FUNC void pushMergedNeuronUpdateGroup1ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* Fx, scalar* Vmem, float* inSynInSyn0, unsigned int numNeurons, scalar alpha, scalar upstreamAlpha, scalar scale, scalar upstreamScale);
EXPORT_FUNC void pushMergedPresynapticUpdateGroup0ToDevice(unsigned int idx, float* inSyn, unsigned int* srcSpkCnt, unsigned int* srcSpk, scalar* weightsg, unsigned int rowStride, unsigned int numSrcNeurons, unsigned int numTrgNeurons);
EXPORT_FUNC void pushMergedPresynapticUpdate0weightsgToDevice(unsigned int idx, scalar* value);
EXPORT_FUNC void pushMergedPresynapticUpdateGroup1ToDevice(unsigned int idx, float* inSyn, unsigned int* srcSpkCnt, unsigned int* srcSpk, unsigned int* rowLength, uint32_t* ind, scalar* g, unsigned int rowStride, unsigned int numSrcNeurons, unsigned int numTrgNeurons);
EXPORT_FUNC void pushMergedPresynapticUpdateGroup2ToDevice(unsigned int idx, float* inSyn, unsigned int* srcSpkCnt, unsigned int* srcSpk, scalar* g, unsigned int rowStride, unsigned int numSrcNeurons, unsigned int numTrgNeurons);
EXPORT_FUNC void pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(unsigned int idx, unsigned int* spkCnt);
EXPORT_FUNC void pushMergedNeuronSpikeQueueUpdateGroup1ToDevice(unsigned int idx, unsigned int* spkCnt);
}  // extern "C"
