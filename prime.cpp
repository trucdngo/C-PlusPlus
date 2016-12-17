//
//  prime.cpp
//  
//
//  Created by truc ngo on 10/9/16.
//  http://stackoverflow.com/questions/18041100/using-c-string-address-of-stack-memory-associated-with-local-variable-returned
//  https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
//


#include "prime.h"
const unsigned int prime::_n = 150000;

//constructor
prime::prime() {
    this->_steps = 0;
    _primeArrayPtr = new unsigned int [_n];
    for (unsigned int i=0; i < _n; i++) {
        _primeArrayPtr[i] = 0;
    }
}

//destructor
prime::~prime() {
    cout << "inside destructor.." << endl;
    delete [] _primeArrayPtr;
};


//return the location at i where p[i] == 0
unsigned int prime::getPrimeArraySize(unsigned int* p) {
    unsigned int i = 0;
    for (; i < _n; i++) {
        if (p[i] == 0) {
            break;
        }
    }
    return i;
}


//printing prime-number array
void prime::printPrimeArray(bool display) {
    unsigned int * p = this->_primeArrayPtr;
    const unsigned int SIZE = getPrimeArraySize(p);
    if (display) {
        for (int i = 0; i < SIZE; i++) {
            cout << "index: " << i << ", value: " << p[i] << endl;
        }
    }
}

/*
void prime::resizeArray() {
    unsigned int * p = this->_primeArrayPtr;
    const unsigned int SIZE = getPrimeArraySize(p);
    unsigned int* newArr = new unsigned int [SIZE];
    memcpy(newArr, p, SIZE * sizeof(int));
    this->_primeArrayPtr = newArr;
}
*/

//Method #1
//Is this number a prime number?
bool prime::isPrime1(unsigned int num) {
    if (num == 2) {
        this->_steps++;
        return true;
    } else if (num == 1 || num % 2 == 0) {
        this->_steps++;
        return false;
    }
    //for numbers with value of 3 and above
    for (unsigned int i = 3; (i*i) <= num; i += 2) {
        this->_steps++;
        if (num%i == 0) {
            return false;
        }
    }
    return true;
}

void prime::getAllPrimeNumbers1() {
    int k = 0;
    const unsigned int SIZE = _n;
    for (unsigned int i=1; i<= SIZE; i++) {
        if (isPrime1(i)) {
            this->_primeArrayPtr[k++] = i;
        }
    }
}

//Method #2
//Is this number a prime number?
//divide input number by every prime number of the primeNumberArray
//p is pointer to primeArray
bool prime::isPrime2(unsigned int num, unsigned int* p, unsigned int indexForNextPrimeNumber) {
    if (num == 2) {
        this->_steps++;
        p[0] = num;
    } else if (num == 1 || num % 2 == 0) {
        this->_steps++;
        return false;
    }
    //p = {2,3,5,7}
    //8 % 2 == 0 -> 8 is not a prime
    //11 % {2,3,5,7} != 0 -> 11 is a prime
    for (unsigned int i = 0; i < indexForNextPrimeNumber; i += 1) {
        this->_steps++;
        if (num % p[i] == 0) {
            return false;
        }
    }
    return true;
}

void prime::getAllPrimeNumbers2() {
    int indexForNextPrimeNumber = 0;
    const unsigned int SIZE = _n;
    for (unsigned int i=1; i<= SIZE; i++) {
        if (isPrime2(i, this->_primeArrayPtr, indexForNextPrimeNumber)) {
            this->_primeArrayPtr[indexForNextPrimeNumber++] = i;
        }
    }
}


void prime::getAllPrimeNumbers3() {
    const unsigned int SIZE = _n+1;
    static unsigned int p[SIZE];
    
    //fill up array with number from 2 to n
    //index: 2 3 4 5 6 7 8 9 10 ...
    //value: 2 3 4 5 6 7 8 9 10 ...
    for (unsigned int i=0; i < SIZE; i++) {
        this->_steps++;
        p[i] = i;
    }
    p[0] = 0;
    p[1] = 0;
    
    //assign all those numbers which are not primes to zero
    for (int i = 2; (i*i) <= SIZE; ++i) {
        for (int j = i; (i*j) <= SIZE; ++j) {
            this->_steps++;
            p[i*j] = 0;
        }
    }
   
    //create a new array to bin those remaining prime numbers
    unsigned int k = 0;
    unsigned int* newP =  new unsigned int [SIZE];
    for (unsigned int i = 0; i < SIZE; i += 1) {
        this->_steps++;
        if (p[i] != 0) {
            this->_steps++;
            newP[k++] = p[i];
        }
    }
    //assign this new array back to object's prime number array
    delete [] this->_primeArrayPtr;
    this->_primeArrayPtr = newP;
}

/* equal operator == */
//return true if two primeNumberArray is of the same
bool prime::operator==(const prime& obj) {
    unsigned int arrayLength1 = getPrimeArraySize(this->_primeArrayPtr);
    unsigned int arrayLength2 = getPrimeArraySize(obj._primeArrayPtr);
    
    bool b1 = (arrayLength1 == arrayLength2) ? true : false;
    bool b2 = true;
    
    for (unsigned int i = 0; i < arrayLength1; i++) {
        if (this->_primeArrayPtr[i] != obj._primeArrayPtr[i]) {
            b2 = false;
            break;
        }
    }
    return (b1 && b2);
}









