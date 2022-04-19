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
unsigned int* glbSpkCntneuron3;
unsigned int* glbSpkneuron3;
scalar* Fxneuron3;
scalar* Vmemneuron3;

// ------------------------------------------------------------------------
// custom update variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// pre and postsynaptic variables
// ------------------------------------------------------------------------
float* inSynsynapse1;
float* inSynsynapse2;

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// synapse variables
// ------------------------------------------------------------------------
scalar* gsynapse1;
scalar* gsynapse2;

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

void pushneuron3SpikesToDevice(bool uninitialisedOnly) {
}

void pushneuron3CurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushFxneuron3ToDevice(bool uninitialisedOnly) {
}

void pushCurrentFxneuron3ToDevice(bool uninitialisedOnly) {
}

void pushVmemneuron3ToDevice(bool uninitialisedOnly) {
}

void pushCurrentVmemneuron3ToDevice(bool uninitialisedOnly) {
}

void pushneuron3StateToDevice(bool uninitialisedOnly) {
    pushFxneuron3ToDevice(uninitialisedOnly);
    pushVmemneuron3ToDevice(uninitialisedOnly);
}

void pushgsynapse1ToDevice(bool uninitialisedOnly) {
}

void pushinSynsynapse1ToDevice(bool uninitialisedOnly) {
}

void pushsynapse1StateToDevice(bool uninitialisedOnly) {
    pushgsynapse1ToDevice(uninitialisedOnly);
    pushinSynsynapse1ToDevice(uninitialisedOnly);
}

void pushgsynapse2ToDevice(bool uninitialisedOnly) {
}

void pushinSynsynapse2ToDevice(bool uninitialisedOnly) {
}

void pushsynapse2StateToDevice(bool uninitialisedOnly) {
    pushgsynapse2ToDevice(uninitialisedOnly);
    pushinSynsynapse2ToDevice(uninitialisedOnly);
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

void pullneuron3SpikesFromDevice() {
}

void pullneuron3CurrentSpikesFromDevice() {
}

void pullFxneuron3FromDevice() {
}

void pullCurrentFxneuron3FromDevice() {
}

void pullVmemneuron3FromDevice() {
}

void pullCurrentVmemneuron3FromDevice() {
}

void pullneuron3StateFromDevice() {
    pullFxneuron3FromDevice();
    pullVmemneuron3FromDevice();
}

void pullgsynapse1FromDevice() {
}

void pullinSynsynapse1FromDevice() {
}

void pullsynapse1StateFromDevice() {
    pullgsynapse1FromDevice();
    pullinSynsynapse1FromDevice();
}

void pullgsynapse2FromDevice() {
}

void pullinSynsynapse2FromDevice() {
}

void pullsynapse2StateFromDevice() {
    pullgsynapse2FromDevice();
    pullinSynsynapse2FromDevice();
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

unsigned int* getneuron3CurrentSpikes(unsigned int batch) {
    return (glbSpkneuron3);
}

unsigned int& getneuron3CurrentSpikeCount(unsigned int batch) {
    return glbSpkCntneuron3[0];
}

scalar* getCurrentFxneuron3(unsigned int batch) {
    return Fxneuron3;
}

scalar* getCurrentVmemneuron3(unsigned int batch) {
    return Vmemneuron3;
}


void copyStateToDevice(bool uninitialisedOnly) {
    pushneuron1StateToDevice(uninitialisedOnly);
    pushneuron2StateToDevice(uninitialisedOnly);
    pushneuron3StateToDevice(uninitialisedOnly);
    pushsynapse1StateToDevice(uninitialisedOnly);
    pushsynapse2StateToDevice(uninitialisedOnly);
}

void copyConnectivityToDevice(bool uninitialisedOnly) {
}

void copyStateFromDevice() {
    pullneuron1StateFromDevice();
    pullneuron2StateFromDevice();
    pullneuron3StateFromDevice();
    pullsynapse1StateFromDevice();
    pullsynapse2StateFromDevice();
}

void copyCurrentSpikesFromDevice() {
    pullneuron1CurrentSpikesFromDevice();
    pullneuron2CurrentSpikesFromDevice();
    pullneuron3CurrentSpikesFromDevice();
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
    Fxneuron2 = new scalar[1];
    Vmemneuron2 = new scalar[1];
    glbSpkCntneuron3 = new unsigned int[1];
    glbSpkneuron3 = new unsigned int[1];
    Fxneuron3 = new scalar[1];
    Vmemneuron3 = new scalar[1];
    
    // ------------------------------------------------------------------------
    // custom update variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // pre and postsynaptic variables
    // ------------------------------------------------------------------------
    inSynsynapse1 = new float[1];
    inSynsynapse2 = new float[1];
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    gsynapse1 = new scalar[1];
    gsynapse2 = new scalar[1];
    
    pushMergedNeuronInitGroup0ToDevice(0, glbSpkCntneuron1, glbSpkneuron1, inputneuron1, Vmemneuron1, scaleValneuron1, 1);
    pushMergedNeuronInitGroup1ToDevice(0, glbSpkCntneuron2, glbSpkneuron2, Fxneuron2, Vmemneuron2, inSynsynapse1, 1);
    pushMergedNeuronInitGroup1ToDevice(1, glbSpkCntneuron3, glbSpkneuron3, Fxneuron3, Vmemneuron3, inSynsynapse2, 1);
    pushMergedSynapseDenseInitGroup0ToDevice(0, gsynapse1, 1, 1, 1);
    pushMergedSynapseDenseInitGroup0ToDevice(1, gsynapse2, 1, 1, 1);
    pushMergedNeuronUpdateGroup0ToDevice(0, glbSpkCntneuron1, glbSpkneuron1, inputneuron1, Vmemneuron1, scaleValneuron1, 1);
    pushMergedNeuronUpdateGroup1ToDevice(0, glbSpkCntneuron2, glbSpkneuron2, Fxneuron2, Vmemneuron2, inSynsynapse1, 1);
    pushMergedNeuronUpdateGroup1ToDevice(1, glbSpkCntneuron3, glbSpkneuron3, Fxneuron3, Vmemneuron3, inSynsynapse2, 1);
    pushMergedPresynapticUpdateGroup0ToDevice(0, inSynsynapse1, glbSpkCntneuron1, glbSpkneuron1, gsynapse1, 1, 1, 1);
    pushMergedPresynapticUpdateGroup0ToDevice(1, inSynsynapse2, glbSpkCntneuron2, glbSpkneuron2, gsynapse2, 1, 1, 1);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(0, glbSpkCntneuron1);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(1, glbSpkCntneuron2);
    pushMergedNeuronSpikeQueueUpdateGroup1ToDevice(0, glbSpkCntneuron3);
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
    delete[] glbSpkCntneuron3;
    delete[] glbSpkneuron3;
    delete[] Fxneuron3;
    delete[] Vmemneuron3;
    
    // ------------------------------------------------------------------------
    // custom update variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // pre and postsynaptic variables
    // ------------------------------------------------------------------------
    delete[] inSynsynapse1;
    delete[] inSynsynapse2;
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    delete[] gsynapse1;
    delete[] gsynapse2;
    
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

