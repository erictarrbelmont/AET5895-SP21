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
    virtual float processSample(float x) = 0; // pure virtual - virtual without an implementation
    
    void prepare(float newFs);

protected:
    // accessible in AudioEffect and derived classes
    float Fs;

private:
    // only accessible in AudioEffect
};
