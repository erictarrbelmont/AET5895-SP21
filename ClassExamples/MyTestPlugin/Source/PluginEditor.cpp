/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyTestPluginAudioProcessorEditor::MyTestPluginAudioProcessorEditor (MyTestPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    gainSlider.addListener(this); // listen to user interaction with this GUI window
    gainSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag); // Circular knob
    gainSlider.setBounds(40,90,120,120); // position on GUI
    gainSlider.setRange(1.f,10.f,.01f);
    //gainSlider.setSkewFactorFromMidPoint(1.f);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 30);
    gainSlider.setValue(audioProcessor.gain);
    addAndMakeVisible(gainSlider);
    
    muteButton.addListener(this);
    muteButton.setBounds(200,90,120,20);
    muteButton.setButtonText("Mute");
    muteButton.setToggleState(audioProcessor.muteOn, dontSendNotification);
    addAndMakeVisible(muteButton);
    
}

MyTestPluginAudioProcessorEditor::~MyTestPluginAudioProcessorEditor()
{
}

//==============================================================================
void MyTestPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::orange);
    g.setFont (15.0f);
    //g.drawFittedText ("My Distortion Plug-in", getLocalBounds(), juce::Justification::centred, 1);
    g.drawFittedText ("My Distortion Plug-in",20,40, 150,100,juce::Justification::centred,1 );
  
}

void MyTestPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


void MyTestPluginAudioProcessorEditor::sliderValueChanged(Slider *slider){
    
    if (slider == &gainSlider){
        audioProcessor.gain = gainSlider.getValue();
    }
    
    
}

void MyTestPluginAudioProcessorEditor::buttonClicked(Button * button){
    
    if (button == &muteButton){
        audioProcessor.muteOn = !audioProcessor.muteOn;
    }
    
}
