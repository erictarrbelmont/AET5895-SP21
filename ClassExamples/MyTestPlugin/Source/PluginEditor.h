/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MyTestPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                            public juce::Slider::Listener,
                                            public juce::Button::Listener,
                                            public juce::Timer
{
public:
    MyTestPluginAudioProcessorEditor (MyTestPluginAudioProcessor&);
    ~MyTestPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider * slider) override;
    void buttonClicked(Button * button) override;

    void timerCallback() override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MyTestPluginAudioProcessor& audioProcessor;
    
    Slider gainSlider;
    
    ToggleButton muteButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyTestPluginAudioProcessorEditor)
};
