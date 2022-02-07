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
unsigned int* glbSpkCntconv2d_1_nrn;
unsigned int* glbSpkconv2d_1_nrn;
scalar* Fxconv2d_1_nrn;
scalar* Vmemconv2d_1_nrn;
unsigned int* glbSpkCntconv2d_input_nrn;
unsigned int* glbSpkconv2d_input_nrn;
scalar* inputconv2d_input_nrn;
scalar* Vmemconv2d_input_nrn;
unsigned int* glbSpkCntconv2d_nrn;
unsigned int* glbSpkconv2d_nrn;
scalar* Fxconv2d_nrn;
scalar* Vmemconv2d_nrn;
unsigned int* glbSpkCntdense_1_nrn;
unsigned int* glbSpkdense_1_nrn;
scalar* Fxdense_1_nrn;
scalar* Vmemdense_1_nrn;
unsigned int* glbSpkCntdense_2_nrn;
unsigned int* glbSpkdense_2_nrn;
scalar* Fxdense_2_nrn;
scalar* Vmemdense_2_nrn;
unsigned int* glbSpkCntdense_nrn;
unsigned int* glbSpkdense_nrn;
scalar* Fxdense_nrn;
scalar* Vmemdense_nrn;

// ------------------------------------------------------------------------
// custom update variables
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// pre and postsynaptic variables
// ------------------------------------------------------------------------
float* inSynconv2d_to_conv2d_1_syn;
float* inSynconv2d_input_to_conv2d_syn;
float* inSyndense_to_dense_1_syn;
float* inSyndense_1_to_dense_2_syn;
float* inSynconv2d_1_to_dense_syn;

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------
const unsigned int maxRowLengthconv2d_input_to_conv2d_syn = 400;
unsigned int* rowLengthconv2d_input_to_conv2d_syn;
uint32_t* indconv2d_input_to_conv2d_syn;
const unsigned int maxRowLengthconv2d_to_conv2d_1_syn = 200;
unsigned int* rowLengthconv2d_to_conv2d_1_syn;
uint32_t* indconv2d_to_conv2d_1_syn;

// ------------------------------------------------------------------------
// synapse variables
// ------------------------------------------------------------------------
scalar* weightsgconv2d_1_to_dense_syn;
scalar* gconv2d_input_to_conv2d_syn;
scalar* kernelgconv2d_input_to_conv2d_syn;
scalar* gconv2d_to_conv2d_1_syn;
scalar* kernelgconv2d_to_conv2d_1_syn;
scalar* gdense_1_to_dense_2_syn;
scalar* gdense_to_dense_1_syn;

}  // extern "C"
// ------------------------------------------------------------------------
// extra global params
// ------------------------------------------------------------------------
void allocateweightsgconv2d_1_to_dense_syn(unsigned int count) {
    weightsgconv2d_1_to_dense_syn = new scalar[count];
    pushMergedPresynapticUpdate0weightsgToDevice(0, weightsgconv2d_1_to_dense_syn);
}
void freeweightsgconv2d_1_to_dense_syn() {
    delete[] weightsgconv2d_1_to_dense_syn;
}
void pushweightsgconv2d_1_to_dense_synToDevice(unsigned int count) {
}
void pullweightsgconv2d_1_to_dense_synFromDevice(unsigned int count) {
}
void allocatekernelgconv2d_input_to_conv2d_syn(unsigned int count) {
    kernelgconv2d_input_to_conv2d_syn = new scalar[count];
    pushMergedSynapseConnectivityInit0kernelgToDevice(0, kernelgconv2d_input_to_conv2d_syn);
}
void freekernelgconv2d_input_to_conv2d_syn() {
    delete[] kernelgconv2d_input_to_conv2d_syn;
}
void pushkernelgconv2d_input_to_conv2d_synToDevice(unsigned int count) {
}
void pullkernelgconv2d_input_to_conv2d_synFromDevice(unsigned int count) {
}
void allocatekernelgconv2d_to_conv2d_1_syn(unsigned int count) {
    kernelgconv2d_to_conv2d_1_syn = new scalar[count];
    pushMergedSynapseConnectivityInit1kernelgToDevice(0, kernelgconv2d_to_conv2d_1_syn);
}
void freekernelgconv2d_to_conv2d_1_syn() {
    delete[] kernelgconv2d_to_conv2d_1_syn;
}
void pushkernelgconv2d_to_conv2d_1_synToDevice(unsigned int count) {
}
void pullkernelgconv2d_to_conv2d_1_synFromDevice(unsigned int count) {
}

