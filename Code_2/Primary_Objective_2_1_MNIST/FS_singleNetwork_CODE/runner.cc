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
unsigned int* glbSpkCntneuron2;
unsigned int* glbSpkneuron2;
scalar* inputneuron2;
scalar* Vmemneuron2;
scalar* scaleValneuron2;

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

void pushneuron2SpikesToDevice(bool uninitialisedOnly) {
}

void pushneuron2CurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushinputneuron2ToDevice(bool uninitialisedOnly) {
}

void pushCurrentinputneuron2ToDevice(bool uninitialisedOnly) {
}

void pushVmemneuron2ToDevice(bool uninitialisedOnly) {
}

void pushCurrentVmemneuron2ToDevice(bool uninitialisedOnly) {
}

void pushscaleValneuron2ToDevice(bool uninitialisedOnly) {
}

void pushCurrentscaleValneuron2ToDevice(bool uninitialisedOnly) {
}

void pushneuron2StateToDevice(bool uninitialisedOnly) {
    pushinputneuron2ToDevice(uninitialisedOnly);
    pushVmemneuron2ToDevice(uninitialisedOnly);
    pushscaleValneuron2ToDevice(uninitialisedOnly);
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

void pullneuron2SpikesFromDevice() {
}

void pullneuron2CurrentSpikesFromDevice() {
}

void pullinputneuron2FromDevice() {
}

void pullCurrentinputneuron2FromDevice() {
}

void pullVmemneuron2FromDevice() {
}

void pullCurrentVmemneuron2FromDevice() {
}

void pullscaleValneuron2FromDevice() {
}

void pullCurrentscaleValneuron2FromDevice() {
}

void pullneuron2StateFromDevice() {
    pullinputneuron2FromDevice();
    pullVmemneuron2FromDevice();
    pullscaleValneuron2FromDevice();
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

unsigned int* getneuron2CurrentSpikes(unsigned int batch) {
    return (glbSpkneuron2);
}

unsigned int& getneuron2CurrentSpikeCount(unsigned int batch) {
    return glbSpkCntneuron2[0];
}

scalar* getCurrentinputneuron2(unsigned int batch) {
    return inputneuron2;
}

scalar* getCurrentVmemneuron2(unsigned int batch) {
    return Vmemneuron2;
}

scalar* getCurrentscaleValneuron2(unsigned int batch) {
    return scaleValneuron2;
}


void copyStateToDevice(bool uninitialisedOnly) {
    pushneuron1StateToDevice(uninitialisedOnly);
    pushneuron2StateToDevice(uninitialisedOnly);
}

void copyConnectivityToDevice(bool uninitialisedOnly) {
}

void copyStateFromDevice() {
    pullneuron1StateFromDevice();
    pullneuron2StateFromDevice();
}

void copyCurrentSpikesFromDevice() {
    pullneuron1CurrentSpikesFromDevice();
    pullneuron2CurrentSpikesFromDevice();
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
    glbSpkCntneuron2 = new unsigned int[1];
    glbSpkneuron2 = new unsigned int[1];
    inputneuron2 = new scalar[1];
    Vmemneuron2 = new scalar[1];
    scaleValneuron2 = new scalar[1];
    
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
    pushMergedNeuronInitGroup0ToDevice(1, glbSpkCntneuron2, glbSpkneuron2, inputneuron2, Vmemneuron2, scaleValneuron2, 1);
    pushMergedNeuronUpdateGroup0ToDevice(0, glbSpkCntneuron1, glbSpkneuron1, inputneuron1, Vmemneuron1, scaleValneuron1, 1);
    pushMergedNeuronUpdateGroup0ToDevice(1, glbSpkCntneuron2, glbSpkneuron2, inputneuron2, Vmemneuron2, scaleValneuron2, 1);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(0, glbSpkCntneuron1);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(1, glbSpkCntneuron2);
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
    delete[] glbSpkCntneuron2;
    delete[] glbSpkneuron2;
    delete[] inputneuron2;
    delete[] Vmemneuron2;
    delete[] scaleValneuron2;
    
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

