//
// Created by mrozi on 5/18/2024.
//
#include <iostream>
#include <cstring>

using namespace std;

class Vozac {
protected:
    char Name[100];
    int Age;
    int NumRaces;
    bool IsVeteran;
public:
    //argukekts
    Vozac(char *Name = (char *) "", int Age = 0, int NumRaces = 0, bool IsVeteran = false) {
        strcpy(this->Name, Name);
        this->Age = Age;
        this->NumRaces = NumRaces;
        this->IsVeteran = IsVeteran;
    }

    //opeeatro<<
    friend ostream &operator<<(ostream &out, Vozac &other) {
        out << other.Name << endl << other.Age << endl << other.NumRaces << endl;
        if (other.IsVeteran)
            cout << "VETERAN" << endl;
        return out;
    }

    //operator ==
    bool operator==(Vozac &other) {
        if (this->Earnings() == other.Earnings())
            return true;
        else
            return false;
    }

    //earnings
    virtual float Earnings() = 0;

    virtual float danok() = 0;
};

class Avtomobilist : public Vozac {
protected:
    float CarPrice;
    float NewPrice;
public:
    //arguments
    Avtomobilist(char *Name = (char *) "", int Age = 0, int NumRaces = 0, bool IsVeteran = false, float CarPrice = 0.0)
            : Vozac(Name, Age, NumRaces, IsVeteran) {
        this->CarPrice = CarPrice;
        this->NewPrice = Avtomobilist::Earnings();
    }

    //moenyy
    float Earnings() {
        return CarPrice / 5;
    }

    //opeeatro<<
    friend ostream &operator<<(ostream &out, Avtomobilist &other) {
        out << other.Name << endl << other.Age << endl << other.NumRaces << endl;
        if (other.IsVeteran)
            cout << "VETERAN" << endl;
        cout << other.NewPrice << endl;
        return out;
    }

    //danok
    float danok() {
        if (NumRaces > 10)
            return Earnings() * 0.15;
        else
            return Earnings() * 0.10;
    }
};

class Motociklist : public Vozac {
protected:
    int HorsePower;
    float NewPrice;
public:
    //argumetns
    Motociklist(char *Name = (char *) "", int Age = 0, int NumRaces = 0, bool IsVeteran = false, int HorsePower = 0)
            : Vozac(Name, Age, NumRaces, IsVeteran) {
        this->HorsePower = HorsePower;
    }

    //moenyy
    float Earnings() {
        return HorsePower * 20;
    }

    //opeeatro<<
    friend ostream &operator<<(ostream &out, Motociklist &other) {
        out << other.Name << endl << other.Age << endl << other.NumRaces << endl;
        if (other.IsVeteran)
            cout << "VETERAN" << endl;
        cout << other.Earnings() << endl;
        return out;
    }

    //danok
    float danok() {
        if (IsVeteran)
            return Earnings() * 0.25;
        else
            return Earnings() * 0.20;
    }
};

int soIstaZarabotuvachka(Vozac **Drivers, int n, Vozac *other) {
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (Drivers[i]->Earnings() == other->Earnings())
            counter++;
    }
    return counter;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac *[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for (int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if (i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for (int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete[] v;
    delete vx;
    return 0;
}