// ------------------------------------------------------------------------
// copying things to device
// ------------------------------------------------------------------------
void pushconv2d_1_nrnSpikesToDevice(bool uninitialisedOnly) {
}

void pushconv2d_1_nrnCurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushFxconv2d_1_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentFxconv2d_1_nrnToDevice(bool uninitialisedOnly) {
}

void pushVmemconv2d_1_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentVmemconv2d_1_nrnToDevice(bool uninitialisedOnly) {
}

void pushconv2d_1_nrnStateToDevice(bool uninitialisedOnly) {
    pushFxconv2d_1_nrnToDevice(uninitialisedOnly);
    pushVmemconv2d_1_nrnToDevice(uninitialisedOnly);
}

void pushconv2d_input_nrnSpikesToDevice(bool uninitialisedOnly) {
}

void pushconv2d_input_nrnCurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushinputconv2d_input_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentinputconv2d_input_nrnToDevice(bool uninitialisedOnly) {
}

void pushVmemconv2d_input_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentVmemconv2d_input_nrnToDevice(bool uninitialisedOnly) {
}

void pushconv2d_input_nrnStateToDevice(bool uninitialisedOnly) {
    pushinputconv2d_input_nrnToDevice(uninitialisedOnly);
    pushVmemconv2d_input_nrnToDevice(uninitialisedOnly);
}

void pushconv2d_nrnSpikesToDevice(bool uninitialisedOnly) {
}

void pushconv2d_nrnCurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushFxconv2d_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentFxconv2d_nrnToDevice(bool uninitialisedOnly) {
}

void pushVmemconv2d_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentVmemconv2d_nrnToDevice(bool uninitialisedOnly) {
}

void pushconv2d_nrnStateToDevice(bool uninitialisedOnly) {
    pushFxconv2d_nrnToDevice(uninitialisedOnly);
    pushVmemconv2d_nrnToDevice(uninitialisedOnly);
}

void pushdense_1_nrnSpikesToDevice(bool uninitialisedOnly) {
}

void pushdense_1_nrnCurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushFxdense_1_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentFxdense_1_nrnToDevice(bool uninitialisedOnly) {
}

void pushVmemdense_1_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentVmemdense_1_nrnToDevice(bool uninitialisedOnly) {
}

void pushdense_1_nrnStateToDevice(bool uninitialisedOnly) {
    pushFxdense_1_nrnToDevice(uninitialisedOnly);
    pushVmemdense_1_nrnToDevice(uninitialisedOnly);
}

void pushdense_2_nrnSpikesToDevice(bool uninitialisedOnly) {
}

void pushdense_2_nrnCurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushFxdense_2_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentFxdense_2_nrnToDevice(bool uninitialisedOnly) {
}

void pushVmemdense_2_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentVmemdense_2_nrnToDevice(bool uninitialisedOnly) {
}

void pushdense_2_nrnStateToDevice(bool uninitialisedOnly) {
    pushFxdense_2_nrnToDevice(uninitialisedOnly);
    pushVmemdense_2_nrnToDevice(uninitialisedOnly);
}

void pushdense_nrnSpikesToDevice(bool uninitialisedOnly) {
}

void pushdense_nrnCurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushFxdense_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentFxdense_nrnToDevice(bool uninitialisedOnly) {
}

void pushVmemdense_nrnToDevice(bool uninitialisedOnly) {
}

void pushCurrentVmemdense_nrnToDevice(bool uninitialisedOnly) {
}

