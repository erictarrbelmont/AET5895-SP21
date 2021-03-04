/*
  ==============================================================================

    Echo.h
    Created: 16 Feb 2021 1:43:15pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Biquad.h"

class Echo{

public:
 
    // Constructor
    Echo();
    
    enum NoteSelection { WHOLE, HALF, QUARTER, EIGHTH, SIXTEENTH };
    
    void processSignal(float * signal, const int numSamples, const int c);
    
    float processSample(float x, int c);
    
    void prepare(float newFs);
    
    void setDelayMS(float newDelayMS);
    
    void setBPM(float newBPM);
    void setNoteDuration (NoteSelection newNoteSelection);

    void setFilterCutoff(float freq);
    
private:
    
    float Fs = 48000.f;
    
    float bpm = 120.f;
    
    NoteSelection noteSelect = QUARTER;
    float noteDuration = 1.f; // 1 - quarter, 2 - half, 0.5 - 8th, 0.25 - 16th
    
    float delayMS = 500.f;
    int delaySamples = round(Fs*delayMS/1000.f); // number of samples of delay
    
    Biquad filter = Biquad{Biquad::FilterType::LPF,0.7071f};
    
    
    static const int BUFFERSIZE = 96000;
    float w[2][BUFFERSIZE] = {0.f};
    int writeIndex[2] = {47999,47999}; // write pointer to array "w"
    
};

