#include "definitionsInternal.h"

std::uniform_real_distribution<float> standardUniformDistribution(0.000000000e+00f, 1.000000000e+00f);
std::normal_distribution<float> standardNormalDistribution(0.000000000e+00f, 1.000000000e+00f);
std::exponential_distribution<float> standardExponentialDistribution(1.000000000e+00f);


extern "C" {
// ------------------------------------------------------------------------
// global variables
// ------------------------------------------------------------------------
unsigned long long iT;
float t;
std::mt19937 hostRNG;

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
unsigned int* glbSpkCntdense_1_nrn;
unsigned int* glbSpkdense_1_nrn;
scalar* Vmemdense_1_nrn;
unsigned int* nSpkdense_1_nrn;
scalar Vthrdense_1_nrn;
unsigned int* glbSpkCntdense_nrn;
unsigned int* glbSpkdense_nrn;
scalar* Vmemdense_nrn;
unsigned int* nSpkdense_nrn;
scalar Vthrdense_nrn;
unsigned int* glbSpkCntflatten_input_nrn;
unsigned int* glbSpkflatten_input_nrn;
scalar* inputflatten_input_nrn;

// ------------------------------------------------------------------------
// custom update variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// pre and postsynaptic variables
// ------------------------------------------------------------------------
float* inSyndense_to_dense_1_syn;
float* inSynflatten_input_to_dense_syn;

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// synapse variables
// ------------------------------------------------------------------------
scalar* gdense_to_dense_1_syn;
scalar* gflatten_input_to_dense_syn;

}  // extern "C"
// ------------------------------------------------------------------------
// extra global params
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// copying things to device
// ------------------------------------------------------------------------
void pushdense_1_nrnSpikesToDevice(bool uninitialisedOnly) {
}

void pushdense_1_nrnCurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushVmemdense_1_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentVmemdense_1_nrnToDevice(bool uninitialisedOnly) {
}

void pushnSpkdense_1_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentnSpkdense_1_nrnToDevice(bool uninitialisedOnly) {
}

void pushdense_1_nrnStateToDevice(bool uninitialisedOnly) {
    pushVmemdense_1_nrnToDevice(uninitialisedOnly);
    pushnSpkdense_1_nrnToDevice(uninitialisedOnly);
}

void pushdense_nrnSpikesToDevice(bool uninitialisedOnly) {
}

void pushdense_nrnCurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushVmemdense_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentVmemdense_nrnToDevice(bool uninitialisedOnly) {
}

void pushnSpkdense_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentnSpkdense_nrnToDevice(bool uninitialisedOnly) {
}

void pushdense_nrnStateToDevice(bool uninitialisedOnly) {
    pushVmemdense_nrnToDevice(uninitialisedOnly);
    pushnSpkdense_nrnToDevice(uninitialisedOnly);
}

void pushflatten_input_nrnSpikesToDevice(bool uninitialisedOnly) {
}

void pushflatten_input_nrnCurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushinputflatten_input_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentinputflatten_input_nrnToDevice(bool uninitialisedOnly) {
}

void pushflatten_input_nrnStateToDevice(bool uninitialisedOnly) {
    pushinputflatten_input_nrnToDevice(uninitialisedOnly);
}

void pushgdense_to_dense_1_synToDevice(bool uninitialisedOnly) {
}

void pushinSyndense_to_dense_1_synToDevice(bool uninitialisedOnly) {
}

void pushdense_to_dense_1_synStateToDevice(bool uninitialisedOnly) {
    pushgdense_to_dense_1_synToDevice(uninitialisedOnly);
    pushinSyndense_to_dense_1_synToDevice(uninitialisedOnly);
}

void pushgflatten_input_to_dense_synToDevice(bool uninitialisedOnly) {
}

void pushinSynflatten_input_to_dense_synToDevice(bool uninitialisedOnly) {
}

void pushflatten_input_to_dense_synStateToDevice(bool uninitialisedOnly) {
    pushgflatten_input_to_dense_synToDevice(uninitialisedOnly);
    pushinSynflatten_input_to_dense_synToDevice(uninitialisedOnly);
}


// ------------------------------------------------------------------------
// copying things from device
// ------------------------------------------------------------------------
void pulldense_1_nrnSpikesFromDevice() {
}

void pulldense_1_nrnCurrentSpikesFromDevice() {
}

void pullVmemdense_1_nrnFromDevice() {
}

void pullCurrentVmemdense_1_nrnFromDevice() {
}

void pullnSpkdense_1_nrnFromDevice() {
}

void pullCurrentnSpkdense_1_nrnFromDevice() {
}

