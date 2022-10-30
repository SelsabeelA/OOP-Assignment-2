//
// Created by Selsabeel on 2022-10-28.
//

#ifndef UNTITLED2_BIGREAL_H
#define UNTITLED2_BIGREAL_H
#include "BigDecimalIntClass.h"
#include <bits/stdc++.h>
using namespace std;

class BigReal {
private:
    BigDecimalInt whole;
    BigDecimalInt decimal;
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
    //bool operator< (BigReal anotherReal);
    //bool operator> (BigReal anotherReal);
    //bool operator== (BigReal anotherReal);
    int size();
    int Sign();
    //friend ostream& operator << (ostream& out, BigReal num);
    //friend istream& operator >> (istream& out, BigReal num);
};

#endif //UNTITLED2_BIGREAL_H
