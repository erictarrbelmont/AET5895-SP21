//
//  main.cpp
//  AmpMod
//
//  Created by Eric Tarr on 1/26/21.
//  Copyright © 2021 Eric Tarr. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "AudioFile/AudioFile.hpp"
using namespace std;

void amplitudeModulation(vector<float> & signal, int Fs, float rate, float depth);


int main() {
    
    // Variables for sound file
    int Fs;
    int bitDepth;
    int numChannels;
    vector<float> signal;
    string filename = "AcGtr.wav";
    
    audioread(filename, signal, Fs, bitDepth, numChannels);
    
    // LFO Parameters (knobs)
    float rate = 8.f; // [0.1 - 10]
    float depth = 100.f; // [0-100]
    
    amplitudeModulation(signal, Fs, rate, depth);
    
    string outName = "ampMod.wav";
    audiowrite(outName, signal, Fs, bitDepth, numChannels);
    
    
    return 0;
}


void amplitudeModulation(vector<float> & signal, int Fs, float rate, float depth){
    int N = (int)signal.size(); // total number of samples
    
    float amp = depth / 200.f;
    float dc = 1.f - amp;
    
    float currentAngle = 0.0f;
    float angleChange = rate * 2.0f * M_PI / (float)Fs;
    float pix2 = 2.0f * M_PI;
    
    for (int n = 0 ; n < N ; n++){
        float x = signal[n];
        float lfo = amp * sin(currentAngle) + dc;
        signal[n] = x * lfo;
        
        currentAngle += angleChange; // curAng = curAng + angCh
        if (currentAngle > pix2){
            currentAngle -= pix2;
        }
    }
    
}










