//--------------------------------------------------------------------------
/*! \file batch_pull_spikes/test.cc

\brief Main test code that is part of the feature testing
suite of minimal models with known analytic outcomes that are used for continuous integration testing.
*/
//--------------------------------------------------------------------------
// Google test includes
#include "gtest/gtest.h"

// Auto-generated simulation code includess
#include "batch_pull_spikes_CODE/definitions.h"

// **NOTE** base-class for simulation tests must be
// included after auto-generated globals are includes
#include "../../utils/simulation_test.h"

void checkSpikes()
{
    // Determine which batch spike SHOULD be in
    // **NOTE** iT was advanced after simulation step
    const unsigned int correctSpikeBatch = (iT - 1)/ 10;
    const unsigned int correctSpikeNeuron = (iT - 1) % 10;
    
    // Loop through batches
    for(unsigned int b = 0; b < 10; b++) {
        // If spike should be in this batch
        if(b == correctSpikeBatch) {
            // Assert that only a single spike was emitted
            ASSERT_EQ(getPopCurrentSpikeCount(b), 1);
            ASSERT_EQ(getPopDelayCurrentSpikeCount(b), 1);
            
            ASSERT_EQ(getPopCurrentSpikes(b)[0], correctSpikeNeuron);
            ASSERT_EQ(getPopDelayCurrentSpikes(b)[0], correctSpikeNeuron);
        }
        // Otherwise, check there are no spikes
        else {
            ASSERT_EQ(getPopCurrentSpikeCount(b), 0);
            ASSERT_EQ(getPopDelayCurrentSpikeCount(b), 0);
        }
    }
}

//----------------------------------------------------------------------------
// SimTest
//----------------------------------------------------------------------------
class SimTest : public SimulationTest
{
public:
    virtual void Init() override
    {
        // Allocate spike recording buffer
        allocateRecordingBuffers(100);
        
        // Allocate spike times
        allocatespikeTimesPop(100);
        allocatespikeTimesPopDelay(100);
        
        // Loop through batches and neurons
        for(unsigned int b = 0; b < 10; b++) {
            for(unsigned int i = 0; i < 10; i++) {
                const unsigned int idx = (b * 10) + i;
                
                // Set spike time to index
                spikeTimesPop[idx] = (scalar)idx;
                spikeTimesPopDelay[idx] = (scalar)idx;
                
                // Configure spike source
                startSpikePop[idx] = idx;
                startSpikePopDelay[idx] = idx;
                endSpikePop[idx] = idx + 1;
                endSpikePopDelay[idx] = idx + 1;
            }
        }
        
        // Upload spike times
        pushspikeTimesPopToDevice(100);
        pushspikeTimesPopDelayToDevice(100);
    }
};

TEST_F(SimTest, BatchPullSpikes)
{
    while(iT < 100) {
        StepGeNN();
        
        // Download all spikes from device and check
        pullPopSpikesFromDevice();
        pullPopDelaySpikesFromDevice();
        checkSpikes();
        
        // Zero host data structures
        std::fill_n(glbSpkCntPop, 10, 0);
        std::fill_n(glbSpkPop, 100, 0);
        std::fill_n(glbSpkCntPopDelay, 60, 0);
        std::fill_n(glbSpkPopDelay, 600, 0);
        
        // Download current spikes from device
        pullPopCurrentSpikesFromDevice();
        pullPopDelayCurrentSpikesFromDevice();
        checkSpikes();
    }
    
    // Download spike recording data
    pullRecordingBuffersFromDevice();
    
    for(unsigned int t = 0; t < 100; t++) {
        const unsigned int correctSpikeBatch = t / 10;
        const unsigned int correctSpikeNeuron = t % 10;
        for(unsigned int b = 0; b < 10; b++) {
            const uint32_t word = recordSpkPop[(t * 1 * 10) + (b * 1)];
            const uint32_t wordDelay = recordSpkPopDelay[(t * 1 * 10) + (b * 1)];
            
            // If there should be a spike in this batch
            if(b == correctSpikeBatch) {
                ASSERT_EQ(word, 1 << correctSpikeNeuron);
                ASSERT_EQ(wordDelay, 1 << correctSpikeNeuron);
            }
            // Otherwise, assert that there are no spikes
            else {
                ASSERT_EQ(word, 0);
                ASSERT_EQ(wordDelay, 0);
            }
            
        }
    }
}

