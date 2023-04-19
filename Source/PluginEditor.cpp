/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ThwampAudioProcessorEditor::ThwampAudioProcessorEditor (ThwampAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsr (audioProcessor.apvts), kick (audioProcessor.apvts), effects (audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (screenWidth, screenHeight);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(adsr);
    addAndMakeVisible(kick);
    addAndMakeVisible(effects);
    
}

ThwampAudioProcessorEditor::~ThwampAudioProcessorEditor()
{
}

//==============================================================================
void ThwampAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void ThwampAudioProcessorEditor::resized()
{
    float buffer = 10.0f;
    float waveFormDisplayWidth = 500.0f;
    float waveFormDisplayHeight = 150.0f;
    waveformDisplay.setBounds(screenWidth/2 - waveFormDisplayWidth/2, buffer, waveFormDisplayWidth, waveFormDisplayHeight);
    
    float adsrComponentWidth = getWidth() - (2*buffer);
    float adsrComponentHeight = getHeight()/4 - (2*buffer);
    adsr.setBounds(buffer, getHeight()/2 + buffer, adsrComponentWidth, adsrComponentHeight);
    
    float kickComponentWidth = getWidth()/2 - (2*buffer);
    float kickComponentHeight = getHeight()/4 - (2*buffer);
    kick.setBounds(buffer, 3*getHeight()/4 + buffer, kickComponentWidth, kickComponentHeight);
    
    float effectsComponentWidth = getWidth()/2 - (2*buffer);
    float effectsComponentHeight = getHeight()/4 - (2*buffer);
    effects.setBounds(getWidth()/2 + buffer, 3*getHeight()/4 + buffer, effectsComponentWidth, effectsComponentHeight);
}