void pulldense_1_nrnStateFromDevice() {
    pullVmemdense_1_nrnFromDevice();
    pullnSpkdense_1_nrnFromDevice();
}

void pulldense_nrnSpikesFromDevice() {
}

void pulldense_nrnCurrentSpikesFromDevice() {
}

void pullVmemdense_nrnFromDevice() {
}

void pullCurrentVmemdense_nrnFromDevice() {
}

void pullnSpkdense_nrnFromDevice() {
}

void pullCurrentnSpkdense_nrnFromDevice() {
}

void pulldense_nrnStateFromDevice() {
    pullVmemdense_nrnFromDevice();
    pullnSpkdense_nrnFromDevice();
}

void pullflatten_input_nrnSpikesFromDevice() {
}

void pullflatten_input_nrnCurrentSpikesFromDevice() {
}

void pullinputflatten_input_nrnFromDevice() {
}

void pullCurrentinputflatten_input_nrnFromDevice() {
}

void pullflatten_input_nrnStateFromDevice() {
    pullinputflatten_input_nrnFromDevice();
}

void pullgdense_to_dense_1_synFromDevice() {
}

void pullinSyndense_to_dense_1_synFromDevice() {
}

void pulldense_to_dense_1_synStateFromDevice() {
    pullgdense_to_dense_1_synFromDevice();
    pullinSyndense_to_dense_1_synFromDevice();
}

void pullgflatten_input_to_dense_synFromDevice() {
}

void pullinSynflatten_input_to_dense_synFromDevice() {
}

void pullflatten_input_to_dense_synStateFromDevice() {
    pullgflatten_input_to_dense_synFromDevice();
    pullinSynflatten_input_to_dense_synFromDevice();
}


// ------------------------------------------------------------------------
// helper getter functions
// ------------------------------------------------------------------------
unsigned int* getdense_1_nrnCurrentSpikes(unsigned int batch) {
    return (glbSpkdense_1_nrn);
}

unsigned int& getdense_1_nrnCurrentSpikeCount(unsigned int batch) {
    return glbSpkCntdense_1_nrn[0];
}

scalar* getCurrentVmemdense_1_nrn(unsigned int batch) {
    return Vmemdense_1_nrn;
}

unsigned int* getCurrentnSpkdense_1_nrn(unsigned int batch) {
    return nSpkdense_1_nrn;
}

unsigned int* getdense_nrnCurrentSpikes(unsigned int batch) {
    return (glbSpkdense_nrn);
}

unsigned int& getdense_nrnCurrentSpikeCount(unsigned int batch) {
    return glbSpkCntdense_nrn[0];
}

scalar* getCurrentVmemdense_nrn(unsigned int batch) {
    return Vmemdense_nrn;
}

unsigned int* getCurrentnSpkdense_nrn(unsigned int batch) {
    return nSpkdense_nrn;
}

unsigned int* getflatten_input_nrnCurrentSpikes(unsigned int batch) {
    return (glbSpkflatten_input_nrn);
}

unsigned int& getflatten_input_nrnCurrentSpikeCount(unsigned int batch) {
    return glbSpkCntflatten_input_nrn[0];
}

scalar* getCurrentinputflatten_input_nrn(unsigned int batch) {
    return inputflatten_input_nrn;
}


void copyStateToDevice(bool uninitialisedOnly) {
    pushdense_1_nrnStateToDevice(uninitialisedOnly);
    pushdense_nrnStateToDevice(uninitialisedOnly);
    pushflatten_input_nrnStateToDevice(uninitialisedOnly);
    pushdense_to_dense_1_synStateToDevice(uninitialisedOnly);
    pushflatten_input_to_dense_synStateToDevice(uninitialisedOnly);
}

void copyConnectivityToDevice(bool uninitialisedOnly) {
}

void copyStateFromDevice() {
    pulldense_1_nrnStateFromDevice();
    pulldense_nrnStateFromDevice();
    pullflatten_input_nrnStateFromDevice();
    pulldense_to_dense_1_synStateFromDevice();
    pullflatten_input_to_dense_synStateFromDevice();
}

void copyCurrentSpikesFromDevice() {
    pulldense_1_nrnCurrentSpikesFromDevice();
    pulldense_nrnCurrentSpikesFromDevice();
    pullflatten_input_nrnCurrentSpikesFromDevice();
}

void copyCurrentSpikeEventsFromDevice() {
}

