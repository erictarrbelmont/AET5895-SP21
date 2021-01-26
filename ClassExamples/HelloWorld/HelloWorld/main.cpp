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
float myFunction(float m, float & n);


int main(int argc, const char * argv[]) {
    
    cout << "Hello, World!\n";

    int a;
    a = 3/2;
    
    int c = 6;
    
    float b;
    b = 5.5f;
    
    float g;
    g = 6.0;
    
    cout << a << endl;
    
    float x[5] = {0.0f};
    x[0] = 12.0f;
    x[3] = -6.2f;
    
    // Pass in variables b & g to function
    float z = myFunction(b,g);
    
    
    return 0;
}

// Implement the function
float myFunction(float m, float & n){
    
    float w = m + n;
    
    m += 1.0f;
    n += 1.0f;
    
    return w;
}
