/*
  ==============================================================================

    LFO.h
    Created: 14 Apr 2023 7:41:35pm
    Author:  Matthew Barker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class LFO
{
public:
    LFO();
    ~LFO();

    void prepareToPlay(double sampleRate);
    void setFrequency(float frequency);
    void setAmplitude(float amplitude);
    void setShape(float shape);
    float getNextSample();
    bool isOneCycleFinished() const;
    void restartCycle();
    void setPhase(float newPhase);
    float getPhase();
  


private:
    double sampleRate;
    float frequency;
    float amplitude;
    float shape;
    float phase;
    float phaseIncrement;
    bool oneCycleFinished;
};



