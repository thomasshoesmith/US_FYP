//--------------------------------------------------------------------------
/*! \file pre_wu_vars_in_sim_code_fused/test.cc

\brief Main test code that is part of the feature testing
suite of minimal models with known analytic outcomes that are used for continuous integration testing.
*/
//--------------------------------------------------------------------------
// Standard C includes
#include <cmath>

// Google test includes
#include "gtest/gtest.h"

// Autogenerated simulation code includess
#include "pre_wu_vars_in_sim_code_fused_CODE/definitions.h"

// **NOTE** base-class for simulation tests must be
// included after auto-generated globals are includes
#include "../../utils/simulation_test.h"

// Combine neuron and synapse policies together to build variable-testing fixture
class SimTest : public SimulationTest
{
public:
    void Simulate()
    {
        while(t < 200.0f) {
            StepGeNN();

            // Ignore first timestep as no postsynaptic events will be processed so wsyn is in it's initial state
            if(t > DT) {
                // Loop through neurons
                for(unsigned int i = 0; i < 10; i++) {
                    // Calculate time of spikes we SHOULD be reading
                    // **NOTE** we delay by 22 timesteps because:
                    // 1) delay = 20
                    // 2) spike times are read in postsynaptic kernel one timestep AFTER being emitted
                    // 3) t is incremented one timestep at te end of StepGeNN
                    const float delayedTime = (scalar)i + (10.0f * std::floor((t - 22.0f - (scalar)i) / 10.0f));

                    // If, theoretically, spike would have arrived before delay it's impossible so time should be a very large negative number
                    if(delayedTime < 0.0f) {
                        ASSERT_FLOAT_EQ(wsyn1[i], 0.0f);
                        ASSERT_FLOAT_EQ(wsyn2[i], 0.0f);
                    }
                    else {
                        ASSERT_FLOAT_EQ(wsyn1[i], delayedTime);
                        ASSERT_FLOAT_EQ(wsyn2[i], delayedTime);
                    }
                }
            }
        }
    }
};

TEST_F(SimTest, PreWuVarsInSimCode)
{
    Simulate();
}
