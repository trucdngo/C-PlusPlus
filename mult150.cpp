//
//  mult150.cpp
//  CPlusPlusDataStructureHW2
//
//  Created by truc ngo on 10/6/16.
//  Copyright © 2016 truc ngo. All rights reserved.
//

#include "mult150.h"

void printString(char*& ptr) {
    cout << "Inside print ptr function: ";
    for (int i = 0; i < (int)(strlen(ptr)); i++) {
        cout << ptr[i] - '0';
    }
    cout << endl;
}

/* constructor */
mult150::mult150(const char* numOne, const char* numTwo) {
    int numOneStr = (int)(strlen(numOne));
    int numTwoStr = (int)(strlen(numTwo));
    if (numOneStr >= numTwoStr) {
        this->_num1 = new char[numOneStr + 1];
        strcpy(_num1, numOne);
        this->_num2 = new char[numTwoStr + 1];
        strcpy(_num2, numTwo);
    } else if (numOneStr < numTwoStr) {
        this->_num1 = new char[numTwoStr + 1];
        strcpy(_num1, numTwo);
        this->_num2 = new char[numOneStr + 1];
        strcpy(_num2, numOne);
    }
    this->_result = new char[SIZE + 1];
    memset(_result,'\0', SIZE + 1);
    this->multiplyTwoStrings();
}


/* copy constructor */
mult150::mult150(const mult150& from) {
    cout << "invoke copy constructor for " << from._num1 <<  " and " << from._num2 << endl;
    unsigned long l = strlen(from._num1) + 1;
    this->_num1 = new char[l];
    strcpy(this->_num1, from._num1);
}


char* mult150::operator=(char*& ptr) {
    cout << "In equal operator for pointer.." << endl;
    delete [] this->_result;
    unsigned long l1 = strlen(ptr);
    this->_result = new char[(int)l1 + 1];
    strcpy(this->_result, ptr);
    return this->_result;
}


/* overridden equal operator */
mult150& mult150::operator=(const mult150 &rhs) {
    cout << "In equal operator: assign " << rhs._num1 << " to this object " << endl;
    cout << "In equal operator: assign " << rhs._num2 << " to this object " << endl;
    cout << "In equal operator: assign " << rhs._result << " to this object " << endl;

    if (this != &rhs) {
        delete [] this->_num1;
        unsigned long l1 = strlen(rhs._num1) + 1;
        this->_num1 = new char[l1];
        strcpy(this->_num1, rhs._num1);
        
        delete [] this->_num2;
        unsigned long l2 = strlen(rhs._num2) + 1;
        this->_num2 = new char[l2];
        strcpy(this->_num2, rhs._num2);
        
        delete [] this->_result;
        unsigned long l3 = strlen(rhs._result) + 1;
        this->_result = new char[l3];
        strcpy(this->_result, rhs._result);
    }
    return *this ;
}


void mult150::multiplyTwoStrings() {    
    int numTwoLength = (int)(strlen(this->_num2));
    char*  strPtr1(this->_num1);
    char*  strPtr2(this->_num2);
    int numberOfZeroNeededToNum2 = 0;
    int counter = 0;
    // if num2 has 3 digits then i = 2, 1, 0
    for (int i = numTwoLength - 1; i >= 0; i--) {
        counter++;
        int indexValue = strPtr2[i] - '0';
        // if 2nd string has only one number, i.e. 2
        if (numTwoLength == 1) {
            mutiplyStringWithACharacter(strPtr1, indexValue);
            break;
        } else {
            // if not the last digit of num2
            if (i > 0 && counter == 1) {
                mutiplyStringWithACharacter(strPtr1, indexValue);
                numberOfZeroNeededToNum2++;
                this->_num2Index = numberOfZeroNeededToNum2;
                i = i - 1;
                indexValue = strPtr2[i] - '0';
                addTwoStrings(indexValue, true); //if true: multiply then add
            } else if (i > 0 && counter >= 2) {
                mutiplyStringWithACharacter(strPtr1, indexValue);
                numberOfZeroNeededToNum2++;
                this->_num2Index = numberOfZeroNeededToNum2;
                addTwoStrings(indexValue, false); //if false: add only
            } else if (i == 0) {
                mutiplyStringWithACharacter(strPtr1, indexValue);
                numberOfZeroNeededToNum2++;
                this->_num2Index = numberOfZeroNeededToNum2;
                addTwoStrings(indexValue, false);
            }
        }
    }
}


