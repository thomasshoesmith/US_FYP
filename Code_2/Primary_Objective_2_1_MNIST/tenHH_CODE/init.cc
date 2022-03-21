#include "definitionsInternal.h"
struct MergedNeuronInitGroup0
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* V;
    scalar* m;
    scalar* h;
    scalar* n;
    unsigned int numNeurons;
    
}
;
static MergedNeuronInitGroup0 mergedNeuronInitGroup0[1];
void pushMergedNeuronInitGroup0ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* m, scalar* h, scalar* n, unsigned int numNeurons) {
    mergedNeuronInitGroup0[idx].spkCnt = spkCnt;
    mergedNeuronInitGroup0[idx].spk = spk;
    mergedNeuronInitGroup0[idx].V = V;
    mergedNeuronInitGroup0[idx].m = m;
    mergedNeuronInitGroup0[idx].h = h;
    mergedNeuronInitGroup0[idx].n = n;
    mergedNeuronInitGroup0[idx].numNeurons = numNeurons;
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
                    initVal = (-6.00000000000000000e+01f);
                    group->V[i] = initVal;
                }
            }
             {
                for (unsigned i = 0; i < (group->numNeurons); i++) {
                    scalar initVal;
                    initVal = (5.29323999999999975e-02f);
                    group->m[i] = initVal;
                }
            }
             {
                for (unsigned i = 0; i < (group->numNeurons); i++) {
                    scalar initVal;
                    initVal = (3.17676699999999979e-01f);
                    group->h[i] = initVal;
                }
            }
             {
                for (unsigned i = 0; i < (group->numNeurons); i++) {
                    scalar initVal;
                    initVal = (5.96120699999999948e-01f);
                    group->n[i] = initVal;
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
