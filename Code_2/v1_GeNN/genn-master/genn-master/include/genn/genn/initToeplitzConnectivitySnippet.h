#pragma once

// Standard C++ includes
#include <functional>
#include <vector>

// Standard C includes
#include <cassert>
#include <cmath>

// GeNN includes
#include "binomial.h"
#include "snippet.h"

//----------------------------------------------------------------------------
// Macros
//----------------------------------------------------------------------------
#define SET_DIAGONAL_BUILD_CODE(CODE) virtual std::string getDiagonalBuildCode() const override{ return CODE; }
#define SET_DIAGONAL_BUILD_STATE_VARS(...) virtual ParamValVec getDiagonalBuildStateVars() const override{ return __VA_ARGS__; }

#define SET_CALC_MAX_ROW_LENGTH_FUNC(FUNC) virtual CalcMaxLengthFunc getCalcMaxRowLengthFunc() const override{ return FUNC; }
#define SET_CALC_KERNEL_SIZE_FUNC(...) virtual CalcKernelSizeFunc getCalcKernelSizeFunc() const override{ return __VA_ARGS__; }

#define SET_MAX_ROW_LENGTH(MAX_ROW_LENGTH) virtual CalcMaxLengthFunc getCalcMaxRowLengthFunc() const override{ return [](unsigned int, unsigned int, const std::vector<double> &){ return MAX_ROW_LENGTH; }; }

//----------------------------------------------------------------------------
// InitToeplitzConnectivitySnippet::Base
//----------------------------------------------------------------------------
//! Base class for all toeplitz connectivity initialisation snippets
namespace InitToeplitzConnectivitySnippet
{
class GENN_EXPORT Base : public Snippet::Base
{
public:
    //----------------------------------------------------------------------------
    // Typedefines
    //----------------------------------------------------------------------------
    typedef std::function<unsigned int(unsigned int, unsigned int, const std::vector<double> &)> CalcMaxLengthFunc;
    typedef std::function<std::vector<unsigned int>(const std::vector<double> &)> CalcKernelSizeFunc;

    //----------------------------------------------------------------------------
    // Declared virtuals
    //----------------------------------------------------------------------------
    virtual std::string getDiagonalBuildCode() const{ return ""; }
    virtual ParamValVec getDiagonalBuildStateVars() const { return {}; }

    //! Get function to calculate the maximum row length of this connector based on the parameters and the size of the pre and postsynaptic population
    virtual CalcMaxLengthFunc getCalcMaxRowLengthFunc() const{ return CalcMaxLengthFunc(); }

    //! Get function to calculate kernel size required for this conenctor based on its parameters
    virtual CalcKernelSizeFunc getCalcKernelSizeFunc() const{ return CalcKernelSizeFunc(); }

    //------------------------------------------------------------------------
    // Public methods
    //------------------------------------------------------------------------
    //! Update hash from snippet
    boost::uuids::detail::sha1::digest_type getHashDigest() const;

    //! Validate names of parameters etc
    void validate() const;
};

//----------------------------------------------------------------------------
// Init
//----------------------------------------------------------------------------
class Init : public Snippet::Init<InitToeplitzConnectivitySnippet::Base>
{
public:
    Init(const Base *snippet, const std::vector<double> &params)
        : Snippet::Init<Base>(snippet, params)
    {
    }
};

//----------------------------------------------------------------------------
// InitToeplitzConnectivitySnippet::Uninitialised
//----------------------------------------------------------------------------
//! Used to mark connectivity as uninitialised - no initialisation code will be run
class Uninitialised : public Base
{
public:
    DECLARE_SNIPPET(InitToeplitzConnectivitySnippet::Uninitialised, 0);
};

//----------------------------------------------------------------------------
// InitToeplitzConnectivitySnippet::Conv2D
//----------------------------------------------------------------------------
//! Initialises convolutional connectivity
//! Row build state variables are used to convert presynaptic neuron index to rows, columns and channels and, 
//! from these, to calculate the range of postsynaptic rows, columns and channels connections will be made within.
class Conv2D : public Base
{
public:
    DECLARE_SNIPPET(Conv2D, 8);

