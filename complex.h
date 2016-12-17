//
//  complex.h
//  CPlusPlusDataStructureHW2
//
//  Created by truc ngo on 10/1/16.
//  Copyright © 2016 truc ngo. All rights reserved.
//

#ifndef complex_h
#define complex_h

#include <iostream>
#include <stdio.h>
using namespace std;

string combine_two_strings(string s1, string s2);

class complex {
public:
    complex(int, int);
    ~complex() {
        cout << "Inside class complex's destructor for: " << this->_ptr << endl;
        delete [] this->_ptr;
    };
    friend ostream& operator<<(ostream& os, const complex& comObject);
    complex(const complex& c);
    void setxy(int x, int y);
    complex& operator=(const complex& com);
    bool operator==(const complex& com);
    bool operator!=(const complex& com);
    
private:
    int _real;
    int _imaginary;
    char* _ptr;
};


#endif /* complex_h */
