/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EchoEffectAudioProcessorEditor::EchoEffectAudioProcessorEditor (EchoEffectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    delayKnob.addListener(this);
    delayKnob.setBounds(100, 50, 125, 125);
    delayKnob.setValue(audioProcessor.delayMS);
    delayKnob.setRange(10.f, 1000.f,1.f);
    delayKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    delayKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(delayKnob);
    
    noteSelector.addListener(this);
    noteSelector.addItem("Half",1);
    noteSelector.addItem("Quarter",2);
    noteSelector.addItem("8th", 3);
    noteSelector.addItem("16th", 4);
    noteSelector.setSelectedId(2);
    noteSelector.setBounds(275, 100, 120, 40);
    addAndMakeVisible(noteSelector);
    
    tempoSyncButton.addListener(this);
    tempoSyncButton.setBounds(275, 175, 100, 40);
    tempoSyncButton.setButtonText("Sync'd");
    tempoSyncButton.setToggleState(audioProcessor.tempoSyncd, dontSendNotification);
    tempoSyncButton.setRadioGroupId(1); // links with "notTempoSyncButton"
    addAndMakeVisible(tempoSyncButton);
    
    notTempoSyncButton.addListener(this);
    notTempoSyncButton.setBounds(100, 175, 100, 40);
    notTempoSyncButton.setButtonText("Sync Off");
    notTempoSyncButton.setToggleState(!audioProcessor.tempoSyncd, dontSendNotification);
    notTempoSyncButton.setRadioGroupId(1);
    addAndMakeVisible(notTempoSyncButton);
    
    delayKnob.setEnabled(!audioProcessor.tempoSyncd);
    noteSelector.setEnabled(audioProcessor.tempoSyncd);
    
    
    meter.setBounds(25, 25, 10, 100);
    meter.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(meter);
    
    startTimerHz(30);

}


EchoEffectAudioProcessorEditor::~EchoEffectAudioProcessorEditor()
{
}

//==============================================================================
void EchoEffectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

//    g.setColour (juce::Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void EchoEffectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void EchoEffectAudioProcessorEditor::sliderValueChanged(Slider * slider){
    
    if (slider == &delayKnob){
        audioProcessor.delayMS = delayKnob.getValue();
    }
    
}

void EchoEffectAudioProcessorEditor::comboBoxChanged(ComboBox *comboBox){
    
    if (comboBox == &noteSelector){
        if (noteSelector.getSelectedId() == 1){
            // half note
            audioProcessor.noteDuration = 2.f;
        }
        if (noteSelector.getSelectedId() == 2){
            // quarter note
            audioProcessor.noteDuration = 1.f;
        }
        if (noteSelector.getSelectedId() == 3){
            // 8th note
            audioProcessor.noteDuration = 0.5f;
        }
        if (noteSelector.getSelectedId() == 4){
            // 8th note
            audioProcessor.noteDuration = 0.25f;
        }
    }
}

void EchoEffectAudioProcessorEditor::buttonClicked(Button * button){
    
    if (button == &tempoSyncButton){
        audioProcessor.tempoSyncd = true;
        delayKnob.setEnabled(false);
        noteSelector.setEnabled(true);
    }
    if (button == &notTempoSyncButton){
        audioProcessor.tempoSyncd = false;
        delayKnob.setEnabled(true);
        noteSelector.setEnabled(false);
    }
}

void EchoEffectAudioProcessorEditor::timerCallback(){
    meter.update(audioProcessor.meterValue);
}
