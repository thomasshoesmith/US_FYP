#include "definitionsInternal.h"
struct MergedNeuronInitGroup0
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* Fx;
    scalar* Vmem;
    float* inSynInSyn0;
    unsigned int numNeurons;
    
}
;
struct MergedNeuronInitGroup1
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* input;
    scalar* Vmem;
    unsigned int numNeurons;
    
}
;
struct MergedSynapseConnectivityInitGroup0
 {
    unsigned int* rowLength;
    uint32_t* ind;
    scalar* g;
    scalar* kernelg;
    unsigned int rowStride;
    unsigned int numSrcNeurons;
    unsigned int numTrgNeurons;
    scalar conv_ic;
    unsigned int kernelSize2;
    
}
;
static MergedNeuronInitGroup0 mergedNeuronInitGroup0[3];
void pushMergedNeuronInitGroup0ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* Fx, scalar* Vmem, float* inSynInSyn0, unsigned int numNeurons) {
    mergedNeuronInitGroup0[idx].spkCnt = spkCnt;
    mergedNeuronInitGroup0[idx].spk = spk;
    mergedNeuronInitGroup0[idx].Fx = Fx;
    mergedNeuronInitGroup0[idx].Vmem = Vmem;
    mergedNeuronInitGroup0[idx].inSynInSyn0 = inSynInSyn0;
    mergedNeuronInitGroup0[idx].numNeurons = numNeurons;
}
static MergedNeuronInitGroup1 mergedNeuronInitGroup1[1];
void pushMergedNeuronInitGroup1ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* input, scalar* Vmem, unsigned int numNeurons) {
    mergedNeuronInitGroup1[idx].spkCnt = spkCnt;
    mergedNeuronInitGroup1[idx].spk = spk;
    mergedNeuronInitGroup1[idx].input = input;
    mergedNeuronInitGroup1[idx].Vmem = Vmem;
    mergedNeuronInitGroup1[idx].numNeurons = numNeurons;
}
static MergedSynapseConnectivityInitGroup0 mergedSynapseConnectivityInitGroup0[2];
void pushMergedSynapseConnectivityInitGroup0ToDevice(unsigned int idx, unsigned int* rowLength, uint32_t* ind, scalar* g, scalar* kernelg, unsigned int rowStride, unsigned int numSrcNeurons, unsigned int numTrgNeurons, scalar conv_ic, unsigned int kernelSize2) {
    mergedSynapseConnectivityInitGroup0[idx].rowLength = rowLength;
    mergedSynapseConnectivityInitGroup0[idx].ind = ind;
    mergedSynapseConnectivityInitGroup0[idx].g = g;
    mergedSynapseConnectivityInitGroup0[idx].kernelg = kernelg;
    mergedSynapseConnectivityInitGroup0[idx].rowStride = rowStride;
    mergedSynapseConnectivityInitGroup0[idx].numSrcNeurons = numSrcNeurons;
    mergedSynapseConnectivityInitGroup0[idx].numTrgNeurons = numTrgNeurons;
    mergedSynapseConnectivityInitGroup0[idx].conv_ic = conv_ic;
    mergedSynapseConnectivityInitGroup0[idx].kernelSize2 = kernelSize2;
}
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
void pushMergedSynapseConnectivityInit0kernelgToDevice(unsigned int idx, scalar* value) {
    mergedSynapseConnectivityInitGroup0[idx].kernelg = value;
}

void initialize() {
    // ------------------------------------------------------------------------
    // Local neuron groups
     {
        // merged neuron init group 0
        for(unsigned int g = 0; g < 3; g++) {
            const auto *group = &mergedNeuronInitGroup0[g]; 
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
     {
        // merged synapse connectivity init group 0
        for(unsigned int g = 0; g < 2; g++) {
            const auto *group = &mergedSynapseConnectivityInitGroup0[g]; 
            memset(group->rowLength, 0, group->numSrcNeurons * sizeof(unsigned int));
            for (unsigned int i = 0; i < group->numSrcNeurons; i++) {
                // Build sparse connectivity
                int inRow = (i / (int)group->conv_ic) / (int)(3.20000000000000000e+01f);
                int inCol = (i / (int)group->conv_ic) % (int)(3.20000000000000000e+01f);
                int inChan = i % (int)group->conv_ic;
                int outRow = min((int)(3.20000000000000000e+01f), max(0, 1 + (int)floor((inRow + (1.00000000000000000e+00f) - (3.00000000000000000e+00f)) / (1.00000000000000000e+00f))));
                int maxOutRow = min((int)(3.20000000000000000e+01f), max(0, 1 + ((inRow + (int)(1.00000000000000000e+00f)) / (int)(1.00000000000000000e+00f))));
                int minOutCol = min((int)(3.20000000000000000e+01f), max(0, 1 + (int)floor((inCol + (1.00000000000000000e+00f) - (3.00000000000000000e+00f)) / (1.00000000000000000e+00f))));
                int maxOutCol = min((int)(3.20000000000000000e+01f), max(0, 1 + ((inCol + (int)(1.00000000000000000e+00f)) / (int)(1.00000000000000000e+00f))));
                while(true) {
                    if(outRow == maxOutRow) {
                       break;
                    }
                    const int strideRow = (outRow * (int)(1.00000000000000000e+00f)) - (int)(1.00000000000000000e+00f);
                    const int kernRow = inRow - strideRow;
                    for(int outCol = minOutCol; outCol < maxOutCol; outCol++) {
                        const int strideCol = (outCol * (int)(1.00000000000000000e+00f)) - (int)(1.00000000000000000e+00f);
                        const int kernCol = inCol - strideCol;
                        for(unsigned int outChan = 0; outChan < (unsigned int)(3.20000000000000000e+01f); outChan++) {
                            const int idPost = ((outRow * (int)(3.20000000000000000e+01f) * (int)(3.20000000000000000e+01f)) +
                                                (outCol * (int)(3.20000000000000000e+01f)) +
                                                outChan);
                            do {
                        const unsigned int idx = (i * group->rowStride) + group->rowLength[i];
                        const unsigned int kernelInd = (kernRow * 3 * group->kernelSize2 * 32) + (kernCol * group->kernelSize2 * 32) + (inChan * 32) + (outChan);
                         {
                            scalar initVal;
                            initVal = group->kernelg[kernelInd];
                            group->g[idx] = initVal;
                        }
                        group->ind[idx] = idPost;
                        group->rowLength[i]++;
                    }
                    while(false);
                        }
                    }
                    outRow++;
                    
                }
            }
        }
    }
}

void initializeSparse() {
    // ------------------------------------------------------------------------
    // Synapse groups with sparse connectivity
    // ------------------------------------------------------------------------
    // Custom sparse WU update groups
}
