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
    // Calculate the period (p) from the frequency
    float p = 1.0f / frequency;

    // Convert the phase (0 to 2pi) to a time variable (t) in the range of 0 to p
    float t = phase * p / (2.0f * juce::MathConstants<float>::pi);

    // Calculate the exponential increase and decrease
    float expWave;
    if (t < p * peakPosition) {
        expWave = std::pow(std::exp(t / (p * peakPosition)) - 1.0f, attackCurve);
        // Normalize the attack part
        float attackMaxValue = std::pow(std::exp(1) - 1, attackCurve);
        expWave /= attackMaxValue;
    } else {
        expWave = std::pow(std::exp((p - t) / (p * (1 - peakPosition))) - 1.0f, decayCurve);
        // Normalize the decay part
        float decayMaxValue = std::pow(std::exp(1) - 1, decayCurve);
        expWave /= decayMaxValue;
    }

    // Scale the wave by the amplitude
    float sample = amplitude * expWave;

    // Update the phase
    phase += phaseIncrement;
    
    return sample;
}


bool LFO::isOneCycleFinished() const
{
    return oneCycleFinished;
}

void LFO::restartCycle() {
    oneCycleFinished = false;
    phase = 0;
}

void LFO::endCycle() {
    oneCycleFinished = true;
}

void LFO::setPhase(float newPhase) {
    phase = newPhase;
}

float LFO::getPhase() {
    return phase; 
}

void LFO::setPeakPosition(float newPeakPosition) {
    peakPosition = newPeakPosition;
}

void LFO::setAttackDecay(float newAttackCurve, float newDecayCurve) {
    attackCurve = newAttackCurve;
    decayCurve = newDecayCurve;
}

