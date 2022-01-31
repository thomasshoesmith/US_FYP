#pragma once

// Standard C++ includes
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <bitset>

// Platform includes
#ifdef _WIN32
#include <windows.h>
#else
extern "C"
{
#include <dlfcn.h>
}
#endif

// GeNN userproject includes
#include "spikeRecorder.h"

//----------------------------------------------------------------------------
// SharedLibraryModel
//----------------------------------------------------------------------------
// Interface for spike recorders
template<typename scalar = float>
class SharedLibraryModel
{
public:
    SharedLibraryModel()
    :   m_Library(nullptr), m_AllocateMem(nullptr), m_AllocateRecordingBuffers(nullptr),
        m_FreeMem(nullptr), m_Initialize(nullptr), m_InitializeSparse(nullptr), 
        m_StepTime(nullptr), m_PullRecordingBuffersFromDevice(nullptr),
        m_NCCLGenerateUniqueID(nullptr), m_NCCLGetUniqueID(nullptr), 
        m_NCCLInitCommunicator(nullptr), m_NCCLUniqueIDBytes(nullptr)
    {
    }

    SharedLibraryModel(const std::string &pathToModel, const std::string &modelName,
                       bool includeModelNameInDLL = false)
    {
        if(!open(pathToModel, modelName, includeModelNameInDLL)) {
            throw std::runtime_error("Unable to open library");
        }
    }

    virtual ~SharedLibraryModel()
    {
        // Close model library if loaded successfully
        if(m_Library) {
            freeMem();
#ifdef _WIN32
            FreeLibrary(m_Library);
#else
            dlclose(m_Library);
#endif
        }
    }

    //----------------------------------------------------------------------------
    // Public API
    //----------------------------------------------------------------------------
    bool open(const std::string &pathToModel, const std::string &modelName,
              bool includeModelNameInDLL = false)
    {
#ifdef _WIN32
        const std::string runnerName = includeModelNameInDLL ? ("runner_" + modelName) : "runner";
#ifdef _DEBUG
        const std::string libraryName = pathToModel + "\\" + runnerName + "_Debug.dll";
#else
        const std::string libraryName = pathToModel + "\\" + runnerName + "_Release.dll";
#endif
        m_Library = LoadLibrary(libraryName.c_str());
#else
        const std::string libraryName = pathToModel + modelName + "_CODE/librunner.so";
        m_Library = dlopen(libraryName.c_str(), RTLD_NOW);
#endif

        // If it fails throw
        if(m_Library != nullptr) {
            m_AllocateMem = (VoidFunction)getSymbol("allocateMem");
            m_AllocateRecordingBuffers = (EGPFunction)getSymbol("allocateRecordingBuffers", true);
            m_FreeMem = (VoidFunction)getSymbol("freeMem");
            m_GetFreeDeviceMemBytes = (GetFreeMemFunction)getSymbol("getFreeDeviceMemBytes");

            m_Initialize = (VoidFunction)getSymbol("initialize");
            m_InitializeSparse = (VoidFunction)getSymbol("initializeSparse");

            m_StepTime = (VoidFunction)getSymbol("stepTime");
            m_PullRecordingBuffersFromDevice = (VoidFunction)getSymbol("pullRecordingBuffersFromDevice", true);
            
            m_T = (scalar*)getSymbol("t");
            m_Timestep = (unsigned long long*)getSymbol("iT");
            
            m_NCCLGenerateUniqueID = (VoidFunction)getSymbol("ncclGenerateUniqueID", true);
            m_NCCLGetUniqueID = (UCharPtrFunction)getSymbol("ncclGetUniqueID", true);
            m_NCCLInitCommunicator = (NCCLInitCommunicatorFunction)getSymbol("ncclInitCommunicator", true);
            m_NCCLUniqueIDBytes = (unsigned int*)getSymbol("ncclUniqueIDBytes", true);
            return true;
        }
        else {
#ifdef _WIN32
            std::cerr << "Unable to load library - error:" << std::to_string(GetLastError()) << std::endl;;
#else
            std::cerr << "Unable to load library - error:" << dlerror() << std::endl;
#endif
            return false;
        }
    }

    void allocateExtraGlobalParam(const std::string &popName, const std::string &egpName, unsigned int count)
    {
        // Get EGP functions and check allocate exists
        const auto funcs = getEGPFunctions(egpName + popName);
        if(std::get<0>(funcs) == nullptr) {
            throw std::runtime_error("You cannot allocate EGP '" + egpName + "' in population '" + popName + "'");
        }

        // Call allocate
        std::get<0>(funcs)(count);
    }
    
