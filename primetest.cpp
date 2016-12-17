//
//  main.cpp
//  CPlusPlusDataStructureHW3
//
//  Created by truc ngo on 10/9/16.
//  Copyright © 2016 truc ngo. All rights reserved.
//

#include "prime.h"

int main(int argc, const char * argv[]) {
    std::cout << std::fixed;
    //std::cout << std::setprecision(0);
    
    cout << "Print prime numbers from 1 to n using School method" << endl;
    clock_t start1 = clock();
    prime P1;
    P1.getAllPrimeNumbers1();
    P1.printPrimeArray(false);
    clock_t end1 = clock();
    double d1 = double(end1 - start1) / CLOCKS_PER_SEC;
    cout << "Basic Steps = " << P1.getBasicStep() << endl;
    cout << "Run time = " << d1 << " secs" << endl;
    cout << endl;
    
    cout << "Print prime numbers from 1 to n using UpTo method" << endl;
    clock_t start2 = clock();
    prime P2;
    P2.getAllPrimeNumbers2();
    P2.printPrimeArray(false);
    clock_t end2 = clock();
    double d2 = double(end2 - start2) / CLOCKS_PER_SEC;
    cout << "Basic Steps = " << P2.getBasicStep() << endl;
    cout << "Run time = " << d2 << " secs" << endl;
    cout << endl;
    
    cout << "Print prime numbers from 1 to n using Seive of Eratosthenes method" << endl;
    clock_t start3 = clock();
    prime P3;
    P3.getAllPrimeNumbers3();
    P3.printPrimeArray(false);
    clock_t end3 = clock();
    double d3 = double(end3 - start3) / CLOCKS_PER_SEC;
    cout << "Basic Steps = " << P3.getBasicStep() << endl;
    cout << "Run time = " << d3 << " secs" << endl;
    
    //Now compare 3 prime-number arrays
    if ((P1 == P3) && (P2 == P3) && (P1 == P2)) {
        cout << endl << "The three prime number arrays are of the same!" << endl;
    }
}

