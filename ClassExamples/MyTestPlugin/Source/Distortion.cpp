/*
  ==============================================================================

    Distortion.cpp
    Created: 4 Feb 2021 2:28:36pm
    Author:  Eric Tarr

  ==============================================================================
*/

#include "Distortion.h"
#include <JuceHeader.h>

float Distortion::processSample(float x){
    
    smoothDrive = alpha * smoothDrive + (1.f-alpha) * drive;
    
    float y = (2.f/M_PI) * atan(smoothDrive * x);
    
    return y;
    
}

void Distortion::setDrive(float newDrive){
    if (newDrive <= 10.f && newDrive >= 1.f){
        drive = newDrive;
    }
}

void Distortion::setFs(float newFs){
    Fs = newFs;
    alpha = exp(-log(9)/(Fs*smoothTime));
}