    void allocateExtraGlobalParam(const std::string &popName, const std::string &varName, const std::string &egpName, unsigned int count)
    {
        // Get EGP functions and check allocate exists
        const auto funcs = getEGPFunctions(egpName + varName + popName);
        if(std::get<0>(funcs) == nullptr) {
            throw std::runtime_error("You cannot allocate EGP '" + egpName + "' for initializing '" + varName + "'in population '" + popName + "'");
        }

        // Call allocate
        std::get<0>(funcs)(count);
    }

    void freeExtraGlobalParam(const std::string &popName, const std::string &egpName)
    {
        // Get EGP functions and check free exists
        const auto funcs = getEGPFunctions(egpName + popName);
        if(std::get<1>(funcs) == nullptr) {
            throw std::runtime_error("You cannot free EGP '" + egpName + "' in population '" + popName + "'");
        }

        // Call free
        std::get<1>(funcs)();
    }
    
    void freeExtraGlobalParam(const std::string &popName, const std::string &varName, const std::string &egpName)
    {
        // Get EGP functions and check free exists
        const auto funcs = getEGPFunctions(egpName + varName + popName);
        if(std::get<1>(funcs) == nullptr) {
            throw std::runtime_error("You cannot free EGP '" + egpName + "' for initializing '" + varName + "'in population '" + popName + "'");
        }

        // Call free
        std::get<1>(funcs)();
    }

    void pullStateFromDevice(const std::string &popName)
    {
        // Get push and pull state functions and check pull exists
        const auto pushPull = getPopPushPullFunction(popName + "State");
        if(pushPull.second == nullptr) {
            throw std::runtime_error("You cannot pull state from population '" + popName + "'");
        }

        // Call pull
        pushPull.second();
    }

    void pullSpikesFromDevice(const std::string &popName)
    {
        // Get push and pull spikes functions and check pull exists
        const auto pushPull = getPopPushPullFunction(popName + "Spikes");
        if(pushPull.second == nullptr) {
            throw std::runtime_error("You cannot pull spikes from population '" + popName + "'");
        }

        // Call pull
        pushPull.second();
    }
    
    void pullSpikeEventsFromDevice(const std::string &popName)
    {
        // Get push and pull spike events functions and check pull exists
        const auto pushPull = getPopPushPullFunction(popName + "SpikeEvents");
        if(pushPull.second == nullptr) {
            throw std::runtime_error("You cannot pull spike events from population '" + popName + "'");
        }

        // Call pull
        pushPull.second();
    }

    void pullCurrentSpikesFromDevice(const std::string &popName)
    {
        // Get push and pull spikes functions and check pull exists
        const auto pushPull = getPopPushPullFunction(popName + "CurrentSpikes");
        if(pushPull.second == nullptr) {
            throw std::runtime_error("You cannot pull current spikes from population '" + popName + "'");
        }

        // Call pull
        pushPull.second();
    }
    
    void pullCurrentSpikesEventsFromDevice(const std::string &popName)
    {
        // Get push and pull spike events functions and check pull exists
        const auto pushPull = getPopPushPullFunction(popName + "CurrentSpikeEvents");
        if(pushPull.second == nullptr) {
            throw std::runtime_error("You cannot pull current spike events from population '" + popName + "'");
        }

        // Call pull
        pushPull.second();
    }
    
    void pullConnectivityFromDevice(const std::string &popName)
    {
        // Get push and pull connectivity functions and check pull exists
        const auto pushPull = getPopPushPullFunction(popName + "Connectivity");
        if(pushPull.second == nullptr) {
            throw std::runtime_error("You cannot pull connectivity from population '" + popName + "'");
        }

        // Call pull
        pushPull.second();
    }

    void pullVarFromDevice(const std::string &popName, const std::string &varName)
    {
        // Get push and pull connectivity functions and check pull exists
        const auto pushPull = getPopPushPullFunction(varName + popName);
        if(pushPull.second == nullptr) {
            throw std::runtime_error("You cannot pull var '" + varName + "' from population '" + popName + "'");
        }

        // Call pull
        pushPull.second();
    }

    void pullExtraGlobalParam(const std::string &popName, const std::string &egpName, unsigned int count)
    {
        // Get EGP functions and check pull exists
        const auto funcs = getEGPFunctions(egpName + popName);
        if(std::get<3>(funcs) == nullptr) {
            throw std::runtime_error("You cannot pull EGP '" + egpName + "' from population '" + popName + "'");
        }

        // Call pull
        std::get<3>(funcs)(count);
    }
    
