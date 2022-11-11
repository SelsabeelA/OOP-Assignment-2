#include"Bank System.h"

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
    cout << "Please Enter Client Name =========>  ";
    cin.ignore();
    getline(cin, name, '\n');
    cout << "Please Enter Client Address =======>  ";
    getline(cin, address);
    cout << "Please Enter Client Phone =======>  ";
    getline(cin, phone, '\n');
    client* newclient = new client(name, address, phone);
    int accounttype;
    cout << "What Type of Account Do You Like? (1) Basic (2) Saving – Type 1 or 2 =========> ";
    cin >> accounttype;
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


