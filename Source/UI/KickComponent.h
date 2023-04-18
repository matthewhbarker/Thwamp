/*
  ==============================================================================

    KickComponent.h
    Created: 14 Apr 2023 3:22:34pm
    Author:  Matthew Barker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class KickComponent  : public juce::Component
{
public:
    KickComponent(juce::AudioProcessorValueTreeState& apvts);
    ~KickComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::Slider kickLevelSlider;
    juce::Slider kickDelaySlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> kickLevelAttachment;
    std::unique_ptr<SliderAttachment> kickDelayAttachment;

    void setSliderParams(juce::Slider& slider);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KickComponent)
};
