/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ThwampAudioProcessorEditor::ThwampAudioProcessorEditor (ThwampAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsr (audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (screenWidth, screenHeight);
//    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(adsr);
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
    float buffer = 50.0f;
//    float waveFormDisplayWidth = 500.0f;
//    float waveFormDisplayHeight = 150.0f;
//    waveformDisplay.setBounds(screenWidth/2 - waveFormDisplayWidth/2, buffer, waveFormDisplayWidth, waveFormDisplayHeight);
    
    float adsrComponentWidth = 250.0f;
    float adsrComponentHeight = 150.0f;
    adsr.setBounds(buffer, getHeight()/2 + adsrComponentHeight, adsrComponentWidth, adsrComponentHeight);
}
