/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EchoEffectAudioProcessor::EchoEffectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

EchoEffectAudioProcessor::~EchoEffectAudioProcessor()
{
}

//==============================================================================
const juce::String EchoEffectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EchoEffectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EchoEffectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EchoEffectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EchoEffectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EchoEffectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EchoEffectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EchoEffectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EchoEffectAudioProcessor::getProgramName (int index)
{
    return {};
}

void EchoEffectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EchoEffectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    echo.prepare(sampleRate);
    vuAnalysis.setSampleRate(sampleRate);
}

void EchoEffectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EchoEffectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
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

void EchoEffectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    if (tempoSyncd){
        playHead = this->getPlayHead();
        playHead->getCurrentPosition(currentPositionInfo);
        
        float newBPM = currentPositionInfo.bpm;
        if (bpm != newBPM){
            // update echo
            echo.setBPM(newBPM);
            bpm = newBPM;
        }
        echo.setNoteDuration(noteDuration);
    }
    else{ // not tempo sync'd
        echo.setDelayMS(delayMS);
    }
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        for (int n = 0; n < buffer.getNumSamples() ; ++n){
            float x = buffer.getReadPointer(channel)[n];
            meterValue = vuAnalysis.processSample(x, channel);
            x = echo.processSample(x, channel);
            buffer.getWritePointer(channel)[n] = x;
        }
//        float * channelData = buffer.getWritePointer(channel);
//        echo.processSignal(channelData, buffer.getNumSamples(), channel);
    }
}

//==============================================================================
bool EchoEffectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EchoEffectAudioProcessor::createEditor()
{
    return new EchoEffectAudioProcessorEditor (*this);
}

//==============================================================================
void EchoEffectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void EchoEffectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EchoEffectAudioProcessor();
}