void mult150::mutiplyStringWithACharacter(char*& strPtr, int number) {
    
    const int extraSpace = 1;
    int str1Length1 = (int)(strlen(strPtr));
    int bufferArraySize = str1Length1 + extraSpace ;
    char resultString[bufferArraySize];
    char* resultStringPtr = resultString;
    memset(resultStringPtr, '\0', bufferArraySize + 1);
    
    int carryOver = 0;
    for (int i = bufferArraySize - 1; i > 0; i--) {
        // temp's max value = 9 * 9 = 81
        int temp = (strPtr[i-extraSpace] - '0') * number + carryOver;
        int digit = temp % 10;
        char ch = (char)(digit) + '0';
        resultStringPtr[i] = ch;
        carryOver = (temp - 10 >= 0) ? (temp / 10) : 0;
        if (carryOver != 0 && i == 1) {
            resultStringPtr[i-1] = (char)carryOver + '0';
        } else if (carryOver == 0 && i == 1) {
            resultStringPtr[i-1] = (char)0 + '0';
        }
    }

    // if first string index has '0', remove it
    // then reassign it back to this->_result and this->_temp
    if (resultStringPtr[0] == '0') {
        int l1 = (int)(strlen(resultStringPtr));
        char* strPtr1 = new char[l1];
        memset(strPtr1, '\0', l1);
        int j = 0;
        for (int i = 1; i < l1; i++) {
            strPtr1[j] = resultStringPtr[i];
            j++;
        }
        delete [] this->_result;
        int l2 = (int)(strlen(strPtr1))+ 1;
        this->_result = new char[l2];
        memset(this->_result, '\0', l2);
        strcpy(this->_result, strPtr1);

    } else {
        delete [] this->_result;
        int l1 = (int)(strlen(resultStringPtr) + 1);
        this->_result = new char[l1];
        memset(this->_result, '\0', l1);
        strcpy(this->_result, resultStringPtr);
    }
}

