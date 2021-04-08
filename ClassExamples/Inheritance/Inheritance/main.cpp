//
//  main.cpp
//  Inheritance
//
//  Created by Eric Tarr on 2/25/21.
//  Copyright © 2021 Eric Tarr. All rights reserved.
//

#include <iostream>

class AudioEffect{
public:
    virtual float processSample(float x) = 0;
    
    void prepare(float newFs){
        Fs = newFs;
    };
    
private: // protected:
    float Fs = 48000.f;
    
};

class Gain : public AudioEffect
{
public:
    float processSample(float x) override{
        return x * dB;
    }
    
    void setGainDB(float newDB){
        dB = newDB;
    }
    
private:
    float dB = 0.f;
};


int main(int argc, const char * argv[]) {
    
    Gain myGain;
    
    myGain.prepare(44100.f);
    myGain.setGainDB(0.5f);
    
    float x = 1.f;
    float y = myGain.processSample(x);
    
}
