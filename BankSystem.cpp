#include"BankSystem.h"

BankAccount::BankAccount() {
    balance = 0;
    string n = to_string(count);
    if (n.size() < 2) n = "00" + n;
    else if (n.size() < 3) n = "0" + n;
    accountID = "FCAI-" + n;
    count++;
}
BankAccount::BankAccount(double balance) {
    string n = to_string(count);
    if (n.size() < 2) n = "00" + n;
    else if (n.size() < 3) n = "0" + n;
    accountID = "FCAI-" + n;
    this->balance = balance;
    count++;
}

string BankAccount::getAccountID() {
    return accountID;
}

double BankAccount::getBalance() {
    return balance;
}
void BankAccount::setBalance(double bal) {
    balance = bal;
}
void BankAccount::setID(string ID) {
    accountID = ID;
    count++;
}
int BankAccount::withdraw(double amount) {
    if (amount > balance) {
        return 0;
    }
    else {
        balance -= amount;
        return 1;
    }
}
int BankAccount::deposit(double amount) {
    if (amount < 0) {
        return 0;
    }
    else {
        balance += amount;
        return 1;
    }
}
void BankAccount::print() {
    cout << "Account ID: " << accountID;
    cout << "\nAcocunt Type : (Basic)\nBalance: " << balance << "\n";
}

long long BankAccount::count = 1;


void SavingsBankAccount::printall() {
    cout << "Account ID: " << accountID;
    cout << "\nAcocunt Type : (Saving)\nInitial Balance: " << balance << "\n";
    cout << "Minimum Balance: " << minimumBalance << "\n";
}
double SavingsBankAccount::getMinimumBalance() {
    return minimumBalance;
}


client::client(string name, string address, string phone) {
    Name = name;
    Address = address;
    PhoneNumber = phone;
}
void client::setAccountType(string type) {
    AccountType = type;
}
string client::getName() { return Name; }
string client::getAddress() { return Address; }
string client::getPhoneNumber() { return PhoneNumber; }
void client::print() {
    cout << "Name: " << getName() << "\nAddress: " << getAddress() << "\nPhone: " << getPhoneNumber() << "\n";
}


