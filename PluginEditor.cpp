#include "PluginEditor.h"

CenteredSoftShaperAudioProcessorEditor::CenteredSoftShaperAudioProcessorEditor (CenteredSoftShaperAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    driveLabel.setText("Drive", juce::dontSendNotification);
    driveLabel.attachToComponent(&driveSlider, false);

    outputSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    outputSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    outputLabel.setText("Output", juce::dontSendNotification);
    outputLabel.attachToComponent(&outputSlider, false);

    addAndMakeVisible(driveSlider);
    addAndMakeVisible(outputSlider);

    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processorRef.parameters, "drive", driveSlider);

    outputAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processorRef.parameters, "output", outputSlider);

    setSize(250, 150);
}

void CenteredSoftShaperAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::orange);
    g.setFont(18.0f);
    g.drawFittedText("Centered Soft Shaper", getLocalBounds(), juce::Justification::centredTop, 1);
}

void CenteredSoftShaperAudioProcessorEditor::resized()
{
    driveSlider.setBounds(30, 50, 80, 80);
    outputSlider.setBounds(140, 50, 80, 80);
}
