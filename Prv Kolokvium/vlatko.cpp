//
// Created by mrozi on 4/3/2024.
//
#include <iostream>
#include <cstring>

using namespace std;

class DeleveryPerson {
private:
    char id[5];
    char *ime;
    int dostavi;
    int region;
public:
    DeleveryPerson(char *id = "", int dostava = 0, int region = 0, char *ime = "") {
        strcpy(this->id, id);
        this->ime = new char[strlen(ime) + 1];//dolzina na ime "ne znaeme kolkava e"
        strcpy(this->ime, ime);
        this->region = region;
        dostava = 0;
    }

    DeleveryPerson(const DeleveryPerson &p) {
        strcpy(this->id, p.id);
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, p.ime);
        this->region = p.region;
        dostavi = p.dostavi;

    }

    //proveruvame dali se isti
    DeleveryPerson &operator=(const DeleveryPerson &p) {
        if (this != &p)//adresa na objektot se razlicni toa znaci deka se isti, dodkolku se isti
        {
            delete[]ime;
            //kopirame cpry constructor
            strcpy(this->id, p.id);
            this->ime = new char[strlen(ime) + 1];
            strcpy(this->ime, p.ime);
            this->region = p.region;
            dostavi = p.dostavi;
        }
        return *this;
    }

    ~DeleveryPerson() {
        delete[]ime;
    }

    void print() {
        cout << "ID: " << id << "Name: " << ime << " Current location: " << region << "# of deliveres: " << dostavi
             << endl;
    }

    friend ostream &operator<<(ostream &o, DeleveryPerson &p) {
        o << "ID: " << p.id << "Name: " << p.ime << " Current location: " << p.region << "# of deliveres: " << p.dostavi
          << endl;
    }

    const char *getId() {
        return id;
    }

};


class DeleveryApp {
private:
    char ime[20];
    DeleveryPerson *niza;
    int n;
public:
    DeleveryApp(char *ime) {
        strcpy(this->ime, ime);
        n = 0;
        niza = new DeleveryPerson[n];
    }

    //copy
    DeleveryApp(const DeleveryApp &a) {
        strcpy(this->ime, a.ime);
        n = a.n;
        niza = new DeleveryPerson[n];
        for (int i = 0; i < n; ++i) {
            niza[i] = a.niza[i];
        }
    }

    DeleveryApp &operator=(const DeleveryApp &a) {
        if (this != &a) {
            delete[]niza;
            strcpy(this->ime, a.ime);
            n = a.n;
            niza = new DeleveryPerson[n];
            for (int i = 0; i < n; ++i) {
                niza[i] = a.niza[i];
            }
        }
    }

    void addDeleveryPerson(DeleveryPerson &person) {
        for (int i = 0; i < n; ++i) {
            if (strcmp(niza[i].getId() == person.getId()) == 0) {//popravi strcmp
                return;
            }
        }
    }
};

int main() {

}
//1.kompozicija, citame argumenti
//2.poteska od dinamicka alokacija i operatori
//3.gledame sto iameme vo main i toa stavame vo constructor