//
// Created by Selsabeel on 2022-10-28.
//

#include "BigReal.h"

string subtract(string, string) {
    //write a function that can take the
    // bigdecimalint values and turn them into string
    // to work with them..
    // it also has to access the sign 
}

int BigReal::Sign() {
    if (integer.Sign() == 1){
        return 1;
    }
    else if (integer.Sign() == -1){
        return -1;
    }
}

BigReal& BigReal::operator= (BigReal& other){
    integer = other.integer;
    decimal = other.decimal;
    return *this;
}

BigReal BigReal::operator+ (BigReal& other){
    BigReal result;
    if( (integer.Sign() == 1 ) & (other.integer.Sign() == 1) ){
        if (decimal.size() != other.decimal.size()){
            while(decimal.size() > other.decimal.size()){
                other.decimal.push_back('0');
            }
            while(decimal.size() < other.decimal.size()){
                decimal.push_back('0');
            }
        }
        string temporaryDecimal = "", temporary2Decimal = "";
        string forpushingback = "";
        temporaryDecimal += integer.getnum() + decimal.getnum();
        temporary2Decimal += other.integer.getnum() + other.decimal.getnum();
        int i =0;
        for(i;i<integer.size();i++){
            forpushingback += temporaryDecimal[i] + temporary2Decimal[i];
        }
        result.integer = forpushingback;
        forpushingback = "";
        for(int j=i;j<(i+decimal.size());j++){
            forpushingback += temporaryDecimal[j] + temporary2Decimal[j];
        }
        result.decimal = forpushingback;
    }
    if ( (integer.Sign() == 1) & (other.integer.Sign() == -1) ){
        subtract(integer.getnum(), other.integer.getnum());
    }
    if( (integer.Sign() == -1 ) & (other.integer.Sign() == -1) ){
        subtract(integer.getnum(), other.integer.getnum());
    }


}
BigReal BigReal::operator- (BigReal& other){
    BigReal result;
    string temp, temp2;
    if( (integer.Sign() == 1 ) & (other.integer.Sign() == 1) ){
        temp = subtract(integer.getnum(), other.integer.getnum());
        temp2 = subtract(other.decimal.getnum(), decimal.getnum());
        result = temp + temp2;
    }
    else if( (integer.Sign() == 1 ) & (other.integer.Sign() == -1) ){
        *this = *this + other; // adding two bigreals normally
        return *this;
    }
    else if( (integer.Sign() == -1 ) & (other.integer.Sign() == 1) ){
        temp = subtract(other.integer.getnum(), integer.getnum());
        temp2 = subtract(other.decimal.getnum(), decimal.getnum());
        result = temp + temp2;
    }
    else if( (integer.Sign() == -1 ) & (other.integer.Sign() == -1) ){
        // wait.. when adding two negative things just add normally lol
        // then turn into negative at the end
        *this = *this + other; // adding two bigreals normally
        this->integer.push_front('-');
    }
    return result;
}