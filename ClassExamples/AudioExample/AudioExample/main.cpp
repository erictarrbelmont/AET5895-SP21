//
//  main.cpp
//  AudioExample
//
//  Created by Hack Audio on 10/5/19.
//  Copyright © 2019 Eric Tarr. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "AudioFile/AudioFile.hpp"
using namespace std;

// Declare our own function
void dBAmpChange(vector<float> & x,float dB);

void stereoWidener(vector<vector<float>> & x, float width);

int main() {
    
    // Import audio file
    // [x,Fs] = audioread('AcGtr.wav');
//    string filename = "AcGtr.wav";
//    int Fs;
//    int bitDepth;
//    int numChannels;
//    vector<float> signal; // dynamic allocation of memory for array
//
//    audioread(filename,signal,Fs,bitDepth,numChannels);
    
//    int N = signal.size();
//    // Loop to change amplitude
//    for (int n = 0 ; n < N ; n++ ){
//        //signal[n] = signal[n] * 0.25f;
//        signal[n] *= 0.25f;
//    }
//    float dBAmp = 6.f;
//    dBAmpChange(signal,dBAmp);
    
    // Stereo Signal (2 channels)
    // Primitive arrays
    //float arr[2][5] = {0.f};
    
    string filename = "stereoDrums.wav";
    int Fs;
    int bitDepth;
    int numChannels;
    vector<vector<float>> signal;
    
    audioread(filename,signal,Fs,bitDepth,numChannels);
    
    float width = 0.2f;
    stereoWidener(signal, width);
    
    // output processed signal
    string outName = "Test.wav";
    audiowrite(outName,signal,Fs,bitDepth,numChannels);
    
    
    return 0;
}

// Define the function (steps of processing)
void dBAmpChange(vector<float> & x, float dB){
    
    //float linAmp = 10^(dB/20);
    float linAmp = pow(10.f,dB/20.f);
    
    int N = x.size();
    for (int n = 0 ; n < N ; n++){
        x[n] *= linAmp;
    }
    
    
    
}


void stereoWidener(vector<vector<float>> & x, float width){
    
    // width range of [0-2]
    
    // Figure out the number of samples in either channel
    int N = x[0].size();
    
    for (int n = 0; n < N ; n++){
        // Separate the two channels
        float L = x[0][n];
        float R = x[1][n];
        
        // Mid-side encoding
        float S = L-R;
        float M = L+R;
        
        // Apply the width
        S *= width;
        M *= (2.0f - width);
        
        // Mid-side decoding (new L & R)
        x[0][n] = (S+M) * 0.5f;
        x[1][n] = (M-S) * 0.5f;
    }
    
}


