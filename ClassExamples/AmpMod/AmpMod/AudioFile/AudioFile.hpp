/**
 * Interface functions for using the bw64 library.
 * These were created to make reading/writing similar
 * to MATLAB.
 * https://github.com/IRT-Open-Source/libbw64
 */
#pragma once
#include "bw64.hpp"

template <typename T>
void audioread(const std::string filename, std::vector<T> & signal,int & Fs, int & bitDepth, int & numChannels ){
    // Mono signals
    
    auto inFile = bw64::readFile(filename);
    Fs = inFile->sampleRate();
    bitDepth = inFile->bitDepth();
    numChannels = inFile->channels();
    int64_t startSample = 3;
    inFile->seek(startSample); // Note: C++ indexing starts at seek(0), seek(1)...
    int64_t numSamples = inFile->numberOfFrames() - startSample;
    signal = std::vector<T> (numSamples);
    //std::cout << inFile->tell();
    inFile->read(&signal[0], numSamples);
    
//    while (!inFile->eof()) {
//        inFile->read(&signal[0], numSamples);
//        std::cout << inFile->tell();
//    }
    
};


template <typename T>
void audioread(const std::string filename, std::vector<std::vector<T>> & signal,int & Fs, int & bitDepth, int & numChannels ){
    
    auto inFile = bw64::readFile(filename);
    Fs = inFile->sampleRate();
    bitDepth = inFile->bitDepth();
    numChannels = inFile->channels();
    
    int64_t startSample = 1;
    inFile->seek(startSample);
    
    // NOTE: "frame" is not the same as "samples" since L,R signals are interleaved.
    // A "frame" includes all of the channels for a sample number.
    // numFrames = length of a mono signal
    // F(1) = L(1), R(1), C(1), ...
    // F(2) = L(2), R(2), C(2), ...
    int64_t numFrames = inFile->numberOfFrames()-startSample;
    
    signal = std::vector<std::vector<T>> (numChannels,std::vector<T> (numFrames));
    
    std::vector<T> buffer(numFrames * inFile->channels());
    while (!inFile->eof()) {
        inFile->read(&buffer[0], numFrames);
        for (int n = 0; n < numFrames ; n++){
            for (int c = 0; c < numChannels ; c++){
                signal[c][n] = buffer[2*n + c];
            }
        }
    }
    
};



template <typename T>
void audiowrite(const std::string filename, const std::vector<T> & signal,const int & Fs,const int & bitDepth,const int & numChannels){
    
    auto outFile = bw64::writeFile(filename,numChannels,Fs,bitDepth);

    int64_t N = signal.size(); // Number of samples

    outFile->write(&signal.front(),N);
};


template <typename T>
void audiowrite(const std::string filename, const std::vector<std::vector<T>> & signal,const int & Fs,const int & bitDepth,const int & numChannels){
    
    auto outFile = bw64::writeFile(filename,numChannels,Fs,bitDepth);
    
    int64_t N = signal[0].size(); // Number of samples
    std::vector<T> buffer(N*numChannels);
    for (int n = 0; n < N ; n++){
        for (int c = 0; c < numChannels ; c++){
            buffer[2*n + c] = signal[c][n];
        }
    }
    outFile->write(&buffer.front(),N);
};
