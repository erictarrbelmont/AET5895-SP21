/*
  ==============================================================================

    Distortion.h
    Created: 4 Feb 2021 2:28:36pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Distortion {
  
public:
    float processSample(float x);
    
    void setDrive(float newDrive);
    
    void setFs(float newFs);

private:
    float smoothDrive = 1.f;
    float drive = 1.f;
    float Fs = 48000.f;
    float smoothTime = 0.01;
    float alpha = exp(-log(9)/(Fs*smoothTime));
    
};