void pushdense_nrnStateToDevice(bool uninitialisedOnly) {
    pushFxdense_nrnToDevice(uninitialisedOnly);
    pushVmemdense_nrnToDevice(uninitialisedOnly);
}

void pushconv2d_input_to_conv2d_synConnectivityToDevice(bool uninitialisedOnly) {
}

void pushconv2d_to_conv2d_1_synConnectivityToDevice(bool uninitialisedOnly) {
}

void pushinSynconv2d_1_to_dense_synToDevice(bool uninitialisedOnly) {
}

void pushconv2d_1_to_dense_synStateToDevice(bool uninitialisedOnly) {
    pushinSynconv2d_1_to_dense_synToDevice(uninitialisedOnly);
}

void pushgconv2d_input_to_conv2d_synToDevice(bool uninitialisedOnly) {
}

void pushinSynconv2d_input_to_conv2d_synToDevice(bool uninitialisedOnly) {
}

void pushconv2d_input_to_conv2d_synStateToDevice(bool uninitialisedOnly) {
    pushgconv2d_input_to_conv2d_synToDevice(uninitialisedOnly);
    pushinSynconv2d_input_to_conv2d_synToDevice(uninitialisedOnly);
}

void pushgconv2d_to_conv2d_1_synToDevice(bool uninitialisedOnly) {
}

void pushinSynconv2d_to_conv2d_1_synToDevice(bool uninitialisedOnly) {
}

void pushconv2d_to_conv2d_1_synStateToDevice(bool uninitialisedOnly) {
    pushgconv2d_to_conv2d_1_synToDevice(uninitialisedOnly);
    pushinSynconv2d_to_conv2d_1_synToDevice(uninitialisedOnly);
}

void pushgdense_1_to_dense_2_synToDevice(bool uninitialisedOnly) {
}

void pushinSyndense_1_to_dense_2_synToDevice(bool uninitialisedOnly) {
}

void pushdense_1_to_dense_2_synStateToDevice(bool uninitialisedOnly) {
    pushgdense_1_to_dense_2_synToDevice(uninitialisedOnly);
    pushinSyndense_1_to_dense_2_synToDevice(uninitialisedOnly);
}

void pushgdense_to_dense_1_synToDevice(bool uninitialisedOnly) {
}

void pushinSyndense_to_dense_1_synToDevice(bool uninitialisedOnly) {
}

void pushdense_to_dense_1_synStateToDevice(bool uninitialisedOnly) {
    pushgdense_to_dense_1_synToDevice(uninitialisedOnly);
    pushinSyndense_to_dense_1_synToDevice(uninitialisedOnly);
}


// ------------------------------------------------------------------------
// copying things from device
// ------------------------------------------------------------------------
void pullconv2d_1_nrnSpikesFromDevice() {
}

void pullconv2d_1_nrnCurrentSpikesFromDevice() {
}

void pullFxconv2d_1_nrnFromDevice() {
}

void pullCurrentFxconv2d_1_nrnFromDevice() {
}

void pullVmemconv2d_1_nrnFromDevice() {
}

void pullCurrentVmemconv2d_1_nrnFromDevice() {
}

void pullconv2d_1_nrnStateFromDevice() {
    pullFxconv2d_1_nrnFromDevice();
    pullVmemconv2d_1_nrnFromDevice();
}

void pullconv2d_input_nrnSpikesFromDevice() {
}

void pullconv2d_input_nrnCurrentSpikesFromDevice() {
}

void pullinputconv2d_input_nrnFromDevice() {
}

void pullCurrentinputconv2d_input_nrnFromDevice() {
}

void pullVmemconv2d_input_nrnFromDevice() {
}

void pullCurrentVmemconv2d_input_nrnFromDevice() {
}

void pullconv2d_input_nrnStateFromDevice() {
    pullinputconv2d_input_nrnFromDevice();
    pullVmemconv2d_input_nrnFromDevice();
}

void pullconv2d_nrnSpikesFromDevice() {
}

void pullconv2d_nrnCurrentSpikesFromDevice() {
}

void pullFxconv2d_nrnFromDevice() {
}

