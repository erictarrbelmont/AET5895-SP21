/*
  ==============================================================================

    MidSide.h
    Created: 18 Mar 2021 2:12:30pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MidSide{
    
public:
    
    void processStereoWidth(float & L, float & R);
    void processStereoWidth(float* leftChannel, float * rightChannel, const int N);
    void processStereoWidth(juce::AudioBuffer<float>& buffer);
    
    void midSideEncode(const float & L, const float & R, float & M, float & S);
    void midSideDecode(const float & M, const float & S, float & L, float & R);
    
    void setStereoWidthValue(float newWidth){
        width = newWidth;
    };
    
    
private:
    
    float width = 1.0f;
    
};
