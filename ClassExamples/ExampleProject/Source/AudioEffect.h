/*
  ==============================================================================

    AudioEffect.h
    Created: 25 Feb 2021 2:44:31pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once

// Base class for general audio effect

class AudioEffect{
  
public:
    float processSample(float x);
    
    void prepare(float newFs);
private:
    float Fs;
};