void pullCurrentFxconv2d_nrnFromDevice() {
}

void pullVmemconv2d_nrnFromDevice() {
}

void pullCurrentVmemconv2d_nrnFromDevice() {
}

void pullconv2d_nrnStateFromDevice() {
    pullFxconv2d_nrnFromDevice();
    pullVmemconv2d_nrnFromDevice();
}

void pulldense_1_nrnSpikesFromDevice() {
}

void pulldense_1_nrnCurrentSpikesFromDevice() {
}

void pullFxdense_1_nrnFromDevice() {
}

void pullCurrentFxdense_1_nrnFromDevice() {
}

void pullVmemdense_1_nrnFromDevice() {
}

void pullCurrentVmemdense_1_nrnFromDevice() {
}

void pulldense_1_nrnStateFromDevice() {
    pullFxdense_1_nrnFromDevice();
    pullVmemdense_1_nrnFromDevice();
}

void pulldense_2_nrnSpikesFromDevice() {
}

void pulldense_2_nrnCurrentSpikesFromDevice() {
}

void pullFxdense_2_nrnFromDevice() {
}

void pullCurrentFxdense_2_nrnFromDevice() {
}

void pullVmemdense_2_nrnFromDevice() {
}

void pullCurrentVmemdense_2_nrnFromDevice() {
}

void pulldense_2_nrnStateFromDevice() {
    pullFxdense_2_nrnFromDevice();
    pullVmemdense_2_nrnFromDevice();
}

void pulldense_nrnSpikesFromDevice() {
}

void pulldense_nrnCurrentSpikesFromDevice() {
}

void pullFxdense_nrnFromDevice() {
}

void pullCurrentFxdense_nrnFromDevice() {
}

void pullVmemdense_nrnFromDevice() {
}

void pullCurrentVmemdense_nrnFromDevice() {
}

void pulldense_nrnStateFromDevice() {
    pullFxdense_nrnFromDevice();
    pullVmemdense_nrnFromDevice();
}

void pullconv2d_input_to_conv2d_synConnectivityFromDevice() {
}

void pullconv2d_to_conv2d_1_synConnectivityFromDevice() {
}

void pullinSynconv2d_1_to_dense_synFromDevice() {
}

void pullconv2d_1_to_dense_synStateFromDevice() {
    pullinSynconv2d_1_to_dense_synFromDevice();
}

void pullgconv2d_input_to_conv2d_synFromDevice() {
}

void pullinSynconv2d_input_to_conv2d_synFromDevice() {
}

void pullconv2d_input_to_conv2d_synStateFromDevice() {
    pullgconv2d_input_to_conv2d_synFromDevice();
    pullinSynconv2d_input_to_conv2d_synFromDevice();
}

void pullgconv2d_to_conv2d_1_synFromDevice() {
}

void pullinSynconv2d_to_conv2d_1_synFromDevice() {
}

void pullconv2d_to_conv2d_1_synStateFromDevice() {
    pullgconv2d_to_conv2d_1_synFromDevice();
    pullinSynconv2d_to_conv2d_1_synFromDevice();
}

void pullgdense_1_to_dense_2_synFromDevice() {
}

void pullinSyndense_1_to_dense_2_synFromDevice() {
}

void pulldense_1_to_dense_2_synStateFromDevice() {
    pullgdense_1_to_dense_2_synFromDevice();
    pullinSyndense_1_to_dense_2_synFromDevice();
}

void pullgdense_to_dense_1_synFromDevice() {
}

void pullinSyndense_to_dense_1_synFromDevice() {
}

void pulldense_to_dense_1_synStateFromDevice() {
    pullgdense_to_dense_1_synFromDevice();
    pullinSyndense_to_dense_1_synFromDevice();
}


// ------------------------------------------------------------------------
// helper getter functions
// ------------------------------------------------------------------------
unsigned int* getconv2d_1_nrnCurrentSpikes(unsigned int batch) {
    return (glbSpkconv2d_1_nrn);
}

unsigned int& getconv2d_1_nrnCurrentSpikeCount(unsigned int batch) {
    return glbSpkCntconv2d_1_nrn[0];
}

