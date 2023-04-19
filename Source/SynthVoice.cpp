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

// This function is called when a new note starts
void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    // Print to console when a note is played
    std::cout << "kick hit" << std::endl;
    
    // Set the current note and update the oscillators' frequency
    currentNote = midiNoteNumber - 48;
    osc.setWaveFrequency(currentNote);
    noiseOsc.setWaveFrequency(currentNote);

    // Trigger the ADSR envelope and increment the active note count
    adsr.noteOn();
    activeNoteCount++;
    
    // Set the base MIDI note and calculate frequencies for the current and base notes
    int baseMidiNote = 72; // C5
    float currentFrequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    float baseFrequency = juce::MidiMessage::getMidiNoteInHertz(baseMidiNote);

    // Calculate and set the amplitude scaling factor
    float amplitudeScalingFactor = 1 + 0.25f * ((currentFrequency - baseFrequency) / (baseFrequency));
    float updatedKickAmplitude = kickAmplitude * amplitudeScalingFactor;
    kickLfo.setAmplitude(updatedKickAmplitude); // Set the adjusted LFO amplitude

    // Calculate and set the updated kick frequency
    float kickFreqStabilizer = kickFrequency * (currentFrequency / baseFrequency - 1); // makes the kick sound better at higher Freqs
    float updatedKickFrequency = kickFrequency + kickFreqStabilizer;
    std::cout << "Old Kick Frequency: " << kickFrequency << ", New Kick Frequency: " << updatedKickFrequency << std::endl;
    kickLfo.setFrequency(updatedKickFrequency);

    // Reset LFO phase
    kickLfo.restartCycle();

    // Set transient parameters
    transientParams.attackTime = 0.1f; // Attack time for the transient (in milliseconds)
    transientParams.decayTime = 0.1f;  // Decay time for the transient (in milliseconds)
    transientParams.strength = 0.2f;   // Strength of the transient
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
    oscGain.prepare(spec);
    oscGain.setGainLinear(0.3f);
    
    noiseOsc.prepareToPlay(spec);
    noiseGain.prepare(spec);
    noiseGain.setGainLinear(0.0005f);
    
    kickLfo.prepareToPlay(sampleRate); // Add this line to initialize the LFO with the sample rate
    
    saturationEnv.setSampleRate(sampleRate);
    distortionEnv.setSampleRate(sampleRate);
    
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
        std::cout << "(" << kickLfo.getPhase() << ", " << lfoValue << ")," <<std::endl;
        if (kickLfo.getPhase() >= juce::MathConstants<float>::twoPi) {
            kickLfo.endCycle();
        }
        
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
    
    // applyTransient(synthBuffer, transientParams, getSampleRate());
        
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        for (int sample = 0; sample < numSamples; ++sample)
            {
//                float saturatedSample = saturation(synthBuffer.getSample(channel, sample), saturationAmount);
//                float distortedSample = hardClipping(saturatedSample, distortionThreshold);
//                outputBuffer.addSample(channel, startSample + sample, distortedSample);
                float saturationEnvValue = saturationEnv.getNextSample();
                float distortionEnvValue = distortionEnv.getNextSample();

                float saturatedSample = saturation(synthBuffer.getSample(channel, sample), saturationLevel * (1 - saturationEnvValue));
                float distortedSample = hardClipping(saturatedSample, distortionLevel * (1 - distortionEnvValue));

                outputBuffer.addSample(channel, startSample + sample, distortedSample);
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

void SynthVoice::updateKick(float newKickAmplitude, float newKickFrequency, float newPeakPosition, float newAttackCurve, float newDecayCurve)
{
    kickAmplitude = newKickAmplitude;
    kickFrequency = newKickFrequency;
    kickLfo.setPeakPosition(newPeakPosition);
    kickLfo.setAttackDecay(newAttackCurve, newDecayCurve);
}

float SynthVoice::saturation(float input, float amount)
{
    return std::tanh(amount * input) / std::tanh(amount);
}

float SynthVoice::hardClipping(float input, float threshold)
{
    if (input > threshold)
        return threshold;
    else if (input < -threshold)
        return -threshold;
    else
        return input;
}

void SynthVoice::updateEffectEnvelopes(float saturationDecayTime, float distortionDecayTime)
{
    juce::ADSR::Parameters saturationEnvParams;
    saturationEnvParams.attack = 0.0f;
    saturationEnvParams.decay = saturationDecayTime;
    saturationEnvParams.sustain = 0.0f;
    saturationEnvParams.release = 0.0f;

    saturationEnv.setParameters(saturationEnvParams);

    juce::ADSR::Parameters distortionEnvParams;
    distortionEnvParams.attack = 0.0f;
    distortionEnvParams.decay = distortionDecayTime;
    distortionEnvParams.sustain = 0.0f;
    distortionEnvParams.release = 0.0f;

    distortionEnv.setParameters(distortionEnvParams);
}

void SynthVoice::updateEffectLevels(float newSaturationLevel, float newDistortionLevel)
{
    saturationLevel = newSaturationLevel;
    distortionLevel = newDistortionLevel;
}

//void SynthVoice::applyTransient(juce::AudioBuffer<float>& buffer, const TransientParameters& params, double sampleRate)
//{
//    juce::AudioBuffer<float> envelopeBuffer;
//    generateTransientEnvelope(envelopeBuffer, params, sampleRate);
//
//    int totalSamples = envelopeBuffer.getNumSamples();
//
//    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
//    {
//        float* channelData = buffer.getWritePointer(channel);
//
//        for (int sample = 0; sample < totalSamples; ++sample)
//        {
//            float transientAmplitude = envelopeBuffer.getSample(0, sample);
//            channelData[sample] = (1.0f - transientAmplitude) * channelData[sample] + transientAmplitude * (channelData[sample] + transientAmplitude * channelData[sample]);
//        }
//    }
//}
//
//void SynthVoice::generateTransientEnvelope(juce::AudioBuffer<float>& envelopeBuffer, const TransientParameters& params, double sampleRate)
//{
//    int attackSamples = static_cast<int>(params.attackTime * sampleRate / 1000.0);
//    int decaySamples = static_cast<int>(params.decayTime * sampleRate / 1000.0);
//    int totalSamples = attackSamples + decaySamples;
//
//    envelopeBuffer.setSize(1, totalSamples);
//    envelopeBuffer.clear();
//
//    float* envelopeData = envelopeBuffer.getWritePointer(0);
//
//    for (int i = 0; i < attackSamples; ++i)
//    {
//        envelopeData[i] = juce::jmap<float>(static_cast<float>(i), 0.0f, static_cast<float>(attackSamples), 0.0f, params.strength);
//    }
//
//    for (int i = attackSamples; i < totalSamples; ++i)
//    {
//        envelopeData[i] = juce::jmap<float>(static_cast<float>(i), static_cast<float>(attackSamples), static_cast<float>(totalSamples), params.strength, 0.0f);
//    }
//}
