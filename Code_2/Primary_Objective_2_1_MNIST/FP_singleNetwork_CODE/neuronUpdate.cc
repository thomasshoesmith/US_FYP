#include "definitionsInternal.h"
#include "supportCode.h"

struct MergedNeuronUpdateGroup0
 {
    unsigned int* spkCnt;
    unsigned int* spk;
    scalar* input;
    scalar* Vmem;
    scalar* scaleVal;
    scalar* measure;
    scalar* exponent;
    scalar* hT;
    unsigned int numNeurons;
    
}
;
struct MergedNeuronSpikeQueueUpdateGroup0
 {
    unsigned int* spkCnt;
    
}
;
static MergedNeuronUpdateGroup0 mergedNeuronUpdateGroup0[1];
void pushMergedNeuronUpdateGroup0ToDevice(unsigned int idx, unsigned int* spkCnt, unsigned int* spk, scalar* input, scalar* Vmem, scalar* scaleVal, scalar* measure, scalar* exponent, scalar* hT, unsigned int numNeurons) {
    mergedNeuronUpdateGroup0[idx].spkCnt = spkCnt;
    mergedNeuronUpdateGroup0[idx].spk = spk;
    mergedNeuronUpdateGroup0[idx].input = input;
    mergedNeuronUpdateGroup0[idx].Vmem = Vmem;
    mergedNeuronUpdateGroup0[idx].scaleVal = scaleVal;
    mergedNeuronUpdateGroup0[idx].measure = measure;
    mergedNeuronUpdateGroup0[idx].exponent = exponent;
    mergedNeuronUpdateGroup0[idx].hT = hT;
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
                scalar lmeasure = group->measure[i];
                scalar lexponent = group->exponent[i];
                scalar lhT = group->hT[i];
                
                // test whether spike condition was fulfilled previously
                // calculate membrane potential
                
                // Convert K to integer
                const int kInt = (int)(8.00000000000000000e+00f);
                
                // Convert Alpha to integer
                const int AlphaInt = (int)(2.00000000000000000e+01f);
                
                // Convert elim to integer
                const int elimInt = (int)(2.00000000000000000e+00f);
                
                // Get timestep within presentation
                const int pipeTimestep = (int)(t / DT);
                
                //printf("%d", pipeTimestep);
                
                // If this is the first timestep, apply input
                if(pipeTimestep == 0) {
                
                    lscaleVal = AlphaInt * pow(2, - fmin(pow(2, elimInt - 1), fmax(0, ceil(log2(1 / (linput / AlphaInt))))));
                    //printf("%.6f", lscaleVal);
                
                    // needs to be cleaned up
                    // scaleVal can be derived from exponent
                    //# TODO: update variable names to logial ones
                    lexponent = fmin(pow(2, elimInt - 1), fmax(0, ceil(log2(1 / (linput / AlphaInt)))));
                    printf(" Exponent:%.6f ", lexponent);
                    //printf(" ScaleVal:%.6f ", lscaleVal);
                
                    lVmem = lexponent;
                    lmeasure = lexponent;
                
                }
                
                if (pipeTimestep == elimInt) {
                    lVmem = linput;
                    //printf("Value: %d", pipeTimestep);
                }
                
                lhT = 0;
                lmeasure = 0;
                
                if (pipeTimestep >= elimInt) {
                
                    lhT = lscaleVal / (1 << (pipeTimestep - 4));
                
                    lmeasure = lscaleVal / (1 << (pipeTimestep - 4));
                
                    //printf(" Value:%d ", pipeTimestep);
                } else {
                
                    lhT = pow(2, elimInt-1) / (1 << pipeTimestep);
                
                    lmeasure = pow(2, elimInt-1) / (1 << pipeTimestep);
                
                }
                //printf(" pTs:%dhT:%.6f ", pipeTimestep, lhT);
                
                
                // test for and register a true spike
                if (
                lVmem >= lhT
                ) {
                    group->spk[group->spkCnt[0]++] = i;
                    // spike reset code
                    
                    lVmem -= lhT;
                    
                }
                group->Vmem[i] = lVmem;
                group->scaleVal[i] = lscaleVal;
                group->measure[i] = lmeasure;
                group->exponent[i] = lexponent;
                group->hT[i] = lhT;
            }
        }
    }
}
