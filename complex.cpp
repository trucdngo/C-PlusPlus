//
//  main.cpp
//  CPlusPlusDataStructureHW2
//
//  Created by truc ngo on 10/1/16.
//  Copyright © 2016 truc ngo. All rights reserved.
//


#include "complex.h"

/* constructor */
complex::complex(int x1, int x2) {
    _real = x1;
    _imaginary = x2;
    string realStr = to_string(_real);
    string imaginaryStr = to_string(_imaginary);
    unsigned long realLength = realStr.length();
    unsigned long imaginaryLength = imaginaryStr.length();
    string newString = combine_two_strings(realStr, imaginaryStr);
    _ptr = new char[realLength + imaginaryLength + 2];
    char const *newString_as_char_array = newString.c_str();
    strcpy(_ptr, newString_as_char_array);
}

/* copy constructor */
complex::complex(const complex& from) {
    cout << "invoke copy constructor for " << from._ptr << endl;
    unsigned long l = strlen(from._ptr);
    this->_ptr = new char[l];
    strcpy(_ptr, from._ptr);
    _real = from._real;
    _imaginary = from._imaginary;
}

void complex::setxy(int x, int y) {
    this->_real = x;
    this->_imaginary = y;
    string realStr = to_string(x);
    string imaginaryStr = to_string(y);
    unsigned long realLength = realStr.length();
    unsigned long imaginaryLength = imaginaryStr.length();
    string newString = combine_two_strings(realStr, imaginaryStr);
    delete [] this->_ptr;
    this->_ptr = new char[realLength + imaginaryLength + 2];
    char const *newString_as_char_array = newString.c_str();
    strcpy(_ptr, newString_as_char_array);
}

/* assigment operator = */
complex& complex::operator=(const complex& com) {
    if (this != &com) {
        this->_real = com._real;
        this->_imaginary = com._imaginary;
        unsigned long l = strlen(com._ptr);
        delete [] this->_ptr;
        this->_ptr = new char[l];
        strcpy(_ptr, com._ptr);
    }
    return *this;
}

/* equal operator == */
bool complex::operator==(const complex& com) {
    bool b1 = (this->_real == com._real) ? true : false;
    bool b2 = (this->_imaginary == com._imaginary) ? true : false;
    bool b3 = (strcmp(this->_ptr, com._ptr) == 0) ? true : false;
    
    if (b1 && b2 && b3) {
        return true;
    } else {
        return false;
    }
}


/* NOT equal operator != */
bool complex::operator!=(const complex& com) {
    bool b1 = (this->_real != com._real) ? true : false;
    bool b2 = (this->_imaginary != com._imaginary) ? true : false;
    bool b3 = (strcmp(this->_ptr, com._ptr) != 0) ? true : false;
    
    if (b1 || b2 || b3) {
        return true;
    } else {
        return false;
    }
}

/* print */
ostream& operator<<(ostream& os, const complex& com)
{
    os << com._ptr << endl;
    return os;
}

string combine_two_strings(string s1, string s2) {
    string negativeSign = "-";
    string sign = s2.substr(0,1);
    string newString = " ";
    // s2 is a negative number
    if (negativeSign.compare(sign) == 0) {
        string s2WithoutNegativeSign = s2.substr(1);
        newString = s1 + sign + "i" + s2WithoutNegativeSign;
    }
    if (negativeSign.compare(sign) != 0) {
        newString = s1 + "+i" + s2;
    }
    return newString;
}


/*
 int length_of_integer(int x) {
 int len = 0;
 if (x > 0) {
 for (len = 0; x > 0; len++) {
 x = x / 10;
 }
 }
 return len;
 }*/


