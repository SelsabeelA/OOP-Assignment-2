#include "BigReal.h"

BigReal ::BigReal(double realnumber) {
    string n = to_string(realnumber), Int = "", frac = "";
    if (n[0] == '+' || n[0] == '-') {
        signNumber = n[0];
        n.erase(n.begin());
    }
    else {
        signNumber = '+';
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
    regex case1("[-+]?[0-9]+"),case2("[-+]?[\\.][0-9]+"),case3("[-+]?[0-9]+[\\.][0-9]+");
    if ((!regex_match(realnumber, case1))&&
        (!regex_match(realnumber, case2))&&(!regex_match(realnumber, case3))) {
        cout << "Invalid input\n";
        exit(1);
    }
    if (realnumber[0] == '+' || realnumber[0] == '-') {
        signNumber = realnumber[0];
        realnumber.erase(realnumber.begin());
    }
    else {
        signNumber = '+';
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
    if (frac.size() == 0) {
        frac = "0";
    }
    else if (Int.size()==0) {
        Int = "0";
    }
    *integer = Int;
    *fraction = frac;
}

BigReal::BigReal(BigDecimalInt bigInteger) {
    if (bigInteger.sign())
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
    if(sign() == -1){
        temp1.setsign('-');
    }
    if(other.sign() == -1){
        temp2.setsign('-');
    }

    string forpushingback = "";

    BigDecimalInt sum(temp1 + temp2);
    if(sum.sign() == 0){
        result.signNumber = '-';
    }
    else{
        result.signNumber = '+';
    }
    string string_sum = sum.getNumber();
    if(string_sum == "0"){
        BigReal result(0);
        return result;
    }
    if(string_sum.size() <= temporaryDecimal.size()){
        result.integer = new BigDecimalInt("0");
        if(string_sum.size()!=temporaryDecimal.size()){
            for(int i =0;i<(temporaryDecimal.size()-string_sum.size());i++){
                forpushingback += "0";
            }
        }
        result.fraction = new BigDecimalInt(forpushingback+string_sum);
        forpushingback="";
        return result;
    }
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
    if(sign() == -1){
        temp1.setsign('-');
    }
    if(other.sign() == -1){
        temp2.setsign('-');
    }

    string forpushingback = "";

    BigDecimalInt sum(temp1 - temp2);
    if(sum.sign() == 0){
        result.signNumber = '-';
    }
    else{
        result.signNumber = '+';
    }
    string string_sum = sum.getNumber();
    int i = 0;
    if(string_sum == "0"){
        BigReal result(0);
        return result;
    }
    if(string_sum.size() <= temporaryDecimal.size()){
        result.integer = new BigDecimalInt("0");
        if(string_sum.size()!=temporaryDecimal.size()){
            for(int i =0;i<(temporaryDecimal.size()-string_sum.size());i++){
                forpushingback += "0";
            }
        }
        result.fraction = new BigDecimalInt(forpushingback+string_sum);
        forpushingback="";
        return result;
    }
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
    integer->setsign(signNumber);
    fraction->setsign(signNumber);
    anotherReal.integer->setsign(anotherReal.signNumber);
    anotherReal.fraction->setsign(anotherReal.signNumber);
    if (*integer < *anotherReal.integer)
        return true;
    else if (*integer == *anotherReal.integer) {
        string s1 = fraction->getNumber();
        string s2 = anotherReal.fraction->getNumber();
        add_zeroes(s1, s2);
        return s1 < s2;
    }
    else
        return false;
}

//operator > overloading function.
bool BigReal :: operator > (BigReal anotherReal) {
    integer->setsign(signNumber);
    fraction->setsign(signNumber);
    anotherReal.integer->setsign(anotherReal.signNumber);
    anotherReal.fraction->setsign(anotherReal.signNumber);
    if (*integer > *anotherReal.integer) {
        return true;
    }
    else if (*integer == *anotherReal.integer) {
        string s1 = fraction->getNumber();
        string s2 = anotherReal.fraction->getNumber();
        add_zeroes(s1, s2);
        return s1 > s2;
    }
    else
        return false;
}
//operator == overloading function.
bool BigReal :: operator == (BigReal anotherReal)
{
    integer->setsign(signNumber);
    fraction->setsign(signNumber);
    anotherReal.integer->setsign(anotherReal.signNumber);
    anotherReal.fraction->setsign(anotherReal.signNumber);
    string s1 = fraction->getNumber();
    string s2 = anotherReal.fraction->getNumber();
    add_zeroes(s1, s2);
    if (*integer == *anotherReal.integer && s1 == s2) {
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
        return -1;
    }
}
//overloading operator <<.
ostream& operator << (ostream& out, BigReal num)
{
    if (num.signNumber == '-')
    {
        out << num.signNumber;
    }
    out << num.integer->getNumber() << "." << num.fraction->getNumber();
    return out;
}
//overload operator >>.
istream& operator >> (istream& in, BigReal& num){
    string realNumber;
    in >> realNumber;
    BigReal temb(realNumber);
    num = temb;
    return in;
}
