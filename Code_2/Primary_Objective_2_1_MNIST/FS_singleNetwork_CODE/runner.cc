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
unsigned int* glbSpkCntneuron1;
unsigned int* glbSpkneuron1;
scalar* inputneuron1;
scalar* Vmemneuron1;
scalar* scaleValneuron1;

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
void pushneuron1SpikesToDevice(bool uninitialisedOnly) {
}

void pushneuron1CurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushinputneuron1ToDevice(bool uninitialisedOnly) {
}

void pushCurrentinputneuron1ToDevice(bool uninitialisedOnly) {
}

void pushVmemneuron1ToDevice(bool uninitialisedOnly) {
}

void pushCurrentVmemneuron1ToDevice(bool uninitialisedOnly) {
}

void pushscaleValneuron1ToDevice(bool uninitialisedOnly) {
}

void pushCurrentscaleValneuron1ToDevice(bool uninitialisedOnly) {
}

void pushneuron1StateToDevice(bool uninitialisedOnly) {
    pushinputneuron1ToDevice(uninitialisedOnly);
    pushVmemneuron1ToDevice(uninitialisedOnly);
    pushscaleValneuron1ToDevice(uninitialisedOnly);
}


// ------------------------------------------------------------------------
// copying things from device
// ------------------------------------------------------------------------
void pullneuron1SpikesFromDevice() {
}

void pullneuron1CurrentSpikesFromDevice() {
}

void pullinputneuron1FromDevice() {
}

void pullCurrentinputneuron1FromDevice() {
}

void pullVmemneuron1FromDevice() {
}

void pullCurrentVmemneuron1FromDevice() {
}

void pullscaleValneuron1FromDevice() {
}

void pullCurrentscaleValneuron1FromDevice() {
}

void pullneuron1StateFromDevice() {
    pullinputneuron1FromDevice();
    pullVmemneuron1FromDevice();
    pullscaleValneuron1FromDevice();
}


// ------------------------------------------------------------------------
// helper getter functions
// ------------------------------------------------------------------------
unsigned int* getneuron1CurrentSpikes(unsigned int batch) {
    return (glbSpkneuron1);
}

unsigned int& getneuron1CurrentSpikeCount(unsigned int batch) {
    return glbSpkCntneuron1[0];
}

scalar* getCurrentinputneuron1(unsigned int batch) {
    return inputneuron1;
}

scalar* getCurrentVmemneuron1(unsigned int batch) {
    return Vmemneuron1;
}

scalar* getCurrentscaleValneuron1(unsigned int batch) {
    return scaleValneuron1;
}


void copyStateToDevice(bool uninitialisedOnly) {
    pushneuron1StateToDevice(uninitialisedOnly);
}

void copyConnectivityToDevice(bool uninitialisedOnly) {
}

void copyStateFromDevice() {
    pullneuron1StateFromDevice();
}

void copyCurrentSpikesFromDevice() {
    pullneuron1CurrentSpikesFromDevice();
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
    glbSpkCntneuron1 = new unsigned int[1];
    glbSpkneuron1 = new unsigned int[1];
    inputneuron1 = new scalar[1];
    Vmemneuron1 = new scalar[1];
    scaleValneuron1 = new scalar[1];
    
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
    
    pushMergedNeuronInitGroup0ToDevice(0, glbSpkCntneuron1, glbSpkneuron1, inputneuron1, Vmemneuron1, scaleValneuron1, 1);
    pushMergedNeuronUpdateGroup0ToDevice(0, glbSpkCntneuron1, glbSpkneuron1, inputneuron1, Vmemneuron1, scaleValneuron1, 1);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(0, glbSpkCntneuron1);
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
    delete[] glbSpkCntneuron1;
    delete[] glbSpkneuron1;
    delete[] inputneuron1;
    delete[] Vmemneuron1;
    delete[] scaleValneuron1;
    
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

