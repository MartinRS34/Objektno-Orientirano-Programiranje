//
// Created by mrozi on 4/3/2024.
//
#include <iostream>
#include <cstring>

using namespace std;
enum tip {
    pop, rap, rok//0->pop,1->rap,2->rok
};

class Pesna {
private:
    char *ime;
    int minuti;
    tip tips;
public:
    //constructor
    Pesna(char *ime = "Martin", int minuti = 0, tip tips = pop) {
//        this->nums = new int[0]; za intiger
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->minuti = minuti;
        this->tips = tips;
    }

    ~Pesna() {
        delete[]ime;
    }

    char *getIme() {
        return ime;
    }

    tip getTips() {
        return tips;
    }

    int getMinuti() const {
        return minuti;
    }

    //copy constructor
    Pesna(const Pesna &p) {
        this->ime = new char[strlen(p.ime) + 1];
        strcpy(this->ime, p.ime);
        this->minuti = p.minuti;
        this->tips = p.tips;
    }

    Pesna &operator=(const Pesna &p) {
        if (this != &p) {
            delete[]ime;
            ime = new char[strlen(ime) + 1];
            strcpy(this->ime, p.ime);
            this->minuti = p.minuti;
            this->tips = p.tips;
        }
    }

    void pecati() {
        //"Happy"-5min
        cout << "\"" << ime << "\"-" << minuti << "min" << endl;
    }
};

class CD {
    Pesna songs[11];
    int count;
    int maxDuration;

public:
    CD(int maxDuration) {
        this->maxDuration = maxDuration;
        this->count = 0;
    }

    CD(const CD &p) {
        this->maxDuration = p.maxDuration;
        this->count = p.count;
        for (int i = 0; i < p.count; ++i) {
            this->songs[i] = p.songs[i];
        }
    }

    void dodadiPesna(Pesna pesna) {
        //maxDuration=20
        int sum = 0;
        if (count < 9) {
            for (int i = 0; i < count; ++i) {
                sum += songs[i].getMinuti();
            }
            if (sum + pesna.getMinuti() < maxDuration) {
                songs[count++] = pesna;
            }
        }
    }

    Pesna getPesna(int i) {
        return songs[i];
    }

    void pecatiPesniPoTip(tip t) {
        //pop,rap,rock
        //"Layla"-2min
        for (int i = 0; i < count; ++i) {
            switch (songs[i].getTips()==t) {
                case 1:
                    cout << "\"" << songs[i].getIme() << "\"-" << songs[i].getMinuti() << "min" << endl;
                    break;
                case 2:
                    cout << "\"" << songs[i].getIme() << "\"-" << songs[i].getMinuti() << "min" << endl;
                    break;
                case 3:
                    cout << "\"" << songs[i].getIme() << "\"-" << songs[i].getMinuti() << "min" << endl;
                    break;
            }
        }
    }

    int getBroj() {
        return count;
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime, minuti, (tip) kojtip);
        p.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);

            omileno.dodadiPesna(p);
        }
        for (int i = 0; i < n; i++)
            (omileno.getPesna(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        cin >> kojtip;
        omileno.pecatiPesniPoTip((tip) kojtip);

    }else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        cin >> kojtip;
        omileno.pecatiPesniPoTip((tip) kojtip);

    }

    return 0;
}