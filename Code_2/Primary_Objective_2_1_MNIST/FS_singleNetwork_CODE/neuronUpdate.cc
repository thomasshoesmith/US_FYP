#include "definitionsInternal.h"
#include "supportCode.h"

struct MergedNeuronUpdateGroup0
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* input;
    scalar* Vmem;
    scalar* scaleVal;
    unsigned int numNeurons;
    
}
;
struct MergedNeuronSpikeQueueUpdateGroup0
 {
    unsigned int* spkCnt;
    
}
;
static MergedNeuronUpdateGroup0 mergedNeuronUpdateGroup0[1];
void pushMergedNeuronUpdateGroup0ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* input, scalar* Vmem, scalar* scaleVal, unsigned int numNeurons) {
    mergedNeuronUpdateGroup0[idx].spkCnt = spkCnt;
    mergedNeuronUpdateGroup0[idx].spk = spk;
    mergedNeuronUpdateGroup0[idx].input = input;
    mergedNeuronUpdateGroup0[idx].Vmem = Vmem;
    mergedNeuronUpdateGroup0[idx].scaleVal = scaleVal;
    mergedNeuronUpdateGroup0[idx].numNeurons = numNeurons;
}
static MergedNeuronSpikeQueueUpdateGroup0 mergedNeuronSpikeQueueUpdateGroup0[1];
void pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(unsigned int idx, unsigned int* spkCnt) {
    mergedNeuronSpikeQueueUpdateGroup0[idx].spkCnt = spkCnt;
}
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// merged extra global parameter functions
// ------------------------------------------------------------------------
void updateNeurons(float t) {
     {
        // merged neuron spike queue update group 0
        for(unsigned int g = 0; g < 1; g++) {
            const auto *group = &mergedNeuronSpikeQueueUpdateGroup0[g]; 
            group->spkCnt[0] = 0;
        }
    }
     {
        // merged neuron update group 0
        for(unsigned int g = 0; g < 1; g++) {
            const auto *group = &mergedNeuronUpdateGroup0[g]; 
            
            for(unsigned int i = 0; i < group->numNeurons; i++) {
                const scalar linput = group->input[i];
                scalar lVmem = group->Vmem[i];
                scalar lscaleVal = group->scaleVal[i];
                
                // test whether spike condition was fulfilled previously
                // calculate membrane potential
                
                // Convert K to integer
                const int kInt = (int)(8.00000000000000000e+00f);
                
                // Get timestep within presentation
                const int pipeTimestep = (int)(t / DT);
                
                // If this is the first timestep, apply input
                if(pipeTimestep == 0) {
                    lVmem = linput;
                }
                
                const scalar hT = (7.81250000000000000e-02f) * (1 << (kInt - (pipeTimestep+1)));
                
                lscaleVal = (7.81250000000000000e-02f) * (1 << (kInt - (pipeTimestep+1)));
                
                // test for and register a true spike
                if (
                lVmem >= hT
                ) {
                    group->spk[group->spkCnt[0]++] = i;
                    // spike reset code
                    
                    lVmem -= hT;
                    
                }
                group->Vmem[i] = lVmem;
                group->scaleVal[i] = lscaleVal;
            }
        }
    }
}