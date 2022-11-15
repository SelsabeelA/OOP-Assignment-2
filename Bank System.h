//#ifndef ASSIGNMENT_2_BANKSYSTEM_H
//#define ASSIGNMENT_2_BANKSYSTEM_H

#include<iostream>
#include <regex>
#include <map>
#include <fstream>
using namespace std;
class BankAccount {
protected:
    string accountID;
    double balance;
    static long long count;
public:
    BankAccount();
    BankAccount(double balance);
    string getAccountID();
    double getBalance();
    void setBalance(double bal);
    void setID(string ID);
    virtual int withdraw(double amount);
    virtual int deposit(double amount);
    void print();
};

class SavingsBankAccount :public BankAccount {
private:
    double minimumBalance = 1000;
public:
    SavingsBankAccount(double balance, double minimumBalance);
    int withdraw(double amount);
    int deposit(double amount);
    void printall();
    double getMinimumBalance();
};


class client {
    string Name, Address, PhoneNumber;
    string AccountType;
public:
    client(string name, string address, string phone);
    void setAccountType(string type);
    string getName();
    string getAddress();
    string getPhoneNumber();
    void print();
};

class BankingApplication {
    map<string, pair<client*, BankAccount*>>dataBasic;
    map<string, pair<client*, SavingsBankAccount*>>dataSaving;
    void fillData();
    void storeData();
    void newAccount();
    void ListClientsAccounts();
    void printBAccount(map<string, pair<client*, BankAccount*>>::iterator it);
    void printSAccount(map<string, pair<client*, SavingsBankAccount*>>::iterator it);
    void WithdrawMoney();
    void DepositMoney();
    void Cases();
public:
    BankingApplication();
    ~BankingApplication();
};


//#endif //ASSIGNMENT_2_BANKSYSTEM_H
