/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/WaveformDisplay.h"
#include "UI/AdsrComponent.h"
#include "UI/KickComponent.h"
#include "UI/EffectsComponent.h"

//==============================================================================
/**
*/
class ThwampAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ThwampAudioProcessorEditor (ThwampAudioProcessor&);
    ~ThwampAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    ThwampAudioProcessor& audioProcessor;
    
    WaveformDisplay waveformDisplay;
    AdsrComponent adsr;
    KickComponent kick;
    EffectsComponent effects; 

    float screenWidth = 600.0f;
    float screenHeight = 400.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ThwampAudioProcessorEditor)
};
