//
// Created by mrozi on 5/18/2024.
//
#include<iostream>
#include<string.h>

using namespace std;

class BadInputException : public exception {
public:
    char *show() {
        return (char *) "Greshna opisna ocenka";
    }
};

class StudentKurs {
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;
    static int MAX;
public:
    StudentKurs(char *ime, int finalenIspit) {
        strcpy(this->ime, ime);
        this->ocenka = finalenIspit;
        this->daliUsno = false;
    }

    //дополни ја класата
    static void setMAX(int m) {
        MAX = m;
    }

    virtual bool getDaliUsno() {
        return daliUsno;
    }

    virtual int Ocenka() {
        return ocenka;
    }

    friend ostream &operator<<(ostream &os, StudentKurs &kurs) {
        //Ime --- ocenka
        os << kurs.ime << " --- " << kurs.Ocenka() << endl;
        return os;
    }

    virtual char *getName() {
        return ime;
    }

    friend class KursFakultet;
};

int StudentKurs::MAX = 10;

//вметни го кодот за StudentKursUsno
class StudentKursUsno : public StudentKurs {
    char *dopolnitelni;
public:
    StudentKursUsno(char *ime = "Darko", int finalenIspit = 8, char *dopolnitelni = "dobar") : StudentKurs(ime,
                                                                                                           finalenIspit) {
        this->daliUsno = true;
        this->dopolnitelni = new char[strlen(dopolnitelni) + 1];
        strcpy(this->dopolnitelni, dopolnitelni);
    }

    bool getDaliUsno() {
        return daliUsno;
    }

    int Ocenka() {
        if (strcmp(dopolnitelni, "odlicen") == 0) {
            if ((ocenka + 2) >= 10) {
                return ocenka;
            } else {
                return ocenka + 2;
            }
        } else if (strcmp(dopolnitelni, "dobro") == 0) {
            if ((ocenka + 1) >= 10) {
                return ocenka;
            } else {
                return (ocenka + 1);
            }
        } else if (strcmp(dopolnitelni, "losho") == 0) {
            return ocenka - 1;
        } else {
            return ocenka;
        }
    }

    char *getName() {
        return ime;
    }

    StudentKursUsno &operator+=(const char *dopolnitelna) {
        int flag = 0, j = 0;
        char *novaocenka = new char[strlen(dopolnitelna) + 1];
        for (int i = 0; i < strlen(dopolnitelna); ++i) {
            if (isalpha(dopolnitelna[i]) == false) {
                flag++;
                continue;
            }
            novaocenka[j++] = dopolnitelna[i];
        }
        novaocenka[j] = NULL;
        delete[] dopolnitelni;
        dopolnitelni = new char[strlen(novaocenka) + 1];
        strcpy(dopolnitelni, novaocenka);
        delete[] novaocenka;
        if (flag) {
            throw BadInputException();
        }
    }

    friend class KursFakultet;
};

class KursFakultet {
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs **studenti, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()) {
                this->studenti[i] = new StudentKursUsno(*dynamic_cast<StudentKursUsno *>(studenti[i]));
            } else this->studenti[i] = new StudentKurs(*studenti[i]);
        }
        this->broj = broj;
    }

    ~KursFakultet() {
        for (int i = 0; i < broj; i++) delete studenti[i];
    }

    void postaviOpisnaOcenka(char *name, char *dopolnitelna) {
        for (int i = 0; i < broj; ++i) {
            if (strcmp(studenti[i]->getName(), name) == 0) {
                StudentKursUsno *darko = dynamic_cast<StudentKursUsno *>(studenti[i]);
                if (darko != NULL) {
                    try {
                        *darko += dopolnitelna;
                    } catch (BadInputException &e) {
                        cout << e.show() << endl;
                    }
                }
            }
        }
    }

    void pecatiStudenti() {
        cout << "Kursot OOP go polozile:" << endl;
        for (int i = 0; i < broj; ++i) {
            if (studenti[i]->Ocenka() >= 6) {
                cout << *studenti[i];
            }
        }
    }
};

int main() {

    StudentKurs **niza;
    int n, m, ocenka;
    char ime[30], opisna[10];
    bool daliUsno;
    cin >> n;
    niza = new StudentKurs *[n];
    for (int i = 0; i < n; i++) {
        cin >> ime;
        cin >> ocenka;
        cin >> daliUsno;
        if (!daliUsno)
            niza[i] = new StudentKurs(ime, ocenka);
        else
            niza[i] = new StudentKursUsno(ime, ocenka);
    }

    KursFakultet programiranje("OOP", niza, n);
    for (int i = 0; i < n; i++) delete niza[i];
    delete[] niza;
    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> ime >> opisna;
        programiranje.postaviOpisnaOcenka(ime, opisna);
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}