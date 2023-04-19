/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ThwampAudioProcessor::ThwampAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
                        apvts(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

ThwampAudioProcessor::~ThwampAudioProcessor()
{
}

//==============================================================================
const juce::String ThwampAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ThwampAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ThwampAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ThwampAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ThwampAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ThwampAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ThwampAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ThwampAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ThwampAudioProcessor::getProgramName (int index)
{
    return {};
}

void ThwampAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ThwampAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void ThwampAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ThwampAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ThwampAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            // ADSR
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");
            
            //OSC
            auto& oscWaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");
            
            //NOISE OSC
            auto& noiseOscWaveChoice = *apvts.getRawParameterValue("OSC2WAVETYPE");

            
            //KICK
            auto& kickAmplitude = *apvts.getRawParameterValue("KICK_AMPLITUDE");
            auto& kickFrequency = *apvts.getRawParameterValue("KICK_FREQUENCY");
            auto& kickPeakPosition = *apvts.getRawParameterValue("KICK_PEAK_POSITION");
            auto& kickAttackCurve = *apvts.getRawParameterValue("KICK_ATTACK_CURVE");
            auto& kickDecayCurve = *apvts.getRawParameterValue("KICK_DECAY_CURVE");
    
            
            // Effect envelopes
            auto& saturationLevel = *apvts.getRawParameterValue("SATURATION_LEVEL");
            auto& saturationDecay = *apvts.getRawParameterValue("SATURATION_DECAY");
            auto& distortionLevel = *apvts.getRawParameterValue("DISTORTION_LEVEL");
            auto& distortionDecay = *apvts.getRawParameterValue("DISTORTION_DECAY");
            
            voice->updateEffectLevels(saturationLevel.load(), distortionLevel.load());
            voice->updateEffectEnvelopes(saturationDecay.load(), distortionDecay.load());
            voice->updateKick(kickAmplitude.load(), kickFrequency.load(), kickPeakPosition.load(), kickAttackCurve.load(), kickDecayCurve.load());
            voice->updateADSR(attack.load(), decay.load(), sustain.load(), release.load());
            voice->getOscillator().setWaveType(oscWaveChoice);
            voice->getNoiseOscillator().setWaveType(noiseOscWaveChoice);
        }
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool ThwampAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ThwampAudioProcessor::createEditor()
{
    return new ThwampAudioProcessorEditor (*this);
}

//==============================================================================
void ThwampAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ThwampAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


juce::AudioProcessorValueTreeState::ParameterLayout ThwampAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "ATTACK",  1 }, "Attack", juce::NormalisableRange<float> { 0.0f, 5.0f }, 0.01f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "DECAY",  1 }, "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "SUSTAIN",  1 }, "Sustain", juce::NormalisableRange<float> { 0.0f, 1.0f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "RELEASE",  1 }, "Release", juce::NormalisableRange<float> { 0.1f, 8.0f }, 1.0f));
    
    // OSC Controlls
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID {"OSC1WAVETYPE", 1}, "Osc 1 Wave Type", juce::StringArray {"Sine", "Saw", "Square", "Noise", "Pulse" }, 0));
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID {"OSC2WAVETYPE", 1}, "Osc 2 Wave Type", juce::StringArray {"Sine", "Saw", "Square", "Noise", "Pulse" }, 3));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"KICK_AMPLITUDE", 1}, "Kick amplitude", 20.0f, 90.0f, 65.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"KICK_FREQUENCY", 1}, "Kick frequency", 3000.0f, 12000.0f, 5000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"KICK_PEAK_POSITION", 1}, "Kick Peak Position", 0.0f, 1.0f, 0.3f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"KICK_ATTACK_CURVE", 1}, "Kick Attack Curve", 1.0f, 5.0f, 4.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"KICK_DECAY_CURVE", 1}, "Kick Decay Curve", 1.0f, 5.0f, 1.0f));

    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"SATURATION_LEVEL", 1}, "Saturation Level", juce::NormalisableRange<float> {4.0f, 12.0f}, 6.8f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"SATURATION_DECAY", 1}, "Saturation Decay", juce::NormalisableRange<float> {0.0f, 1.0f}, 0.5f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"DISTORTION_LEVEL", 1}, "Distortion Level", juce::NormalisableRange<float> {0.1f, 1.0f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"DISTORTION_DECAY", 1}, "Distortion Decay", juce::NormalisableRange<float> {0.0f, 1.0f}, 0.5f));

    

//
    return { params.begin(), params.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ThwampAudioProcessor();
}


