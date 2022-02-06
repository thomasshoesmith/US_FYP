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
float* inSynconv2d_1_to_dense_syn;

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------
const unsigned int maxRowLengthconv2d_input_to_conv2d_syn = 288;
unsigned int* rowLengthconv2d_input_to_conv2d_syn;
uint32_t* indconv2d_input_to_conv2d_syn;
const unsigned int maxRowLengthconv2d_to_conv2d_1_syn = 288;
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
    pushMergedSynapseConnectivityInit0kernelgToDevice(1, kernelgconv2d_to_conv2d_1_syn);
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
    pushdense_nrnStateToDevice(uninitialisedOnly);
    pushconv2d_1_to_dense_synStateToDevice(uninitialisedOnly);
    pushconv2d_input_to_conv2d_synStateToDevice(uninitialisedOnly);
    pushconv2d_to_conv2d_1_synStateToDevice(uninitialisedOnly);
}

void copyConnectivityToDevice(bool uninitialisedOnly) {
    pushconv2d_input_to_conv2d_synConnectivityToDevice(uninitialisedOnly);
    pushconv2d_to_conv2d_1_synConnectivityToDevice(uninitialisedOnly);
}

void copyStateFromDevice() {
    pullconv2d_1_nrnStateFromDevice();
    pullconv2d_input_nrnStateFromDevice();
    pullconv2d_nrnStateFromDevice();
    pulldense_nrnStateFromDevice();
    pullconv2d_1_to_dense_synStateFromDevice();
    pullconv2d_input_to_conv2d_synStateFromDevice();
    pullconv2d_to_conv2d_1_synStateFromDevice();
}

