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
class EchoEffectAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        public juce::Slider::Listener
{
public:
    EchoEffectAudioProcessorEditor (EchoEffectAudioProcessor&);
    ~EchoEffectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider * slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EchoEffectAudioProcessor& audioProcessor;
    
    Slider delayKnob;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EchoEffectAudioProcessorEditor)
};
