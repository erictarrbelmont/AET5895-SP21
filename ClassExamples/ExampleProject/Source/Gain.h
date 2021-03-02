/*
  ==============================================================================

    Gain.h
    Created: 25 Feb 2021 2:45:24pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once

#include "AudioEffect.h"

// Derived class from AudioEffect

class Gain : public AudioEffect
{
public:
    void setGainValue(float newGain);
    
private:
    float gain = 1.f;
    
};
