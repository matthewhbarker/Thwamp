/*
  ==============================================================================

    AdsrData.cpp
    Created: 8 Apr 2023 2:00:37pm
    Author:  Matthew Barker

  ==============================================================================
*/

//#include "AdsrData.h"
//
//void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release)
//{
//    adsrParams.attack = attack;
//    adsrParams.decay = decay;
//    adsrParams.sustain = sustain;
//    adsrParams.release = release;
//
//    setParameters(adsrParams);
//}

#include "AdsrData.h"

void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release, const float offset, const double sampleRate)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    setParameters(adsrParams);

    // Calculate the offset in samples
    offsetSamples = static_cast<int>(offset * sampleRate);
}

void AdsrData::applyEnvelopeToBuffer(juce::AudioBuffer<float>& buffer, int startSample, int numSamples)
{
    for (int sample = 0; sample < numSamples; ++sample)
        {
            // If the current offset sample is less than the offset samples, clear the buffer
            if (currentOffsetSample < offsetSamples)
            {
                for (int channel = 0; channel < buffer.getNumChannels(); ++channel) // Skip the sample, it doesnt need changing
                {
                    buffer.setSample(channel, startSample + sample, 0.0f);
                }
            }
            else
            {
                // Apply the envelope to the buffer
                float env = getNextSample();
                for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
                {
                    float inputSample = buffer.getSample(channel, startSample + sample);
                    buffer.setSample(channel, startSample + sample, inputSample * env);
                }
            }

            // Increment the current offset sample
            currentOffsetSample++;
        }
}