scalar* getCurrentFxconv2d_1_nrn(unsigned int batch) {
    return Fxconv2d_1_nrn;
}

scalar* getCurrentVmemconv2d_1_nrn(unsigned int batch) {
    return Vmemconv2d_1_nrn;
}

unsigned int* getconv2d_input_nrnCurrentSpikes(unsigned int batch) {
    return (glbSpkconv2d_input_nrn);
}

unsigned int& getconv2d_input_nrnCurrentSpikeCount(unsigned int batch) {
    return glbSpkCntconv2d_input_nrn[0];
}

scalar* getCurrentinputconv2d_input_nrn(unsigned int batch) {
    return inputconv2d_input_nrn;
}

scalar* getCurrentVmemconv2d_input_nrn(unsigned int batch) {
    return Vmemconv2d_input_nrn;
}

unsigned int* getconv2d_nrnCurrentSpikes(unsigned int batch) {
    return (glbSpkconv2d_nrn);
}

unsigned int& getconv2d_nrnCurrentSpikeCount(unsigned int batch) {
    return glbSpkCntconv2d_nrn[0];
}

scalar* getCurrentFxconv2d_nrn(unsigned int batch) {
    return Fxconv2d_nrn;
}

scalar* getCurrentVmemconv2d_nrn(unsigned int batch) {
    return Vmemconv2d_nrn;
}

unsigned int* getdense_1_nrnCurrentSpikes(unsigned int batch) {
    return (glbSpkdense_1_nrn);
}

unsigned int& getdense_1_nrnCurrentSpikeCount(unsigned int batch) {
    return glbSpkCntdense_1_nrn[0];
}

scalar* getCurrentFxdense_1_nrn(unsigned int batch) {
    return Fxdense_1_nrn;
}

scalar* getCurrentVmemdense_1_nrn(unsigned int batch) {
    return Vmemdense_1_nrn;
}

unsigned int* getdense_2_nrnCurrentSpikes(unsigned int batch) {
    return (glbSpkdense_2_nrn);
}

unsigned int& getdense_2_nrnCurrentSpikeCount(unsigned int batch) {
    return glbSpkCntdense_2_nrn[0];
}

scalar* getCurrentFxdense_2_nrn(unsigned int batch) {
    return Fxdense_2_nrn;
}

scalar* getCurrentVmemdense_2_nrn(unsigned int batch) {
    return Vmemdense_2_nrn;
}

unsigned int* getdense_nrnCurrentSpikes(unsigned int batch) {
    return (glbSpkdense_nrn);
}

unsigned int& getdense_nrnCurrentSpikeCount(unsigned int batch) {
    return glbSpkCntdense_nrn[0];
}

scalar* getCurrentFxdense_nrn(unsigned int batch) {
    return Fxdense_nrn;
}

scalar* getCurrentVmemdense_nrn(unsigned int batch) {
    return Vmemdense_nrn;
}


void copyStateToDevice(bool uninitialisedOnly) {
    pushconv2d_1_nrnStateToDevice(uninitialisedOnly);
    pushconv2d_input_nrnStateToDevice(uninitialisedOnly);
    pushconv2d_nrnStateToDevice(uninitialisedOnly);
    pushdense_1_nrnStateToDevice(uninitialisedOnly);
    pushdense_2_nrnStateToDevice(uninitialisedOnly);
    pushdense_nrnStateToDevice(uninitialisedOnly);
    pushconv2d_1_to_dense_synStateToDevice(uninitialisedOnly);
    pushconv2d_input_to_conv2d_synStateToDevice(uninitialisedOnly);
    pushconv2d_to_conv2d_1_synStateToDevice(uninitialisedOnly);
    pushdense_1_to_dense_2_synStateToDevice(uninitialisedOnly);
    pushdense_to_dense_1_synStateToDevice(uninitialisedOnly);
}

void copyConnectivityToDevice(bool uninitialisedOnly) {
    pushconv2d_input_to_conv2d_synConnectivityToDevice(uninitialisedOnly);
    pushconv2d_to_conv2d_1_synConnectivityToDevice(uninitialisedOnly);
}

