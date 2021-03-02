/*
  ==============================================================================

    Gain.cpp
    Created: 25 Feb 2021 2:45:24pm
    Author:  Eric Tarr

  ==============================================================================
*/

#include "Gain.h"


float Gain::processSample(float x){
    return x * gain;
}


void Gain::setGainValue(float newGain){
    gain = newGain;
}
