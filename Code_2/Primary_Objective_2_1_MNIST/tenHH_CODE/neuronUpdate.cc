#include "definitionsInternal.h"
#include "supportCode.h"

struct MergedNeuronUpdateGroup0
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
struct MergedNeuronSpikeQueueUpdateGroup0
 {
    unsigned int* spkCnt;
    
}
;
static MergedNeuronUpdateGroup0 mergedNeuronUpdateGroup0[1];
void pushMergedNeuronUpdateGroup0ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* V, scalar* m, scalar* h, scalar* n, unsigned int numNeurons) {
    mergedNeuronUpdateGroup0[idx].spkCnt = spkCnt;
    mergedNeuronUpdateGroup0[idx].spk = spk;
    mergedNeuronUpdateGroup0[idx].V = V;
    mergedNeuronUpdateGroup0[idx].m = m;
    mergedNeuronUpdateGroup0[idx].h = h;
    mergedNeuronUpdateGroup0[idx].n = n;
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
                scalar lm = group->m[i];
                scalar lh = group->h[i];
                scalar ln = group->n[i];
                
                float Isyn = 0;
                // test whether spike condition was fulfilled previously
                const bool oldSpike = (lV >= 0.0f);
                // calculate membrane potential
                scalar Imem;
                unsigned int mt;
                scalar mdt= DT/25.0f;
                for (mt=0; mt < 25; mt++) {
                   Imem= -(lm*lm*lm*lh*(7.15000000000000036e+00f)*(lV-((5.00000000000000000e+01f)))+
                       ln*ln*ln*ln*(1.42999999999999994e+00f)*(lV-((-9.50000000000000000e+01f)))+
                       (2.67200000000000007e-02f)*(lV-((-6.35630000000000024e+01f)))-Isyn);
                   scalar _a;
                   if (lV == -52.0f) {
                       _a= 1.28f;
                   }
                   else {
                       _a= 0.32f*(-52.0f-lV)/(exp((-52.0f-lV)/4.0f)-1.0f);
                   }
                   scalar _b;
                   if (lV == -25.0f) {
                       _b= 1.4f;
                   }
                   else {
                       _b= 0.28f*(lV+25.0f)/(exp((lV+25.0f)/5.0f)-1.0f);
                   }
                   lm+= (_a*(1.0f-lm)-_b*lm)*mdt;
                   _a= 0.128f*exp((-48.0f-lV)/18.0f);
                   _b= 4.0f / (exp((-25.0f-lV)/5.0f)+1.0f);
                   lh+= (_a*(1.0f-lh)-_b*lh)*mdt;
                   if (lV == -50.0f) {
                       _a= 0.16f;
                   }
                   else {
                       _a= 0.032f*(-50.0f-lV)/(exp((-50.0f-lV)/5.0f)-1.0f);
                   }
                   _b= 0.5f*exp((-55.0f-lV)/40.0f);
                   ln+= (_a*(1.0f-ln)-_b*ln)*mdt;
                   lV+= Imem/(1.42999999999999988e-01f)*mdt;
                }
                
                // test for and register a true spike
                if ((lV >= 0.0f) && !(oldSpike)) {
                    group->spk[group->spkCnt[0]++] = i;
                }
                group->V[i] = lV;
                group->m[i] = lm;
                group->h[i] = lh;
                group->n[i] = ln;
            }
        }
    }
}
