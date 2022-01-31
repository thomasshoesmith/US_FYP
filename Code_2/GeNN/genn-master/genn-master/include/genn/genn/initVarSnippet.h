#pragma once

// GeNN includes
#include "snippet.h"

//----------------------------------------------------------------------------
// Macros
//----------------------------------------------------------------------------
#define SET_CODE(CODE) virtual std::string getCode() const override{ return CODE; }

//----------------------------------------------------------------------------
// InitVarSnippet::Base
//----------------------------------------------------------------------------
//! Base class for all value initialisation snippets
namespace InitVarSnippet
{
class GENN_EXPORT Base : public Snippet::Base
{
public:
    //----------------------------------------------------------------------------
    // Declared virtuals
    //----------------------------------------------------------------------------
    virtual std::string getCode() const{ return ""; }

    //----------------------------------------------------------------------------
    // Public API
    //----------------------------------------------------------------------------
    //! Update hash from snippet
    boost::uuids::detail::sha1::digest_type getHashDigest() const;

    //! Validate names of parameters etc
    using Snippet::Base::validate;

    //! Does this var init snippet require kernel-based connectivity
    bool requiresKernel() const;
};

//----------------------------------------------------------------------------
// InitVarSnippet::Uninitialised
//----------------------------------------------------------------------------
//! Used to mark variables as uninitialised - no initialisation code will be run
class Uninitialised : public Base
{
public:
    DECLARE_SNIPPET(InitVarSnippet::Uninitialised, 0);
};

//----------------------------------------------------------------------------
// InitVarSnippet::Constant
//----------------------------------------------------------------------------
//! Initialises variable to a constant value
/*! This snippet takes 1 parameter:
 *
    - \c value - The value to intialise the variable to

    \note This snippet type is seldom used directly - Models::VarInit
    has an implicit constructor that, internally, creates one of these snippets*/
class Constant : public Base
{
public:
    DECLARE_SNIPPET(InitVarSnippet::Constant, 1);

    SET_CODE("$(value) = $(constant);");

    SET_PARAM_NAMES({"constant"});
};

//----------------------------------------------------------------------------
// InitVarSnippet::Kernel
//----------------------------------------------------------------------------
//! Used to initialise synapse variables from a kernel
class Kernel : public Base
{
    DECLARE_SNIPPET(InitVarSnippet::Kernel, 0);

    SET_CODE("$(value) = $(kernel)[$(id_kernel)];");

    SET_EXTRA_GLOBAL_PARAMS({{"kernel", "scalar*"}});
};

//----------------------------------------------------------------------------
// InitVarSnippet::Uniform
//----------------------------------------------------------------------------
//! Initialises variable by sampling from the uniform distribution
/*! This snippet takes 2 parameters:
 *
    - \c min - The minimum value
    - \c max - The maximum value */
class Uniform : public Base
{
public:
    DECLARE_SNIPPET(InitVarSnippet::Uniform, 2);

    SET_CODE(
        "const scalar scale = $(max) - $(min);\n"
        "$(value) = $(min) + ($(gennrand_uniform) * scale);");

    SET_PARAM_NAMES({"min", "max"});
};

//----------------------------------------------------------------------------
// InitVarSnippet::Normal
//----------------------------------------------------------------------------
//! Initialises variable by sampling from the normal distribution
/*! This snippet takes 2 parameters:
 *
    - \c mean - The mean
    - \c sd - The standard deviation*/
class Normal : public Base
{
public:
    DECLARE_SNIPPET(InitVarSnippet::Normal, 2);

    SET_CODE("$(value) = $(mean) + ($(gennrand_normal) * $(sd));");

