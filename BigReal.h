/*
Author1: Selsabeel Asim Ali Elbagir
ID1: 20210714
Author2: Salma Abdelaziz Nabieh Soliman
ID2: 20211048
Author3:
ID3:
Section: S9/S10
TA: 
Professor: Dr.El-Ramly
Course: Object Oriented Programming
Description: 
*/

#ifndef UNTITLED2_BIGREAL_H
#define UNTITLED2_BIGREAL_H
#include "BigDecimalIntClass.h"
#include <bits/stdc++.h>
using namespace std;

class BigReal {
private:
    BigDecimalInt integer;
    BigDecimalInt decimal;
    char signNumber;
public:
    BigReal (double realNumber = 0.0); // Default constructor
    BigReal (string realNumber);
    BigReal (BigDecimalInt bigInteger);
    BigReal (const BigReal& other); // Copy constructor
    BigReal (BigReal&& other); // Move constructor
    BigReal& operator= (BigReal& other); // Assignment operator
    BigReal& operator= (BigReal&& other); // Move assignment*/
    BigReal operator+ (BigReal& other);
    BigReal operator- (BigReal& other);
    bool operator< (BigReal anotherReal);
    bool operator> (BigReal anotherReal);
    bool operator== (BigReal anotherReal);
    int size();
    int sign();
    friend ostream& operator << (ostream& out, BigReal num);
    friend istream& operator >> (istream& out, BigReal num);
};

#endif //UNTITLED2_BIGREAL_H
