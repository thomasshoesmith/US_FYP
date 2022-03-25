#include "definitionsInternal.h"
#include "supportCode.h"

struct MergedPresynapticUpdateGroup0
 {
    float* inSyn;
    unsigned int* srcSpkCnt;
    unsigned int* srcSpk;
    unsigned int* rowLength;
    uint32_t* ind;
    unsigned int rowStride;
    unsigned int numSrcNeurons;
    unsigned int numTrgNeurons;
    
}
;
static MergedPresynapticUpdateGroup0 mergedPresynapticUpdateGroup0[1];
void pushMergedPresynapticUpdateGroup0ToDevice(unsigned int idx, float* inSyn, unsigned int* srcSpkCnt, unsigned int* srcSpk, unsigned int* rowLength, uint32_t* ind, unsigned int rowStride, unsigned int numSrcNeurons, unsigned int numTrgNeurons) {
    mergedPresynapticUpdateGroup0[idx].inSyn = inSyn;
    mergedPresynapticUpdateGroup0[idx].srcSpkCnt = srcSpkCnt;
    mergedPresynapticUpdateGroup0[idx].srcSpk = srcSpk;
    mergedPresynapticUpdateGroup0[idx].rowLength = rowLength;
    mergedPresynapticUpdateGroup0[idx].ind = ind;
    mergedPresynapticUpdateGroup0[idx].rowStride = rowStride;
    mergedPresynapticUpdateGroup0[idx].numSrcNeurons = numSrcNeurons;
    mergedPresynapticUpdateGroup0[idx].numTrgNeurons = numTrgNeurons;
}
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
void updateSynapses(float t) {
     {
        // merged presynaptic update group 0
        for(unsigned int g = 0; g < 1; g++) {
            const auto *group = &mergedPresynapticUpdateGroup0[g]; 
            // process presynaptic events: True Spikes
            for (unsigned int i = 0; i < group->srcSpkCnt[0]; i++) {
                const unsigned int ipre = group->srcSpk[i];
                const unsigned int npost = group->rowLength[ipre];
                for (unsigned int j = 0; j < npost; j++) {
                    const unsigned int synAddress = (ipre * group->rowStride) + j;
                    const unsigned int ipost = group->ind[synAddress];
                    group->inSyn[ipost] += (0.00000000000000000e+00f);
                }
            }
            
        }
    }
}
