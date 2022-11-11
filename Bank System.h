/*
Author1: Selsabeel Asim Ali Elbagir
ID1: 20210714
Author2: Salma Abdelaziz Nabieh Soliman
ID2: 20211048
Author3: Sama Ahmed Saeed Kalil
ID3: 20210163
Section: S9/S10
TA: Ahmed 
Professor: Dr.El-Ramly
Course: Object Oriented Programming
Description:
*/
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
    BankAccount() {
        balance = 0;
        string n = to_string(count);
        if (n.size() < 2) n = "00" + n;
        else if (n.size() < 3) n = "0" + n;
        accountID = "FCAI-" + n;
        count++;
    }
    BankAccount(double balance) {
        string n = to_string(count);
        if (n.size() < 2) n = "00" + n;
        else if (n.size() < 3) n = "0" + n;
        accountID = "FCAI-" + n;
        this->balance = balance;
        count++;
    }
    string getAccountID() {
        return accountID;
    }
    double getBalance() {
        return balance;
    }
    void setBalance(double bal) {
        balance = bal;
    }
    void setID(string ID) {
        accountID = ID;
        count++;
    }
    virtual int withdraw(double amount) {
        if (amount > balance) {
            return 0;
        }
        else {
            balance -= amount;
            return 1;
        }
    }
    virtual int deposit(double amount) {
        if (amount < 0) {
            return 0;
        }
        else {
            balance += amount;
            return 1;
        }
    }
    void print() {
        cout << "Account ID: " << accountID;
        cout << "\nAcocunt Type : (Basic)\nBalance: " << balance << "\n";
    }
};
long long BankAccount::count = 1;

class SavingsBankAccount :public BankAccount {
private:
    double minimumBalance = 1000;
public:
    SavingsBankAccount(double balance, double minimumBalance);
    int withdraw(double amount);
    int deposit(double amount);
    void printall() {
        cout << "Account ID: " << accountID;
        cout << "\nAcocunt Type : (Saving)\nInitial Balance: " << balance << "\n";
        cout << "Minimum Balance: " << minimumBalance << "\n";
    }
    double getMinimumBalance() { return minimumBalance; }
};


class client {
    string Name, Address, PhoneNumber;
    string AccountType;
public:
    client(string name, string address, string phone) {
        Name = name;
        Address = address;
        PhoneNumber = phone;
    }
    void setAccountType(string type) {
        AccountType = type;
    }
    string getName() { return Name; }
    string getAddress() { return Address; }
    string getPhoneNumber() { return PhoneNumber; }
    void print() {
        cout << "Name: " << getName() << "\nAddress: " << getAddress() << "\nPhone: " << getPhoneNumber() << "\n";
    }
};

class BankingApplication {
    map<string, pair<client*, BankAccount*>>dataBasic;
    map<string, pair<client*, SavingsBankAccount*>>dataSaving;
    void fillData();
    void storeData();
    void newAccount();
    void ListClientsAccounts();
    void WithdrawMoney();
    void DepositMoney();
public:
    BankingApplication() {
        fillData();
        int comp = 0;
        do {
            cout << "Welcome to FCAI Banking Application \n1. Create a New Account\n";
            cout << "2. List Clients and Accounts\n3. Withdraw Money\n4. Deposit Money\n";
            cout << "Please Enter Choice =========>  ";
            int operation;
            cin >> operation;
            if (operation == 1)newAccount();
            else if (operation == 2)ListClientsAccounts();
            else if (operation == 3)WithdrawMoney();
            else if (operation == 4)DepositMoney();
            else {
                cout << "There is no of such an choice\n";
                exit(1);
            }
            cout << "\nIf you want to complete Enter 1 else Enter 0==> ";
            cin >> comp;
            cout << "\n";
        } while (comp);
    }
    ~BankingApplication() {
        storeData();
        for (auto it = dataBasic.begin(); it != dataBasic.end(); it++) {
            delete it->second.first;
            delete it->second.second;
        }
        for (auto it = dataSaving.begin(); it != dataSaving.end(); it++) {
            delete it->second.first;
            delete it->second.second;
        }
    }
};

