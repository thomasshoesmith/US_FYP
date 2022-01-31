#include "definitionsInternal.h"
#include "supportCode.h"

struct MergedPresynapticUpdateGroup0
 {
    float* inSyn;
    unsigned int* srcSpkCnt;
    unsigned int* srcSpk;
    scalar* weightsg;
    unsigned int rowStride;
    unsigned int numSrcNeurons;
    unsigned int numTrgNeurons;
    
}
;
struct MergedPresynapticUpdateGroup1
 {
    float* inSyn;
    unsigned int* srcSpkCnt;
    unsigned int* srcSpk;
    unsigned int* rowLength;
    uint32_t* ind;
    scalar* g;
    unsigned int rowStride;
    unsigned int numSrcNeurons;
    unsigned int numTrgNeurons;
    
}
;
struct MergedPresynapticUpdateGroup2
 {
    float* inSyn;
    unsigned int* srcSpkCnt;
    unsigned int* srcSpk;
    scalar* g;
    unsigned int rowStride;
    unsigned int numSrcNeurons;
    unsigned int numTrgNeurons;
    
}
;
static MergedPresynapticUpdateGroup0 mergedPresynapticUpdateGroup0[1];
void pushMergedPresynapticUpdateGroup0ToDevice(unsigned int idx, float* inSyn, unsigned int* srcSpkCnt, unsigned int* srcSpk, scalar* weightsg, unsigned int rowStride, unsigned int numSrcNeurons, unsigned int numTrgNeurons) {
    mergedPresynapticUpdateGroup0[idx].inSyn = inSyn;
    mergedPresynapticUpdateGroup0[idx].srcSpkCnt = srcSpkCnt;
    mergedPresynapticUpdateGroup0[idx].srcSpk = srcSpk;
    mergedPresynapticUpdateGroup0[idx].weightsg = weightsg;
    mergedPresynapticUpdateGroup0[idx].rowStride = rowStride;
    mergedPresynapticUpdateGroup0[idx].numSrcNeurons = numSrcNeurons;
    mergedPresynapticUpdateGroup0[idx].numTrgNeurons = numTrgNeurons;
}
static MergedPresynapticUpdateGroup1 mergedPresynapticUpdateGroup1[2];
void pushMergedPresynapticUpdateGroup1ToDevice(unsigned int idx, float* inSyn, unsigned int* srcSpkCnt, unsigned int* srcSpk, unsigned int* rowLength, uint32_t* ind, scalar* g, unsigned int rowStride, unsigned int numSrcNeurons, unsigned int numTrgNeurons) {
    mergedPresynapticUpdateGroup1[idx].inSyn = inSyn;
    mergedPresynapticUpdateGroup1[idx].srcSpkCnt = srcSpkCnt;
    mergedPresynapticUpdateGroup1[idx].srcSpk = srcSpk;
    mergedPresynapticUpdateGroup1[idx].rowLength = rowLength;
    mergedPresynapticUpdateGroup1[idx].ind = ind;
    mergedPresynapticUpdateGroup1[idx].g = g;
    mergedPresynapticUpdateGroup1[idx].rowStride = rowStride;
    mergedPresynapticUpdateGroup1[idx].numSrcNeurons = numSrcNeurons;
    mergedPresynapticUpdateGroup1[idx].numTrgNeurons = numTrgNeurons;
}
static MergedPresynapticUpdateGroup2 mergedPresynapticUpdateGroup2[2];
void pushMergedPresynapticUpdateGroup2ToDevice(unsigned int idx, float* inSyn, unsigned int* srcSpkCnt, unsigned int* srcSpk, scalar* g, unsigned int rowStride, unsigned int numSrcNeurons, unsigned int numTrgNeurons) {
    mergedPresynapticUpdateGroup2[idx].inSyn = inSyn;
    mergedPresynapticUpdateGroup2[idx].srcSpkCnt = srcSpkCnt;
    mergedPresynapticUpdateGroup2[idx].srcSpk = srcSpk;
    mergedPresynapticUpdateGroup2[idx].g = g;
    mergedPresynapticUpdateGroup2[idx].rowStride = rowStride;
    mergedPresynapticUpdateGroup2[idx].numSrcNeurons = numSrcNeurons;
    mergedPresynapticUpdateGroup2[idx].numTrgNeurons = numTrgNeurons;
}
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
void pushMergedPresynapticUpdate0weightsgToDevice(unsigned int idx, scalar* value) {
    mergedPresynapticUpdateGroup0[idx].weightsg = value;
}

