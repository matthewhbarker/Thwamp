/*
  ==============================================================================

    EffectsComponent.h
    Created: 18 Apr 2023 7:26:30pm
    Author:  Matthew Barker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class EffectsComponent  : public juce::Component
{
public:
    EffectsComponent(juce::AudioProcessorValueTreeState& apvts);
    ~EffectsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider saturationLevelSlider;
    juce::Slider saturationDecaySlider;
    
    juce::Slider distortionLevelSlider;
    juce::Slider distortionDecaySlider;
    
    juce::Label saturationLevelLabel;
    juce::Label saturationDecayLabel;
    juce::Label distortionLevelLabel;
    juce::Label distortionDecayLabel;


    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> saturationLevelAttachment;
    std::unique_ptr<SliderAttachment> saturationDecayAttachment;
    
    std::unique_ptr<SliderAttachment> distortionLevelAttachment;
    std::unique_ptr<SliderAttachment> distortionDecayAttachment;
    
    // void setSliderParams(juce::Slider& slider);
    juce::Label& getLabelForSlider(juce::Slider& slider);
    void setSliderParams(juce::Slider& slider, const juce::String& labelText);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsComponent)
};
