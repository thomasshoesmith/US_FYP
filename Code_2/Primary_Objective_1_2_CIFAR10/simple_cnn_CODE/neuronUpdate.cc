#include "definitionsInternal.h"
#include "supportCode.h"

struct MergedNeuronUpdateGroup0
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* input;
    scalar* Vmem;
    unsigned int numNeurons;
    
}
;
struct MergedNeuronUpdateGroup1
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* Fx;
    scalar* Vmem;
    float* inSynInSyn0;
    unsigned int numNeurons;
    scalar alpha;
    scalar upstreamAlpha;
    scalar scale;
    scalar upstreamScale;
    
}
;
struct MergedNeuronSpikeQueueUpdateGroup0
 {
    unsigned int* spkCnt;
    
}
;
struct MergedNeuronSpikeQueueUpdateGroup1
 {
    unsigned int* spkCnt;
    
}
;
static MergedNeuronUpdateGroup0 mergedNeuronUpdateGroup0[1];
void pushMergedNeuronUpdateGroup0ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* input, scalar* Vmem, unsigned int numNeurons) {
    mergedNeuronUpdateGroup0[idx].spkCnt = spkCnt;
    mergedNeuronUpdateGroup0[idx].spk = spk;
    mergedNeuronUpdateGroup0[idx].input = input;
    mergedNeuronUpdateGroup0[idx].Vmem = Vmem;
    mergedNeuronUpdateGroup0[idx].numNeurons = numNeurons;
}
static MergedNeuronUpdateGroup1 mergedNeuronUpdateGroup1[3];
void pushMergedNeuronUpdateGroup1ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* Fx, scalar* Vmem, float* inSynInSyn0, unsigned int numNeurons, scalar alpha, scalar upstreamAlpha, scalar scale, scalar upstreamScale) {
    mergedNeuronUpdateGroup1[idx].spkCnt = spkCnt;
    mergedNeuronUpdateGroup1[idx].spk = spk;
    mergedNeuronUpdateGroup1[idx].Fx = Fx;
    mergedNeuronUpdateGroup1[idx].Vmem = Vmem;
    mergedNeuronUpdateGroup1[idx].inSynInSyn0 = inSynInSyn0;
    mergedNeuronUpdateGroup1[idx].numNeurons = numNeurons;
    mergedNeuronUpdateGroup1[idx].alpha = alpha;
    mergedNeuronUpdateGroup1[idx].upstreamAlpha = upstreamAlpha;
    mergedNeuronUpdateGroup1[idx].scale = scale;
    mergedNeuronUpdateGroup1[idx].upstreamScale = upstreamScale;
}
static MergedNeuronSpikeQueueUpdateGroup0 mergedNeuronSpikeQueueUpdateGroup0[3];
void pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(unsigned int idx, unsigned int* spkCnt) {
    mergedNeuronSpikeQueueUpdateGroup0[idx].spkCnt = spkCnt;
}
static MergedNeuronSpikeQueueUpdateGroup1 mergedNeuronSpikeQueueUpdateGroup1[1];
void pushMergedNeuronSpikeQueueUpdateGroup1ToDevice(unsigned int idx, unsigned int* spkCnt) {
    mergedNeuronSpikeQueueUpdateGroup1[idx].spkCnt = spkCnt;
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
        for(unsigned int g = 0; g < 3; g++) {
            const auto *group = &mergedNeuronSpikeQueueUpdateGroup0[g]; 
            group->spkCnt[0] = 0;
        }
    }
     {
        // merged neuron spike queue update group 1
        for(unsigned int g = 0; g < 1; g++) {
            const auto *group = &mergedNeuronSpikeQueueUpdateGroup1[g]; 
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
                
                const scalar hT = (3.92156862745098034e-03f) * (1 << (kInt - (1 + pipeTimestep)));
                
                // test for and register a true spike
                if (
                lVmem >= hT
                ) {
                    group->spk[group->spkCnt[0]++] = i;
                    // spike reset code
                    
                    lVmem -= hT;
                    
                }
                group->Vmem[i] = lVmem;
            }
        }
    }
     {
        // merged neuron update group 1
        for(unsigned int g = 0; g < 3; g++) {
            const auto *group = &mergedNeuronUpdateGroup1[g]; 
            
            for(unsigned int i = 0; i < group->numNeurons; i++) {
                scalar lFx = group->Fx[i];
                scalar lVmem = group->Vmem[i];
                
                float Isyn = 0;
                 {
                    // pull inSyn values in a coalesced access
                    float linSyn = group->inSynInSyn0[i];
                    Isyn += linSyn; linSyn = 0;
                    
                    group->inSynInSyn0[i] = linSyn;
                }
                // test whether spike condition was fulfilled previously
                // calculate membrane potential
                
                // Convert K to integer
                const int kInt = (int)(8.00000000000000000e+00f);
                
                // Get timestep within presentation
                const int pipeTimestep = (int)(t / DT);
                
                // Calculate magic constants. For RelU hT=h=T
                // **NOTE** d uses last timestep as that was when spike was SENT
                const scalar hT = group->scale * (1 << (kInt - (1 + pipeTimestep)));
                const scalar d = group->upstreamScale * (1 << ((kInt - pipeTimestep) % kInt));
                
                // Accumulate input
                // **NOTE** needs to be before applying input as spikes from LAST timestep must be processed
                lFx += (Isyn * d);
                
                // If this is the first timestep, apply input
                if(pipeTimestep == 0) {
                    lVmem = lFx;
                    lFx = 0.0f;
                }
                
                // test for and register a true spike
                if (
                lVmem >= hT
                ) {
                    group->spk[group->spkCnt[0]++] = i;
                    // spike reset code
                    
                    lVmem -= hT;
                    
                }
                group->Fx[i] = lFx;
                group->Vmem[i] = lVmem;
            }
        }
    }
}