    SET_PARAM_NAMES({"mean", "sd"});
};

//----------------------------------------------------------------------------
// InitVarSnippet::NormalClipped
//----------------------------------------------------------------------------
//! Initialises variable by sampling from the normal distribution,
//! Resamples value if out of range specified my min and max
/*! This snippet takes 2 parameters:
 *
    - \c mean - The mean
    - \c sd - The standard deviation
    - \c min - The minimum value
    - \c max - The maximum value*/
class NormalClipped : public Base
{
public:
    DECLARE_SNIPPET(InitVarSnippet::NormalClipped, 4);

    SET_CODE(
        "scalar normal;\n"
        "do\n"
        "{\n"
        "   normal = $(mean) + ($(gennrand_normal) * $(sd));\n"
        "} while (normal > $(max) || normal < $(min));\n"
        "$(value) = normal;\n");

    SET_PARAM_NAMES({"mean", "sd", "min", "max"});
};

//----------------------------------------------------------------------------
// InitVarSnippet::NormalClippedDelay
//----------------------------------------------------------------------------
//! Initialises variable by sampling from the normal distribution,
//! Resamples value of out of range specified my min and max.
//! This snippet is intended for initializing (dendritic) delay parameters
//! where parameters are specified in ms but converted to timesteps.
/*! This snippet takes 2 parameters:
 *
    - \c mean - The mean [ms]
    - \c sd - The standard deviation [ms]
    - \c min - The minimum value [ms]
    - \c max - The maximum value [ms]*/
class NormalClippedDelay : public Base
{
public:
    DECLARE_SNIPPET(InitVarSnippet::NormalClippedDelay, 4);

    SET_CODE(
        "scalar normal;\n"
        "do\n"
        "{\n"
        "   normal = $(meanTimestep) + ($(gennrand_normal) * $(sdTimestep));\n"
        "} while (normal > $(maxTimestep) || normal < $(minTimestep));\n"
        "$(value) = rint(normal);\n");

    SET_PARAM_NAMES({"mean", "sd", "min", "max"});
    SET_DERIVED_PARAMS({
        {"meanTimestep", [](const std::vector<double> &pars, double dt){ return pars[0] / dt; }},
        {"sdTimestep", [](const std::vector<double> &pars, double dt){ return pars[1] / dt; }},
        {"minTimestep", [](const std::vector<double> &pars, double dt){ return pars[2] / dt; }},
        {"maxTimestep", [](const std::vector<double> &pars, double dt){ return pars[3] / dt; }}});
};

//----------------------------------------------------------------------------
// InitVarSnippet::Exponential
//----------------------------------------------------------------------------
//! Initialises variable by sampling from the exponential distribution
/*! This snippet takes 1 parameter:
 *
    - \c lambda - mean event rate (events per unit time/distance)*/
class Exponential : public Base
{
public:
    DECLARE_SNIPPET(InitVarSnippet::Exponential, 1);

    SET_CODE("$(value) = $(lambda) * $(gennrand_exponential);");

    SET_PARAM_NAMES({"lambda"});
};

//----------------------------------------------------------------------------
// InitVarSnippet::Gamma
//----------------------------------------------------------------------------
//! Initialises variable by sampling from the gamma distribution
/*! This snippet takes s parameters:
 *
    - \c a - distribution shape
    - \c b - distribution scale*/
class Gamma : public Base
{
public:
    DECLARE_SNIPPET(InitVarSnippet::Gamma, 2);

    SET_CODE("$(value) = $(b) * $(gennrand_gamma, $(a));");

    SET_PARAM_NAMES({"a", "b"});
};

//----------------------------------------------------------------------------
// InitVarSnippet::Binomial
//----------------------------------------------------------------------------
//! Initialises variable by sampling from the binomial distribution
/*! This snippet takes 2 parameters:
 *
    - \c n - number of trials
    - \c p - success probability for each trial*/
class Binomial : public Base
{
public:
    DECLARE_SNIPPET(InitVarSnippet::Binomial, 2);

    SET_CODE("$(value) = $(gennrand_binomial, (unsigned int)$(n), $(p));");

    SET_PARAM_NAMES({"n", "p"});
};
}   // namespace InitVarSnippet
