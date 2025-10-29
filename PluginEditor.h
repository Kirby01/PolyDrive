#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class CenteredSoftShaperAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    CenteredSoftShaperAudioProcessorEditor (CenteredSoftShaperAudioProcessor&);
    ~CenteredSoftShaperAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    CenteredSoftShaperAudioProcessor& processorRef;

    juce::Slider driveSlider, outputSlider;
    juce::Label driveLabel, outputLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CenteredSoftShaperAudioProcessorEditor)
};
