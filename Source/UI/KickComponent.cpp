/*
  ==============================================================================

    KickComponent.cpp
    Created: 14 Apr 2023 3:22:34pm
    Author:  Matthew Barker

  ==============================================================================
*/

#include <JuceHeader.h>
#include "KickComponent.h"

//==============================================================================
KickComponent::KickComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    kickLevelAttachment = std::make_unique<SliderAttachment>(apvts, "KICK_LEVEL", kickLevelSlider);
    kickDelayAttachment = std::make_unique<SliderAttachment>(apvts, "KICK_DELAY", kickDelaySlider);

    setSliderParams(kickLevelSlider);
    setSliderParams(kickDelaySlider);
}

KickComponent::~KickComponent()
{
}

void KickComponent::paint (juce::Graphics& g)
{
    const auto bounds = getLocalBounds();
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 2 - padding;
    const auto sliderHeight = bounds.getHeight() - padding;
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;

    kickLevelSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    kickDelaySlider.setBounds(kickLevelSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

void KickComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void KickComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
