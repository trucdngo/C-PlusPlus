//
//  amicabletest.cpp
//  CPlusPlusDataStrutureHW1
//
//  Created by truc ngo on 9/27/16.
//  Copyright © 2016 truc ngo. All rights reserved.
//

#include "amicable.h"
#include "amicable.cpp"

int main() {
    clock_t start = clock();
    cout << "Here are pairs of amicable pairs: " << endl;
    amicable a(100000000);
    a.getAmicablePairs();
    clock_t end = clock();
    double d = double(end - start) / CLOCKS_PER_SEC;
    cout << "Run time for amicable for is " << d << " secs" << endl;
    return 0 ;
}