void mult150::addTwoStrings(int indexValue, bool multiplyAndAdd) {
    
    if (this->_temp == nullptr) {
        int l0 = (int)(strlen(this->_result)) + 1;
        this->_temp = new char[l0];
        strcpy(this->_temp, this->_result);
    }
    
    // Make copy of this->_result
    // Adding '0' to string[0]
    int l1 = (int)(strlen(this->_temp));
    int lengthOfResultString = l1 + 1;
    char copyOfResultPtr[lengthOfResultString];
    memset(copyOfResultPtr, '\0', lengthOfResultString);
    copyOfResultPtr[0] = '0';
    int j = 1;
    for (int i = 0; i < l1; i++) {
        copyOfResultPtr[j] = this->_temp[i];
        j++;
    }
    copyOfResultPtr[j] = '\0';

    char*  strPtr1(this->_num1);
    //now update "this->_result" with the sum of products returned by mutiplyStringWithACharacter()
    if (multiplyAndAdd) {
        mutiplyStringWithACharacter(strPtr1, indexValue);
    }
    
    //  51(as A) * 19
    //  if 51 * 1 = 51(as B) and len(B) == len(A), then add '0' at string[0].
    //  51 * 19
    //= 0459
    //  051  <-- add '0' front of '51'
    int l2 = (int)(strlen(this->_result));
    int l3 = (int)(strlen(strPtr1));
    if (l2  == l3) {
        int l4 = l2 + 2;
        char* strPtr2 = new char[l4];
        memset(strPtr2, '\0', l4);
        strPtr2[0] = '0';
        int j = 1;
        for (int i = 0; i < l2; i++) {
            strPtr2[j] = this->_result[i];
            j++;
        }
        delete [] this->_result;
        strcpy(this->_result, strPtr2);
    }
    
    // Insert Zeros at the end of the string
    // Number of zeros is the counter of index number of number2 going from right to left
    int l7 = (int)(strlen(this->_result));
    int numOfZeros = this->_num2Index;
    int l8 = l7 + numOfZeros + 1;
    char tempStringPtr2[l8];
    memset(tempStringPtr2, '\0', l8);
    int i = 0;
    for (; i < l7; i++) {
        tempStringPtr2[i] = this->_result[i];
    }
    for (; i < l8-1; i++) {
        tempStringPtr2[i] = '0';
    }
    // Why can't I delete this->_result here?
    // delete [] this->_result;
    int l81 = l8 + 1;
    this->_result = new char[l81];
    memset(this->_result, '\0', l81);
    strcpy(this->_result, tempStringPtr2);

    // need to fill up one or more zero at the beginning of string
    int l11 = (int)(strlen(copyOfResultPtr));
    int l12 = (int)(strlen(this->_result));
    if (l11 > l12) {
        int l11_l12 = l11 - l12;
        int aPtrLen = l11 + 2;
        char* aPtr = new char[aPtrLen];
        memset(aPtr, '\0', aPtrLen);
        for (int counter1 = 0; counter1 < l11_l12; counter1++) {
            aPtr[counter1] = '0';
        }
        for (int counter2 = 0; counter2 < l12; counter2++) {
            aPtr[counter2 + l11_l12] = this->_result[counter2];
        }
        delete [] this->_result;
        memset(this->_result, '\0', aPtrLen);
        strcpy(this->_result, aPtr);
    } else {
        int l12_l11 = l12 - l11;
        int bPtrLen = l12 + 2;
        char* bPtr = new char[bPtrLen];
        memset(bPtr, '\0', bPtrLen);
        for (int counter1 = 0; counter1 < l12_l11; counter1++) {
            bPtr[counter1] = '0';
        }
        for (int counter2 = 0; counter2 < l11; counter2++) {
            bPtr[counter2 + l12_l11] = copyOfResultPtr[counter2];
        }
        memset(copyOfResultPtr, '\0', bPtrLen);
        strcpy(copyOfResultPtr, bPtr);
    }
   
    // Adding two strings
    lengthOfResultString = (int)(strlen(copyOfResultPtr));
    int bufferArraySize = lengthOfResultString + 2;
    char resultString[bufferArraySize];
    char* strPtr3 = resultString;
    memset(strPtr3, '\0', bufferArraySize);
    int carryOver = 0;
    for (int i = lengthOfResultString - 1; i >= 0; i--) {
        int temp = copyOfResultPtr[i] - '0' + this->_result[i] - '0' + carryOver;
        int digit = temp % 10;
        char ch = (char)(digit) + '0';
        strPtr3[i+1] = ch;
        carryOver = (temp - 10 >= 0) ? 1 : 0;
        if (carryOver > 0 && i == 0) {
            strPtr3[i] = (char)carryOver + '0';
        } else if (carryOver == 0 && i == 0) {
            strPtr3[i] = (char)0 + '0';
        }
    }

    // Remove those '0s' from beginning of the string if exists
    if (strPtr3[0] == '0') {
        int l9 = (int)(strlen(strPtr3));
        //determine how many zero (zeros) from the left of the string
        int zeros = 0;
        for (; zeros < l9; zeros++) {
            if (strPtr3[zeros] != '0') {
                break;
            }
        }
        // reduce from '00969' to '969'
        char* strPtr4 = new char[l9];
        memset(strPtr4, '\0', l9);
        int j = 0;
        for (int i = zeros; i < l9; i++) {
            strPtr4[j] = strPtr3[i];
            j++;
        }
        delete [] this->_result;
        int l10 = (int)(strlen(strPtr4))+ 1;
        this->_result = new char[l10];
        memset(this->_result, '\0', l10);
        strcpy(this->_result, strPtr4);
      
        // store result back into this->_temp
        delete [] this->_temp;
        this->_temp = new char[l10];
        memset(this->_temp, '\0', l10);
        strcpy(this->_temp, strPtr4);

    } else {
        // store result back into this->_result
        delete [] this->_result;
        int l9 = (int)(strlen(strPtr3) + 1);
        this->_result = new char[l9];
        memset(this->_result, '\0', l9);
        strcpy(this->_result, strPtr3);
       
        // store result back into this->_temp
        delete [] this->_temp;
        this->_temp = new char[l9];
        memset(this->_temp, '\0', l9);
        strcpy(this->_temp, strPtr3);
    }
}

/* print */
ostream& operator<<(ostream& os, const mult150& mult)
{
    os << "Value of argument #1 is: " << mult._num1 << endl;
    os << "Value of argument #2 is: " << mult._num2 << endl;
    os << "Value of multiplication product is: " << mult._result << endl;
    return os;
}