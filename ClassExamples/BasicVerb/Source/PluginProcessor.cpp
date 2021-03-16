/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicVerbAudioProcessor::BasicVerbAudioProcessor()
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

BasicVerbAudioProcessor::~BasicVerbAudioProcessor()
{
}

//==============================================================================
const juce::String BasicVerbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BasicVerbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasicVerbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BasicVerbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BasicVerbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BasicVerbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BasicVerbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BasicVerbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BasicVerbAudioProcessor::getProgramName (int index)
{
    return {};
}

void BasicVerbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BasicVerbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 2;
    
    gain.prepare(spec);
    gain.reset();
    
    reverb.prepare(spec);
    reverb.reset();
    
}

void BasicVerbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasicVerbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void BasicVerbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Need to convert AudioBuffer to AudioBlock for DSP Module
    dsp::AudioBlock<float> block (buffer);
    
    // Do DSP processing in here:
    
    //block.multiplyBy(0.125f);
    
    //gain.setGainDecibels(-12.f);
    
    //gain.process(dsp::ProcessContextReplacing<float> (block));
    
    dsp::Reverb::Parameters params = reverb.getParameters();
    params.roomSize = 0.95;
    params.damping = 0.1;
    reverb.setParameters(params);
    
    reverb.process(dsp::ProcessContextReplacing<float> (block));
    
    
    
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        for (int n = 0; n < block.getNumSamples(); n++){
//            float x = block.getSample(channel,n);
//            float y = gain.processSample(x);
//            block.setSample(channel,n,y);
//        }
//    }
    
    /////////
    block.copyTo(buffer);
    
    
    // At end of processBlock, convert block back to buffer
    


}

//==============================================================================
bool BasicVerbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BasicVerbAudioProcessor::createEditor()
{
    return new BasicVerbAudioProcessorEditor (*this);
}

//==============================================================================
void BasicVerbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BasicVerbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BasicVerbAudioProcessor();
}
