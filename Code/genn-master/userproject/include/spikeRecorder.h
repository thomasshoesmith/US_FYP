#pragma once

// Standard C++ includes
#include <algorithm>
#include <fstream>
#include <iterator>
#include <list>
#include <string>
#include <tuple>
#include <vector>

// Standard C includes
#include <cassert>
#include <cstdint>

#ifdef _WIN32
#include <intrin.h>
#endif
//----------------------------------------------------------------------------
// SpikeWriterText
//----------------------------------------------------------------------------
//! Class to write spikes to text file
class SpikeWriterText
{
public:
    SpikeWriterText(const std::string &filename, const std::string &delimiter = " ", bool header = false)
    :   m_Stream(filename), m_Delimiter(delimiter)
    {
        // Set precision
        m_Stream.precision(16);

        if(header) {
            m_Stream << "Time [ms], Neuron ID" << std::endl;
        }
    }

// GCC 4.x does not provide a move constructor for ofstream
#if !defined(__GNUC__) || __clang__ || __GNUC__ > 4
    SpikeWriterText(SpikeWriterText&& other)
    :   m_Stream(std::move(other.m_Stream)),
        m_Delimiter(std::move(other.m_Delimiter))
    {
    }
#endif

protected:
    //----------------------------------------------------------------------------
    // Protected API
    //----------------------------------------------------------------------------
    void recordSpikes(double t, unsigned int spikeCount, const unsigned int *currentSpikes)
    {
        for(unsigned int i = 0; i < spikeCount; i++) {
            m_Stream << t << m_Delimiter << currentSpikes[i] << std::endl;
        }
    }

private:
    //----------------------------------------------------------------------------
    // Members
    //----------------------------------------------------------------------------
    std::ofstream m_Stream;
    const std::string m_Delimiter;
};

//----------------------------------------------------------------------------
// SpikeWriterTextCached
//----------------------------------------------------------------------------
//! Class to write spikes to text file, caching in memory before writing
class SpikeWriterTextCached
{
public:
    SpikeWriterTextCached(const std::string &filename, const std::string &delimiter = " ", bool header = false)
    :   m_Stream(filename), m_Delimiter(delimiter)
    {
        // Set precision
        m_Stream.precision(16);

        if(header) {
            m_Stream << "Time [ms], Neuron ID" << std::endl;
        }
    }

// GCC 4.x does not provide a move constructor for ofstream
#if !defined(__GNUC__) || __clang__ || __GNUC__ > 4
    SpikeWriterTextCached(SpikeWriterTextCached&& other)
    :   m_Stream(std::move(other.m_Stream)),
        m_Delimiter(std::move(other.m_Delimiter)),
        m_Cache(std::move(other.m_Cache))
    {
    }
#endif

    ~SpikeWriterTextCached()
    {
        writeCache();
    }

    //----------------------------------------------------------------------------
    // Public API
    //----------------------------------------------------------------------------
    void writeCache()
    {
        // Loop through timesteps
        for(const auto &timestep : m_Cache) {
            // Loop through spikes
            for(unsigned int spike : timestep.second) {
                // Write CSV
                m_Stream << timestep.first << m_Delimiter << spike << std::endl;
            }
        }

        // Clear cache
        m_Cache.clear();
    }

protected:
    //----------------------------------------------------------------------------
    // Protected API
    //----------------------------------------------------------------------------
    void recordSpikes(double t, unsigned int spikeCount, const unsigned int *currentSpikes)
    {
        // Add a new entry to the cache
        m_Cache.emplace_back();

        // Fill in time
        m_Cache.back().first = t;

        // Reserve vector to hold spikes
        m_Cache.back().second.reserve(spikeCount);

        // Copy spikes into vector
        std::copy_n(currentSpikes, spikeCount, std::back_inserter(m_Cache.back().second));
    }

private:
    //----------------------------------------------------------------------------
    // Members
    //----------------------------------------------------------------------------
    std::ofstream m_Stream;
    const std::string m_Delimiter;

    std::list<std::pair<double, std::vector<unsigned int>>> m_Cache;
};

//----------------------------------------------------------------------------
// SpikeRecorderBase
//----------------------------------------------------------------------------
//! Class to read spikes from neuron groups
template<typename Writer = SpikeWriterText>
class SpikeRecorder : public Writer
{
public:
    typedef unsigned int& (*GetCurrentSpikeCountFunc)(unsigned int);
    typedef unsigned int* (*GetCurrentSpikesFunc)(unsigned int);
    
    template<typename... WriterArgs>
    SpikeRecorder(unsigned int batch, GetCurrentSpikesFunc getCurrentSpikes, 
                  GetCurrentSpikeCountFunc getCurrentSpikeCount, WriterArgs &&... writerArgs)
    :   Writer(std::forward<WriterArgs>(writerArgs)...), m_Batch(batch),
        m_GetCurrentSpikes(getCurrentSpikes), m_GetCurrentSpikeCount(getCurrentSpikeCount), m_Sum(0)
    {
    }
    
