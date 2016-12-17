//
//  prime.hpp
//  
//
//  Created by truc ngo on 10/9/16.
//
//

#ifndef prime_hpp
#define prime_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

class prime {
public:
    prime();
    bool isPrime1(unsigned int i);
    bool isPrime2(unsigned int i, unsigned int* p, unsigned int indexForNextPrimeNumber);
    unsigned int getPrimeArraySize(unsigned int* p);
    bool operator==(const prime& obj);
    unsigned int getBasicStep() { return _steps; }
    void getAllPrimeNumbers1();
    void getAllPrimeNumbers2();
    void getAllPrimeNumbers3();
    void printPrimeArray(bool = true);
    void resizeArray();
    ~prime();
    
private:
    static const unsigned int _n;
    unsigned int* _primeArrayPtr;
    unsigned int _steps;
    
};

#endif /* prime_hpp */
