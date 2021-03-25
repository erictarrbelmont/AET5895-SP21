/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GraphicsExampleAudioProcessorEditor::GraphicsExampleAudioProcessorEditor (GraphicsExampleAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(420,420);
    bgImage = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    
    knob1.addListener(this);
    knob1.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    knob1.setBounds(50,50, 200, 200);
    knob1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    knob1.setLookAndFeel(&largeKnob);
    addAndMakeVisible(knob1);
    
    knob2.addListener(this);
    knob2.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    knob2.setBounds(300,300, 100, 100);
    knob2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    knob2.setLookAndFeel(&lookAndFeel3);
    addAndMakeVisible(knob2);
}

GraphicsExampleAudioProcessorEditor::~GraphicsExampleAudioProcessorEditor()
{
}

//==============================================================================
void GraphicsExampleAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.drawImageAt(bgImage, 0, 0);
}

void GraphicsExampleAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void GraphicsExampleAudioProcessorEditor::sliderValueChanged(Slider * slider){}