void copyCurrentSpikesFromDevice() {
    pullconv2d_1_nrnCurrentSpikesFromDevice();
    pullconv2d_input_nrnCurrentSpikesFromDevice();
    pullconv2d_nrnCurrentSpikesFromDevice();
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
    glbSpkconv2d_1_nrn = new unsigned int[32768];
    Fxconv2d_1_nrn = new scalar[32768];
    Vmemconv2d_1_nrn = new scalar[32768];
    glbSpkCntconv2d_input_nrn = new unsigned int[1];
    glbSpkconv2d_input_nrn = new unsigned int[3072];
    inputconv2d_input_nrn = new scalar[3072];
    Vmemconv2d_input_nrn = new scalar[3072];
    glbSpkCntconv2d_nrn = new unsigned int[1];
    glbSpkconv2d_nrn = new unsigned int[32768];
    Fxconv2d_nrn = new scalar[32768];
    Vmemconv2d_nrn = new scalar[32768];
    glbSpkCntdense_nrn = new unsigned int[1];
    glbSpkdense_nrn = new unsigned int[10];
    Fxdense_nrn = new scalar[10];
    Vmemdense_nrn = new scalar[10];
    
    // ------------------------------------------------------------------------
    // custom update variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // pre and postsynaptic variables
    // ------------------------------------------------------------------------
    inSynconv2d_to_conv2d_1_syn = new float[32768];
    inSynconv2d_input_to_conv2d_syn = new float[32768];
    inSynconv2d_1_to_dense_syn = new float[10];
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    rowLengthconv2d_input_to_conv2d_syn = new unsigned int[3072];
    indconv2d_input_to_conv2d_syn = new uint32_t[884736];
    rowLengthconv2d_to_conv2d_1_syn = new unsigned int[32768];
    indconv2d_to_conv2d_1_syn = new uint32_t[9437184];
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    gconv2d_input_to_conv2d_syn = new scalar[884736];
    gconv2d_to_conv2d_1_syn = new scalar[9437184];
    
    pushMergedNeuronInitGroup0ToDevice(0, glbSpkCntconv2d_1_nrn, glbSpkconv2d_1_nrn, Fxconv2d_1_nrn, Vmemconv2d_1_nrn, inSynconv2d_to_conv2d_1_syn, 32768);
    pushMergedNeuronInitGroup0ToDevice(1, glbSpkCntconv2d_nrn, glbSpkconv2d_nrn, Fxconv2d_nrn, Vmemconv2d_nrn, inSynconv2d_input_to_conv2d_syn, 32768);
    pushMergedNeuronInitGroup0ToDevice(2, glbSpkCntdense_nrn, glbSpkdense_nrn, Fxdense_nrn, Vmemdense_nrn, inSynconv2d_1_to_dense_syn, 10);
    pushMergedNeuronInitGroup1ToDevice(0, glbSpkCntconv2d_input_nrn, glbSpkconv2d_input_nrn, inputconv2d_input_nrn, Vmemconv2d_input_nrn, 3072);
    pushMergedSynapseConnectivityInitGroup0ToDevice(0, rowLengthconv2d_input_to_conv2d_syn, indconv2d_input_to_conv2d_syn, gconv2d_input_to_conv2d_syn, kernelgconv2d_input_to_conv2d_syn, 288, 3072, 32768, 3.00000000000000000e+00f, 3);
    pushMergedSynapseConnectivityInitGroup0ToDevice(1, rowLengthconv2d_to_conv2d_1_syn, indconv2d_to_conv2d_1_syn, gconv2d_to_conv2d_1_syn, kernelgconv2d_to_conv2d_1_syn, 288, 32768, 32768, 3.20000000000000000e+01f, 32);
    pushMergedNeuronUpdateGroup0ToDevice(0, glbSpkCntconv2d_input_nrn, glbSpkconv2d_input_nrn, inputconv2d_input_nrn, Vmemconv2d_input_nrn, 3072);
    pushMergedNeuronUpdateGroup1ToDevice(0, glbSpkCntconv2d_1_nrn, glbSpkconv2d_1_nrn, Fxconv2d_1_nrn, Vmemconv2d_1_nrn, inSynconv2d_to_conv2d_1_syn, 32768, 2.80759109796262241e+00f, 8.79895258884803910e-01f, 1.09671527264164938e-02f, 3.43709085501876527e-03f);
    pushMergedNeuronUpdateGroup1ToDevice(1, glbSpkCntconv2d_nrn, glbSpkconv2d_nrn, Fxconv2d_nrn, Vmemconv2d_nrn, inSynconv2d_input_to_conv2d_syn, 32768, 8.79895258884803910e-01f, 1.00392156862745097e+00f, 3.43709085501876527e-03f, 3.92156862745098034e-03f);
    pushMergedNeuronUpdateGroup1ToDevice(2, glbSpkCntdense_nrn, glbSpkdense_nrn, Fxdense_nrn, Vmemdense_nrn, inSynconv2d_1_to_dense_syn, 10, 9.79877666398590641e-01f, 2.80759109796262241e+00f, 3.82764713436949469e-03f, 1.09671527264164938e-02f);
    pushMergedPresynapticUpdateGroup0ToDevice(0, inSynconv2d_1_to_dense_syn, glbSpkCntconv2d_1_nrn, glbSpkconv2d_1_nrn, weightsgconv2d_1_to_dense_syn, 10, 32768, 10);
    pushMergedPresynapticUpdateGroup1ToDevice(0, inSynconv2d_input_to_conv2d_syn, glbSpkCntconv2d_input_nrn, glbSpkconv2d_input_nrn, rowLengthconv2d_input_to_conv2d_syn, indconv2d_input_to_conv2d_syn, gconv2d_input_to_conv2d_syn, 288, 3072, 32768);
    pushMergedPresynapticUpdateGroup1ToDevice(1, inSynconv2d_to_conv2d_1_syn, glbSpkCntconv2d_nrn, glbSpkconv2d_nrn, rowLengthconv2d_to_conv2d_1_syn, indconv2d_to_conv2d_1_syn, gconv2d_to_conv2d_1_syn, 288, 32768, 32768);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(0, glbSpkCntconv2d_1_nrn);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(1, glbSpkCntconv2d_input_nrn);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(2, glbSpkCntconv2d_nrn);
    pushMergedNeuronSpikeQueueUpdateGroup1ToDevice(0, glbSpkCntdense_nrn);
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