    void pullExtraGlobalParam(const std::string &popName, const std::string &varName, const std::string &egpName, unsigned int count)
    {
        // Get EGP functions and check pull exists
        const auto funcs = getEGPFunctions(egpName + varName + popName);
        if(std::get<3>(funcs) == nullptr) {
            throw std::runtime_error("You cannot pull EGP '" + egpName + "' for initializing '" + varName + "'in population '" + popName + "'");
        }

        // Call pull
        std::get<3>(funcs)(count);
    }

    void pushStateToDevice(const std::string &popName, bool uninitialisedOnly = false)
    {
        // Get push and pull state functions and check pull exists
        const auto pushPull = getPopPushPullFunction(popName + "State");
        if(pushPull.first == nullptr) {
            throw std::runtime_error("You cannot push state to population '" + popName + "'");
        }

        // Call push
        pushPull.first(uninitialisedOnly);
    }

    void pushSpikesToDevice(const std::string &popName, bool uninitialisedOnly = false)
    {
        // Get push and pull spikes functions and check pull exists
        const auto pushPull = getPopPushPullFunction(popName + "Spikes");
        if(pushPull.first == nullptr) {
            throw std::runtime_error("You cannot push spikes to population '" + popName + "'");
        }

        // Call push
        pushPull.first(uninitialisedOnly);
    }
    
    void pushSpikeEventsToDevice(const std::string &popName, bool uninitialisedOnly = false)
    {
        // Get push and pull spike events functions and check pull exists
        const auto pushPull = getPopPushPullFunction(popName + "SpikeEvents");
        if(pushPull.first == nullptr) {
            throw std::runtime_error("You cannot push spike events to population '" + popName + "'");
        }

        // Call push
        pushPull.first(uninitialisedOnly);
    }

    void pushCurrentSpikesToDevice(const std::string &popName, bool uninitialisedOnly = false)
    {
        // Get push and pull spikes functions and check pull exists
        const auto pushPull = getPopPushPullFunction(popName + "CurrentSpikes");
        if(pushPull.first == nullptr) {
            throw std::runtime_error("You cannot push current spikes to population '" + popName + "'");
        }

        // Call push
        pushPull.first(uninitialisedOnly);
    }
    
    void pushCurrentSpikeEventsToDevice(const std::string &popName, bool uninitialisedOnly = false)
    {
        // Get push and pull spike events functions and check pull exists
        const auto pushPull = getPopPushPullFunction(popName + "CurrentSpikeEvents");
        if(pushPull.first == nullptr) {
            throw std::runtime_error("You cannot push current spike events to population '" + popName + "'");
        }

        // Call push
        pushPull.first(uninitialisedOnly);
    }

    void pushConnectivityToDevice(const std::string &popName, bool uninitialisedOnly = false)
    {
        // Get push and pull connectivity functions and check pull exists
        const auto pushPull = getPopPushPullFunction(popName + "Connectivity");
        if(pushPull.first == nullptr) {
            throw std::runtime_error("You cannot push connectivity to population '" + popName + "'");
        }

        // Call push
        pushPull.first(uninitialisedOnly);
    }

    void pushVarToDevice(const std::string &popName, const std::string &varName, bool uninitialisedOnly = false)
    {
        // Get push and pull connectivity functions and check pull exists
        const auto pushPull = getPopPushPullFunction(varName + popName);
        if(pushPull.first == nullptr) {
            throw std::runtime_error("You cannot push var '" + varName + "' to population '" + popName + "'");
        }

        // Call push
        pushPull.first(uninitialisedOnly);
    }

    void pushExtraGlobalParam(const std::string &popName, const std::string &egpName, unsigned int count)
    {
        // Get EGP functions and check push exists
        const auto funcs = getEGPFunctions(egpName + popName);
        if(std::get<2>(funcs) == nullptr) {
            throw std::runtime_error("You cannot push EGP '" + egpName + "' to population '" + popName + "'");
        }

        // Call push
        std::get<2>(funcs)(count);
    }
    
    void pushExtraGlobalParam(const std::string &popName, const std::string &varName, const std::string &egpName, unsigned int count)
    {
        // Get EGP functions and check push exists
        const auto funcs = getEGPFunctions(egpName + varName + popName);
        if(std::get<2>(funcs) == nullptr) {
            throw std::runtime_error("You cannot push EGP '" + egpName + "' for initializing '" + varName + "'in population '" + popName + "'");
        }

        // Call push
        std::get<2>(funcs)(count);
    }