    SET_PARAM_NAMES({"conv_kh", "conv_kw",
                     "conv_ih", "conv_iw", "conv_ic",
                     "conv_oh", "conv_ow", "conv_oc"});
    SET_DERIVED_PARAMS({{"conv_bw", [](const std::vector<double> &pars, double){ return (((int)pars[3] + (int)pars[1] - 1) - (int)pars[6]) / 2; }},
                        {"conv_bh", [](const std::vector<double> &pars, double){ return (((int)pars[2] + (int)pars[0] - 1) - (int)pars[5]) / 2; }}});

    SET_DIAGONAL_BUILD_STATE_VARS({{"kernRow", "int", "($(id_diag) / (int)$(conv_oc)) / (int)$(conv_kw)"},
                                   {"kernCol", "int", "($(id_diag) / (int)$(conv_oc)) % (int)$(conv_kw)"},
                                   {"kernOutChan", "int", "$(id_diag) % (int)$(conv_oc)"},
                                   {"flipKernRow", "int", "(int)$(conv_kh) - $(kernRow) - 1"},
                                   {"flipKernCol", "int", "(int)$(conv_kw) - $(kernCol) - 1"}});

    SET_DIAGONAL_BUILD_CODE(
        "const int preRow = ($(id_pre) / (int)$(conv_ic)) / (int)$(conv_iw);\n"
        "const int preCol = ($(id_pre) / (int)$(conv_ic)) % (int)$(conv_iw);\n"
        "const int preChan = $(id_pre) % (int)$(conv_ic);\n"
        "// If we haven't gone off edge of output\n"
        "const int postRow = preRow + $(kernRow) - (int)$(conv_bh);\n"
        "const int postCol = preCol + $(kernCol) - (int)$(conv_bw);\n"
        "if(postRow >= 0 && postCol >= 0 && postRow < (int)$(conv_oh) && postCol < (int)$(conv_ow)) {\n"
        "    // Calculate postsynaptic index\n"
        "    const int postInd = ((postRow * (int)$(conv_ow) * (int)$(conv_oc)) +\n"
        "                         (postCol * (int)$(conv_oc)) +\n"
        "                         $(kernOutChan));\n"
        "    $(addSynapse, postInd,  $(flipKernRow), $(flipKernCol), preChan, $(kernOutChan));\n"
        "}\n");

    SET_CALC_MAX_ROW_LENGTH_FUNC(
        [](unsigned int, unsigned int, const std::vector<double> &pars)
        {
            const unsigned int convKH = (unsigned int)pars[0];
            const unsigned int convKW = (unsigned int)pars[1];
            const unsigned int convOC = (unsigned int)pars[7];
            return (convKH * convKW * convOC);
        });

    SET_CALC_KERNEL_SIZE_FUNC(
        [](const std::vector<double> &pars)->std::vector<unsigned int>
        {
            const unsigned int convKH = (unsigned int)pars[0];
            const unsigned int convKW = (unsigned int)pars[1];
            const unsigned int convIC = (unsigned int)pars[4];
            const unsigned int convOC = (unsigned int)pars[7];
            return {convKH, convKW, convIC, convOC};
        });
};

//----------------------------------------------------------------------------
// InitToeplitzConnectivitySnippet::AvgPoolConv2D
//----------------------------------------------------------------------------
//! Initialises convolutional connectivity preceded by averaging pooling
//! Row build state variables are used to convert presynaptic neuron index to rows, columns and channels and, 
//! from these, to calculate the range of postsynaptic rows, columns and channels connections will be made within.
class AvgPoolConv2D : public Base
{
public:
    DECLARE_SNIPPET(AvgPoolConv2D, 12);

