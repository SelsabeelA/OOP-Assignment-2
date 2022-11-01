#include "BigReal.h"

//Write your method functions here :)
//constructor
BigReal :: BigReal (string realNumber) {
    if(realNumber[0] == '-'){
        signNumber = '-';
    }
    else{
        signNumber = '+';
    }
    integer.setNumber(realNumber.substr(0, realNumber.find('.')));
    decimal.setNumber(realNumber.substr(realNumber.find('.') + 1, realNumber.length()));
}
//operator < overloading function.
bool BigReal :: operator < (BigReal anotherReal) {
    if (integer < anotherReal.integer)
        return true;
    else if (integer == anotherReal.integer) {
        string s1 = decimal.getNumber();
        string s2 = anotherReal.decimal.getNumber();
        if(s1.size() > s2.size()) {
            int diff = s1.length() - s2.length();
            for (int i = 0; i < diff; i++) {
                s2 += '0';
            }
        }
        else if(s1.size() < s2.size()) {
            int diff = s2.length() - s1.length();
            for (int i = 0; i < diff; i++) {
                s1 += '0';
            }
        }
        return s1 < s2;
    }
    else
        return false;
}

//operator > overloading function.
bool BigReal :: operator > (BigReal anotherReal) {
    if (integer > anotherReal.integer) {
        return true;
    }
    else if (integer == anotherReal.integer) {
        string s1 = decimal.getNumber();
        string s2 = anotherReal.decimal.getNumber();
        if(s1.size() > s2.size()) {
            int diff = s1.length() - s2.length();
            for (int i = 0; i < diff; i++) {
                s2 += '0';
            }
        }
        else if(s1.size() < s2.size()) {
            int diff = s2.length() - s1.length();
            for (int i = 0; i < diff; i++) {
                s1 += '0';
            }
        }
        return s1 > s2;
    }
    else
        return false;
}
//operator == overloading function.
bool BigReal :: operator == (BigReal anotherReal)
{
    string s1 = decimal.getNumber();
    string s2 = anotherReal.decimal.getNumber();
    if(s1.size() > s2.size()) {
        int diff = s1.length() - s2.length();
        for (int i = 0; i < diff; i++) {
            s2 += '0';
        }
    }
    else if(s1.size() < s2.size()) {
        int diff = s2.length() - s1.length();
        for (int i = 0; i < diff; i++) {
            s1 += '0';
        }
    }
    if(integer == anotherReal.integer && s1 == s2){
        return true;
    }
    else{
        return false;
    }
}
//size function.
int BigReal :: size()
{
    return integer.size() + decimal.size();
}
//sign function.
int BigReal ::sign()
{
    if (signNumber == '+')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//overloading operator <<.
ostream& operator << (ostream& out, BigReal num)
{
    out << num.integer << "." << num.decimal;
    return out;
}
//overload operator >>.
/*istream& operator >> (istream& in, BigReal num){
      string realNumber;
        in >> realNumber;
        num = BigReal(realNumber);
        return in;
}*/


