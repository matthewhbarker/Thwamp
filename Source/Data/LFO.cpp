/*
  ==============================================================================

    LFO.cpp
    Created: 14 Apr 2023 7:41:35pm
    Author:  Matthew Barker

  ==============================================================================
*/

#include "LFO.h"

LFO::LFO()
    : sampleRate(0.0), frequency(0.0f), amplitude(0.0f), shape(0.0f),
      phase(0.0f), phaseIncrement(0.0f), oneCycleFinished(false)
{
}

LFO::~LFO()
{
}

void LFO::prepareToPlay(double sr)
{
    sampleRate = sr;
}

void LFO::setFrequency(float freq)
{
    frequency = freq;
    phaseIncrement = 2.0f * juce::MathConstants<float>::pi * frequency / static_cast<float>(sampleRate);
}

void LFO::setAmplitude(float amp)
{
    amplitude = amp;
}

void LFO::setShape(float shp)
{
    shape = shp;
}

float LFO::getNextSample()
{
//    // Calculate the period (p) from the frequency
//    float p = 1.0f / frequency;
//
//    // Convert the phase (0 to 2pi) to a time variable (t) in the range of 0 to p
//    float t = phase * p / (2.0f * juce::MathConstants<float>::pi);
//
////    // Calculate the triangle wave using the Wikipedia equation
////    float triangle = 2.0f * std::abs(t / p - std::floor(t / p + 0.5f));
////
////    float shapeFactor = 5.0f; // You can adjust this value to change the skewness of the waveform
////    float skewedTriangle = std::pow(triangle, shapeFactor);
////
////    float maxValue = std::pow(1.0f, shapeFactor);
////    float normalizedSkewedTriangle = skewedTriangle / maxValue;
////
////
////    // Scale the triangle wave by the amplitude
////    //float sample = amplitude * triangle;
////    float sample = amplitude * normalizedSkewedTriangle;
////     Calculate the triangle wave using the Wikipedia equation
//    // Calculate the custom sine wave
//    // Calculate the first triangle wave
//        float triangle1 = 2.0f * std::abs(t / p - std::floor(t / p + 0.5f));
//
//        // Calculate the second triangle wave with a phase offset
//        float phaseOffset = 0.5f; // Adjust this value to change the phase difference
//        float t2 = (phase + phaseOffset) * p / (2.0f * juce::MathConstants<float>::pi);
//        float triangle2 = 2.0f * std::abs(t2 / p - std::floor(t2 / p + 0.5f));
//
//        // Combine the two triangle waves and normalize the result
//        float combinedWave = (triangle1 + triangle2) / 2.0f;
//
//        // Scale the combined wave by the amplitude
//        float sample = amplitude * combinedWave;
//
//
//    // Update the phase
//    phase += phaseIncrement;
//
//    if (phase >= juce::MathConstants<float>::twoPi)
//    {
//        phase -= juce::MathConstants<float>::twoPi;
//        oneCycleFinished = true;
//    }
//
//    return sample;
    
    // Calculate the period (p) from the frequency
    float p = 1.0f / frequency;

    // Convert the phase (0 to 2pi) to a time variable (t) in the range of 0 to p
    float t = phase * p / (2.0f * juce::MathConstants<float>::pi);

    // Calculate the exponential increase and decrease
    float expWave;
    if (t < p / 2.0f) {
        expWave = std::exp(t * 2.0f / p) - 1.0f;
    } else {
        expWave = std::exp((p - t) * 2.0f / p) - 1.0f;
    }

    // Normalize the wave
    float maxValue = std::exp(1) - 1;
    float normalizedExpWave = expWave / maxValue;

    // Scale the wave by the amplitude
    float sample = amplitude * normalizedExpWave;

    // Update the phase
    phase += phaseIncrement;

    if (phase >= juce::MathConstants<float>::twoPi)
    {
        phase -= juce::MathConstants<float>::twoPi;
        oneCycleFinished = true;
    }

    return sample;
    
}


bool LFO::isOneCycleFinished() const
{
    return oneCycleFinished;
}

void LFO::restartCycle() {
    oneCycleFinished = false;
}

void LFO::setPhase(float newPhase) {
    phase = newPhase;
}

float LFO::getPhase() {
    return phase; 
}