    template<typename... WriterArgs>
    SpikeRecorder(GetCurrentSpikesFunc getCurrentSpikes, GetCurrentSpikeCountFunc getCurrentSpikeCount,
                  WriterArgs &&... writerArgs)
    :   SpikeRecorder(0, getCurrentSpikes, getCurrentSpikeCount, std::forward<WriterArgs>(writerArgs)...)
    {
    }

    SpikeRecorder(SpikeRecorder<Writer>&& other) = default;

    //----------------------------------------------------------------------------
    // Public API
    //----------------------------------------------------------------------------
    void record(double t)
    {
        const unsigned int spikeCount = m_GetCurrentSpikeCount(m_Batch);
        m_Sum += spikeCount;
        this->recordSpikes(t, spikeCount, m_GetCurrentSpikes(m_Batch));
    }
    
    unsigned int getSum() const{ return m_Sum; }

private:
    //----------------------------------------------------------------------------
    // Members
    //----------------------------------------------------------------------------
    const unsigned int m_Batch;
    GetCurrentSpikesFunc m_GetCurrentSpikes;
    GetCurrentSpikeCountFunc m_GetCurrentSpikeCount;
    unsigned int m_Sum;
};

//! Writes spikes recorded using GeNN's spike timing sytem directly to binary file
/*! \param filename string containing filename to write to.
    \param spkRecord pointer to spike recording data to write (accessable via ``recordSpk<neuron group name>`` or ``recordSpkEvent<neuron group name>``).
    \param popSize number of neurons in population
    \param numTimesteps how many timesteps were recorded (should match the value passed to ``allocateRecordingBuffers``).
    \param append boolean specifying whether to overwrite or append to any existing file called filename. */
inline void writeBinarySpikeRecording(const std::string &filename, const uint32_t *spkRecord,
                                      unsigned int popSize, unsigned int numTimesteps, bool append = false)
{
    // Calculate recording size
    const unsigned int numWords = ((popSize + 31) / 32) * numTimesteps;
    
    // Write spikes to binary file
    std::ofstream spikes(filename, append ? std::ofstream::app | std::ofstream::binary : std::ofstream::binary);
    spikes.write(reinterpret_cast<const char*>(spkRecord), sizeof(uint32_t) * numWords);
}


inline int _clz(unsigned int value)
{
#ifdef _WIN32
    unsigned long leadingZero = 0;
    if(_BitScanReverse(&leadingZero, value)) {
        return 31 - leadingZero;
    }
    else {
        return 32;
    }
#else
    return __builtin_clz(value);
#endif
}

//! Writes spikes recorded using GeNN's spike timing sytem directly to text file 
//! with one column containing spike times in ms and one neuron ids
/*! \param filename string containing filename to write to.
    \param spkRecord pointer to spike recording data to write (accessable via ``recordSpk<neuron group name>`` or ``recordSpkEvent<neuron group name>``).
    \param popSize number of neurons in population
    \param numTimesteps number of timesteps recorded
    \param dt double precision number specifying size of each timestep
    \param delimiter string specifying character(s) which should appear between columns in text file
    \param header boolean specifying whether to write a header row at start of text file or not
    \param append boolean specifying whether to overwrite or append to any existing file called filename. 
    \param startTime double precision number specifying start time of current data.*/
inline void writeTextSpikeRecording(const std::string &filename, const uint32_t *spkRecord,
                                    unsigned int popSize, unsigned int numTimesteps, double dt = 1.0,
                                    const std::string &delimiter = " ", bool header = false, bool append = false, 
                                    double startTime = 0.0)
{
    // Calculate number of words per-timestep
    const unsigned int timestepWords = (popSize + 31) / 32;
    
    // Create stream and set precision
    std::ofstream stream(filename, append ? std::ofstream::app : std::ofstream::out);
    stream.precision(16);
    
    // Write header if required
    if(header) {
        stream << "Time [ms], Neuron ID" << std::endl;
    }
    
    // Loop through timesteps
    for(unsigned int t = 0; t < numTimesteps; t++) {
        // Convert timestep to time
        const double time = startTime + (t * dt);
        
        // Loop through words representing timestep
        for(unsigned int w = 0; w < timestepWords; w++) {
            // Get word
            uint32_t spikeWord = spkRecord[(t * timestepWords) + w];
            
            // Calculate neuron id of highest bit of this word
            unsigned int neuronID = (w * 32) + 31;
            
            // While bits remain
            while(spikeWord != 0) {
                // Calculate leading zeros
                const int numLZ = _clz(spikeWord);
                
                // If all bits have now been processed, zero spike word
                // Otherwise shift past the spike we have found
                spikeWord = (numLZ == 31) ? 0 : (spikeWord << (numLZ + 1));
                
                // Subtract number of leading zeros from neuron ID
                neuronID -= numLZ;
                
                // Write out CSV line
                stream << time << delimiter << neuronID << std::endl;
                
                // New neuron id of the highest bit of this word
                neuronID--;
            }
        }
    }
}
