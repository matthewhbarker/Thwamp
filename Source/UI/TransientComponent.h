/*
  ==============================================================================

    TransientComponent.h
    Created: 13 Apr 2023 12:04:46pm
    Author:  Matthew Barker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class TransientComponent : public juce::Component {
public:
    TransientComponent(juce::AudioProcessorValueTreeState& apvts);
    ~TransientComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void setSliderParams(juce::Slider& slider, const juce::String& labelText);
    juce::Label& getLabelForSlider(juce::Slider& slider);

    juce::Slider transientAmplitudeSlider;
    juce::Slider transientFrequencySlider;
    juce::Slider transientPeakPositionSlider;
    juce::Slider transientAttackCurveSlider;
    juce::Slider transientDecayCurveSlider;

    juce::Label transientAmplitudeLabel;
    juce::Label transientFrequencyLabel;
    juce::Label transientPeakPositionLabel;
    juce::Label transientAttackCurveLabel;
    juce::Label transientDecayCurveLabel;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> transientAmplitudeAttachment;
    std::unique_ptr<SliderAttachment> transientFrequencyAttachment; 
    std::unique_ptr<SliderAttachment> transientPeakPositionAttachment;
    std::unique_ptr<SliderAttachment> transientAttackCurveAttachment;
    std::unique_ptr<SliderAttachment> transientDecayCurveAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransientComponent)
};
