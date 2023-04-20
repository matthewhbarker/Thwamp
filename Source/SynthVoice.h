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

    void updateADSR(const float attack, const float decay, const float sustain, const float release, const float offset, const double sampleRate);
    void updateOscGain(float newGain);
    void updateNoiseGain(float newGain);
    void updateKick(float newKickAmplitude, float newKickFrequency, float newPeakPosition, float newAttackCurve, float newDecayCurve);
    void updateTransient(float newTransientAmplitude, float newTransientFrequency, float newTransientPeakPosition, float newAttackCurve, float newDecayCurve);
    
    void updateEffectEnvelopes(float saturationDecayTime, float distortionDecayTime);
    void updateEffectLevels(float newSaturationLevel, float newDistortionLevel);
    
    OscData& getOscillator() {return osc; }
    OscData& getNoiseOscillator() { return noiseOsc; }
    
private:
    
    AdsrData adsr;
    juce::AudioBuffer<float> synthBuffer;
    float kickAmplitude;
    float kickFrequency;
    
    OscData osc;
    OscData noiseOsc;
    OscData transientOsc;
    
    AdsrData transientAdsr;
    
    float transientAmplitude;
    float transientFrequency; 

    juce::dsp::Gain<float> oscGain;
    juce::dsp::Gain<float> noiseGain;
    juce::dsp::Gain<float> transientGain; 
    
    int activeNoteCount = 0;
    AdsrData kickAdsr;
    int currentNote;
    
    LFO kickLfo;
    LFO transientLfo;
    
    juce::ADSR saturationEnv;
    juce::ADSR distortionEnv;
    
    float saturationAmount = 12.0f; 
    float saturationLevel = 12.0f;
    
    float distortionThreshold = 0.9f;
    float distortionLevel = 0.9f;
    
    float saturation(float input, float amount);
    float hardClipping(float input, float threshold);

        
    bool isPrepared { false };
    
};
