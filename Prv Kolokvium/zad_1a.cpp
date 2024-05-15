//#include<iostream>
//#include<cstring>
//
//using namespace std;
//
//class HotelReservation {
//protected:
//    int denovi;
//    int broj_lica;
//    string ime;
//    string prezime;
//
//public:
//    HotelReservation(string ime, string prezime, int denovi, int broj_lica) {
//        this->ime = ime;
//        this->prezime = prezime;
//        this->denovi = denovi;
//        this->broj_lica = broj_lica;
//    }
//
//    virtual int price() {
//        return denovi * broj_lica * 25;
//    }
//
//    virtual int price(int amount) {
//        if (amount >= price())
//            return amount - price();
//        else {
//            cout << "Za vashata rezervacija treba da naplatite " << price() << endl;
//            return -1;
//        }
//    }
//};
//
//
//class HalfBoardHotelReservation : public HotelReservation {
//public:
//    HalfBoardHotelReservation(string ime, string prezime, int denovi, int
//    broj_lica) : HotelReservation(ime, prezime, denovi, broj_lica) {}
//
//    //препокривање на price(int amount)
//    int price(int amount) {
//        int cena = HotelReservation::price() + broj_lica * 5; // пристап до protected податокот broj_lica
//        if (amount >= cena)
//            return amount - cena;
//        else {
//            cout << "Za vashata rezervacija treba da naplatite " << cena << endl;
//            return -1;
//        }
//    }
//};
//
//class Hotel {
//private:
//    string ime;
//    int saldo;
//public:
//    Hotel(string ime) {
//        this->ime = ime;
//        saldo = 0;
//    }
//
//    // референца кон основната класа може да референцира објекти и кон изведените класи
//    int pay(HotelReservation &hr, int uplata) {
//        int kusur = hr.price(uplata); //полиморфизам
//        // која дефиниција на price ќе се повика?
//        // важно: vrtiCena е виртуелна функција
//        if (kusur != -1)
//            saldo += uplata - kusur;
//        return kusur;
//    }
//};
//
//int main() {
//
//    Hotel h("Bristol");
//    HotelReservation *hr1 = new HotelReservation("Petko", "Petkovski", 5, 5);
//    int cena = h.pay(*hr1, 1000);
//    if (cena != -1)
//        cout << "Kusur : " << cena << endl;
//    HalfBoardHotelReservation *hr2 =
//            new HalfBoardHotelReservation("Risto", "Ristovski", 5, 5);
//    cena = h.pay(*hr2, 1000);
//    if (cena != -1)
//        cout << "Kusur : " << cena << endl;
//    //покажувач кон основна класа покажува кон објект од изведена
//    HotelReservation *hr3 = new HalfBoardHotelReservation("Ana", "Anovska", 4, 2);
//    cena = h.pay(*hr3, 100);
//    if (cena != -1)
//        cout << "Kusur : " << cena << endl;
//    HalfBoardHotelReservation hr4("Tome", "Tomovski", 5, 3);
//    cena = h.pay(hr4, 1000);
//    if (cena != -1)
//        cout << "Kusur : " << cena << endl;
//}
#include <iostream>
#include <cstring>

using namespace std;

class Employee {
protected:
    char name[50];
    int age;

public:
    Employee(const char* empName, int empAge) : age(empAge) {
        strncpy(name, empName, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }

    virtual void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }

    virtual ~Employee() {} // Виртуелен деструктор
};

class Payable {
protected:
    double salary;

public:
    Payable(double pay) : salary(pay) {}

    virtual double calculateSalary() const = 0;

    virtual ~Payable() {} // Виртуелен деструктор

    virtual void displayInfo() const = 0; // Make displayInfo() a pure virtual function
};

class Developer : public Employee, public Payable {
private:
    char programmingLanguage[50];

public:
    Developer(const char* empName, int empAge, double empSalary, const char* lang)
            : Employee(empName, empAge), Payable(empSalary) {
        strncpy(programmingLanguage, lang, sizeof(programmingLanguage) - 1);
        programmingLanguage[sizeof(programmingLanguage) - 1] = '\0';
    }

    void displayInfo() const override {
        Employee::displayInfo();
        cout << "Programming Language: " << programmingLanguage << endl;
        cout << "Salary: " << calculateSalary() << endl;
    }

    double calculateSalary() const override {
        return salary * 0.90; // Salary after 10% tax deduction
    }

    ~Developer() override {} // Виртуелен деструктор
};

class Manager : public Employee, public Payable {
private:
    int numberOfDepartments;

public:
    Manager(const char* empName, int empAge, double empSalary, int departments)
            : Employee(empName, empAge), Payable(empSalary), numberOfDepartments(departments) {}

    void displayInfo() const override {
        Employee::displayInfo();
        cout << "Number of Departments: " << numberOfDepartments << endl;
        cout << "Salary: " << calculateSalary() << endl;
    }

    double calculateSalary() const override {
        return salary * (1.0 + (0.05 * numberOfDepartments)); // Salary plus 5% bonus per department
    }

    ~Manager() override {} // Виртуелен деструктор
};

double biggestSalary(Payable* payable[], int n) {
    double maxSalary = payable[0]->calculateSalary();
    for (int i = 1; i < n; ++i) {
        double salary = payable[i]->calculateSalary();
        if (salary > maxSalary) {
            maxSalary = salary;
        }
    }
    return maxSalary;
}

int main() {
    Payable* payable[5];
    for (int i = 0; i < 5; ++i) {
        char name[50];
        int age;
        double salary;
        cin >> name >> age >> salary;
        if (i % 2 == 0) {
            char programmingLanguage[50];
            cin >> programmingLanguage;
            payable[i] = new Developer(name, age, salary, programmingLanguage);
        } else {
            int numberOfDepartments;
            cin >> numberOfDepartments;
            payable[i] = new Manager(name, age, salary, numberOfDepartments);
        }
        payable[i]->displayInfo();
    }
    cout << "Biggest Salary: " << biggestSalary(payable, 5) << endl;

    // Ослободување на меморија
    for (int i = 0; i < 5; ++i) {
        delete payable[i];
    }

    return 0;
}
