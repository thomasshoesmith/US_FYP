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
scalar* Fxneuron2;
scalar* Vmemneuron2;

// ------------------------------------------------------------------------
// custom update variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// pre and postsynaptic variables
// ------------------------------------------------------------------------
float* inSynsynapse1;

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// synapse variables
// ------------------------------------------------------------------------
scalar* gsynapse1;

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

void pushFxneuron2ToDevice(bool uninitialisedOnly) {
}

void pushCurrentFxneuron2ToDevice(bool uninitialisedOnly) {
}

void pushVmemneuron2ToDevice(bool uninitialisedOnly) {
}

void pushCurrentVmemneuron2ToDevice(bool uninitialisedOnly) {
}

void pushneuron2StateToDevice(bool uninitialisedOnly) {
    pushFxneuron2ToDevice(uninitialisedOnly);
    pushVmemneuron2ToDevice(uninitialisedOnly);
}

void pushgsynapse1ToDevice(bool uninitialisedOnly) {
}

void pushinSynsynapse1ToDevice(bool uninitialisedOnly) {
}

void pushsynapse1StateToDevice(bool uninitialisedOnly) {
    pushgsynapse1ToDevice(uninitialisedOnly);
    pushinSynsynapse1ToDevice(uninitialisedOnly);
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

void pullFxneuron2FromDevice() {
}

void pullCurrentFxneuron2FromDevice() {
}

void pullVmemneuron2FromDevice() {
}

void pullCurrentVmemneuron2FromDevice() {
}

void pullneuron2StateFromDevice() {
    pullFxneuron2FromDevice();
    pullVmemneuron2FromDevice();
}

void pullgsynapse1FromDevice() {
}

void pullinSynsynapse1FromDevice() {
}

void pullsynapse1StateFromDevice() {
    pullgsynapse1FromDevice();
    pullinSynsynapse1FromDevice();
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

scalar* getCurrentFxneuron2(unsigned int batch) {
    return Fxneuron2;
}

scalar* getCurrentVmemneuron2(unsigned int batch) {
    return Vmemneuron2;
}


void copyStateToDevice(bool uninitialisedOnly) {
    pushneuron1StateToDevice(uninitialisedOnly);
    pushneuron2StateToDevice(uninitialisedOnly);
    pushsynapse1StateToDevice(uninitialisedOnly);
}

void copyConnectivityToDevice(bool uninitialisedOnly) {
}

void copyStateFromDevice() {
    pullneuron1StateFromDevice();
    pullneuron2StateFromDevice();
    pullsynapse1StateFromDevice();
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
    glbSpkneuron1 = new unsigned int[2];
    inputneuron1 = new scalar[2];
    Vmemneuron1 = new scalar[2];
    scaleValneuron1 = new scalar[2];
    glbSpkCntneuron2 = new unsigned int[1];
    glbSpkneuron2 = new unsigned int[2];
    Fxneuron2 = new scalar[2];
    Vmemneuron2 = new scalar[2];
    
    // ------------------------------------------------------------------------
    // custom update variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // pre and postsynaptic variables
    // ------------------------------------------------------------------------
    inSynsynapse1 = new float[2];
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    gsynapse1 = new scalar[4];
    
    pushMergedNeuronInitGroup0ToDevice(0, glbSpkCntneuron1, glbSpkneuron1, inputneuron1, Vmemneuron1, scaleValneuron1, inSynsynapse1, 2);
    pushMergedNeuronInitGroup1ToDevice(0, glbSpkCntneuron2, glbSpkneuron2, Fxneuron2, Vmemneuron2, 2);
    pushMergedSynapseDenseInitGroup0ToDevice(0, gsynapse1, 2, 2, 2);
    pushMergedNeuronUpdateGroup0ToDevice(0, glbSpkCntneuron1, glbSpkneuron1, inputneuron1, Vmemneuron1, scaleValneuron1, inSynsynapse1, 2);
    pushMergedNeuronUpdateGroup1ToDevice(0, glbSpkCntneuron2, glbSpkneuron2, Fxneuron2, Vmemneuron2, 2);
    pushMergedPresynapticUpdateGroup0ToDevice(0, inSynsynapse1, glbSpkCntneuron1, glbSpkneuron1, gsynapse1, 2, 2, 2);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(0, glbSpkCntneuron1);
    pushMergedNeuronSpikeQueueUpdateGroup1ToDevice(0, glbSpkCntneuron2);
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
    delete[] Fxneuron2;
    delete[] Vmemneuron2;
    
    // ------------------------------------------------------------------------
    // custom update variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // pre and postsynaptic variables
    // ------------------------------------------------------------------------
    delete[] inSynsynapse1;
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    delete[] gsynapse1;
    
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

