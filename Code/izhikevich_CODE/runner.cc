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
unsigned int* glbSpkCntPop;
unsigned int* glbSpkPop;
scalar* VPop;
scalar* UPop;
scalar* aPop;
scalar* bPop;
scalar* cPop;
scalar* dPop;
// current source variables

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
void pushPopSpikesToDevice(bool uninitialisedOnly) {
}

void pushPopCurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushVPopToDevice(bool uninitialisedOnly) {
}

void pushCurrentVPopToDevice(bool uninitialisedOnly) {
}

void pushUPopToDevice(bool uninitialisedOnly) {
}

void pushCurrentUPopToDevice(bool uninitialisedOnly) {
}

void pushaPopToDevice(bool uninitialisedOnly) {
}

void pushCurrentaPopToDevice(bool uninitialisedOnly) {
}

void pushbPopToDevice(bool uninitialisedOnly) {
}

void pushCurrentbPopToDevice(bool uninitialisedOnly) {
}

void pushcPopToDevice(bool uninitialisedOnly) {
}

void pushCurrentcPopToDevice(bool uninitialisedOnly) {
}

void pushdPopToDevice(bool uninitialisedOnly) {
}

void pushCurrentdPopToDevice(bool uninitialisedOnly) {
}

void pushPopStateToDevice(bool uninitialisedOnly) {
    pushVPopToDevice(uninitialisedOnly);
    pushUPopToDevice(uninitialisedOnly);
    pushaPopToDevice(uninitialisedOnly);
    pushbPopToDevice(uninitialisedOnly);
    pushcPopToDevice(uninitialisedOnly);
    pushdPopToDevice(uninitialisedOnly);
}

void pushCSStateToDevice(bool uninitialisedOnly) {
}


// ------------------------------------------------------------------------
// copying things from device
// ------------------------------------------------------------------------
void pullPopSpikesFromDevice() {
}

void pullPopCurrentSpikesFromDevice() {
}

void pullVPopFromDevice() {
}

void pullCurrentVPopFromDevice() {
}

void pullUPopFromDevice() {
}

void pullCurrentUPopFromDevice() {
}

void pullaPopFromDevice() {
}

void pullCurrentaPopFromDevice() {
}

void pullbPopFromDevice() {
}

void pullCurrentbPopFromDevice() {
}

void pullcPopFromDevice() {
}

void pullCurrentcPopFromDevice() {
}

void pulldPopFromDevice() {
}

void pullCurrentdPopFromDevice() {
}

void pullPopStateFromDevice() {
    pullVPopFromDevice();
    pullUPopFromDevice();
    pullaPopFromDevice();
    pullbPopFromDevice();
    pullcPopFromDevice();
    pulldPopFromDevice();
}

void pullCSStateFromDevice() {
}


// ------------------------------------------------------------------------
// helper getter functions
// ------------------------------------------------------------------------
unsigned int* getPopCurrentSpikes(unsigned int batch) {
    return (glbSpkPop);
}

unsigned int& getPopCurrentSpikeCount(unsigned int batch) {
    return glbSpkCntPop[0];
}

scalar* getCurrentVPop(unsigned int batch) {
    return VPop;
}

scalar* getCurrentUPop(unsigned int batch) {
    return UPop;
}

scalar* getCurrentaPop(unsigned int batch) {
    return aPop;
}

scalar* getCurrentbPop(unsigned int batch) {
    return bPop;
}

scalar* getCurrentcPop(unsigned int batch) {
    return cPop;
}

scalar* getCurrentdPop(unsigned int batch) {
    return dPop;
}


void copyStateToDevice(bool uninitialisedOnly) {
    pushPopStateToDevice(uninitialisedOnly);
    pushCSStateToDevice(uninitialisedOnly);
}

void copyConnectivityToDevice(bool uninitialisedOnly) {
}

void copyStateFromDevice() {
    pullPopStateFromDevice();
    pullCSStateFromDevice();
}

void copyCurrentSpikesFromDevice() {
    pullPopCurrentSpikesFromDevice();
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
    glbSpkCntPop = new unsigned int[1];
    glbSpkPop = new unsigned int[4];
    VPop = new scalar[4];
    UPop = new scalar[4];
    aPop = new scalar[4];
    bPop = new scalar[4];
    cPop = new scalar[4];
    dPop = new scalar[4];
    // current source variables
    
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
    
    pushMergedNeuronInitGroup0ToDevice(0, glbSpkCntPop, glbSpkPop, VPop, UPop, 4);
    pushMergedNeuronUpdateGroup0ToDevice(0, glbSpkCntPop, glbSpkPop, VPop, UPop, aPop, bPop, cPop, dPop, 4);
    pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(0, glbSpkCntPop);
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
    delete[] glbSpkCntPop;
    delete[] glbSpkPop;
    delete[] VPop;
    delete[] UPop;
    delete[] aPop;
    delete[] bPop;
    delete[] cPop;
    delete[] dPop;
    // current source variables
    
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

