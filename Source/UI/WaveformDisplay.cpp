/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 9 Apr 2023 1:05:11pm
    Author:  Matthew Barker

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay()
    : backgroundColor(juce::Colours::black), waveformColor(juce::Colours::white)
{
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint(juce::Graphics& g)
{
    // Clear the background
//    g.fillAll(backgroundColor);
//
//    // Draw the waveform path
//    g.setColour(waveformColor);
//    g.strokePath(waveformPath, juce::PathStrokeType(2.0f));
}

void WaveformDisplay::resized()
{
    // You may want to scale or position the waveform path based on the size of the component.
}

void WaveformDisplay::updateWaveform(float attack, float decay, float sustain, float release) {
    return;
}