    template<typename Writer, typename... WriterArgs>
    SpikeRecorder<Writer> getSpikeRecorder(const std::string &popName, WriterArgs &&... writerArgs)
    {
        // Get functions to access spikes
        auto getSpikesFn = (typename SpikeRecorder<Writer>::GetCurrentSpikesFunc)getSymbol("get" + popName + "CurrentSpikes");
        auto getSpikeCountFn = (typename SpikeRecorder<Writer>::GetCurrentSpikeCountFunc)getSymbol("get" + popName + "CurrentSpikeCount");

        // Add cached recorder
        return SpikeRecorder<Writer>(getSpikesFn, getSpikeCountFn, std::forward<WriterArgs>(writerArgs)...);
    }

    // Gets a pointer to an array in the shared library
    template<typename T>
    T *getArray(const std::string &varName)
    {
        return *(static_cast<T**>(getSymbol(varName)));
    }

    // Gets a scalar from the shared library
    template<typename T>
    T *getScalar(const std::string &varName)
    {
        return (static_cast<T*>(getSymbol(varName)));
    }

    void allocateMem()
    {
        m_AllocateMem();
    }

    void allocateRecordingBuffers(unsigned int timesteps)
    {
        if(m_AllocateRecordingBuffers == nullptr) {
            throw std::runtime_error("Cannot allocate recording buffers - model may not have recording enabled");
        }
        m_AllocateRecordingBuffers(timesteps);
    }

    void freeMem()
    {
        m_FreeMem();
    }

    size_t getFreeDeviceMemBytes()
    {
        return m_GetFreeDeviceMemBytes();
    }
    
    void ncclGenerateUniqueID()
    {
        if(m_NCCLGenerateUniqueID == nullptr) {
            throw std::runtime_error("Cannot generate NCCL unique ID - model may not have been built with NCCL support");
        }
        m_NCCLGenerateUniqueID();
    }
    
    unsigned char *ncclGetUniqueID()
    {
        if(m_NCCLGetUniqueID == nullptr) {
            throw std::runtime_error("Cannot get NCCL unique ID - model may not have been built with NCCL support");
        }
        return m_NCCLGetUniqueID();
    }
    
    unsigned int ncclGetUniqueIDBytes() const
    {
        if(m_NCCLUniqueIDBytes == nullptr) {
            throw std::runtime_error("Cannot get NCCL unique ID bytes - model may not have been built with NCCL support");
        }
        
        return *m_NCCLUniqueIDBytes;
    }

    void ncclInitCommunicator(int rank, int numRanks)
    {
        if(m_NCCLInitCommunicator == nullptr) {
            throw std::runtime_error("Cannot initialise NCCL communicator - model may not have been built with NCCL support");
        }
        m_NCCLInitCommunicator(rank, numRanks);
    }
    
    
     
    void initialize()
    {
        m_Initialize();
    }

    void initializeSparse()
    {
        m_InitializeSparse();
    }

    void stepTime()
    {
        m_StepTime();
    }
    
    void customUpdate(const std::string &name)
    {
        auto c = m_CustomUpdates.find(name);
        if(c != m_CustomUpdates.cend()) {
            c->second();
        }
        else {
            auto customUpdateFn = (VoidFunction)getSymbol("update" + name);
            m_CustomUpdates.emplace(name, customUpdateFn);
            customUpdateFn();
        }
    }
    
    void pullRecordingBuffersFromDevice()
    {
        if(m_PullRecordingBuffersFromDevice == nullptr) {
            throw std::runtime_error("Cannot pull recording buffers from device - model may not have recording enabled");
        }
        m_PullRecordingBuffersFromDevice();
    }

    scalar getTime() const
    {
        return *m_T;
    }

    unsigned long long getTimestep() const
    {
        return *m_Timestep;
    }

    void setTime(scalar t)
    {
        *m_T = t;
    }

    void setTimestep(unsigned long long iT)
    {
        *m_Timestep = iT;
    }

    double getNeuronUpdateTime() const{ return *(double*)getSymbol("neuronUpdateTime"); }
    double getInitTime() const{ return *(double*)getSymbol("initTime"); }
    double getPresynapticUpdateTime() const{ return *(double*)getSymbol("presynapticUpdateTime"); }
    double getPostsynapticUpdateTime() const{ return *(double*)getSymbol("postsynapticUpdateTime"); }
    double getSynapseDynamicsTime() const{ return *(double*)getSymbol("synapseDynamicsTime"); }
    double getInitSparseTime() const{ return *(double*)getSymbol("initSparseTime"); }
    double getCustomUpdateTime(const std::string &name)const{ return *(double*)getSymbol("customUpdate" + name + "Time"); }
    double getCustomUpdateTransposeTime(const std::string &name)const{ return *(double*)getSymbol("customUpdate" + name + "TransposeTime"); }
    
