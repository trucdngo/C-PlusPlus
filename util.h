/*----------------------------------------------------------------
Copyright (c) 2014 Author: Jagadeesh Vasudevamurthy
file: util.h
-----------------------------------------------------------------*/

/*----------------------------------------------------------------
include this file for all the programs
-----------------------------------------------------------------*/
#ifndef UTIL_H
#define UTIL_H

/*----------------------------------------------------------------
Basic include files
-----------------------------------------------------------------*/
#include <iostream>
#include <fstream>

#include <iomanip>      // std::setprecision
using namespace std;

#ifdef _WIN32
#include <cassert>
#include <ctime>
//#include "vld.h"  //Comment this line, if you have NOT installed Visual leak detector
#else
#include <assert.h>
#include <time.h>
#include <math.h> //required for log2
#include <string.h> //for strlen,strcat and strcpy on linux
#endif

//'sprintf': This function or variable may be unsafe. Consider using sprintf_s instead.To disable deprecation, 
//use _CRT_SECURE_NO_WARNINGS
//To overcome above warning
#ifdef _MSC_VER
#pragma warning(disable: 4996) /* Disable deprecation */
#endif

/*--------------------------------------------------------
class random number generator
----------------------------------------------------------*/
class Random {
public:
  Random() { srand((unsigned)time(0)); }
  int get_random_number(int a = 0, int b = 10000) const {
    int upper_bound, lower_bound;
    if (a < b) { upper_bound = b - a; lower_bound = a; }
    else if (a >= b) { upper_bound = a - b; lower_bound = b; }

    return(lower_bound + rand() % upper_bound);
  }
  /* no body can copy random or equal random */
  Random(const Random& x) = delete;
  Random& operator=(const Random& x) = delete;
private:
  
};



/*----------------------------------------------------------------
STL
-----------------------------------------------------------------*/
#include <stdexcept> //Without this catch will NOT work on Linux
#include <vector>
#include <string>

/*----------------------------------------------------------------
All external here
-----------------------------------------------------------------*/
extern int Strcmp(const char* s1, const char* s2);
extern void Strcpy(char* s1, const char* s2);
extern void print_integer(const int& x);
extern void print_integer(const int*& x);
extern void print_integer(int& x);
extern void print_integer(int*& x);
extern int int_ascending_order(const int& c1, const int& c2);
extern int int_ascending_order(int* const& c1, int* const& c2);
extern int int_descending_order(const int& c1, const int& c2);
extern int int_descending_order(int* const& c1, int* const& c2);
extern void delete_int(int*& c);
extern void delete_charstar(char*& c);
extern int charcompare(const char& c1, const char& c2);
extern void print_char(char& c);
extern void print_string(char*& c);
extern void free_string(char*& c);
extern int string_descending_order(char* const& c1, char* const& c2);
extern int string_ascending_order(char* const& c1, char* const& c2);


#endif

//EOF

