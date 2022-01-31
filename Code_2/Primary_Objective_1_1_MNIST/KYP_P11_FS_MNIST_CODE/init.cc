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
    
}
;
struct MergedSynapseConnectivityInitGroup1
 {
    unsigned int* rowLength;
    uint32_t* ind;
    scalar* g;
    scalar* kernelg;
    unsigned int rowStride;
    unsigned int numSrcNeurons;
    unsigned int numTrgNeurons;
    
}
;
static MergedNeuronInitGroup0 mergedNeuronInitGroup0[5];
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
static MergedSynapseConnectivityInitGroup0 mergedSynapseConnectivityInitGroup0[1];
void pushMergedSynapseConnectivityInitGroup0ToDevice(unsigned int idx, unsigned int* rowLength, uint32_t* ind, scalar* g, scalar* kernelg, unsigned int rowStride, unsigned int numSrcNeurons, unsigned int numTrgNeurons) {
    mergedSynapseConnectivityInitGroup0[idx].rowLength = rowLength;
    mergedSynapseConnectivityInitGroup0[idx].ind = ind;
    mergedSynapseConnectivityInitGroup0[idx].g = g;
    mergedSynapseConnectivityInitGroup0[idx].kernelg = kernelg;
    mergedSynapseConnectivityInitGroup0[idx].rowStride = rowStride;
    mergedSynapseConnectivityInitGroup0[idx].numSrcNeurons = numSrcNeurons;
    mergedSynapseConnectivityInitGroup0[idx].numTrgNeurons = numTrgNeurons;
}
static MergedSynapseConnectivityInitGroup1 mergedSynapseConnectivityInitGroup1[1];
void pushMergedSynapseConnectivityInitGroup1ToDevice(unsigned int idx, unsigned int* rowLength, uint32_t* ind, scalar* g, scalar* kernelg, unsigned int rowStride, unsigned int numSrcNeurons, unsigned int numTrgNeurons) {
    mergedSynapseConnectivityInitGroup1[idx].rowLength = rowLength;
    mergedSynapseConnectivityInitGroup1[idx].ind = ind;
    mergedSynapseConnectivityInitGroup1[idx].g = g;
    mergedSynapseConnectivityInitGroup1[idx].kernelg = kernelg;
    mergedSynapseConnectivityInitGroup1[idx].rowStride = rowStride;
    mergedSynapseConnectivityInitGroup1[idx].numSrcNeurons = numSrcNeurons;
    mergedSynapseConnectivityInitGroup1[idx].numTrgNeurons = numTrgNeurons;
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

void pushMergedSynapseConnectivityInit1kernelgToDevice(unsigned int idx, scalar* value) {
    mergedSynapseConnectivityInitGroup1[idx].kernelg = value;
}

void initialize() {
    // ------------------------------------------------------------------------
    // Local neuron groups
     {
        // merged neuron init group 0
        for(unsigned int g = 0; g < 5; g++) {
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
        for(unsigned int g = 0; g < 1; g++) {
            const auto *group = &mergedSynapseConnectivityInitGroup0[g]; 
            memset(group->rowLength, 0, group->numSrcNeurons * sizeof(unsigned int));
            for (unsigned int i = 0; i < group->numSrcNeurons; i++) {
                // Build sparse connectivity
                int inRow = (i / (int)(1.00000000000000000e+00f)) / (int)(2.80000000000000000e+01f);
                int inCol = (i / (int)(1.00000000000000000e+00f)) % (int)(2.80000000000000000e+01f);
                int inChan = i % (int)(1.00000000000000000e+00f);
                int outRow = min((int)(2.40000000000000000e+01f), max(0, 1 + (int)floor((inRow + (0.00000000000000000e+00f) - (5.00000000000000000e+00f)) / (1.00000000000000000e+00f))));
                int maxOutRow = min((int)(2.40000000000000000e+01f), max(0, 1 + ((inRow + (int)(0.00000000000000000e+00f)) / (int)(1.00000000000000000e+00f))));
                int minOutCol = min((int)(2.40000000000000000e+01f), max(0, 1 + (int)floor((inCol + (0.00000000000000000e+00f) - (5.00000000000000000e+00f)) / (1.00000000000000000e+00f))));
                int maxOutCol = min((int)(2.40000000000000000e+01f), max(0, 1 + ((inCol + (int)(0.00000000000000000e+00f)) / (int)(1.00000000000000000e+00f))));
                while(true) {
                    if(outRow == maxOutRow) {
                       break;
                    }
                    const int strideRow = (outRow * (int)(1.00000000000000000e+00f)) - (int)(0.00000000000000000e+00f);
                    const int kernRow = inRow - strideRow;
                    for(int outCol = minOutCol; outCol < maxOutCol; outCol++) {
                        const int strideCol = (outCol * (int)(1.00000000000000000e+00f)) - (int)(0.00000000000000000e+00f);
                        const int kernCol = inCol - strideCol;
                        for(unsigned int outChan = 0; outChan < (unsigned int)(1.60000000000000000e+01f); outChan++) {
                            const int idPost = ((outRow * (int)(2.40000000000000000e+01f) * (int)(1.60000000000000000e+01f)) +
                                                (outCol * (int)(1.60000000000000000e+01f)) +
                                                outChan);
                            do {
                        const unsigned int idx = (i * group->rowStride) + group->rowLength[i];
                        const unsigned int kernelInd = (kernRow * 5 * 1 * 16) + (kernCol * 1 * 16) + (inChan * 16) + (outChan);
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
     {
        // merged synapse connectivity init group 1
        for(unsigned int g = 0; g < 1; g++) {
            const auto *group = &mergedSynapseConnectivityInitGroup1[g]; 
            memset(group->rowLength, 0, group->numSrcNeurons * sizeof(unsigned int));
            for (unsigned int i = 0; i < group->numSrcNeurons; i++) {
                // Build sparse connectivity
                while(true) {
                    
                    // Stash all parameters in registers
                    // **NOTE** this means parameters from group structure only get converted from float->int once
                    // **NOTE** if they're actually constant, compiler is still likely to treat them as constants rather than allocating registers
                    const int pool_kh = (2.00000000000000000e+00f), pool_kw = (2.00000000000000000e+00f);
                    const int pool_sh = (2.00000000000000000e+00f), pool_sw = (2.00000000000000000e+00f);
                    const int pool_padh = (0.00000000000000000e+00f), pool_padw = (0.00000000000000000e+00f);
                    const int pool_ih = (2.40000000000000000e+01f), pool_iw = (2.40000000000000000e+01f), pool_ic = (1.60000000000000000e+01f);
                    const int conv_kh = (5.00000000000000000e+00f), conv_kw = (5.00000000000000000e+00f);
                    const int conv_sh = (1.00000000000000000e+00f), conv_sw = (1.00000000000000000e+00f);
                    const int conv_padh = (0.00000000000000000e+00f), conv_padw = (0.00000000000000000e+00f);
                    const int conv_ow = (8.00000000000000000e+00f), conv_oh = (8.00000000000000000e+00f), conv_oc = (8.00000000000000000e+00f);
                    
                    // Convert presynaptic neuron ID to row, column and channel in pool input
                    const int poolInRow = (i / pool_ic) / pool_iw;
                    const int poolInCol = (i / pool_ic) % pool_iw;
                    const int poolInChan = i % pool_ic;
                    
                    // Calculate corresponding pool output
                    const int poolOutRow = (poolInRow + pool_padh) / pool_sh;
                    const int poolStrideRow = poolOutRow * pool_sh - pool_padh;
                    const int poolCropKH = min(poolStrideRow + pool_kh, pool_ih) - max(poolStrideRow, 0);
                    const int poolOutCol = (poolInCol + pool_padw) / pool_sw;
                    const int poolStrideCol = poolOutCol * pool_sw - pool_padw;
                    const int poolCropKW = min(poolStrideCol + pool_kw, pool_iw) - max(poolStrideCol, 0);
                    
                    if ((poolInRow < (poolStrideRow + pool_kh)) && (poolInCol < (poolStrideCol + pool_kw))) {
                    
                        // Calculate range of output rows and columns which this pool output connects to
                        const int minOutRow = min(conv_oh, max(0, 1 + ((poolOutRow + conv_padh - conv_kh) / conv_sh)));
                        const int maxOutRow = min(conv_oh, max(0, 1 + ((poolOutRow + conv_padh) / conv_sh)));
                        const int minOutCol = min(conv_ow, max(0, 1 + ((poolOutCol + conv_padw - conv_kw) / conv_sw)));
                        const int maxOutCol = min(conv_ow, max(0, 1 + ((poolOutCol + conv_padw) / conv_sw)));
                    
                        // Loop through output rows, columns and channels
                        for(int convOutRow = minOutRow; convOutRow < maxOutRow; convOutRow++) {
                            const int strideRow = (convOutRow * conv_sh) - conv_padh;
                            const int kernRow = poolOutRow - strideRow;
                            for(int convOutCol = minOutCol; convOutCol < maxOutCol; convOutCol++) {
                                const int strideCol = (convOutCol * conv_sw) - conv_padw;
                                const int kernCol = poolOutCol - strideCol;
                                for(int outChan = 0; outChan < conv_oc; outChan++) {
                                    // Calculate postsynaptic index and add synapse
                                    const int idPost = ((convOutRow * conv_ow * conv_oc) +
                                                        (convOutCol * conv_oc) +
                                                        outChan);
                                    do {
                        const unsigned int idx = (i * group->rowStride) + group->rowLength[i];
                        const unsigned int kernelInd = (kernRow * 5 * 16 * 8) + (kernCol * 16 * 8) + (poolInChan * 8) + (outChan);
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
                        }
                    }
                    
                    // End the row
                    break;
                    
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
