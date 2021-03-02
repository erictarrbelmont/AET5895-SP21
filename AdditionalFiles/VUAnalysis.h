//
//  VUAnalysis.h
//
//
//  Copyright © 2019 Eric Tarr. All rights reserved.
//  Code may not be distributed without permission
//
//  This class can be used to analyze a conventional bi-polar audio signal over a full-scale
//  range of -1 to +1. It converts that signal into a uni-polar measurement of signal amplitude
//  over a range of 0 to +1. 
//
//  For this implementation, I used first-order smoothing. Values for the smoothing were
//  selected to match the performance of the channel meter in Logic
//
//  I attempted to use second-order smoothing based on the following paper, but it was going
//  unstable for various sampling rates.
//  https://asa.scitation.org/doi/full/10.1121/1.2387130
//  "A model of the VU (volume-unit) meter, with speech applications" (JASA, 2007)

#ifndef VUAnalysis_h
#define VUAnalysis_h

// Class definition
class VUAnalysis  
{
public:
    VUAnalysis (){}; // Constructor
    ~VUAnalysis (){}; // Destructor
    
    // Process an individual sample
    // Example:
    // vuMeterValue = instance->processSample (buffer.getReadPointer (channel)[sample] , channel);
    float processSample (float inputSample,int channel)
    {
        float outputSample = inputSample;
        inputSample = fabs(inputSample);

        if (previousSample[channel] < inputSample){
            g = ga; // Meter rising
        }
        else{
            g = gr; // Meter falling
        }
        
        outputSample = (1.0f - g) * inputSample + g * previousSample[channel];
        previousSample[channel] = outputSample;
        
        // Convert to decibel scale
        outputSample = 20.0f * log10(outputSample);
        
        // Set a floor, -75 was picked to closely match the meter in Logic
        if (outputSample < -75.0f){outputSample = -75.0f;}
        
        // Convert from scale: -75 dB to 0 db, over to the scale: 0 to 1 for the meter
        outputSample = (outputSample/75.0f) + 1;
        
        return outputSample;
    }
    
    void setSampleRate(int sampleRate)
    {
        if (this->sampleRate != sampleRate){
            this -> sampleRate = sampleRate;
            // Update Rise and Fall Time, these values were picked to match Logic's meter
            ga = exp(-log(9)/((float)sampleRate * 0.05));
            gr = exp(-log(9)/((float)sampleRate * 0.85));
            
            previousSample[0] = 0.0f;
            previousSample[1] = 0.0f;
        }
    }
    
private:
    
    float sampleRate = 1.0;
    
    float ga;
    float gr;
    float g;
    
    float previousSample[2] = {0.0f};

    float b0, b1, b2;
    float a0, a1, a2;
    
};

#endif
