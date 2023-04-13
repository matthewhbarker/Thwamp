/*
  ==============================================================================

    OscData.h
    Created: 8 Apr 2023 2:00:28pm
    Author:  Matthew Barker

  ==============================================================================
*/

#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator <float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock);
    void setWaveFrequency(const int midiNoteNumber);
    void setWaveType(const int choice);
    
private:
};
