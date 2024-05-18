//
// Created by mrozi on 5/18/2024.
//
#include <iostream>
#include <cstring>

#define MAX 100
using namespace std;


class UserExistsException {
protected:
    char Message[100];
public:
    UserExistsException() {
        strcpy(Message, "The user already exists in the list!");
    }

    void message() {
        cout << Message << endl;
    }
};

enum typeC {
    standard, // 0
    loyal, // 1
    vip // 2
};

class Customer {
protected:
    char NameCutomer[50];
    char Email[50];
    typeC Version;
    int Discount;
    static int AdditinalDisount;
    int NumBought;
public:
    //argumetns         Customer c(name, email, (typeC) tC, numProducts);
    Customer(char *NameSuctomer = (char *) "Kiro", char *Email = (char *) "Belsko maalo", typeC Version = standard,
             int NumBought = 0) {
        strcpy(this->NameCutomer, NameSuctomer);
        strcpy(this->Email, Email);
        this->Version = Version;
        this->NumBought = NumBought;
        this->Discount = 10;
    }

    //opeataro <<
    friend ostream &operator<<(ostream &out, Customer &other) {
        out << other.NameCutomer << endl;
        out << other.Email << endl;
        out << other.NumBought << endl;
        if (other.Version == 0)
            out << "standard 0" << endl;
        else if (other.Version == 1)
            out << "loyal " << other.Discount << endl;
        else
            out << "vip " << other.Discount + AdditinalDisount << endl;
        return out;
    }

    //set
    void setDiscount1(int change) {
        this->Discount = change;
    }

    //get
    char *getEmail() {
        return Email;
    }

    friend class FINKI_bookstore;
};

int Customer::AdditinalDisount = 20;

class FINKI_bookstore {
protected:
    Customer *RegisteredCustomers;
    int NumCustomers;
public:
    //argumetns
    FINKI_bookstore() {
        RegisteredCustomers = nullptr;
        NumCustomers = 0;
    }

    void setCustomers(Customer *NewCustomers, int N) {
        RegisteredCustomers = new Customer[N];
        for (int i = 0; i < N; i++) {
            RegisteredCustomers[i] = NewCustomers[i];
        }
        NumCustomers = N;
    }

    //opeator <<
    friend ostream &operator<<(ostream &out, FINKI_bookstore &other) {
        for (int i = 0; i < other.NumCustomers; i++) {
            out << other.RegisteredCustomers[i];
        }
        return out;
    }

    //operator +=
    FINKI_bookstore &operator+=(Customer &NewCutomer) {
        for (int i = 0; i < NumCustomers; i++) {
            if (!strcmp(RegisteredCustomers[i].getEmail(), NewCutomer.getEmail()))
                throw UserExistsException();
        }
        Customer *NewThing = new Customer[NumCustomers + 1];
        for (int i = 0; i < NumCustomers; i++) {
            NewThing[i] = RegisteredCustomers[i];
        }
        NewThing[NumCustomers++] = NewCutomer;
        delete[] RegisteredCustomers;
        RegisteredCustomers = NewThing;
        return *this;
    }

    //update
    void update() {
        for (int i = 0; i < NumCustomers; i++) {
            if (RegisteredCustomers[i].Version == 0) {
                if (RegisteredCustomers[i].NumBought > 5)
                    RegisteredCustomers[i].Version = (typeC) 1;
            } else if (RegisteredCustomers[i].Version == 1) {
                if (RegisteredCustomers[i].NumBought > 10)
                    RegisteredCustomers[i].Version = (typeC) 2;
            }
        }
    }

    friend class Customer;
};

int main() {
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1) {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2) {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3) {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc << endl;
    }

    if (testCase == 4) {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try {
            fc += c;
        } catch (UserExistsException &e) {
            e.message();
        }

        cout << fc;
    }

    if (testCase == 5) {
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try {
            fc += c;
        } catch (UserExistsException &e) {
            e.message();
        }

        cout << fc;
    }

    if (testCase == 6) {
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}