void allocateMem() {
    // ------------------------------------------------------------------------
    // global variables
    // ------------------------------------------------------------------------
     {
        uint32_t seedData[std::mt19937::state_size];
        std::random_device seedSource;
        for(int i = 0; i < std::mt19937::state_size; i++) {
            seedData[i] = seedSource();
        }
        std::seed_seq seeds(std::begin(seedData), std::end(seedData));
        hostRNG.seed(seeds);
    }
    
    // ------------------------------------------------------------------------
    // timers
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    // local neuron groups
    // ------------------------------------------------------------------------
    glbSpkCntdense_1_nrn = new unsigned int[1];
    glbSpkdense_1_nrn = new unsigned int[10];
    Vmemdense_1_nrn = new scalar[10];
    nSpkdense_1_nrn = new unsigned int[10];
    glbSpkCntdense_nrn = new unsigned int[1];
    glbSpkdense_nrn = new unsigned int[128];
    Vmemdense_nrn = new scalar[128];
    nSpkdense_nrn = new unsigned int[128];
    glbSpkCntflatten_input_nrn = new unsigned int[1];
    glbSpkflatten_input_nrn = new unsigned int[784];
    inputflatten_input_nrn = new scalar[784];
    
    // ------------------------------------------------------------------------
    // custom update variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // pre and postsynaptic variables
    // ------------------------------------------------------------------------
    inSyndense_to_dense_1_syn = new float[10];
    inSynflatten_input_to_dense_syn = new float[128];
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    gdense_to_dense_1_syn = new scalar[1280];
    gflatten_input_to_dense_syn = new scalar[100352];
    
    pushMergedNeuronInitGroup0ToDevice(0, glbSpkCntdense_1_nrn, glbSpkdense_1_nrn, Vmemdense_1_nrn, nSpkdense_1_nrn, inSyndense_to_dense_1_syn, 10);
    pushMergedNeuronInitGroup0ToDevice(1, glbSpkCntdense_nrn, glbSpkdense_nrn, Vmemdense_nrn, nSpkdense_nrn, inSynflatten_input_to_dense_syn, 128);
    pushMergedNeuronInitGroup1ToDevice(0, glbSpkCntflatten_input_nrn, glbSpkflatten_input_nrn, inputflatten_input_nrn, 784);
    pushMergedNeuronUpdateGroup0ToDevice(0, glbSpkCntdense_1_nrn, glbSpkdense_1_nrn, Vmemdense_1_nrn, nSpkdense_1_nrn, inSyndense_to_dense_1_syn, 10, Vthrdense_1_nrn);
    pushMergedNeuronUpdateGroup0ToDevice(1, glbSpkCntdense_nrn, glbSpkdense_nrn, Vmemdense_nrn, nSpkdense_nrn, inSynflatten_input_to_dense_syn, 128, Vthrdense_nrn);
    pushMergedNeuronUpdateGroup1ToDevice(0, glbSpkCntflatten_input_nrn, glbSpkflatten_input_nrn, inputflatten_input_nrn, 784);
    pushMergedPresynapticUpdateGroup0ToDevice(0, inSyndense_to_dense_1_syn, glbSpkCntdense_nrn, glbSpkdense_nrn, gdense_to_dense_1_syn, 10, 128, 10);
    pushMergedPresynapticUpdateGroup0ToDevice(1, inSynflatten_input_to_dense_syn, glbSpkCntflatten_input_nrn, glbSpkflatten_input_nrn, gflatten_input_to_dense_syn, 128, 784, 128);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(0, glbSpkCntdense_1_nrn);
    pushMergedNeuronSpikeQueueUpdateGroup1ToDevice(0, glbSpkCntdense_nrn);
    pushMergedNeuronSpikeQueueUpdateGroup1ToDevice(1, glbSpkCntflatten_input_nrn);
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
    delete[] glbSpkCntdense_1_nrn;
    delete[] glbSpkdense_1_nrn;
    delete[] Vmemdense_1_nrn;
    delete[] nSpkdense_1_nrn;
    delete[] glbSpkCntdense_nrn;
    delete[] glbSpkdense_nrn;
    delete[] Vmemdense_nrn;
    delete[] nSpkdense_nrn;
    delete[] glbSpkCntflatten_input_nrn;
    delete[] glbSpkflatten_input_nrn;
    delete[] inputflatten_input_nrn;
    
    // ------------------------------------------------------------------------
    // custom update variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // pre and postsynaptic variables
    // ------------------------------------------------------------------------
    delete[] inSyndense_to_dense_1_syn;
    delete[] inSynflatten_input_to_dense_syn;
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    delete[] gdense_to_dense_1_syn;
    delete[] gflatten_input_to_dense_syn;
    
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

