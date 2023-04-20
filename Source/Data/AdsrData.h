/*
  ==============================================================================

    AdsrData.h
    Created: 8 Apr 2023 2:00:37pm
    Author:  Matthew Barker

  ==============================================================================
*/

//#pragma once
//#include <JuceHeader.h>
//
//class AdsrData : public juce::ADSR
//{
//public:
//    void updateADSR(const float attack, const float decay, const float sustain, const float release);
//
//
//private:
//    juce::ADSR::Parameters adsrParams;
//};

#pragma once
#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release, const float offset, const double sampleRate);
    void applyEnvelopeToBuffer(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);
    
private:
    juce::ADSR::Parameters adsrParams;
    int offsetSamples;
    int currentOffsetSample = 0;
};
