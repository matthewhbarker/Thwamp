/*
  ==============================================================================

    WaveformDisplay.h
    Created: 9 Apr 2023 1:05:11pm
    Author:  Matthew Barker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================

class WaveformDisplay : public juce::Component
{
public:
    WaveformDisplay();
    ~WaveformDisplay() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    
    void updateWaveform(float attack, float decay, float sustain, float release /* other parameters */);

private:
    juce::Path waveformPath;
    juce::Colour backgroundColor;
    juce::Colour waveformColor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};
