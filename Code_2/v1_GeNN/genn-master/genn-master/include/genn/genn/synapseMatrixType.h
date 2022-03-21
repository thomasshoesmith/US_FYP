#pragma once

//----------------------------------------------------------------------------
// Enumerations
//----------------------------------------------------------------------------
//! Flags defining differnet types of synaptic matrix connectivity
enum class SynapseMatrixConnectivity : unsigned int
{
    DENSE       = (1 << 0),
    BITMASK     = (1 << 1),
    SPARSE      = (1 << 2),
    PROCEDURAL  = (1 << 3),
    TOEPLITZ    = (1 << 4),
};

//! Flags defining different types of synaptic matrix connectivity
enum class SynapseMatrixWeight : unsigned int
{
    GLOBAL          = (1 << 5),
    INDIVIDUAL      = (1 << 6),
    PROCEDURAL      = (1 << 7),
    INDIVIDUAL_PSM  = (1 << 8),
    KERNEL          = (1 << 9)
};

//! Supported combinations of SynapticMatrixConnectivity and SynapticMatrixWeight
enum class SynapseMatrixType : unsigned int
{
    DENSE_GLOBALG                       = static_cast<unsigned int>(SynapseMatrixConnectivity::DENSE) | static_cast<unsigned int>(SynapseMatrixWeight::GLOBAL),
    DENSE_GLOBALG_INDIVIDUAL_PSM        = static_cast<unsigned int>(SynapseMatrixConnectivity::DENSE) | static_cast<unsigned int>(SynapseMatrixWeight::GLOBAL) | static_cast<unsigned int>(SynapseMatrixWeight::INDIVIDUAL_PSM),
    DENSE_INDIVIDUALG                   = static_cast<unsigned int>(SynapseMatrixConnectivity::DENSE) | static_cast<unsigned int>(SynapseMatrixWeight::INDIVIDUAL) | static_cast<unsigned int>(SynapseMatrixWeight::INDIVIDUAL_PSM),
    DENSE_PROCEDURALG                   = static_cast<unsigned int>(SynapseMatrixConnectivity::DENSE) | static_cast<unsigned int>(SynapseMatrixWeight::PROCEDURAL) | static_cast<unsigned int>(SynapseMatrixWeight::INDIVIDUAL_PSM),
    BITMASK_GLOBALG                     = static_cast<unsigned int>(SynapseMatrixConnectivity::BITMASK) | static_cast<unsigned int>(SynapseMatrixWeight::GLOBAL),
    BITMASK_GLOBALG_INDIVIDUAL_PSM      = static_cast<unsigned int>(SynapseMatrixConnectivity::BITMASK) | static_cast<unsigned int>(SynapseMatrixWeight::GLOBAL) | static_cast<unsigned int>(SynapseMatrixWeight::INDIVIDUAL_PSM),
    SPARSE_GLOBALG                      = static_cast<unsigned int>(SynapseMatrixConnectivity::SPARSE) | static_cast<unsigned int>(SynapseMatrixWeight::GLOBAL),
    SPARSE_GLOBALG_INDIVIDUAL_PSM       = static_cast<unsigned int>(SynapseMatrixConnectivity::SPARSE) | static_cast<unsigned int>(SynapseMatrixWeight::GLOBAL) | static_cast<unsigned int>(SynapseMatrixWeight::INDIVIDUAL_PSM),
    SPARSE_INDIVIDUALG                  = static_cast<unsigned int>(SynapseMatrixConnectivity::SPARSE) | static_cast<unsigned int>(SynapseMatrixWeight::INDIVIDUAL) | static_cast<unsigned int>(SynapseMatrixWeight::INDIVIDUAL_PSM),
    PROCEDURAL_GLOBALG                  = static_cast<unsigned int>(SynapseMatrixConnectivity::PROCEDURAL) | static_cast<unsigned int>(SynapseMatrixWeight::GLOBAL),
    PROCEDURAL_GLOBALG_INDIVIDUAL_PSM   = static_cast<unsigned int>(SynapseMatrixConnectivity::PROCEDURAL) | static_cast<unsigned int>(SynapseMatrixWeight::GLOBAL) | static_cast<unsigned int>(SynapseMatrixWeight::INDIVIDUAL_PSM),
    PROCEDURAL_PROCEDURALG              = static_cast<unsigned int>(SynapseMatrixConnectivity::PROCEDURAL) | static_cast<unsigned int>(SynapseMatrixWeight::PROCEDURAL) | static_cast<unsigned int>(SynapseMatrixWeight::INDIVIDUAL_PSM),
    PROCEDURAL_KERNELG                  = static_cast<unsigned int>(SynapseMatrixConnectivity::PROCEDURAL) | static_cast<unsigned int>(SynapseMatrixWeight::KERNEL) | static_cast<unsigned int>(SynapseMatrixWeight::INDIVIDUAL_PSM),
    TOEPLITZ_KERNELG                    = static_cast<unsigned int>(SynapseMatrixConnectivity::TOEPLITZ) | static_cast<unsigned int>(SynapseMatrixWeight::KERNEL) | static_cast<unsigned int>(SynapseMatrixWeight::INDIVIDUAL_PSM),
};

//----------------------------------------------------------------------------
// Operators
//----------------------------------------------------------------------------
inline bool operator & (SynapseMatrixType type, SynapseMatrixConnectivity connType)
{
    return (static_cast<unsigned int>(type) & static_cast<unsigned int>(connType)) != 0;
}

inline bool operator & (SynapseMatrixType type, SynapseMatrixWeight weightType)
{
    return (static_cast<unsigned int>(type) & static_cast<unsigned int>(weightType)) != 0;
}

inline SynapseMatrixType operator | (SynapseMatrixWeight weightType, SynapseMatrixConnectivity connType)
{
    return static_cast<SynapseMatrixType>(static_cast<unsigned int>(weightType) | static_cast<unsigned int>(connType));
}

//----------------------------------------------------------------------------
// Helpers
//----------------------------------------------------------------------------
// **THINK** these are kinda nasty as they can return things that aren't actually in the bit enums i.e. ORd together things
inline SynapseMatrixConnectivity getSynapseMatrixConnectivity(SynapseMatrixType type)
{
    return static_cast<SynapseMatrixConnectivity>(static_cast<unsigned int>(type) & 0x1F);
}

inline SynapseMatrixWeight getSynapseMatrixWeight(SynapseMatrixType type)
{
    return static_cast<SynapseMatrixWeight>(static_cast<unsigned int>(type) & ~0x1F);
}
