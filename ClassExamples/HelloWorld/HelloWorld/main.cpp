//
//  main.cpp
//  HelloWorld
//
//  Created by Eric Tarr on 1/14/21.
//  Copyright © 2021 Eric Tarr. All rights reserved.
//


#include <iostream>

using namespace std;

// Declare a new function
//float myFunction(float m, float & n);

void processSignal(float * signal, const int numSamples);

int main(int argc, const char * argv[]) {
    
    //cout << "Hello, World!\n";
    static const int numSamples = 5;
    float array[numSamples];
    for (int n = 0; n < 5; n++){
        array[n] = n;
    }

    // New "data type" called pointer
    float * index; // use * to say this is a pointer to something that is a float
    
    index = array;
     
    processSignal(index, numSamples);
    

    
//    cout << index << endl; // memory location or reference of signal array
//    cout << *index << endl; // this is "de-referencing" the pointer
//                            // access data in memory location
//
//    index++;
//
//    cout << index << endl; // memory location or reference of signal array
//    cout << *index << endl; // this is "de-referencing" the pointer
//                            // access data in memory location
//
//    float number = 10.f;
//
//    index = &number; // assign memory location of number to float pointer
//
//    cout << index << endl; // memory location or reference of signal array
//    cout << *index << endl; // this is "de-referencing" the pointer
    
    return 0;
}

void processSignal(float * signal, const int numSamples){
    
    for (int n = 0; n < numSamples ; n++){
        float x = *signal; // get value at pointer and assign to "x"
        
        *signal = 2.f*x;
        
        signal++;
    }
    
}


//// Implement the function
//float myFunction(float m, float & n){
//
//    float w = m + n;
//
//    m += 1.0f;
//    n += 1.0f;
//
//    return w;
//}
