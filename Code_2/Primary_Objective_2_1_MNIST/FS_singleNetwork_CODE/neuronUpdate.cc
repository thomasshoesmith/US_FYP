#include "definitionsInternal.h"
#include "supportCode.h"

struct MergedNeuronUpdateGroup0
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* Fx;
    scalar* Vmem;
    float* inSynInSyn0;
    unsigned int numNeurons;
    
}
;
struct MergedNeuronUpdateGroup1
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* input;
    scalar* Vmem;
    scalar* scaleVal;
    unsigned int numNeurons;
    
}
;
struct MergedNeuronUpdateGroup2
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    unsigned int* spkQuePtr;
    scalar* Fx;
    scalar* Vmem;
    float* inSynInSyn0;
    unsigned int numNeurons;
    
}
;
struct MergedNeuronSpikeQueueUpdateGroup0
 {
    unsigned int* spkCnt;
    
}
;
struct MergedNeuronSpikeQueueUpdateGroup1
 {
    unsigned int* spkQuePtr;
    unsigned int* spkCnt;
    
}
;
struct MergedNeuronSpikeQueueUpdateGroup2
 {
    unsigned int* spkCnt;
    
}
;
static MergedNeuronUpdateGroup0 mergedNeuronUpdateGroup0[1];
void pushMergedNeuronUpdateGroup0ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* Fx, scalar* Vmem, float* inSynInSyn0, unsigned int numNeurons) {
    mergedNeuronUpdateGroup0[idx].spkCnt = spkCnt;
    mergedNeuronUpdateGroup0[idx].spk = spk;
    mergedNeuronUpdateGroup0[idx].Fx = Fx;
    mergedNeuronUpdateGroup0[idx].Vmem = Vmem;
    mergedNeuronUpdateGroup0[idx].inSynInSyn0 = inSynInSyn0;
    mergedNeuronUpdateGroup0[idx].numNeurons = numNeurons;
}
static MergedNeuronUpdateGroup1 mergedNeuronUpdateGroup1[1];
void pushMergedNeuronUpdateGroup1ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* input, scalar* Vmem, scalar* scaleVal, unsigned int numNeurons) {
    mergedNeuronUpdateGroup1[idx].spkCnt = spkCnt;
    mergedNeuronUpdateGroup1[idx].spk = spk;
    mergedNeuronUpdateGroup1[idx].input = input;
    mergedNeuronUpdateGroup1[idx].Vmem = Vmem;
    mergedNeuronUpdateGroup1[idx].scaleVal = scaleVal;
    mergedNeuronUpdateGroup1[idx].numNeurons = numNeurons;
}
static MergedNeuronUpdateGroup2 mergedNeuronUpdateGroup2[1];
void pushMergedNeuronUpdateGroup2ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, unsigned int* spkQuePtr, scalar* Fx, scalar* Vmem, float* inSynInSyn0, unsigned int numNeurons) {
    mergedNeuronUpdateGroup2[idx].spkCnt = spkCnt;
    mergedNeuronUpdateGroup2[idx].spk = spk;
    mergedNeuronUpdateGroup2[idx].spkQuePtr = spkQuePtr;
    mergedNeuronUpdateGroup2[idx].Fx = Fx;
    mergedNeuronUpdateGroup2[idx].Vmem = Vmem;
    mergedNeuronUpdateGroup2[idx].inSynInSyn0 = inSynInSyn0;
    mergedNeuronUpdateGroup2[idx].numNeurons = numNeurons;
}
static MergedNeuronSpikeQueueUpdateGroup0 mergedNeuronSpikeQueueUpdateGroup0[1];
void pushMergedNeuronSpikeQueueUpdateGroup0ToDevice(unsigned int idx, unsigned int* spkCnt) {
    mergedNeuronSpikeQueueUpdateGroup0[idx].spkCnt = spkCnt;
}
static MergedNeuronSpikeQueueUpdateGroup1 mergedNeuronSpikeQueueUpdateGroup1[1];
void pushMergedNeuronSpikeQueueUpdateGroup1ToDevice(unsigned int idx, unsigned int* spkQuePtr, unsigned int* spkCnt) {
    mergedNeuronSpikeQueueUpdateGroup1[idx].spkQuePtr = spkQuePtr;
    mergedNeuronSpikeQueueUpdateGroup1[idx].spkCnt = spkCnt;
}
static MergedNeuronSpikeQueueUpdateGroup2 mergedNeuronSpikeQueueUpdateGroup2[1];
void pushMergedNeuronSpikeQueueUpdateGroup2ToDevice(unsigned int idx, unsigned int* spkCnt) {
    mergedNeuronSpikeQueueUpdateGroup2[idx].spkCnt = spkCnt;
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
        // merged neuron spike queue update group 1
        for(unsigned int g = 0; g < 1; g++) {
            const auto *group = &mergedNeuronSpikeQueueUpdateGroup1[g]; 
            group->spkCnt[*group->spkQuePtr] = 0; 
        }
    }
     {
        // merged neuron spike queue update group 2
        for(unsigned int g = 0; g < 1; g++) {
            const auto *group = &mergedNeuronSpikeQueueUpdateGroup2[g]; 
            group->spkCnt[0] = 0;
        }
    }
     {
        // merged neuron update group 0
        for(unsigned int g = 0; g < 1; g++) {
            const auto *group = &mergedNeuronUpdateGroup0[g]; 
            
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
                const scalar hT = (7.81250000000000000e-02f) * (1 << (kInt - (1 + (pipeTimestep % kInt))));
                const scalar d = (7.81250000000000000e-02f) * (1 << ((kInt - pipeTimestep) % kInt));
                
                // Accumulate input
                // **NOTE** needs to be before applying input as spikes from LAST timestep must be processed
                lFx += (Isyn * d);
                //printf(" isyn:%.6f ",(Isyn * d));
                //printf(" d:%d ", d);
                
                printf(" pipeTimestep@0:%d ", pipeTimestep);
                
                // If this is the first timestep, apply input
                //printf(" pipeTimestep:%d ", pipeTimestep);
                if(pipeTimestep == 8) {
                    //printf(" pipeTimestep@0:%d ", pipeTimestep);
                    //printf(" Fx:%.6f ", lFx);
                    lVmem = lFx;
                    lFx = 0.0f;
                }
                //printf(" Vmem:%.6f ", lVmem);
                
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
     {
        // merged neuron update group 1
        for(unsigned int g = 0; g < 1; g++) {
            const auto *group = &mergedNeuronUpdateGroup1[g]; 
            
            for(unsigned int i = 0; i < group->numNeurons; i++) {
                const scalar linput = group->input[i];
                scalar lVmem = group->Vmem[i];
                scalar lscaleVal = group->scaleVal[i];
                
                // test whether spike condition was fulfilled previously
                // calculate membrane potential
                
                // Convert K to integer
                const int kInt = (int)(8.00000000000000000e+00f);
                
                // Get timestep within presentation | mod to keep within range
                const int pipeTimestep = (int)(t / DT);
                
                // If this is the first timestep, apply input
                if(pipeTimestep == 0) {
                    lVmem = linput;
                }
                
                // check pipetimestep < 8
                const scalar hT = (7.81250000000000000e-02f) * (1 << (kInt - ((pipeTimestep % kInt)+1)));
                
                lscaleVal = (7.81250000000000000e-02f) * (1 << (kInt - ((pipeTimestep % kInt)+1)));
                //printf(" Vmem:%.6f ", lVmem);
                //printf(" scaleVal:%.6f ", lscaleVal);
                
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
     {
        // merged neuron update group 2
        for(unsigned int g = 0; g < 1; g++) {
            const auto *group = &mergedNeuronUpdateGroup2[g]; 
            const unsigned int readDelayOffset = (((*group->spkQuePtr + 1) % 2) * group->numNeurons);
            const unsigned int writeDelayOffset = (*group->spkQuePtr * group->numNeurons);
            
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
                const scalar hT = (7.81250000000000000e-02f) * (1 << (kInt - (1 + (pipeTimestep % kInt))));
                const scalar d = (7.81250000000000000e-02f) * (1 << ((kInt - pipeTimestep) % kInt));
                
                // Accumulate input
                // **NOTE** needs to be before applying input as spikes from LAST timestep must be processed
                lFx += (Isyn * d);
                //printf(" isyn:%.6f ",(Isyn * d));
                //printf(" d:%d ", d);
                
                printf(" pipeTimestep@0:%d ", pipeTimestep);
                
                // If this is the first timestep, apply input
                //printf(" pipeTimestep:%d ", pipeTimestep);
                if(pipeTimestep == 8) {
                    //printf(" pipeTimestep@0:%d ", pipeTimestep);
                    //printf(" Fx:%.6f ", lFx);
                    lVmem = lFx;
                    lFx = 0.0f;
                }
                //printf(" Vmem:%.6f ", lVmem);
                
                // test for and register a true spike
                if (
                lVmem >= hT
                ) {
                    group->spk[writeDelayOffset + group->spkCnt[*group->spkQuePtr]++] = i;
                    // spike reset code
                    
                    lVmem -= hT;
                    
                }
                group->Fx[i] = lFx;
                group->Vmem[i] = lVmem;
            }
        }
    }
}
