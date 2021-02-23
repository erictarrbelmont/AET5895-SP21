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
    
    float y = (2.f/M_PI) * atan(drive * x);
    
    return y;
    
}

void Distortion::setDrive(float newDrive){
    if (newDrive <= 10.f && newDrive >= 1.f){
        drive = newDrive;
    }
}
