/*
  ==============================================================================

    Distortion.h
    Created: 4 Feb 2021 2:28:36pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once

class Distortion {
  
public:
    float processSample(float x);
    
    void setDrive(float newDrive);

private:
    float drive = 1.f;
    
};