    void *getSymbol(const std::string &symbolName, bool allowMissing = false, void *defaultSymbol = nullptr) const
    {
#ifdef _WIN32
        void *symbol = GetProcAddress(m_Library, symbolName.c_str());
#else
        void *symbol = dlsym(m_Library, symbolName.c_str());
#endif

        // If this symbol's missing
        if(symbol == nullptr) {
            // If this isn't allowed, throw error
            if(!allowMissing) {
                throw std::runtime_error("Cannot find symbol '" + symbolName + "'");
            }
            // Otherwise, return default
            else {
                return defaultSymbol;
            }
        }
        // Otherwise, return symbolPopulationFuncs
        else {
            return symbol;
        }
    }

private:
    //----------------------------------------------------------------------------
    // Typedefines
    //----------------------------------------------------------------------------
    typedef void (*VoidFunction)(void);
    typedef unsigned char* (*UCharPtrFunction)(void);
    typedef void (*PushFunction)(bool);
    typedef void (*PullFunction)(void);
    typedef void (*EGPFunction)(unsigned int);
    typedef size_t (*GetFreeMemFunction)(void);
    typedef void (*NCCLInitCommunicatorFunction)(int, int);

    typedef std::pair<PushFunction, PullFunction> PushPullFunc;
    typedef std::tuple<EGPFunction, VoidFunction, EGPFunction, EGPFunction> EGPFunc;

    //----------------------------------------------------------------------------
    // Private methods
    //----------------------------------------------------------------------------
    PushPullFunc getPopPushPullFunction(const std::string &description)
    {
        // If description is found, return associated push and pull functions
        const auto popVar = m_PopulationVars.find(description);
        if(popVar != m_PopulationVars.end()) {
            return popVar->second;
        }
        else {
            // Get symbols for push and pull functions
            auto pushFunc = (PushFunction)getSymbol("push" + description + "ToDevice", true);
            auto pullFunc = (PullFunction)getSymbol("pull" + description + "FromDevice", true);

            // Add to map
            auto newPopVar = m_PopulationVars.emplace(std::piecewise_construct,
                                                      std::forward_as_tuple(description),
                                                      std::forward_as_tuple(pushFunc, pullFunc));

            // Return newly added push and pull functions
            return newPopVar.first->second;
        }
    }

    EGPFunc getEGPFunctions(const std::string &description)
    {
        // If description is found, return associated EGP functions
        const auto popEGP = m_PopulationEPGs.find(description);
        if(popEGP != m_PopulationEPGs.end()) {
            return popEGP->second;
        }
        else {
            // Get symbols for push and pull functions
            auto allocateFunc = (EGPFunction)getSymbol("allocate" + description, true);
            auto freeFunc = (VoidFunction)getSymbol("free" + description, true);
            auto pushFunc = (EGPFunction)getSymbol("push" + description + "ToDevice", true);
            auto pullFunc = (EGPFunction)getSymbol("pull" + description + "FromDevice", true);

            // Add to map
            auto newPopEGP = m_PopulationEPGs.emplace(std::piecewise_construct,
                                                      std::forward_as_tuple(description),
                                                      std::forward_as_tuple(allocateFunc, freeFunc,
                                                                            pushFunc, pullFunc));

            // Return newly functions
            return newPopEGP.first->second;
        }
    }

    //----------------------------------------------------------------------------
    // Members
    //----------------------------------------------------------------------------
#ifdef _WIN32
    HMODULE m_Library;
#else
    void *m_Library;
#endif

    VoidFunction m_AllocateMem;
    EGPFunction m_AllocateRecordingBuffers;
    VoidFunction m_FreeMem;
    GetFreeMemFunction m_GetFreeDeviceMemBytes;
    VoidFunction m_Initialize;
    VoidFunction m_InitializeSparse;
    VoidFunction m_StepTime;

    PullFunction m_PullRecordingBuffersFromDevice;

    VoidFunction m_NCCLGenerateUniqueID;
    UCharPtrFunction m_NCCLGetUniqueID;
    NCCLInitCommunicatorFunction m_NCCLInitCommunicator;
    const unsigned int *m_NCCLUniqueIDBytes;
    
    std::unordered_map<std::string, PushPullFunc> m_PopulationVars;
    std::unordered_map<std::string, EGPFunc> m_PopulationEPGs;
    std::unordered_map<std::string, VoidFunction> m_CustomUpdates;
    scalar *m_T;
    unsigned long long *m_Timestep;
};
