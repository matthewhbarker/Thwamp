#include <JuceHeader.h>
#include "EffectsComponent.h"

//==============================================================================
EffectsComponent::EffectsComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    saturationLevelAttachment = std::make_unique<SliderAttachment>(apvts, "SATURATION_LEVEL", saturationLevelSlider);
    saturationDecayAttachment = std::make_unique<SliderAttachment>(apvts, "SATURATION_DECAY", saturationDecaySlider);
    
    distortionLevelAttachment = std::make_unique<SliderAttachment>(apvts, "DISTORTION_LEVEL", distortionLevelSlider);
    distortionDecayAttachment = std::make_unique<SliderAttachment>(apvts, "DISTORTION_DECAY", distortionDecaySlider);
    
    setSliderParams(saturationLevelSlider, "Saturation Level");
    setSliderParams(saturationDecaySlider, "Saturation Decay");
    setSliderParams(distortionLevelSlider, "Distortion Level");
    setSliderParams(distortionDecaySlider, "Distortion Decay");
}

EffectsComponent::~EffectsComponent()
{
}

void EffectsComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void EffectsComponent::resized()
{
    const auto bounds = getLocalBounds();
    const auto padding = 10;
    const auto text_padding = 15;
    const auto sliderWidth = bounds.getWidth() / 2;
    const auto sliderHeight = bounds.getHeight()/2;
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;

    saturationLevelSlider.setBounds(sliderStartX, sliderStartY + text_padding, sliderWidth, sliderHeight - text_padding);
    saturationDecaySlider.setBounds(sliderStartX, saturationLevelSlider.getBottom()+ text_padding, sliderWidth, sliderHeight - text_padding);
    
    distortionLevelSlider.setBounds(saturationLevelSlider.getRight() + padding, sliderStartY + text_padding, sliderWidth, sliderHeight - text_padding);
    distortionDecaySlider.setBounds(saturationDecaySlider.getRight() + padding, distortionLevelSlider.getBottom() + text_padding, sliderWidth, sliderHeight - text_padding);

    saturationLevelLabel.setBounds(saturationLevelSlider.getX(), saturationLevelSlider.getY() - 20, sliderWidth, 20);
    saturationDecayLabel.setBounds(saturationDecaySlider.getX(), saturationDecaySlider.getY() - 20, sliderWidth, 20);
    distortionLevelLabel.setBounds(distortionLevelSlider.getX(), distortionLevelSlider.getY() - 20, sliderWidth, 20);
    distortionDecayLabel.setBounds(distortionDecaySlider.getX(), distortionDecaySlider.getY() - 20, sliderWidth, 20);
}

void EffectsComponent::setSliderParams(juce::Slider& slider, const juce::String& labelText)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 50);
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    slider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    addAndMakeVisible(slider);

    juce::Label& label = getLabelForSlider(slider);
    label.setText(labelText, juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.setColour(juce::Label::textColourId, juce::Colours::white);


    addAndMakeVisible(label);
}

juce::Label& EffectsComponent::getLabelForSlider(juce::Slider& slider)
{
 if (&slider == &saturationLevelSlider) return saturationLevelLabel;
 if (&slider == &saturationDecaySlider) return saturationDecayLabel;
 if (&slider == &distortionLevelSlider) return distortionLevelLabel;
 if (&slider == &distortionDecaySlider) return distortionDecayLabel;

 jassertfalse;
 return saturationLevelLabel;
}