void updateSynapses(float t) {
     {
        // merged presynaptic update group 0
        for(unsigned int g = 0; g < 1; g++) {
            const auto *group = &mergedPresynapticUpdateGroup0[g]; 
            // process presynaptic events: True Spikes
            for (unsigned int i = 0; i < group->srcSpkCnt[0]; i++) {
                const unsigned int ipre = group->srcSpk[i];
                for (unsigned int ipost = 0; ipost < group->numTrgNeurons; ipost++) {
                    const unsigned int synAddress = (ipre * group->numTrgNeurons) + ipost;
                    scalar lg;
                     {
                        
                        const int pool_kh = (2.00000000000000000e+00), pool_kw = (2.00000000000000000e+00);
                        const int pool_sh = (2.00000000000000000e+00), pool_sw = (2.00000000000000000e+00);
                        const int pool_padh = (0.00000000000000000e+00), pool_padw = (0.00000000000000000e+00);
                        const int pool_ih = (8.00000000000000000e+00), pool_iw = (8.00000000000000000e+00), pool_ic = (8.00000000000000000e+00);
                        
                        // Convert presynaptic neuron ID to row, column and channel in pool input
                        const int poolInRow = (ipre / pool_ic) / pool_iw;
                        const int poolInCol = (ipre / pool_ic) % pool_iw;
                        const int poolInChan = ipre % pool_ic;
                        
                        // Calculate corresponding pool output
                        const int poolOutRow = (poolInRow + pool_padh) / pool_sh;
                        const int poolStrideRow = poolOutRow * pool_sh - pool_padh;
                        const int poolCropKH = min(poolStrideRow + pool_kh, pool_ih) - max(poolStrideRow, 0);
                        const int poolOutCol = (poolInCol + pool_padw) / pool_sw;
                        const int poolStrideCol = poolOutCol * pool_sw - pool_padw;
                        const int poolCropKW = min(poolStrideCol + pool_kw, pool_iw) - max(poolStrideCol, 0);
                        
                        lg = 0.0;
                        if ((poolInRow < (poolStrideRow + pool_kh)) && (poolInCol < (poolStrideCol + pool_kw))) {
                        
                            const int dense_iw = (4.00000000000000000e+00), dense_ic = (8.00000000000000000e+00);
                            const int dense_units = (1.28000000000000000e+02);
                        
                            const int dense_in_unit = poolOutRow * (dense_iw * dense_ic) + poolOutCol * (dense_ic) + poolInChan;
                            const int dense_out_unit = ipost;
                        
                            lg = group->weightsg[
                                dense_in_unit * (dense_units) +
                                dense_out_unit
                            ] / (poolCropKH * poolCropKW);
                        }
                        
                    }
                    group->inSyn[ipost] += lg;
                }
            }
            
        }
    }
     {
        // merged presynaptic update group 1
        for(unsigned int g = 0; g < 2; g++) {
            const auto *group = &mergedPresynapticUpdateGroup1[g]; 
            // process presynaptic events: True Spikes
            for (unsigned int i = 0; i < group->srcSpkCnt[0]; i++) {
                const unsigned int ipre = group->srcSpk[i];
                const unsigned int npost = group->rowLength[ipre];
                for (unsigned int j = 0; j < npost; j++) {
                    const unsigned int synAddress = (ipre * group->rowStride) + j;
                    const unsigned int ipost = group->ind[synAddress];
                    group->inSyn[ipost] += group->g[synAddress];
                }
            }
            
        }
    }
     {
        // merged presynaptic update group 2
        for(unsigned int g = 0; g < 2; g++) {
            const auto *group = &mergedPresynapticUpdateGroup2[g]; 
            // process presynaptic events: True Spikes
            for (unsigned int i = 0; i < group->srcSpkCnt[0]; i++) {
                const unsigned int ipre = group->srcSpk[i];
                for (unsigned int ipost = 0; ipost < group->numTrgNeurons; ipost++) {
                    const unsigned int synAddress = (ipre * group->numTrgNeurons) + ipost;
                    group->inSyn[ipost] += group->g[synAddress];
                }
            }
            
        }
    }
}
