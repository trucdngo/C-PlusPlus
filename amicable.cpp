//
//  amicable.cpp
//  CPlusPlusDataStrutureHW1
//
//  Created by truc ngo on 9/27/16.
//  Copyright © 2016 truc ngo. All rights reserved.
//
//  References
//  http://www.cplusplus.com/reference/vector/vector/
//  http://stackoverflow.com/questions/3450860/check-if-a-stdvector-contains-a-certain-object

#include "amicable.h"

class amicable {
public:
    amicable(long x) {
        _maxValue = x;
    }
    void getAmicablePairs();
    long getSumOfProperDivisors(long);
    bool pairAlreadyClaimed(Vec v, long i);
    
private:
    long _maxValue;
};

long amicable::getSumOfProperDivisors(long n) {
    long sum = 0;
    long nBy2 = n/2;
    for (int i=1; i<=nBy2; i++) {
        //if there is no remainder, it is a proper divisor.
        if(n%i == 0)
            sum +=i;
    }
    return sum;
}

bool amicable::pairAlreadyClaimed(Vec v, long x) {
    if(std::find(v.begin(), v.end(), x) != v.end()) {
        return true;
    } else {
        return false;
    }
}

void amicable::getAmicablePairs() {
    Vec listOfAmicablePair;
    long counter = 0L;
    for (long i = 2; i < _maxValue; i++) {
        long pairXa = getSumOfProperDivisors(i);
        long pairXb = getSumOfProperDivisors(pairXa);
        if ((i == pairXb) & (pairXa != pairXb)) {
            if (!pairAlreadyClaimed(listOfAmicablePair, i)) {
                cout << counter << ": " << i  << " and " << pairXa << endl;
                counter++;
                listOfAmicablePair.push_back(pairXa);
            }
        }
    }
}

//int main() {
//    clock_t start = clock();
//    cout << "Here are pairs of amicable pairs: " << endl;
//    amicable a(100000000);
//    a.getAmicablePairs();
//    clock_t end = clock();
//    double d = double(end - start) / CLOCKS_PER_SEC;
//    cout << "Run time for amicable for is " << d << " secs" << endl;
//    return 0 ;
//}