BankingApplication::BankingApplication() {
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

BankingApplication::~BankingApplication() {
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


SavingsBankAccount::SavingsBankAccount(double balance, double minimumBalance) {
    this->minimumBalance = minimumBalance;
    if (balance < minimumBalance) {
        cout << "The Entered balance is less than minimum balance.." << endl;
        cout << "Therefore, balance has been seted to minimum balance." << endl;
        this->setBalance(minimumBalance);
    }
    else {
        this->setBalance(balance);
    }
}
int SavingsBankAccount::withdraw(double amount) {
    if (amount > getBalance()) {
        return 0;
    }
    else if (getBalance() - amount < minimumBalance) {
        return 0;
    }
    else {
        setBalance(getBalance() - amount);
        return 1;
    }
}
int SavingsBankAccount::deposit(double amount) {
    if (amount < 100) {
        return 0;
    }
    else {
        setBalance(getBalance() + amount);
        return 1;
    }
}

void BankingApplication::fillData() {
    fstream file;
    file.open("data.txt", ios::in);
    if (file.fail()) {
        file.close();
        file.open("data.txt", ios::out);
        file.close();
    }
    else {
        string type;
        while (getline(file, type)) {
            string name, addr, phone;
            getline(file, name);
            getline(file, addr);
            getline(file, phone);
            client* cl = new client(name, addr, phone);
            if (type == "1") {
                cl->setAccountType("Basic");
                double balance;
                string id;
                getline(file, id);
                file >> balance;
                BankAccount* b = new BankAccount(balance);
                b->setID(id);
                dataBasic[id] = { cl,b };
            }
            else if (type == "2") {
                cl->setAccountType("Saving");
                double balance, minimumb;
                string id;
                getline(file, id);
                file >> balance;
                file >> minimumb;
                SavingsBankAccount* s = new SavingsBankAccount(balance, minimumb);
                s->setID(id);
                dataSaving[id] = { cl,s };
            }
            string line;
            getline(file, line);
        }
    }
}
void BankingApplication::storeData() {
    //name address phone type (1) ID balance//type (2) ID balance Minimum balance
    fstream file;
    file.open("data.txt", ios::out);
    for (auto it = dataBasic.begin(); it != dataBasic.end(); it++) {
        file << "1\n" << it->second.first->getName() << "\n" << it->second.first->getAddress() << "\n";
        file << it->second.first->getPhoneNumber() << "\n" << it->first << "\n" << it->second.second->getBalance() << "\n";
    }
    for (auto it = dataSaving.begin(); it != dataSaving.end(); it++) {
        file << "2\n" << it->second.first->getName() << "\n" << it->second.first->getAddress() << "\n";
        file << it->second.first->getPhoneNumber() << "\n" << it->first << "\n" << it->second.second->getBalance() << "\n";
        file << it->second.second->getMinimumBalance() << "\n";
    }
}
void BankingApplication::newAccount() {
    string name, address, phone;
    cout << "\nPlease Enter Client Name =========>  ";
    cin.ignore();
    getline(cin, name, '\n');
    cout << "\nPlease Enter Client Address =======>  ";
    getline(cin, address);
    cout << "\nPlease Enter Client Phone =======>  ";
    getline(cin, phone, '\n');
    client* newclient = new client(name, address, phone);
    int accounttype;
    cout << "What Type of Account Do You Like? (1) Basic (2) Saving? Type 1 or 2 =========> ";
    cin >> accounttype;
    cout << endl;
    if (accounttype == 1) {
        double b;
        cout << "Please Enter the Starting Balance =========> ";
        cin.ignore();
        cin >> b;
        BankAccount* bank = new BankAccount(b);
        newclient->setAccountType("Basic");
        dataBasic[bank->getAccountID()] = { newclient , bank };
        cout << "An account was created with ID ";
        cout << bank->getAccountID() << " and Starting Balance " << bank->getBalance() << " L.E. ";
    }
    else if (accounttype == 2) {
        double b, minb;
        cout << "Please Enter Initial balance should be >= min balance =======> ";
        cin >> b;
        cout << "Please Enter minimum balance<= Initial balance =======> ";
        cin >> minb;
        SavingsBankAccount* account = new SavingsBankAccount(b, minb);
        newclient->setAccountType("Saving");
        dataSaving[account->getAccountID()] = { newclient , account };
        cout << "An account was created with ID ";
        cout << account->getAccountID() << " and Initial balance " << account->getBalance();
        cout << " L.E. " << "and minimum balance " << account->getMinimumBalance() << " L.E. \n";
    }
}
void BankingApplication::ListClientsAccounts() {
    for (auto it = dataBasic.begin(); it != dataBasic.end(); it++) {
        string dash(20, '-');
        cout << dash << "\n";
        it->second.first->print();
        cout << "Account ID: " << it->second.second->getAccountID() << " (Basic)\nBalance: " << it->second.second->getBalance();
        cout << "\n" << dash << "\n";
    }
    for (auto it = dataSaving.begin(); it != dataSaving.end(); it++) {
        string dash(20, '-');
        cout << dash << "\n";
        it->second.first->print();
        cout << "Account ID: " << it->second.second->getAccountID() << " (Saving)\nInitial balance: " << it->second.second->getBalance();
        cout << "\nMinimum Balance: " << it->second.second->getMinimumBalance();
        cout << "\n" << dash << "\n";
    }
}
void BankingApplication::WithdrawMoney() {
    string id;
    cout << "Please Enter Account ID (e.g., FCAI-015) =========> ";
    cin.ignore();
    cin >> id;
    int flag = 0;
    for (auto it = dataBasic.begin(); it != dataBasic.end(); it++) {
        if (it->first == id) {
            flag = 1;
            dataBasic[id].second->print();
            double withdr;
            cout << "Please Enter The Amount to Withdraw =========> ";
            cin >> withdr;
            while (!dataBasic[id].second->withdraw(withdr)) {
                cout << "Sorry.This is more than what you can withdraw.\n";
                cout << "Please Enter The Amount to Withdraw =========> ";
                cin.ignore();
                cin >> withdr;
            }
            cout << "Account ID: " << dataBasic[id].second->getAccountID();
            cout << "\nNew Balance: " << dataBasic[id].second->getBalance() << "\n";
        }
    }
    for (auto it = dataSaving.begin(); it != dataSaving.end(); it++) {
        cout << "Withdrow saving\n";
        if (it->first == id) {
            flag = 1;
            dataSaving[id].second->printall();
            double withdr;
            cout << "Please Enter The Amount to Withdraw =========> ";
            cin >> withdr;
            while (!dataSaving[id].second->withdraw(withdr)) {
                cout << "Sorry.This is more than what you can withdraw.\n";
                cout << "Please Enter The Amount to Withdraw =========> ";
                cin.ignore();
                cin >> withdr;
            }
            cout << "Account ID: " << dataSaving[id].second->getAccountID();
            cout << "\nNew Balance: " << dataSaving[id].second->getBalance() << "\n";
        }
    }
    if (!flag) {
        cout << "There is no account with this ID\n";
        exit(1);
    }
}
void BankingApplication::DepositMoney() {
    string id;
    cout << "Please Enter Account ID (e.g., FCAI-015) =========> "; cin.ignore();
    cin >> id;
    int flag = 0;
    for (auto it = dataBasic.begin(); it != dataBasic.end(); it++) {
        if (it->first == id) {
            flag = 1;
            dataBasic[id].second->print();
            double deposit;
            cout << "Please Enter The Amount to Deposit =========> ";
            cin >> deposit;
            while (!dataBasic[id].second->deposit(deposit)) {
                cout << "Sorry.This is less than what you can Deposit.\n";
                cout << "Please Enter The Amount to Deposit =========> ";
                cin >> deposit;
            }
            cout << "Account ID: " << dataBasic[id].second->getAccountID();
            cout << "\nNew Balance: " << dataBasic[id].second->getBalance() << "\n";
        }
    }
    for (auto it = dataSaving.begin(); it != dataSaving.end(); it++) {
        if (it->first == id) {
            flag = 1;
            dataSaving[id].second->printall();
            double deposit;
            cout << "Please Enter The Amount to Withdraw =========> ";
            cin >> deposit;
            while (!dataSaving[id].second->deposit(deposit)) {
                cout << "Sorry.This is less than what you can Deposit.\n";
                cout << "Please Enter The Amount to Deposit =========> ";
                cin >> deposit;
            }
            cout << "Account ID: " << dataSaving[id].second->getAccountID();
            cout << "\nNew Balance: " << dataSaving[id].second->getBalance() << "\nMinimum Balance: " << dataSaving[id].second->getBalance() << "\n";
        }
    }
    if (!flag) {
        cout << "There is no account with this ID\n";
        exit(1);
    }
}

