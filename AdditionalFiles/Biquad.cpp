//
//  Biquad.cpp
//
//  Copyright © 2019 Eric Tarr. All rights reserved.
//  Code may not be distributed without permission
//
// Implementation of Audio EQ Cookbook Formulas for 2nd-order filter
// https://www.w3.org/2011/audio/audio-eq-cookbook.html

#include "Biquad.h"

Biquad::Biquad(Biquad::FilterType newFilterType, double newQ) :
    filterType(newFilterType), Q(newQ)
{}

void Biquad::processBlock(dsp::AudioBlock<float> samples)
{
    auto numSamples = samples.getNumSamples();
    auto numChannels = samples.getNumChannels();
    for (uint16 channel = 0; channel < numChannels ; channel++){
        for (uint16 n = 0; n < numSamples ; n++){
            double x = (double)samples.getSample(channel,n);
            x = processSample(x,channel);
            samples.setSample(channel,n,(float)x);
        }
    }
}

double Biquad::processSample(double x, int channel)
{
    // Output, processed sample (Direct Form 1)
    double y = b0 * x + b1 * x1[channel] + b2 * x2[channel]
            + (-a1) * y1[channel] + (-a2) * y2[channel];

    x2[channel] = x1[channel]; // store delay samples for next process step
    x1[channel] = x;
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y;
};

void Biquad::setFs(double newFs)
{
    Fs = newFs;
    updateCoefficients(); // Need to update if Fs changes
};

void Biquad::setFreq(double newFreq)
{
    freq = jlimit(20.0, 20000.0, newFreq);
    updateCoefficients();
};

void Biquad::setQ(double newQ)
{
    Q = jlimit(0.1, 10.0, newQ);
    updateCoefficients();
};

void Biquad::setAmpdB(double newAmpdB)
{
    ampdB = jlimit(-30.0, 30.0, newAmpdB);
    updateCoefficients();
};

void Biquad::updateCoefficients()
{
    double A = std::pow(10.0, ampdB / 40.0); // Linear amplitude
    
    // Normalize frequency
    double w0 = (2.0 * M_PI) * freq / Fs;
    
    // Bandwidth/slope/resonance parameter
    double alpha = std::sin(w0) / (2.0 * Q);
    
    double cw0 = std::cos(w0);
    switch (filterType)
    {
        case LPF:
        {
            a0 = 1.0 + alpha;
            double B0 = (1.0 - cw0) / 2.0;
            b0 = B0/a0;
            double B1 = 1.0 - cw0;
            b1 = B1/a0;
            double B2 = (1.0 - cw0) / 2.0;
            b2 = B2/a0;
            double A1 = -2.0 * cw0;
            a1 = A1/a0;
            double A2 = 1.0 - alpha;
            a2 = A2/a0;
            break;
        }
        case HPF:
        {
            a0 = 1.0 + alpha;
            double B0 = (1.0 + cw0) / 2.0;
            b0 = B0/a0;
            double B1 = -(1.0 + cw0);
            b1 = B1/a0;
            double B2 = (1.0 + cw0) / 2.0;
            b2 = B2/a0;
            double A1 = -2.0 * cw0;
            a1 = A1/a0;
            double A2 = 1.0 - alpha;
            a2 = A2/a0;
            break;
        }
        case BPF1:
        {
            double sw0 = std::sin(w0);
            a0 = 1.0 + alpha;
            double B0 = sw0 / 2.0;
            b0 = B0/a0;
            double B1 = 0.0;
            b1 = B1/a0;
            double B2 = -sw0 / 2.0;
            b2 = B2/a0;
            double A1 = -2.0 * cw0;
            a1 = A1/a0;
            double A2 = 1.0 - alpha;
            a2 = A2/a0;
            break;
        }
        case BPF2:
        {
            a0 = 1.0 + alpha;
            double B0 = alpha;
            b0 = B0/a0;
            double B1 = 0.0;
            b1 = B1/a0;
            double B2 = -alpha;
            b2 = B2/a0;
            double A1 = -2.0 * cw0;
            a1 = A1/a0;
            double A2 = 1.0 - alpha;
            a2 = A2/a0;

            break;
        }
        case NOTCH:
        {
            a0 = 1.0 + alpha;
            double B0 = 1.0;
            b0 = B0/a0;
            double B1 = -2.0 * cw0;
            b1 = B1/a0;
            double B2 = 1.0;
            b2 = B2/a0;
            double A1 = -2.0 * cw0;
            a1 = A1/a0;
            double A2 = 1.0 - alpha;
            a2 = A2/a0;
            break;
        }
        case LSHELF:
        {
            double sqA = std::sqrt(A);
            a0 = (A + 1.0) + (A - 1.0) * cw0 + 2.0 * sqA * alpha;
            double B0 = A * ((A + 1.0) - (A - 1.0) * cw0 + 2.0 * sqA * alpha);
            b0 = B0/a0;
            double B1 = 2.0 * A * ((A - 1.0) - (A + 1.0) * cw0);
            b1 = B1/a0;
            double B2 = A * ((A + 1.0) - (A - 1.0) * cw0 - 2.0 * sqA * alpha);
            b2 = B2/a0;
            double A1 = -2.0 * ((A - 1.0) + (A + 1.0) * cw0);
            a1 = A1/a0;
            double A2 = (A + 1.0) + (A - 1.0) * cw0 - 2.0 * sqA * alpha;
            a2 = A2/a0;

            break;
        }

        case HSHELF:
        {
            double sqA = std::sqrt(A);
            a0 = (A + 1.0) - (A - 1.0) * cw0 + 2.0 * sqA * alpha;
            double B0 = A * ((A + 1.0) + (A - 1.0) * cw0 + 2.0 * sqA * alpha);
            b0 = B0/a0;
            double B1 = -2.0 * A * ((A - 1.0) + (A + 1.0) * cw0);
            b1 = B1/a0;
            double B2 = A * ((A + 1.0) + (A - 1.0) * cw0 - 2.0 * sqA * alpha);
            b2 = B2/a0;
            double A1 = 2.0 * ((A - 1.0) - (A + 1.0) * cw0);
            a1 = A1/a0;
            double A2 = (A + 1.0) - (A - 1.0) * cw0 - 2.0 * sqA * alpha;
            a2 = A2/a0;

            break;
        }

        case PEAK:

        {
            a0 = 1.0 + alpha / A;
            double B0 = 1.0 + alpha * A;
            b0 = B0/a0;
            double B1 = -2.0 * cw0;
            b1 = B1/a0;
            double B2 = 1.0 - alpha * A;
            b2 = B2/a0;
            double A1 = -2.0 * cw0;
            a1 = A1/a0;
            double A2 = 1.0 - alpha / A;
            a2 = A2/a0;
            
            break;
        }

        case APF:
        {
            a0 = 1.0 + alpha;
            double B0 = 1.0 - alpha;
            b0 = B0/a0;
            double B1 = -2.0 * cw0;
            b1 = B1/a0;
            double B2 = 1.0 + alpha;
            b2 = B2/a0;
            double A1 = -2.0 * cw0;
            a1 = A1/a0;
            double A2 = 1.0 - alpha;
            a2 = A2/a0;

            break;
        }
    }
};
