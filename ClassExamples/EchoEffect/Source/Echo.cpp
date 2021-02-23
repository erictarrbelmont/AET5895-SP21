/*
  ==============================================================================

    Echo.cpp
    Created: 16 Feb 2021 1:43:15pm
    Author:  Eric Tarr

  ==============================================================================
*/

#include "Echo.h"


// Constructor
Echo::Echo(){}

float Echo::processSample(float x, int c){
    
    int delayIndex = writeIndex[c] - delaySamples;
    
    if (delayIndex < 0){
        delayIndex += BUFFERSIZE;
    }
    
    float y = x + 0.7f * w[c][delayIndex];
    
    // Feed-forward
    //w[c][index[c]] = x;
    
    // Feed-back
    w[c][writeIndex[c]] = y;
    
    writeIndex[c]++;
    if (writeIndex[c] >= BUFFERSIZE){
        writeIndex[c] = 0;
    }
    
    return y;
    
}

void Echo::prepare(float newFs){
    Fs = newFs;
    delaySamples = round(Fs*delayMS/1000.f);

}

void Echo::setDelayMS(float newDelayMS){
    if (newDelayMS <= 1000.f){
        delayMS = newDelayMS;
        delaySamples = round(Fs*delayMS/1000.f);
    }
}

