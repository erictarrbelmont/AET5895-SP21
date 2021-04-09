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
class StereoWidenerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    StereoWidenerAudioProcessorEditor (StereoWidenerAudioProcessor&);
    ~StereoWidenerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //void sliderValueChanged(Slider * slider) override;
    
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    StereoWidenerAudioProcessor& audioProcessor;

    Slider widthSlider;
    
public:
    std::vector<std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>> sliderAttachments;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoWidenerAudioProcessorEditor)
};
