/*
Author1: Selsabeel Asim Ali Elbagir
ID1: 20210714
Author2: Salma Abdelaziz Nabieh Soliman
ID2: 20211048
Author3: Sama Ahmed Saeed Kalil
ID3: 20210163
Section: S9/S10
TA: 
Professor: Dr.El-Ramly
Course: Object Oriented Programming
Description: 
*/

#ifndef UNTITLED2_BIGREAL_H
#define UNTITLED2_BIGREAL_H
#include "BigDecimalIntClass.h"
#include <regex>
using namespace std;


class BigReal {
private:
	BigDecimalInt* integer = new BigDecimalInt("0");
    BigDecimalInt* fraction = new BigDecimalInt("0");
    char signNumber;
public:
    BigReal(double realnumber = 0.0);       // Default constructor
    BigReal(string realnumber);
    BigReal(BigDecimalInt bigInteger);
    BigReal(const BigReal& other);   // copy constructor
    BigReal(BigReal&& other);       //  Move constructor
	BigReal& operator= (BigReal& other);   // Assignment operator
    BigReal& operator=(BigReal&& other); //  Move Assignment
    BigReal operator+ (BigReal& other);
    BigReal operator-(BigReal& other);
    bool operator < (BigReal anotherReal);
    bool operator > (BigReal anotherReal);
    bool operator == (BigReal anotherReal);
    int sign();
    int size();
    friend ostream& operator << (ostream& out, BigReal num);
    friend istream& operator >> (istream& out, BigReal& num);
    ~BigReal() {
		delete integer;
		delete fraction;
	}

};

#endif //UNTITLED2_BIGREAL_H
