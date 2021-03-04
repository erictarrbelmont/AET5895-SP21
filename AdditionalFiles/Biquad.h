//
//  Biquad.h
//
//  Copyright © 2019 Eric Tarr. All rights reserved.
//  Code may not be distributed without permission
//

/*
    This class implements the RBJ Audio EQ Cookbook Formulas

        http://shepazu.github.io/Audio-EQ-Cookbook/audio-eq-cookbook.html
 
    There are options for all of the standard filter types: LPF, HPF, etc. These
    filters are great as the building blocks for more complicated (i.e. higher
    order) filters because the RBJ filters are stable and work will when
    parameters are changed.
 
    Note: A Butterworth filter (flat passband) can be created by setting the RBJ
    filter's Q=sqrt(2)/2
*/

#pragma once

#include <math.h>
#include "../JuceLibraryCode/JuceHeader.h"

class Biquad
{
public:
    enum FilterType
    {
        LPF,
        HPF,
        BPF1,
        BPF2,
        NOTCH,
        LSHELF,
        HSHELF,
        PEAK,
        APF
    };
    Biquad() = default;
    Biquad(FilterType filterType, double Q);
    ~Biquad() = default;
    
    void processBlock(dsp::AudioBlock<float> samples);
    
    double processSample(double x, int channel);

    void setFs(double Fs);

    void setFreq(double freq);

    void setQ(double Q);

    void setAmpdB(double ampdB);

    void setFilterType (FilterType filterTypeParam)
    {
        this->filterType = filterTypeParam;
    }

private:
    FilterType filterType = LPF;

    double Fs = 48000.0; // Sampling Rate

    // Variables for User to Modify Filter
    double freq = 20.0; // frequency in Hz
    double Q = 0.707; // Q => [0.1 - 10]
    double ampdB = 0.0; // Amplitude on dB scale

    // Variables for Biquad Implementation
    // 2 channels - L,R : Up to 2nd Order
    double x1[2] = { 0.0 }; // 1 sample of delay feedforward
    double x2[2] = { 0.0 }; // 2 samples of delay feedforward
    double y1[2] = { 0.0 }; // 1 sample of delay feedback
    double y2[2] = { 0.0 }; // 2 samples of delay feedback

    // Filter coefficients
    double b0 = 1.0; // initialized to pass signal
    double b1 = 0.0; // without filtering
    double b2 = 0.0;
    double a0 = 1.0;
    double a1 = 0.0;
    double a2 = 0.0;

    void updateCoefficients();
};
