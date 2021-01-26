//
//  main.cpp
//  Synthesis
//
//  Created by Eric Tarr on 1/21/21.
//  Copyright © 2021 Eric Tarr. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "AudioFile/AudioFile.hpp"
using namespace std;


int main() {

    // Specify parameters of signal
    int Fs = 48000;
    int bitDepth = 16;
    int numChannels = 1;
    vector<float> signal;
    
    float lenSec = 3.0f; // length in seconds
    int N = round(lenSec * Fs); // length in samples
    
    signal.resize(N);
    
    float A = 0.5f;
    float freq = 220.0f;
    
    float currentAngle = 0.0f;
    float angleChange = freq * 2.0f * M_PI / (float)Fs;
    float pix2 = 2.0f * M_PI;
    
    float duty = 75.f;
    float cyclePoint = 2.f*M_PI*(duty/100.f);
    for (int n = 0; n < N ; n++){
        //float currentSample = sin(currentAngle);
        if (currentAngle < cyclePoint){
            signal[n] = A;// * 1.f;
        }
        else{
            signal[n] = -A;// * -1.f;
        }
        
        currentAngle += angleChange; // curAng = curAng + angCh
        if (currentAngle > pix2){
            currentAngle -= pix2;
        }
    }
    
    string outName = "Squarewave75.wav";
    audiowrite(outName,signal,Fs,bitDepth,numChannels);
    
    
    return 0;
}
