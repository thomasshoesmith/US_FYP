//--------------------------------------------------------------------------
/*! \file decode_matrix_den_delay_individualg_ragged/test.cc

\brief Main test code that is part of the feature testing
suite of minimal models with known analytic outcomes that are used for continuous integration testing.
*/
//--------------------------------------------------------------------------


// Google test includes
#include "gtest/gtest.h"

// Auto-generated simulation code includess
#include "decode_matrix_den_delay_individualg_ragged_CODE/definitions.h"

// **NOTE** base-class for simulation tests must be
// included after auto-generated globals are includes
#include "../../utils/simulation_test_den_delay_decoder_matrix.h"

//----------------------------------------------------------------------------
// SimTest
//----------------------------------------------------------------------------
class SimTest : public SimulationTestDecoderDenDelayMatrix
{
public:
    //----------------------------------------------------------------------------
    // SimulationTest virtuals
    //----------------------------------------------------------------------------
    virtual void Init()
    {
        // Loop through presynaptic neurons
        for(unsigned int i = 0; i < 10; i++)
        {
            // Set rowlength to 1
            rowLengthSyn[i] = 1;

            // Connect row to output neuron with weight of one and dendritic delay of (9 - i)
            indSyn[i] = 0;
            dSyn[i] = (uint8_t)(9 - i);
        }
    }
};

TEST_F(SimTest, DecodeMatrixDenDelayIndividualgRagged)
{
    // Check total error is less than some tolerance
    EXPECT_TRUE(Simulate());
}
