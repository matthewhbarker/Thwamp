/*
  ==============================================================================

    SynthVoice.cpp
    Created: 8 Apr 2023 1:12:50pm
    Author:  Matthew Barker

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    std::cout << "kick hit" << std::endl;

    currentNote = midiNoteNumber - 48;
    osc.setWaveFrequency(currentNote);
    noiseOsc.setWaveFrequency(currentNote);
    adsr.noteOn();
    activeNoteCount++;
    // kickLfo.setFrequency(10.0f); // Decrease the LFO frequency for a longer duration
    kickLfo.setAmplitude(20.0f); // Increase the LFO amplitude for a more pronounced kick effect
    kickLfo.setFrequency(9000.0f); // You can adjust this value for the desired LFO frequency
    kickLfo.restartCycle(); // Reset LFO phase

//    if (activeNoteCount == 1) {
//        kickLfo.setPhase(0.0f); // Reset the phase of the LFO
//    }
    
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    
    if (!allowTailOff || !adsr.isActive())
    {
        clearCurrentNote();
    }
    activeNoteCount--;
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}
void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    osc.prepareToPlay(spec);
    noiseOsc.prepareToPlay(spec);
    
    oscGain.prepare(spec);
    oscGain.setGainLinear(0.3f);
    
    noiseGain.prepare(spec);
    noiseGain.setGainLinear(0.001f);
    
    kickLevel = 50;
    kickLfo.prepareToPlay(sampleRate); // Add this line to initialize the LFO with the sample rate

//    kickLfo.prepareToPlay(spec);
    
    isPrepared = true;
}


void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) {

    jassert(isPrepared);
    
    if (!isVoiceActive()) return;
    
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    if (!kickLfo.isOneCycleFinished())
    {
        float lfoValue = kickLfo.getNextSample();
        osc.updateKickMod(lfoValue);
        std::cout << "LFO Value: " << lfoValue << ", LFO Phase: " << kickLfo.getPhase() << std::endl;
    } else {
//        std::cout << "kick end" << std::endl;
        osc.updateKickMod(0.0f);
    }
//
    
    osc.setWaveFrequency(currentNote);
    
    juce::AudioBuffer<float> oscBuffer;
    oscBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    oscBuffer.clear();
    juce::dsp::AudioBlock<float> oscBlock{oscBuffer};
    osc.getNextAudioBlock(oscBlock);
    oscGain.process(juce::dsp::ProcessContextReplacing<float>(oscBlock));

    juce::AudioBuffer<float> noiseBuffer;
    noiseBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    noiseBuffer.clear();
    juce::dsp::AudioBlock<float> noiseBlock{noiseBuffer};
    noiseOsc.getNextAudioBlock(noiseBlock);
    noiseGain.process(juce::dsp::ProcessContextReplacing<float>(noiseBlock));
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
        synthBuffer.addFrom(channel, 0, oscBuffer, channel, 0, numSamples);
        synthBuffer.addFrom(channel, 0, noiseBuffer, channel, 0, numSamples);
    }
    
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    
    float saturationAmount = 5.0f; // Adjust this value to control the amount of saturation
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        //outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        
        for (int sample = 0; sample < numSamples; ++sample)
            {
                float saturatedSample = saturation(synthBuffer.getSample(channel, sample), saturationAmount);
                outputBuffer.addSample(channel, startSample + sample, saturatedSample);
            }

        if (!adsr.isActive())
        {
            clearCurrentNote();
        }
    }
    
}


void SynthVoice::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::updateOscGain(float newGain) {
    oscGain.setGainLinear(newGain);
}

void SynthVoice::updateNoiseGain(float newGain) {
    noiseGain.setGainLinear(newGain);
}

void SynthVoice::updateKick(float newKickLevel, float newKickDelay)
{
    kickLevel = newKickLevel;
    kickDelay = newKickDelay;
}

float SynthVoice::saturation(float input, float amount)
{
    return std::tanh(amount * input) / std::tanh(amount);
}
