/*
  ==============================================================================

    OscData.cpp
    Created: 8 Apr 2023 2:00:28pm
    Author:  Matthew Barker

  ==============================================================================
*/


#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    prepare(spec);
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}

void OscData::setWaveType(const int choice)
{
    switch (choice) {
        case 0:
            // Sine wave
            initialise([](float x) { return std::sin (x); });
            break;
        case 1:
            // Saw wave
            initialise( [](float x) { return x / juce::MathConstants<float>::pi; });
            break;
        case 2:
            // Square wave
            initialise( [](float x) {return x < 0.0f ? -1.0f : 1.0f; });
            break;
        case 3:
            // Noise wave
            initialise([](float x) { return (2.0f * rand() / RAND_MAX) - 1.0f; });
            break;
        case 4:
            // Pulse wave
            initialise( [](float x) { return x < 0.5f ? 1.0f : -1.0f; });
            break;
        default:
            jassertfalse; // something went wrong
            break;
    }
}
