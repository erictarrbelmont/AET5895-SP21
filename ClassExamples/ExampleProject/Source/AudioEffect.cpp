/*
  ==============================================================================

    AudioEffect.cpp
    Created: 25 Feb 2021 2:44:31pm
    Author:  Eric Tarr

  ==============================================================================
*/

#include "AudioEffect.h"


//float AudioEffect::processSample(float x){
//    return x;
//}

void AudioEffect::prepare(float newFs){
    Fs = newFs;
}
