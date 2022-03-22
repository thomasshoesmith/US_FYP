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
unsigned int* glbSpkCntneuron0;
unsigned int* glbSpkneuron0;
scalar* Vneuron0;
unsigned int* SpikeCountneuron0;
// current source variables
scalar* magnitudecurrent_input;
unsigned int* glbSpkCntneuron1;
unsigned int* glbSpkneuron1;
scalar* Vneuron1;
unsigned int* SpikeCountneuron1;
unsigned int* glbSpkCntneuron2;
unsigned int* glbSpkneuron2;
scalar* Vneuron2;
unsigned int* SpikeCountneuron2;

// ------------------------------------------------------------------------
// custom update variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// pre and postsynaptic variables
// ------------------------------------------------------------------------
float* inSynsynapse0;
float* inSynsynapse1;

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// synapse variables
// ------------------------------------------------------------------------
scalar* gsynapse0;
scalar* gsynapse1;

}  // extern "C"
// ------------------------------------------------------------------------
// extra global params
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// copying things to device
// ------------------------------------------------------------------------
void pushneuron0SpikesToDevice(bool uninitialisedOnly) {
}

void pushneuron0CurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushVneuron0ToDevice(bool uninitialisedOnly) {
}

void pushCurrentVneuron0ToDevice(bool uninitialisedOnly) {
}

void pushSpikeCountneuron0ToDevice(bool uninitialisedOnly) {
}

void pushCurrentSpikeCountneuron0ToDevice(bool uninitialisedOnly) {
}

void pushneuron0StateToDevice(bool uninitialisedOnly) {
    pushVneuron0ToDevice(uninitialisedOnly);
    pushSpikeCountneuron0ToDevice(uninitialisedOnly);
}

void pushmagnitudecurrent_inputToDevice(bool uninitialisedOnly) {
}

void pushcurrent_inputStateToDevice(bool uninitialisedOnly) {
    pushmagnitudecurrent_inputToDevice(uninitialisedOnly);
}

void pushneuron1SpikesToDevice(bool uninitialisedOnly) {
}

void pushneuron1CurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushVneuron1ToDevice(bool uninitialisedOnly) {
}

void pushCurrentVneuron1ToDevice(bool uninitialisedOnly) {
}

void pushSpikeCountneuron1ToDevice(bool uninitialisedOnly) {
}

void pushCurrentSpikeCountneuron1ToDevice(bool uninitialisedOnly) {
}

void pushneuron1StateToDevice(bool uninitialisedOnly) {
    pushVneuron1ToDevice(uninitialisedOnly);
    pushSpikeCountneuron1ToDevice(uninitialisedOnly);
}

void pushneuron2SpikesToDevice(bool uninitialisedOnly) {
}

void pushneuron2CurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushVneuron2ToDevice(bool uninitialisedOnly) {
}

void pushCurrentVneuron2ToDevice(bool uninitialisedOnly) {
}

void pushSpikeCountneuron2ToDevice(bool uninitialisedOnly) {
}

void pushCurrentSpikeCountneuron2ToDevice(bool uninitialisedOnly) {
}

void pushneuron2StateToDevice(bool uninitialisedOnly) {
    pushVneuron2ToDevice(uninitialisedOnly);
    pushSpikeCountneuron2ToDevice(uninitialisedOnly);
}

void pushgsynapse0ToDevice(bool uninitialisedOnly) {
}

void pushinSynsynapse0ToDevice(bool uninitialisedOnly) {
}

