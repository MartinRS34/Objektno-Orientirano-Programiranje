//
// Created by mrozi on 4/7/2024.
//
#include <iostream>
#include <cstring>

using namespace std;

class Ucesnik {
private:
    char *ime;
    bool pol;
    int vozrast;

    void copy(const Ucesnik &u) {
        this->ime = new char[strlen(u.ime) + 1];
        strcpy(this->ime, u.ime);
        this->vozrast = u.vozrast;
        this->pol = u.pol;
    }

public:
    Ucesnik(char *ime = (char *) "fgvhb", bool pol = true, int vozrast = 1) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->pol = pol;
        this->vozrast = vozrast;
    }

    Ucesnik(const Ucesnik &u) {
        copy(u);
    }

    int getVozrast() const {
        return vozrast;
    }

    Ucesnik &operator=(const Ucesnik &other) {
        if (this != &other) {
            delete[] ime;
            copy(other);
        }
        return *this;
    }

    ~Ucesnik() {
        delete[] ime;
    }

    bool operator>(const Ucesnik &ucesnik) {
        return this->vozrast > ucesnik.vozrast;
    }

    friend ostream &operator<<(ostream &out, const Ucesnik &uu) {
        out << uu.ime << endl << (uu.pol ? "mashki" : "zhenski") << endl << uu.vozrast << endl;
        return out;
    }
};

class Maraton {
private:
    char lokacija[101];
    Ucesnik *ucesnik;
    int brojUcesnici;
    int numEntered;

    void copy(const Maraton &m) {
        this->numEntered = m.numEntered;
        strcpy(this->lokacija, m.lokacija);
        this->brojUcesnici = m.brojUcesnici;
        this->ucesnik = new Ucesnik[m.brojUcesnici];
        for (int i = 0; i < m.brojUcesnici; ++i) {
            this->ucesnik[i] = m.ucesnik[i];
        }
    }

public:
    Maraton(char *lokacija = "", int brojUcesnici = 0) {
        strcpy(this->lokacija, lokacija);
        this->ucesnik = new Ucesnik[brojUcesnici];
        this->brojUcesnici = brojUcesnici;
        this->numEntered = 0;
    }

    Maraton &operator=(const Maraton &m) {
        if (this != &m) {
            delete[] ucesnik;
            copy(m);
        }
        return *this;
    }

    ~Maraton() {
        delete[] ucesnik;
    }

    Maraton(const Maraton &m) {
        copy(m);
    }

    Maraton &operator+=(const Ucesnik &newUcenik) {
        if (numEntered > brojUcesnici) {
            return *this;
        }
        Ucesnik *tmp = new Ucesnik[numEntered + 1];
        for (int i = 0; i < numEntered; ++i) {
            tmp[i] = ucesnik[i];
        }
        tmp[numEntered++] = newUcenik;
        delete[] ucesnik;
        ucesnik = tmp;
        return *this;
    }

    float prosecnoVozrast() {
        int sum = 0;
        for (int i = 0; i < brojUcesnici; ++i) {
            sum += ucesnik[i].getVozrast();
        }
        return (float) (sum) / numEntered;
    }

    void pecatiPomladi(Ucesnik &u) {
        for (int i = 0; i < numEntered; ++i) {
            if (ucesnik[i].getVozrast() < u.getVozrast()) {
                cout << ucesnik[i];
            }
        }
    }

};

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija, n);
    Ucesnik **u = new Ucesnik *[n];
    for (int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for (int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete[] u;
    return 0;
}
