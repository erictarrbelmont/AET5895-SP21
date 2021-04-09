/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StereoWidenerAudioProcessorEditor::StereoWidenerAudioProcessorEditor (StereoWidenerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    widthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    widthSlider.setBounds(50, 75, 100, 100);
    widthSlider.setRange(0.f,2.f);
    widthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    addAndMakeVisible(widthSlider);
    
    //sliderAttachments = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.state,"widthValue",widthSlider);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"widthValue",widthSlider));
}

StereoWidenerAudioProcessorEditor::~StereoWidenerAudioProcessorEditor()
{
}

//==============================================================================
void StereoWidenerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void StereoWidenerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


