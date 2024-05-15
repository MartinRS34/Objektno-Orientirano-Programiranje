//
// Created by mrozi on 4/7/2024.
//
#include <iostream>
#include <cstring>

using namespace std;

class Pica {
private:
    char pica[16];
    int cena;
    char *sostojki;
    int popust;

    //copy constructor
    void copy(const Pica &p) {
        strcpy(this->pica, p.pica);
        this->cena = p.cena;
        this->sostojki = new char[strlen(p.sostojki) + 1];
        strcpy(this->sostojki, p.sostojki);
        this->popust = p.popust;
    }

public:
    //constructor,copy,operator=

    //constructor 2in1
    Pica(char *pica = "Problem constructor", int cena = 250, char *sostojki = "asdf", int popust = 0) {
        strcpy(this->pica, pica);
        this->cena = cena;
        this->sostojki = new char[strlen(sostojki) + 1];
        strcpy(this->sostojki, sostojki);
        this->popust = popust;
    }

    //operator=
    Pica &operator=(const Pica &p) {
        if (this != &p) {
            delete[] sostojki;
            copy(p);
        }
        return *this;
    }

    //destructor
    ~Pica() {
        delete[] sostojki;
    }

    //popust,ime na pica, cena, sostojki
    void pecati() {
        cout << popust << endl << pica << endl << cena << sostojki << endl;
    }

    bool istiSe(Pica p) {
        return strcmp(pica, p.pica) == 0;
    }

    int getCena() {
        return cena;
    }

    int getPopust() {
        return popust;
    }
};

class Picerija {
private:
    char ime[16];
    Pica *pica;
    int countPica;
    int numEntered;

    //copy
    void copy(const Picerija &p) {
        this->numEntered = p.numEntered;
        strcpy(ime, p.ime);
        this->pica = new Pica[p.countPica];
        for (int i = 0; i < p.countPica; ++i) {
            this->pica[i] = p.pica[i];
        }
//        this->countPica = p.countPica;
    }

public:
    //constructor, copy, operator=

    //constructor
    Picerija(char *ime = "Default constructor Picerija") {
        strcpy(this->ime, ime);
        this->pica = new Pica[0];
//        this->countPica = countPica;
        this->numEntered = 0;
    }

    //operator=
    Picerija &operator=(const Picerija &p) {
        if (this != &p) {
            delete[] pica;
            copy(p);
        }
        return *this;
    }

    ~Picerija() {
        delete[]pica;
    }

    char *getIme() {
        return ime;
    }

    void setIme(char *ime) {
        strcpy(this->ime, ime);
    }


    //operator+=
    Picerija &operator+=(Pica &p) {

        for (int i = 0; i < numEntered; i++) {
            if (p.istiSe(pica[i])) {
                return *this;
            }
        }

        Pica *tmp = new Pica[numEntered + 1];
        for (int i = 0; i < numEntered; ++i) {
            tmp[i] = pica[i];
        }

        tmp[countPica++] = p;
        delete[]pica;
        pica = tmp;

        return *this;

    }

    void piciNaPromocija() {
        for (int i = 0; i < countPica; i++) {
            if (pica[i].getPopust() < 100) {
                pica[i].pecati();
                cout << " " << pica[i].getCena() * (1 - pica[i].getPopust() / 100.0) << endl;
            }
        }
    }
};

int main() {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++) {
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1 += p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2 += p;

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}
