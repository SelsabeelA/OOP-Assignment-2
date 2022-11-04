#include "BigReal.h"

BigReal ::BigReal(double realnumber) {
    string n = to_string(realnumber), Int = "", frac = "";
    if (n[0] == '+' || n[0] == '-') {
        signNumber = n[0];
        n.erase(0);
    }
    int i = 0;
    while ((i < n.size()) && (n[i] != '.')) {
        Int += n[i];
        i++;
    }
    i++;
    while (i < n.size()) {
        frac += n[i];
        i++;
    }
    *integer = Int;
    *fraction = frac;
}
BigReal::BigReal(string realnumber) {
    regex validInput("[-+]?[0-9]*[\.]?[0-9]*");
    if (!regex_match(realnumber, validInput)) {
        cout << "Invalid input\n";
        exit(1);
    }
    if (realnumber[0] == '+' || realnumber[0] == '-') {
        signNumber = realnumber[0];
        realnumber.erase(realnumber.begin());
    }
    string Int = "", frac = "";
    int i = 0;
    while ((i < realnumber.size()) && (realnumber[i] != '.')) {
        Int += realnumber[i];
        i++;
    }
    i++;
    while (i < realnumber.size()) {
        frac += realnumber[i];
        i++;
    }
    *integer = Int;
    *fraction = frac;
}

BigReal::BigReal(BigDecimalInt bigInteger) {
    if (bigInteger.Sign())
        signNumber = '+';
    else
        signNumber = '-';
    *integer = bigInteger;
    BigDecimalInt frac("0");
    *fraction = frac;
}

BigReal::BigReal(const BigReal& other) {
    signNumber = other.signNumber;
    *integer = *other.integer;
    *fraction = *other.fraction;
}

BigReal::BigReal(BigReal&& other) {      //  Move constructor
    signNumber = other.signNumber;
    integer = other.integer;
    fraction = other.fraction;
    other.integer = nullptr;
    other.fraction = nullptr;
}
BigReal& BigReal:: operator= (BigReal& other) {
    signNumber = other.signNumber;
    *integer = *other.integer;
    *fraction = *other.fraction;
    return *this;
}

BigReal& BigReal:: operator=(BigReal&& other)
{
    signNumber = other.signNumber;
    integer = other.integer;
    fraction = other.fraction; 
    other.integer = nullptr;
    other.fraction = nullptr;
    return *this;
}
 



void add_zeroes(string& temporaryDecimal, string& temporaryOtherDecimal) {
    if (temporaryDecimal.size() != temporaryOtherDecimal.size()) {
        while (temporaryDecimal.size() > temporaryOtherDecimal.size()) {
            temporaryOtherDecimal += "0";
        }
        while (temporaryOtherDecimal.size() > temporaryDecimal.size()) {
            temporaryDecimal += "0";
        }
    }
}



BigReal BigReal::operator+ (BigReal& other) {
    BigReal result;
    string temporaryDecimal = fraction->getNumber();
    string temporaryOtherDecimal = other.fraction->getNumber();
    add_zeroes(temporaryDecimal, temporaryOtherDecimal);

    string temporaryInteger = integer->getNumber();
    string temporaryOtherInteger = other.integer->getNumber();

    BigDecimalInt temp1(temporaryInteger + temporaryDecimal);
    BigDecimalInt temp2(temporaryOtherInteger + temporaryOtherDecimal);

    string forpushingback = "";

    BigDecimalInt sum(temp1 + temp2);
    string string_sum = sum.getNumber();;
    int i = 0;
    for (i; i < temporaryInteger.size(); i++) {
        forpushingback += string_sum[i];
    }
    result.integer = new BigDecimalInt (forpushingback);
    forpushingback = "";
    for (int j = i; j < (i + temporaryDecimal.size()); j++) {
        forpushingback += string_sum[j];
    }
    result.fraction = new BigDecimalInt (forpushingback);
    return result;
}


BigReal BigReal::operator-(BigReal& other) {
    BigReal result;
    string temporaryDecimal = fraction->getNumber();
    string temporaryOtherDecimal = other.fraction->getNumber();
    add_zeroes(temporaryDecimal, temporaryOtherDecimal);

    string temporaryInteger = integer->getNumber();
    string temporaryOtherInteger = other.integer->getNumber();;

    BigDecimalInt temp1(temporaryInteger + temporaryDecimal);
    BigDecimalInt temp2(temporaryOtherInteger + temporaryOtherDecimal);

    string forpushingback = "";

    BigDecimalInt sum(temp1 - temp2);
    string string_sum = sum.getNumber();
    int i = 0;
    for (i; i < temporaryInteger.size(); i++) {
        forpushingback += string_sum[i];
    }
    result.integer = new BigDecimalInt(forpushingback);
    forpushingback = "";
    for (int j = i; j < (i + temporaryDecimal.size()); j++) {
        forpushingback += string_sum[j];
    }
    result.fraction = new BigDecimalInt(forpushingback);
    return result;
}

//operator < overloading function.
bool BigReal :: operator < (BigReal anotherReal) {
    if (*integer < *anotherReal.integer)
        return true;
    else if (*integer == *anotherReal.integer) {
        string s1 = fraction->getNumber();
        string s2 = anotherReal.fraction->getNumber();
        if (s1.size() > s2.size()) {
            int diff = s1.length() - s2.length();
            for (int i = 0; i < diff; i++) {
                s2 += '0';
            }
        }
        else if (s1.size() < s2.size()) {
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
    if (*integer > *anotherReal.integer) {
        return true;
    }
    else if (*integer == *anotherReal.integer) {
        string s1 = fraction->getNumber();
        string s2 = anotherReal.fraction->getNumber();
        if (s1.size() > s2.size()) {
            int diff = s1.length() - s2.length();
            for (int i = 0; i < diff; i++) {
                s2 += '0';
            }
        }
        else if (s1.size() < s2.size()) {
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
    string s1 = fraction->getNumber();
    string s2 = anotherReal.fraction->getNumber();
    if (s1.size() > s2.size()) {
        int diff = s1.length() - s2.length();
        for (int i = 0; i < diff; i++) {
            s2 += '0';
        }
    }
    else if (s1.size() < s2.size()) {
        int diff = s2.length() - s1.length();
        for (int i = 0; i < diff; i++) {
            s1 += '0';
        }
    }
    if (integer == anotherReal.integer && s1 == s2) {
        return true;
    }
    else {
        return false;
    }
}
//size function.
int BigReal::size()
{
    return integer->size() + fraction->size();
}
//sign function.
int BigReal::sign()
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
    out << num.integer->getNumber() << "." << num.fraction->getNumber();
    return out;
}
//overload operator >>.
/*istream& operator >> (istream& in, BigReal num){
      string realNumber;
        in >> realNumber;
        num = BigReal(realNumber);
        return in;
}*/





