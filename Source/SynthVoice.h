/*
  ==============================================================================

    SynthVoice.h
    Created: 8 Apr 2023 1:12:50pm
    Author:  Matthew Barker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"

#include "Data/AdsrData.h"
#include "Data/OscData.h"

#include "Data/LFO.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
    void updateOscGain(float newGain);
    void updateNoiseGain(float newGain);
    void updateKick(float newKickLevel, float newKickDelay);
    
    OscData& getOscillator() {return osc; }
    OscData& getNoiseOscillator() { return noiseOsc; }
    
private:
    
    AdsrData adsr;
    juce::AudioBuffer<float> synthBuffer;
    float kickLevel;
    float kickDelay;
    
    OscData osc;
    OscData noiseOsc;

    juce::dsp::Gain<float> oscGain;
    juce::dsp::Gain<float> noiseGain;
    
    int activeNoteCount = 0;
    AdsrData kickAdsr;
    int currentNote;
    
    int kickSampleCounter;
    
    LFO kickLfo;
    
    float saturation(float input, float amount);
    
    bool isPrepared { false };
    
};
