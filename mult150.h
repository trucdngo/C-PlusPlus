//
//  mult150.h
//  CPlusPlusDataStructureHW2
//
//  Created by truc ngo on 10/6/16.
//  Copyright © 2016 truc ngo. All rights reserved.
//

#ifndef mult150_h
#define mult150_h
#define SIZE 150

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class mult150 {
public:
    mult150(const char* numOne, const char* numTwo);
    mult150(const mult150&);
    mult150& operator=(const mult150&);
    char* operator=(char*& ptr);
    void addTwoStrings(int index, bool multiplyAndAdd = true);
    void mutiplyStringWithACharacter(char*&, int);
    ~mult150() {
        cout << "Inside mult150 destructor" << endl;
        delete [] this->_num1;
        delete [] this->_num2;
        delete [] this->_result;
        delete [] this->_temp;
    }
    void multiplyTwoStrings();
    friend ostream& operator<<(ostream& os, const mult150& comObject);
    
private:
    //multiplication of two arguments
    char* _num1;
    char* _num2;
    char* _result;
    char* _temp = nullptr;
    int _num2Index;
};

#endif /* mult150_h */
