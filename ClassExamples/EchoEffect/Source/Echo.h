/*
  ==============================================================================

    Echo.h
    Created: 16 Feb 2021 1:43:15pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Echo{

public:
 
    // Constructor
    Echo();
    
    void processSignal(float * signal, int numSamples);
    
    float processSample(float x, int c);
    
    void prepare(float newFs);
    
    void setDelayMS(float newDelayMS);

private:
    
    float Fs = 48000.f;
    
    float delayMS = 500.f;
    int delaySamples = round(Fs*delayMS/1000.f); // number of samples of delay
    
    static const int BUFFERSIZE = 96000;
    float w[2][BUFFERSIZE] = {0.f};
    int writeIndex[2] = {47999,47999}; // write pointer to array "w"
    
};

