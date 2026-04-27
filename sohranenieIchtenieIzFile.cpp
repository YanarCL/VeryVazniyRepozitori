#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class BankProduct {
protected:
    string clientName;
    double balance;
    int year;

public:
    BankProduct(string n = "", double b = 0, int y = 0)
        : clientName(n), balance(b), year(y) {
    }
    virtual ~BankProduct() {}
    virtual double pribil() const = 0;
    virtual void Print() const = 0;
    virtual void Read(ifstream& in) = 0;
    virtual void Save(ofstream& out) = 0;
};

class Deposit : public BankProduct {
public:
    Deposit(string n = "", double b = 0, int y = 0)
        : BankProduct(n, b, y) {
    }
    double pribil() const override {
        return balance * 0.05 * year;
    }
    void Print() const override {
        cout << "Deposit:\n";
        cout << "Client Name: " << clientName << endl;
        cout << "Balance: " << balance << endl;
        cout << "Years: " << year << endl;
    }
    void Read(ifstream& in) override {
        getline(in, clientName);
        in >> balance >> year;
        in.ignore(10000, '\n');
    }
    void Save(ofstream& out) override {
        out << "Deposit\n";
        out << "Name: " << clientName << endl;
        out << "Balance: " << balance << endl;
        out << "Years: " << year << endl;
    }
};

class Credit : public BankProduct {
public:
    Credit(string n = "", double b = 0, int y = 0)
        : BankProduct(n, b, y) {
    }
    double pribil() const override {
        return balance * 0.1 * year;
    }
    void Print() const override {
        cout << "Credit:\n";
        cout << "Client Name: " << clientName << endl;
        cout << "Balance: " << balance << endl;
        cout << "Years: " << year << endl;
    }
    void Read(ifstream& in) override {
        getline(in, clientName);
        in >> balance >> year;
        in.ignore(10000, '\n');
    }
    void Save(ofstream& out) override {
        out << "Credit\n";
        out << "Name: " << clientName << endl;
        out << "Balance: " << balance << endl;
        out << "Years: " << year << endl;
    }
};

class Investment : public BankProduct {
public:
    Investment(string n = "", double b = 0, int y = 0)
        : BankProduct(n, b, y) {
    }
    double pribil() const override {
        double bonus = (rand() % 6) / 100.0;
        return balance * (0.07 + bonus) * year;
    }
    void Print() const override {
        cout << "Investment:\n";
        cout << "Client Name: " << clientName << endl;
        cout << "Balance: " << balance << endl;
        cout << "Years: " << year << endl;
    }
    void Read(ifstream& in) override {
        getline(in, clientName);
        in >> balance >> year;
        in.ignore(10000, '\n');
    }
    void Save(ofstream& out) override {
        out << "Investment\n";
        out << "Name: " << clientName << endl;
        out << "Balance: " << balance << endl;
        out << "Years: " << year << endl;
    }
};

int main() {
    int total, choice;
    cout << "skok budet: ";
    cin >> total;
    while (total < 0  cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Uncorrect!!";
        cin >> total;
    }
    ifstream in("input.txt");
    ofstream out("output.txt");
    BankProduct** bank = new BankProduct * [total];
    cout << "chto dobavlyaem: ";
    for (int i = 0; i < total; i++) {
        cin >> choice;
        while (choice < 1  choice > 3) {
            cout << "Uncorrect!!";
            cin >> choice;
        }
        switch (choice) {
        case 1: bank[i] = new Deposit(); break;
        case 2: bank[i] = new Credit(); break;
        case 3: bank[i] = new Investment(); break;
        }
    }
    
    for (int i = 0; i < total; i++) {
        bank[i]->Read(in);
    }
    cout << "infa " << endl;
    for (int i = 0; i < total; i++) {
        bank[i]->Print();
        double m = bank[i]->pribil();
        cout << "Money: " << m << endl << endl;

        bank[i]->Save(out);
        out << "Money: " << m << endl;
    }
    for (int i = 0; i < total; i++) {
        delete bank[i];
    }
    delete[] bank;
}
