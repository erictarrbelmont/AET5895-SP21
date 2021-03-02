/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Echo.h"
#include "VUAnalysis.h"

//==============================================================================
/**
*/
class EchoEffectAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    EchoEffectAudioProcessor();
    ~EchoEffectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float delayMS = 100.f;
    float noteDuration = 1.f;
    bool tempoSyncd = true;
    
    std::atomic<float> meterValue; // good for things that "interrupt" the audio thread
    
private:
    
    Echo echo;
    VUAnalysis vuAnalysis;
    
    AudioPlayHead* playHead;
    AudioPlayHead::CurrentPositionInfo currentPositionInfo;
    
    float bpm = 120.f;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EchoEffectAudioProcessor)
};
