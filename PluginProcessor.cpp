#include "PluginProcessor.h"
#include "PluginEditor.h"

CenteredSoftShaperAudioProcessor::CenteredSoftShaperAudioProcessor()
    : parameters(*this, nullptr, "PARAMETERS", {
        std::make_unique<juce::AudioParameterFloat>("drive",  "Drive",  0.1f, 5.0f, 1.0f),
        std::make_unique<juce::AudioParameterFloat>("output", "Output", 0.1f, 10.0f, 1.0f)
    })
{
}

bool CenteredSoftShaperAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}

void CenteredSoftShaperAudioProcessor::prepareToPlay(double, int) {}

void CenteredSoftShaperAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    const float drive  = *parameters.getRawParameterValue("drive");
    const float output = *parameters.getRawParameterValue("output");

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* samples = buffer.getWritePointer(channel);

        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            float a = samples[i] * drive;

            // Polynomial shaper core
            float y = -0.1f * std::pow(a, 4.0f) + 0.2f * std::pow(a, 2.0f) + a;

            // Soft limiter for stability
            y = y / (1.0f + std::abs(y));

            samples[i] = y * output;
        }
    }
}

void CenteredSoftShaperAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary(*xml, destData);
}

void CenteredSoftShaperAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary(data, sizeInBytes));

    if (xml != nullptr && xml->hasTagName(parameters.state.getType()))
        parameters.replaceState(juce::ValueTree::fromXml(*xml));
}


juce::AudioProcessorEditor* CenteredSoftShaperAudioProcessor::createEditor()
{
    return new CenteredSoftShaperAudioProcessorEditor(*this);
}

// This fixes the LNK2001 linker error:
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CenteredSoftShaperAudioProcessor();
}

