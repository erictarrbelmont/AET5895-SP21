/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyTestPluginAudioProcessor::MyTestPluginAudioProcessor()
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
    addParameter(gain = new AudioParameterFloat("gainDistortion", // string for identifying parameter in code
                                    "Gain", // string shown in DAW to user
                                    1.f, // minimum value for range
                                    10.f, // maximum value for range
                                    5.f  // default value
                                    ));
    
    
}

MyTestPluginAudioProcessor::~MyTestPluginAudioProcessor()
{
}

//==============================================================================
const juce::String MyTestPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MyTestPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MyTestPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MyTestPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MyTestPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MyTestPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MyTestPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MyTestPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MyTestPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void MyTestPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MyTestPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MyTestPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MyTestPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MyTestPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    if (muteOn){
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            for (int n = 0; n < buffer.getNumSamples() ; n++){
                buffer.getWritePointer(channel)[n] = 0.f;
            }
        }
    }
    else{
        
        myDistortion.setDrive(*gain);
        
        
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            for (int n = 0; n < buffer.getNumSamples() ; n++){
                float x = buffer.getReadPointer(channel)[n];
                
                //x = x * gain;
                
                // Distortion
                //x = hardClip(x);
                x = myDistortion.processSample(x);
                
                // Equalizer
                
                // Reverb
                
                // Output Gain
                buffer.getWritePointer(channel)[n] = x; // -12 dB
            }
        }
    }
    
    
}

//==============================================================================
bool MyTestPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MyTestPluginAudioProcessor::createEditor()
{
    return new MyTestPluginAudioProcessorEditor (*this);
}

//==============================================================================
void MyTestPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    std::unique_ptr<XmlElement> xml (new XmlElement("MyDistortionParameters") );
    xml->setAttribute("gainDistortion", (double) *gain);
    
    copyXmlToBinary(*xml, destData);
}

void MyTestPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> xml (getXmlFromBinary(data, sizeInBytes));
    if (xml != nullptr){
        if (xml->hasTagName("MyDistortionParameters")){
            *gain = xml->getDoubleAttribute("gainDistortion",5.f);
        }
    }
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyTestPluginAudioProcessor();
}


float MyTestPluginAudioProcessor::hardClip (float x){
    float y;
    if ( x > 0.5f){
        y = 0.5f;
    }
    else if( x < -0.5f){
        y = -0.5f;
    }
    else{
        y = x;
    }
    return y;
}


