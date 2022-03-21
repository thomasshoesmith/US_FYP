#include "definitionsInternal.h"


extern "C" {
// ------------------------------------------------------------------------
// global variables
// ------------------------------------------------------------------------
unsigned long long iT;
float t;

// ------------------------------------------------------------------------
// timers
// ------------------------------------------------------------------------
double initTime = 0.0;
double initSparseTime = 0.0;
double neuronUpdateTime = 0.0;
double presynapticUpdateTime = 0.0;
double postsynapticUpdateTime = 0.0;
double synapseDynamicsTime = 0.0;
// ------------------------------------------------------------------------
// merged group arrays
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// local neuron groups
// ------------------------------------------------------------------------
unsigned int* glbSpkCntPop1;
unsigned int* glbSpkPop1;
scalar* VPop1;
scalar* mPop1;
scalar* hPop1;
scalar* nPop1;

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

}  // extern "C"
// ------------------------------------------------------------------------
// extra global params
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// copying things to device
// ------------------------------------------------------------------------
void pushPop1SpikesToDevice(bool uninitialisedOnly) {
}

void pushPop1CurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushVPop1ToDevice(bool uninitialisedOnly) {
}

void pushCurrentVPop1ToDevice(bool uninitialisedOnly) {
}

void pushmPop1ToDevice(bool uninitialisedOnly) {
}

void pushCurrentmPop1ToDevice(bool uninitialisedOnly) {
}

void pushhPop1ToDevice(bool uninitialisedOnly) {
}

void pushCurrenthPop1ToDevice(bool uninitialisedOnly) {
}

void pushnPop1ToDevice(bool uninitialisedOnly) {
}

void pushCurrentnPop1ToDevice(bool uninitialisedOnly) {
}

void pushPop1StateToDevice(bool uninitialisedOnly) {
    pushVPop1ToDevice(uninitialisedOnly);
    pushmPop1ToDevice(uninitialisedOnly);
    pushhPop1ToDevice(uninitialisedOnly);
    pushnPop1ToDevice(uninitialisedOnly);
}


// ------------------------------------------------------------------------
// copying things from device
// ------------------------------------------------------------------------
void pullPop1SpikesFromDevice() {
}

void pullPop1CurrentSpikesFromDevice() {
}

void pullVPop1FromDevice() {
}

void pullCurrentVPop1FromDevice() {
}

void pullmPop1FromDevice() {
}

void pullCurrentmPop1FromDevice() {
}

void pullhPop1FromDevice() {
}

void pullCurrenthPop1FromDevice() {
}

void pullnPop1FromDevice() {
}

void pullCurrentnPop1FromDevice() {
}

void pullPop1StateFromDevice() {
    pullVPop1FromDevice();
    pullmPop1FromDevice();
    pullhPop1FromDevice();
    pullnPop1FromDevice();
}


// ------------------------------------------------------------------------
// helper getter functions
// ------------------------------------------------------------------------
unsigned int* getPop1CurrentSpikes(unsigned int batch) {
    return (glbSpkPop1);
}

unsigned int& getPop1CurrentSpikeCount(unsigned int batch) {
    return glbSpkCntPop1[0];
}

scalar* getCurrentVPop1(unsigned int batch) {
    return VPop1;
}

scalar* getCurrentmPop1(unsigned int batch) {
    return mPop1;
}

scalar* getCurrenthPop1(unsigned int batch) {
    return hPop1;
}

scalar* getCurrentnPop1(unsigned int batch) {
    return nPop1;
}


void copyStateToDevice(bool uninitialisedOnly) {
    pushPop1StateToDevice(uninitialisedOnly);
}

void copyConnectivityToDevice(bool uninitialisedOnly) {
}

void copyStateFromDevice() {
    pullPop1StateFromDevice();
}

void copyCurrentSpikesFromDevice() {
    pullPop1CurrentSpikesFromDevice();
}

void copyCurrentSpikeEventsFromDevice() {
}

void allocateMem() {
    // ------------------------------------------------------------------------
    // global variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // timers
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    // local neuron groups
    // ------------------------------------------------------------------------
    glbSpkCntPop1 = new unsigned int[1];
    glbSpkPop1 = new unsigned int[10];
    VPop1 = new scalar[10];
    mPop1 = new scalar[10];
    hPop1 = new scalar[10];
    nPop1 = new scalar[10];
    
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
    
    pushMergedNeuronInitGroup0ToDevice(0, glbSpkCntPop1, glbSpkPop1, VPop1, mPop1, hPop1, nPop1, 10);
    pushMergedNeuronUpdateGroup0ToDevice(0, glbSpkCntPop1, glbSpkPop1, VPop1, mPop1, hPop1, nPop1, 10);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(0, glbSpkCntPop1);
}

void freeMem() {
    // ------------------------------------------------------------------------
    // global variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // timers
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    // local neuron groups
    // ------------------------------------------------------------------------
    delete[] glbSpkCntPop1;
    delete[] glbSpkPop1;
    delete[] VPop1;
    delete[] mPop1;
    delete[] hPop1;
    delete[] nPop1;
    
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
    
}

size_t getFreeDeviceMemBytes() {
    return 0;
}

void stepTime() {
    updateSynapses(t);
    updateNeurons(t); 
    iT++;
    t = iT*DT;
}

