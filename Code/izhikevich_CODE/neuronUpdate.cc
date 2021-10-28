#include "definitionsInternal.h"
#include "supportCode.h"

struct MergedNeuronUpdateGroup0
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* V;
    scalar* U;
    scalar* a;
    scalar* b;
    scalar* c;
    scalar* d;
    unsigned int numNeurons;
    
}
;
struct MergedNeuronSpikeQueueUpdateGroup0
 {
    unsigned int* spkCnt;
    
}
;
static MergedNeuronUpdateGroup0 mergedNeuronUpdateGroup0[1];
void pushMergedNeuronUpdateGroup0ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* U, scalar* a, scalar* b, scalar* c, scalar* d, unsigned int numNeurons) {
    mergedNeuronUpdateGroup0[idx].spkCnt = spkCnt;
    mergedNeuronUpdateGroup0[idx].spk = spk;
    mergedNeuronUpdateGroup0[idx].V = V;
    mergedNeuronUpdateGroup0[idx].U = U;
    mergedNeuronUpdateGroup0[idx].a = a;
    mergedNeuronUpdateGroup0[idx].b = b;
    mergedNeuronUpdateGroup0[idx].c = c;
    mergedNeuronUpdateGroup0[idx].d = d;
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
                scalar lV = group->V[i];
                scalar lU = group->U[i];
                const scalar la = group->a[i];
                const scalar lb = group->b[i];
                const scalar lc = group->c[i];
                const scalar ld = group->d[i];
                
                float Isyn = 0;
                // current source 0
                 {
                    Isyn += (1.00000000000000000e+01f);
                    
                }
                // test whether spike condition was fulfilled previously
                // calculate membrane potential
                if (lV >= 30.0f){
                   lV=lc;
                   lU+=ld;
                } 
                lV+=0.5f*(0.04f*lV*lV+5.0f*lV+140.0f-lU+Isyn)*DT; //at two times for numerical stability
                lV+=0.5f*(0.04f*lV*lV+5.0f*lV+140.0f-lU+Isyn)*DT;
                lU+=la*(lb*lV-lU)*DT;
                if (lV > 30.0f){   //keep this to not confuse users with unrealistiv voltage values 
                  lV=30.0f; 
                }
                
                // test for and register a true spike
                if (lV >= 29.99f) {
                    group->spk[group->spkCnt[0]++] = i;
                }
                group->V[i] = lV;
                group->U[i] = lU;
            }
        }
    }
}
