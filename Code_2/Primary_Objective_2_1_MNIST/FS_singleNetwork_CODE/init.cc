#include "definitionsInternal.h"
struct MergedNeuronInitGroup0
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* input;
    scalar* Vmem;
    scalar* scaleVal;
    unsigned int numNeurons;
    
}
;
struct MergedNeuronInitGroup1
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* Fx;
    scalar* Vmem;
    float* inSynInSyn0;
    unsigned int numNeurons;
    
}
;
static MergedNeuronInitGroup0 mergedNeuronInitGroup0[1];
void pushMergedNeuronInitGroup0ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* input, scalar* Vmem, scalar* scaleVal, unsigned int numNeurons) {
    mergedNeuronInitGroup0[idx].spkCnt = spkCnt;
    mergedNeuronInitGroup0[idx].spk = spk;
    mergedNeuronInitGroup0[idx].input = input;
    mergedNeuronInitGroup0[idx].Vmem = Vmem;
    mergedNeuronInitGroup0[idx].scaleVal = scaleVal;
    mergedNeuronInitGroup0[idx].numNeurons = numNeurons;
}
static MergedNeuronInitGroup1 mergedNeuronInitGroup1[1];
void pushMergedNeuronInitGroup1ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* Fx, scalar* Vmem, float* inSynInSyn0, unsigned int numNeurons) {
    mergedNeuronInitGroup1[idx].spkCnt = spkCnt;
    mergedNeuronInitGroup1[idx].spk = spk;
    mergedNeuronInitGroup1[idx].Fx = Fx;
    mergedNeuronInitGroup1[idx].Vmem = Vmem;
    mergedNeuronInitGroup1[idx].inSynInSyn0 = inSynInSyn0;
    mergedNeuronInitGroup1[idx].numNeurons = numNeurons;
}
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
void initialize() {
    // ------------------------------------------------------------------------
    // Local neuron groups
     {
        // merged neuron init group 0
        for(unsigned int g = 0; g < 1; g++) {
            const auto *group = &mergedNeuronInitGroup0[g]; 
            group->spkCnt[0] = 0;
            for (unsigned i = 0; i < (group->numNeurons); i++) {
                group->spk[i] = 0;
            }
             {
                for (unsigned i = 0; i < (group->numNeurons); i++) {
                    scalar initVal;
                    initVal = (1.70000000000000000e+01f);
                    group->input[i] = initVal;
                }
            }
             {
                for (unsigned i = 0; i < (group->numNeurons); i++) {
                    scalar initVal;
                    initVal = (0.00000000000000000e+00f);
                    group->Vmem[i] = initVal;
                }
            }
             {
                for (unsigned i = 0; i < (group->numNeurons); i++) {
                    scalar initVal;
                    initVal = (0.00000000000000000e+00f);
                    group->scaleVal[i] = initVal;
                }
            }
            // current source variables
        }
    }
     {
        // merged neuron init group 1
        for(unsigned int g = 0; g < 1; g++) {
            const auto *group = &mergedNeuronInitGroup1[g]; 
            group->spkCnt[0] = 0;
            for (unsigned i = 0; i < (group->numNeurons); i++) {
                group->spk[i] = 0;
            }
             {
                for (unsigned i = 0; i < (group->numNeurons); i++) {
                    scalar initVal;
                    initVal = (0.00000000000000000e+00f);
                    group->Fx[i] = initVal;
                }
            }
             {
                for (unsigned i = 0; i < (group->numNeurons); i++) {
                    scalar initVal;
                    initVal = (0.00000000000000000e+00f);
                    group->Vmem[i] = initVal;
                }
            }
             {
                for (unsigned i = 0; i < (group->numNeurons); i++) {
                    group->inSynInSyn0[i] = 0.000000000e+00f;
                }
            }
            // current source variables
        }
    }
    // ------------------------------------------------------------------------
    // Custom update groups
    // ------------------------------------------------------------------------
    // Custom dense WU update groups
    // ------------------------------------------------------------------------
    // Synapse groups with dense connectivity
    // ------------------------------------------------------------------------
    // Synapse groups with kernel connectivity
    // ------------------------------------------------------------------------
    // Synapse groups with sparse connectivity
}

void initializeSparse() {
    // ------------------------------------------------------------------------
    // Synapse groups with sparse connectivity
    // ------------------------------------------------------------------------
    // Custom sparse WU update groups
}
