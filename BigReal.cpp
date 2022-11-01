#include "BigReal.h"

//Write your method functions here :)
//constructor
/*BigReal :: BigReal (string realNumber) {

    integer.setNumber(realNumber.substr(0, realNumber.find('.')));
    decimal.setNumber(realNumber.substr(realNumber.find('.') + 1, realNumber.length()));
}*/
//operator < overloading function.
bool BigReal :: operator < (BigReal anotherReal) {
    if (integer < anotherReal.integer)
        return true;
    else if (integer == anotherReal.integer)
        return decimal < anotherReal.decimal;
    else
        return false;
}
//operator > overloading function.
bool BigReal :: operator > (BigReal anotherReal) {
    if (integer > anotherReal.integer) {
        return true;
    }
    else if (integer == anotherReal.integer) {
        return decimal > anotherReal.decimal;
    }
    else {
        return false;
    }
}
//operator == overloading function.
bool BigReal :: operator == (BigReal anotherReal){
    if(integer == anotherReal.integer && decimal == anotherReal.decimal){
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
    if (integer.sign() == '+')
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