    SET_PARAM_NAMES({"conv_kh", "conv_kw",
                     "pool_kh", "pool_kw",
                     "pool_sh", "pool_sw",
                     "pool_ih", "pool_iw", "pool_ic",
                     "conv_oh", "conv_ow", "conv_oc"});
    SET_DERIVED_PARAMS({{"conv_bw", [](const std::vector<double> &pars, double){ return (int(ceil((pars[7] - pars[3] + 1.0) / pars[5])) + (int)pars[1] - 1 - (int)pars[10]) / 2; }},
                        {"conv_bh", [](const std::vector<double> &pars, double){ return (int(ceil((pars[6] - pars[2] + 1.0) / pars[4])) + (int)pars[0] - 1 - (int)pars[9]) / 2; }}});

    SET_DIAGONAL_BUILD_STATE_VARS({{"kernRow", "int", "($(id_diag) / (int)$(conv_oc)) / (int)$(conv_kw)"},
                                   {"kernCol", "int", "($(id_diag) / (int)$(conv_oc)) % (int)$(conv_kw)"},
                                   {"kernOutChan", "int", "$(id_diag) % (int)$(conv_oc)"},
                                   {"flipKernRow", "int", "(int)$(conv_kh) - $(kernRow) - 1"},
                                   {"flipKernCol", "int", "(int)$(conv_kw) - $(kernCol) - 1"}});

    SET_DIAGONAL_BUILD_CODE(
        "// Convert spike ID into row, column and channel going INTO pool\n"
        "const int prePoolInRow = ($(id_pre) / (int)$(pool_ic)) / (int)$(pool_iw);\n"
        "const int prePoolInCol = ($(id_pre) / (int)$(pool_ic)) % (int)$(pool_iw);\n"
        "const int preChan = $(id_pre) % (int)$(pool_ic);\n"
        "// Calculate row and column going OUT of pool\n"
        "const int poolPreOutRow = prePoolInRow / (int)$(pool_sh);\n"
        "const int poolStrideRow = poolPreOutRow * (int)$(pool_sh);\n"
        "const int poolPreOutCol = prePoolInCol / (int)$(pool_sw);\n"
        "const int poolStrideCol = poolPreOutCol * (int)$(pool_sw);\n"
        "if(prePoolInRow < (poolStrideRow + (int)$(pool_kh)) && prePoolInCol < (poolStrideCol + (int)$(pool_kw))) {\n"
        "   // If we haven't gone off edge of output\n"
        "   const int postRow = poolPreOutRow + $(kernRow) - (int)$(conv_bh);\n"
        "   const int postCol = poolPreOutCol + $(kernCol) - (int)$(conv_bw);\n"
        "   if(postRow >= 0 && postCol >= 0 && postRow < (int)$(conv_oh) && postCol < (int)$(conv_ow)) {\n"
        "        // Calculate postsynaptic index\n"
        "       const int postInd = ((postRow * (int)$(conv_ow) * (int)$(conv_oc)) +\n"
        "                             (postCol * (int)$(conv_oc)) +\n"
        "                             $(kernOutChan));\n"
        "       $(addSynapse, postInd,  $(flipKernRow), $(flipKernCol), preChan, $(kernOutChan));\n"
        "   }\n"
        "}\n");

    SET_CALC_MAX_ROW_LENGTH_FUNC(
        [](unsigned int, unsigned int, const std::vector<double> &pars)
        {
            const unsigned int convKH = (unsigned int)pars[0];
            const unsigned int convKW = (unsigned int)pars[1];
            const unsigned int convOC = (unsigned int)pars[11];
            return (convKH * convKW * convOC);
        });

    SET_CALC_KERNEL_SIZE_FUNC(
        [](const std::vector<double> &pars)->std::vector<unsigned int>
        {
            const unsigned int convKH = (unsigned int)pars[0];
            const unsigned int convKW = (unsigned int)pars[1];
            const unsigned int poolIC = (unsigned int)pars[8];
            const unsigned int convOC = (unsigned int)pars[11];
            return {convKH, convKW, poolIC, convOC};
        });
};
}   // namespace InitToeplitzConnectivitySnippet