void pushsynapse0StateToDevice(bool uninitialisedOnly) {
    pushgsynapse0ToDevice(uninitialisedOnly);
    pushinSynsynapse0ToDevice(uninitialisedOnly);
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
void pullneuron0SpikesFromDevice() {
}

void pullneuron0CurrentSpikesFromDevice() {
}

void pullVneuron0FromDevice() {
}

void pullCurrentVneuron0FromDevice() {
}

void pullSpikeCountneuron0FromDevice() {
}

void pullCurrentSpikeCountneuron0FromDevice() {
}

void pullneuron0StateFromDevice() {
    pullVneuron0FromDevice();
    pullSpikeCountneuron0FromDevice();
}

void pullmagnitudecurrent_inputFromDevice() {
}

void pullcurrent_inputStateFromDevice() {
    pullmagnitudecurrent_inputFromDevice();
}

void pullneuron1SpikesFromDevice() {
}

void pullneuron1CurrentSpikesFromDevice() {
}

void pullVneuron1FromDevice() {
}

void pullCurrentVneuron1FromDevice() {
}

void pullSpikeCountneuron1FromDevice() {
}

void pullCurrentSpikeCountneuron1FromDevice() {
}

void pullneuron1StateFromDevice() {
    pullVneuron1FromDevice();
    pullSpikeCountneuron1FromDevice();
}

void pullneuron2SpikesFromDevice() {
}

void pullneuron2CurrentSpikesFromDevice() {
}

void pullVneuron2FromDevice() {
}

void pullCurrentVneuron2FromDevice() {
}

void pullSpikeCountneuron2FromDevice() {
}

void pullCurrentSpikeCountneuron2FromDevice() {
}

void pullneuron2StateFromDevice() {
    pullVneuron2FromDevice();
    pullSpikeCountneuron2FromDevice();
}

void pullgsynapse0FromDevice() {
}

void pullinSynsynapse0FromDevice() {
}

void pullsynapse0StateFromDevice() {
    pullgsynapse0FromDevice();
    pullinSynsynapse0FromDevice();
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
unsigned int* getneuron0CurrentSpikes(unsigned int batch) {
    return (glbSpkneuron0);
}

unsigned int& getneuron0CurrentSpikeCount(unsigned int batch) {
    return glbSpkCntneuron0[0];
}

scalar* getCurrentVneuron0(unsigned int batch) {
    return Vneuron0;
}

unsigned int* getCurrentSpikeCountneuron0(unsigned int batch) {
    return SpikeCountneuron0;
}

unsigned int* getneuron1CurrentSpikes(unsigned int batch) {
    return (glbSpkneuron1);
}

unsigned int& getneuron1CurrentSpikeCount(unsigned int batch) {
    return glbSpkCntneuron1[0];
}

scalar* getCurrentVneuron1(unsigned int batch) {
    return Vneuron1;
}

unsigned int* getCurrentSpikeCountneuron1(unsigned int batch) {
    return SpikeCountneuron1;
}

unsigned int* getneuron2CurrentSpikes(unsigned int batch) {
    return (glbSpkneuron2);
}

unsigned int& getneuron2CurrentSpikeCount(unsigned int batch) {
    return glbSpkCntneuron2[0];
}

scalar* getCurrentVneuron2(unsigned int batch) {
    return Vneuron2;
}

unsigned int* getCurrentSpikeCountneuron2(unsigned int batch) {
    return SpikeCountneuron2;
}


void copyStateToDevice(bool uninitialisedOnly) {
    pushneuron0StateToDevice(uninitialisedOnly);
    pushcurrent_inputStateToDevice(uninitialisedOnly);
    pushneuron1StateToDevice(uninitialisedOnly);
    pushneuron2StateToDevice(uninitialisedOnly);
    pushsynapse0StateToDevice(uninitialisedOnly);
    pushsynapse1StateToDevice(uninitialisedOnly);
}

void copyConnectivityToDevice(bool uninitialisedOnly) {
}

void copyStateFromDevice() {
    pullneuron0StateFromDevice();
    pullcurrent_inputStateFromDevice();
    pullneuron1StateFromDevice();
    pullneuron2StateFromDevice();
    pullsynapse0StateFromDevice();
    pullsynapse1StateFromDevice();
}

void copyCurrentSpikesFromDevice() {
    pullneuron0CurrentSpikesFromDevice();
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
    glbSpkCntneuron0 = new unsigned int[1];
    glbSpkneuron0 = new unsigned int[784];
    Vneuron0 = new scalar[784];
    SpikeCountneuron0 = new unsigned int[784];
    // current source variables
    magnitudecurrent_input = new scalar[784];
    glbSpkCntneuron1 = new unsigned int[1];
    glbSpkneuron1 = new unsigned int[128];
    Vneuron1 = new scalar[128];
    SpikeCountneuron1 = new unsigned int[128];
    glbSpkCntneuron2 = new unsigned int[1];
    glbSpkneuron2 = new unsigned int[10];
    Vneuron2 = new scalar[10];
    SpikeCountneuron2 = new unsigned int[10];
    
    // ------------------------------------------------------------------------
    // custom update variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // pre and postsynaptic variables
    // ------------------------------------------------------------------------
    inSynsynapse0 = new float[128];
    inSynsynapse1 = new float[10];
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    gsynapse0 = new scalar[100352];
    gsynapse1 = new scalar[1280];
    
    pushMergedNeuronInitGroup0ToDevice(0, glbSpkCntneuron0, glbSpkneuron0, Vneuron0, SpikeCountneuron0, magnitudecurrent_input, 784);
    pushMergedNeuronInitGroup1ToDevice(0, glbSpkCntneuron1, glbSpkneuron1, Vneuron1, SpikeCountneuron1, inSynsynapse0, 128);
    pushMergedNeuronInitGroup1ToDevice(1, glbSpkCntneuron2, glbSpkneuron2, Vneuron2, SpikeCountneuron2, inSynsynapse1, 10);
    pushMergedNeuronUpdateGroup0ToDevice(0, glbSpkCntneuron1, glbSpkneuron1, Vneuron1, SpikeCountneuron1, inSynsynapse0, 128);
    pushMergedNeuronUpdateGroup0ToDevice(1, glbSpkCntneuron2, glbSpkneuron2, Vneuron2, SpikeCountneuron2, inSynsynapse1, 10);
    pushMergedNeuronUpdateGroup1ToDevice(0, glbSpkCntneuron0, glbSpkneuron0, Vneuron0, SpikeCountneuron0, magnitudecurrent_input, 784);
    pushMergedPresynapticUpdateGroup0ToDevice(0, inSynsynapse0, glbSpkCntneuron0, glbSpkneuron0, gsynapse0, 128, 784, 128);
    pushMergedPresynapticUpdateGroup0ToDevice(1, inSynsynapse1, glbSpkCntneuron1, glbSpkneuron1, gsynapse1, 10, 128, 10);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(0, glbSpkCntneuron0);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(1, glbSpkCntneuron1);
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
    delete[] glbSpkCntneuron0;
    delete[] glbSpkneuron0;
    delete[] Vneuron0;
    delete[] SpikeCountneuron0;
    // current source variables
    delete[] magnitudecurrent_input;
    delete[] glbSpkCntneuron1;
    delete[] glbSpkneuron1;
    delete[] Vneuron1;
    delete[] SpikeCountneuron1;
    delete[] glbSpkCntneuron2;
    delete[] glbSpkneuron2;
    delete[] Vneuron2;
    delete[] SpikeCountneuron2;
    
    // ------------------------------------------------------------------------
    // custom update variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // pre and postsynaptic variables
    // ------------------------------------------------------------------------
    delete[] inSynsynapse0;
    delete[] inSynsynapse1;
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    delete[] gsynapse0;
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

