/*
 ==============================================================================
 
 TransientComponent.cpp
 Created: 13 Apr 2023 12:04:46pm
 Author:  Matthew Barker
 
 ==============================================================================
 */

#include "TransientComponent.h"

//==============================================================================
TransientComponent::TransientComponent(juce::AudioProcessorValueTreeState& apvts) {
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    transientAmplitudeAttachment = std::make_unique<SliderAttachment>(apvts, "TRANSIENT_AMPLITUDE", transientAmplitudeSlider);
    transientFrequencyAttachment = std::make_unique<SliderAttachment>(apvts, "TRANSIENT_FREQUENCY", transientFrequencySlider);
    transientPeakPositionAttachment = std::make_unique<SliderAttachment>(apvts, "TRANSIENT_PEAK_POSITION", transientPeakPositionSlider);
    transientAttackCurveAttachment = std::make_unique<SliderAttachment>(apvts, "TRANSIENT_ATTACK_CURVE", transientAttackCurveSlider);
    transientDecayCurveAttachment = std::make_unique<SliderAttachment>(apvts, "TRANSIENT_DECAY_CURVE", transientDecayCurveSlider);
    
    setSliderParams(transientAmplitudeSlider, "Amplitude");
    setSliderParams(transientFrequencySlider, "Frequency");
    setSliderParams(transientPeakPositionSlider, "Peak Position");
    setSliderParams(transientAttackCurveSlider, "Attack Curve");
    setSliderParams(transientDecayCurveSlider, "Decay Curve");
}

TransientComponent::~TransientComponent() {
}

void TransientComponent::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::black);
}

void TransientComponent::resized() {
    const auto bounds = getLocalBounds();
    const auto padding = 0;
    const auto text_padding = 15;
    const auto sliderWidth = bounds.getWidth() / 3;
    const auto sliderHeight = bounds.getHeight()/2;
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;

    transientAmplitudeSlider.setBounds(sliderStartX, sliderStartY + text_padding, sliderWidth, sliderHeight - text_padding);
    transientFrequencySlider.setBounds(transientAmplitudeSlider.getRight() + padding, sliderStartY + text_padding, sliderWidth, sliderHeight - text_padding);
    transientPeakPositionSlider.setBounds(transientFrequencySlider.getRight() + padding, sliderStartY + text_padding, sliderWidth, sliderHeight - text_padding);
    
    transientAttackCurveSlider.setBounds((bounds.getWidth()/4) - sliderWidth/2, transientAmplitudeSlider.getBottom() + text_padding, sliderWidth, sliderHeight - text_padding);
    transientDecayCurveSlider.setBounds((3 * bounds.getWidth()/4) - sliderWidth/2, transientAmplitudeSlider.getBottom() + text_padding, sliderWidth, sliderHeight - text_padding);

    
    transientAmplitudeLabel.setBounds(transientAmplitudeSlider.getX(), transientAmplitudeSlider.getY() - 20, sliderWidth, 20);
    transientFrequencyLabel.setBounds(transientFrequencySlider.getX(), transientFrequencySlider.getY() - 20, sliderWidth, 20);
    transientPeakPositionLabel.setBounds(transientPeakPositionSlider.getX(), transientPeakPositionSlider.getY() - 20, sliderWidth, 20);
    transientAttackCurveLabel.setBounds(transientAttackCurveSlider.getX(), transientAttackCurveSlider.getY() - 20, sliderWidth, 20);
    transientDecayCurveLabel.setBounds(transientDecayCurveSlider.getX(), transientDecayCurveSlider.getY() - 20, sliderWidth, 20);


}

void TransientComponent::setSliderParams(juce::Slider& slider, const juce::String& labelText) {
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 50);
    slider.setTextBoxIsEditable(true);
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite); // Remove the text box outline (optional)
    slider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white); // Change the text color (optional)
    addAndMakeVisible(slider);
    
    juce::Label& label = getLabelForSlider(slider);
    label.setText(labelText, juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.setColour(juce::Label::textColourId, juce::Colours::white);
    
    addAndMakeVisible(label);
}

juce::Label& TransientComponent::getLabelForSlider(juce::Slider& slider) {
    if (&slider == &transientAmplitudeSlider) return transientAmplitudeLabel;
    if (&slider == &transientFrequencySlider) return transientFrequencyLabel;
    if (&slider == &transientPeakPositionSlider) return transientPeakPositionLabel;
    if (&slider == &transientAttackCurveSlider) return transientAttackCurveLabel;
    if (&slider == &transientDecayCurveSlider) return transientDecayCurveLabel;
    
    jassertfalse;
    return transientAmplitudeLabel;
}
