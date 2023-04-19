///*
//  ==============================================================================
//
//    KickComponent.cpp
//    Created: 14 Apr 2023 3:22:34pm
//    Author:  Matthew Barker
//
//  ==============================================================================
//*/

#include <JuceHeader.h>
#include "KickComponent.h"

//==============================================================================
KickComponent::KickComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    kickAmplitudeAttachment = std::make_unique<SliderAttachment>(apvts, "KICK_AMPLITUDE", kickAmplitudeSlider);
    kickFrequencyAttachment = std::make_unique<SliderAttachment>(apvts, "KICK_FREQUENCY", kickFrequencySlider);
    kickPeakPositionAttachment = std::make_unique<SliderAttachment>(apvts, "KICK_PEAK_POSITION", kickPeakPositionSlider);
    kickAttackCurveAttachment = std::make_unique<SliderAttachment>(apvts, "KICK_ATTACK_CURVE", kickAttackCurveSlider);
    kickDecayCurveAttachment = std::make_unique<SliderAttachment>(apvts, "KICK_DECAY_CURVE", kickDecayCurveSlider);

    
    setSliderParams(kickAmplitudeSlider, "Amplitude");
    setSliderParams(kickFrequencySlider, "Frequency");
    setSliderParams(kickPeakPositionSlider, "Peak Position");
    setSliderParams(kickAttackCurveSlider, "Attack Curve");
    setSliderParams(kickDecayCurveSlider, "Decay Curve");
}

KickComponent::~KickComponent()
{
}

void KickComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void KickComponent::resized()
{
    const auto bounds = getLocalBounds();
    const auto padding = 0;
    const auto text_padding = 15;
    const auto sliderWidth = bounds.getWidth() / 3;
    const auto sliderHeight = bounds.getHeight()/2;
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;

    kickAmplitudeSlider.setBounds(sliderStartX, sliderStartY + text_padding, sliderWidth, sliderHeight - text_padding);
    kickFrequencySlider.setBounds(kickAmplitudeSlider.getRight() + padding, sliderStartY + text_padding, sliderWidth, sliderHeight - text_padding);
    kickPeakPositionSlider.setBounds(kickFrequencySlider.getRight() + padding, sliderStartY + text_padding, sliderWidth, sliderHeight - text_padding);
    
    kickAttackCurveSlider.setBounds((bounds.getWidth()/4) - sliderWidth/2, kickAmplitudeSlider.getBottom() + text_padding, sliderWidth, sliderHeight - text_padding);
    kickDecayCurveSlider.setBounds((3 * bounds.getWidth()/4) - sliderWidth/2, kickAmplitudeSlider.getBottom() + text_padding, sliderWidth, sliderHeight - text_padding);

    
    kickAmplitudeLabel.setBounds(kickAmplitudeSlider.getX(), kickAmplitudeSlider.getY() - 20, sliderWidth, 20);
    kickFrequencyLabel.setBounds(kickFrequencySlider.getX(), kickFrequencySlider.getY() - 20, sliderWidth, 20);
    kickPeakPositionLabel.setBounds(kickPeakPositionSlider.getX(), kickPeakPositionSlider.getY() - 20, sliderWidth, 20);
    kickAttackCurveLabel.setBounds(kickAttackCurveSlider.getX(), kickAttackCurveSlider.getY() - 20, sliderWidth, 20);
    kickDecayCurveLabel.setBounds(kickDecayCurveSlider.getX(), kickDecayCurveSlider.getY() - 20, sliderWidth, 20);

}

void KickComponent::setSliderParams(juce::Slider& slider, const juce::String& labelText)
{
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

juce::Label& KickComponent::getLabelForSlider(juce::Slider& slider)
{
    if (&slider == &kickAmplitudeSlider) return kickAmplitudeLabel;
    if (&slider == &kickFrequencySlider) return kickFrequencyLabel;
    if (&slider == &kickPeakPositionSlider) return kickPeakPositionLabel;
    if (&slider == &kickAttackCurveSlider) return kickAttackCurveLabel;
    if (&slider == &kickDecayCurveSlider) return kickDecayCurveLabel;
    
    jassertfalse;
    return kickAmplitudeLabel;
}
