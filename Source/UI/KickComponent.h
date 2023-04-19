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
    
    juce::Slider kickAmplitudeSlider;
    juce::Slider kickFrequencySlider;
    juce::Slider kickPeakPositionSlider;
    juce::Slider kickAttackCurveSlider;
    juce::Slider kickDecayCurveSlider;
    
    juce::Label kickAmplitudeLabel;
    juce::Label kickFrequencyLabel;
    juce::Label kickPeakPositionLabel;
    juce::Label kickAttackCurveLabel;
    juce::Label kickDecayCurveLabel;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> kickAmplitudeAttachment;
    std::unique_ptr<SliderAttachment> kickFrequencyAttachment;
    std::unique_ptr<SliderAttachment> kickPeakPositionAttachment;
    std::unique_ptr<SliderAttachment> kickAttackCurveAttachment;
    std::unique_ptr<SliderAttachment> kickDecayCurveAttachment;

    void setSliderParams(juce::Slider& slider, const juce::String& labelText);
    juce::Label& getLabelForSlider(juce::Slider& slider);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KickComponent)
};