void copyStateFromDevice() {
    pullconv2d_1_nrnStateFromDevice();
    pullconv2d_input_nrnStateFromDevice();
    pullconv2d_nrnStateFromDevice();
    pulldense_1_nrnStateFromDevice();
    pulldense_2_nrnStateFromDevice();
    pulldense_nrnStateFromDevice();
    pullconv2d_1_to_dense_synStateFromDevice();
    pullconv2d_input_to_conv2d_synStateFromDevice();
    pullconv2d_to_conv2d_1_synStateFromDevice();
    pulldense_1_to_dense_2_synStateFromDevice();
    pulldense_to_dense_1_synStateFromDevice();
}

void copyCurrentSpikesFromDevice() {
    pullconv2d_1_nrnCurrentSpikesFromDevice();
    pullconv2d_input_nrnCurrentSpikesFromDevice();
    pullconv2d_nrnCurrentSpikesFromDevice();
    pulldense_1_nrnCurrentSpikesFromDevice();
    pulldense_2_nrnCurrentSpikesFromDevice();
    pulldense_nrnCurrentSpikesFromDevice();
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
    glbSpkCntconv2d_1_nrn = new unsigned int[1];
    glbSpkconv2d_1_nrn = new unsigned int[512];
    Fxconv2d_1_nrn = new scalar[512];
    Vmemconv2d_1_nrn = new scalar[512];
    glbSpkCntconv2d_input_nrn = new unsigned int[1];
    glbSpkconv2d_input_nrn = new unsigned int[784];
    inputconv2d_input_nrn = new scalar[784];
    Vmemconv2d_input_nrn = new scalar[784];
    glbSpkCntconv2d_nrn = new unsigned int[1];
    glbSpkconv2d_nrn = new unsigned int[9216];
    Fxconv2d_nrn = new scalar[9216];
    Vmemconv2d_nrn = new scalar[9216];
    glbSpkCntdense_1_nrn = new unsigned int[1];
    glbSpkdense_1_nrn = new unsigned int[64];
    Fxdense_1_nrn = new scalar[64];
    Vmemdense_1_nrn = new scalar[64];
    glbSpkCntdense_2_nrn = new unsigned int[1];
    glbSpkdense_2_nrn = new unsigned int[10];
    Fxdense_2_nrn = new scalar[10];
    Vmemdense_2_nrn = new scalar[10];
    glbSpkCntdense_nrn = new unsigned int[1];
    glbSpkdense_nrn = new unsigned int[128];
    Fxdense_nrn = new scalar[128];
    Vmemdense_nrn = new scalar[128];
    
    // ------------------------------------------------------------------------
    // custom update variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // pre and postsynaptic variables
    // ------------------------------------------------------------------------
    inSynconv2d_to_conv2d_1_syn = new float[512];
    inSynconv2d_input_to_conv2d_syn = new float[9216];
    inSyndense_to_dense_1_syn = new float[64];
    inSyndense_1_to_dense_2_syn = new float[10];
    inSynconv2d_1_to_dense_syn = new float[128];
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    rowLengthconv2d_input_to_conv2d_syn = new unsigned int[784];
    indconv2d_input_to_conv2d_syn = new uint32_t[313600];
    rowLengthconv2d_to_conv2d_1_syn = new unsigned int[9216];
    indconv2d_to_conv2d_1_syn = new uint32_t[1843200];
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    gconv2d_input_to_conv2d_syn = new scalar[313600];
    gconv2d_to_conv2d_1_syn = new scalar[1843200];
    gdense_1_to_dense_2_syn = new scalar[640];
    gdense_to_dense_1_syn = new scalar[8192];
    
    pushMergedNeuronInitGroup0ToDevice(0, glbSpkCntconv2d_1_nrn, glbSpkconv2d_1_nrn, Fxconv2d_1_nrn, Vmemconv2d_1_nrn, inSynconv2d_to_conv2d_1_syn, 512);
    pushMergedNeuronInitGroup0ToDevice(1, glbSpkCntconv2d_nrn, glbSpkconv2d_nrn, Fxconv2d_nrn, Vmemconv2d_nrn, inSynconv2d_input_to_conv2d_syn, 9216);
    pushMergedNeuronInitGroup0ToDevice(2, glbSpkCntdense_1_nrn, glbSpkdense_1_nrn, Fxdense_1_nrn, Vmemdense_1_nrn, inSyndense_to_dense_1_syn, 64);
    pushMergedNeuronInitGroup0ToDevice(3, glbSpkCntdense_2_nrn, glbSpkdense_2_nrn, Fxdense_2_nrn, Vmemdense_2_nrn, inSyndense_1_to_dense_2_syn, 10);
    pushMergedNeuronInitGroup0ToDevice(4, glbSpkCntdense_nrn, glbSpkdense_nrn, Fxdense_nrn, Vmemdense_nrn, inSynconv2d_1_to_dense_syn, 128);
    pushMergedNeuronInitGroup1ToDevice(0, glbSpkCntconv2d_input_nrn, glbSpkconv2d_input_nrn, inputconv2d_input_nrn, Vmemconv2d_input_nrn, 784);
    pushMergedSynapseConnectivityInitGroup0ToDevice(0, rowLengthconv2d_input_to_conv2d_syn, indconv2d_input_to_conv2d_syn, gconv2d_input_to_conv2d_syn, kernelgconv2d_input_to_conv2d_syn, 400, 784, 9216);
    pushMergedSynapseConnectivityInitGroup1ToDevice(0, rowLengthconv2d_to_conv2d_1_syn, indconv2d_to_conv2d_1_syn, gconv2d_to_conv2d_1_syn, kernelgconv2d_to_conv2d_1_syn, 200, 9216, 512);
    pushMergedNeuronUpdateGroup0ToDevice(0, glbSpkCntconv2d_input_nrn, glbSpkconv2d_input_nrn, inputconv2d_input_nrn, Vmemconv2d_input_nrn, 784);
    pushMergedNeuronUpdateGroup1ToDevice(0, glbSpkCntconv2d_1_nrn, glbSpkconv2d_1_nrn, Fxconv2d_1_nrn, Vmemconv2d_1_nrn, inSynconv2d_to_conv2d_1_syn, 512, 8.24664522058823479e+00f, 2.72428744446997539e+00f, 3.22134578929227922e-02f, 1.06417478299608414e-02f);
    pushMergedNeuronUpdateGroup1ToDevice(1, glbSpkCntconv2d_nrn, glbSpkconv2d_nrn, Fxconv2d_nrn, Vmemconv2d_nrn, inSynconv2d_input_to_conv2d_syn, 9216, 2.72428744446997539e+00f, 1.00392156862745097e+00f, 1.06417478299608414e-02f, 3.92156862745098034e-03f);
    pushMergedNeuronUpdateGroup1ToDevice(2, glbSpkCntdense_1_nrn, glbSpkdense_1_nrn, Fxdense_1_nrn, Vmemdense_1_nrn, inSyndense_to_dense_1_syn, 64, 1.59408863740808826e+01f, 9.44853419883578383e+00f, 6.22690873987534477e-02f, 3.69083367142022806e-02f);
    pushMergedNeuronUpdateGroup1ToDevice(3, glbSpkCntdense_2_nrn, glbSpkdense_2_nrn, Fxdense_2_nrn, Vmemdense_2_nrn, inSyndense_1_to_dense_2_syn, 10, 1.00392156862745097e+00f, 1.59408863740808826e+01f, 3.92156862745098034e-03f, 6.22690873987534477e-02f);
    pushMergedNeuronUpdateGroup1ToDevice(4, glbSpkCntdense_nrn, glbSpkdense_nrn, Fxdense_nrn, Vmemdense_nrn, inSynconv2d_1_to_dense_syn, 128, 9.44853419883578383e+00f, 8.24664522058823479e+00f, 3.69083367142022806e-02f, 3.22134578929227922e-02f);
    pushMergedPresynapticUpdateGroup0ToDevice(0, inSynconv2d_1_to_dense_syn, glbSpkCntconv2d_1_nrn, glbSpkconv2d_1_nrn, weightsgconv2d_1_to_dense_syn, 128, 512, 128);
    pushMergedPresynapticUpdateGroup1ToDevice(0, inSynconv2d_input_to_conv2d_syn, glbSpkCntconv2d_input_nrn, glbSpkconv2d_input_nrn, rowLengthconv2d_input_to_conv2d_syn, indconv2d_input_to_conv2d_syn, gconv2d_input_to_conv2d_syn, 400, 784, 9216);
    pushMergedPresynapticUpdateGroup1ToDevice(1, inSynconv2d_to_conv2d_1_syn, glbSpkCntconv2d_nrn, glbSpkconv2d_nrn, rowLengthconv2d_to_conv2d_1_syn, indconv2d_to_conv2d_1_syn, gconv2d_to_conv2d_1_syn, 200, 9216, 512);
    pushMergedPresynapticUpdateGroup2ToDevice(0, inSyndense_1_to_dense_2_syn, glbSpkCntdense_1_nrn, glbSpkdense_1_nrn, gdense_1_to_dense_2_syn, 10, 64, 10);
    pushMergedPresynapticUpdateGroup2ToDevice(1, inSyndense_to_dense_1_syn, glbSpkCntdense_nrn, glbSpkdense_nrn, gdense_to_dense_1_syn, 64, 128, 64);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(0, glbSpkCntconv2d_1_nrn);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(1, glbSpkCntconv2d_input_nrn);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(2, glbSpkCntconv2d_nrn);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(3, glbSpkCntdense_1_nrn);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(4, glbSpkCntdense_nrn);
    pushMergedNeuronSpikeQueueUpdateGroup1ToDevice(0, glbSpkCntdense_2_nrn);
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
    delete[] glbSpkCntconv2d_1_nrn;
    delete[] glbSpkconv2d_1_nrn;
    delete[] Fxconv2d_1_nrn;
    delete[] Vmemconv2d_1_nrn;
    delete[] glbSpkCntconv2d_input_nrn;
    delete[] glbSpkconv2d_input_nrn;
    delete[] inputconv2d_input_nrn;
    delete[] Vmemconv2d_input_nrn;
    delete[] glbSpkCntconv2d_nrn;
    delete[] glbSpkconv2d_nrn;
    delete[] Fxconv2d_nrn;
    delete[] Vmemconv2d_nrn;
    delete[] glbSpkCntdense_1_nrn;
    delete[] glbSpkdense_1_nrn;
    delete[] Fxdense_1_nrn;
    delete[] Vmemdense_1_nrn;
    delete[] glbSpkCntdense_2_nrn;
    delete[] glbSpkdense_2_nrn;
    delete[] Fxdense_2_nrn;
    delete[] Vmemdense_2_nrn;
    delete[] glbSpkCntdense_nrn;
    delete[] glbSpkdense_nrn;
    delete[] Fxdense_nrn;
    delete[] Vmemdense_nrn;
    
    // ------------------------------------------------------------------------
    // custom update variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // pre and postsynaptic variables
    // ------------------------------------------------------------------------
    delete[] inSynconv2d_to_conv2d_1_syn;
    delete[] inSynconv2d_input_to_conv2d_syn;
    delete[] inSyndense_to_dense_1_syn;
    delete[] inSyndense_1_to_dense_2_syn;
    delete[] inSynconv2d_1_to_dense_syn;
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    delete[] rowLengthconv2d_input_to_conv2d_syn;
    delete[] indconv2d_input_to_conv2d_syn;
    delete[] rowLengthconv2d_to_conv2d_1_syn;
    delete[] indconv2d_to_conv2d_1_syn;
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    delete[] gconv2d_input_to_conv2d_syn;
    delete[] gconv2d_to_conv2d_1_syn;
    delete[] gdense_1_to_dense_2_syn;
    delete[] gdense_to_dense_1_syn;
    
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

