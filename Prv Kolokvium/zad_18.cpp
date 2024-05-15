#include<iostream>
#include<cstring>

using namespace std;

enum Tip {//GLEDAME VO KONSTRUKTOROT KAKO E IMETO NA enum I TAKA GO IMENUVAME
    LINUX, UNIX, WINDOWS
};

class OperativenSistem {
private:
    char *imeOP;//dinamicka alocokacija
    float version;
    Tip osType;
    float goleminaGB;

    void copy(const OperativenSistem &other) {
        this->imeOP = new char[strlen(other.imeOP) + 1];
        strcpy(this->imeOP, other.imeOP);
        this->version = other.version;
        this->osType = other.osType;
        this->goleminaGB = other.goleminaGB;
    }

public:
    //constructor,copy, operator=

    //constructor
    OperativenSistem(char *imeOP = "", float version = 0, Tip osType = WINDOWS,
                     float goleminaGB = 0) {
        this->imeOP = new char[strlen(imeOP) + 1];
        strcpy(this->imeOP, imeOP);
        this->version = version;
        this->osType = osType;
        this->goleminaGB = goleminaGB;
    }

    //copy
    OperativenSistem(const OperativenSistem &other) {
//        delete[]imeOP;//GRESKA VO KORACI VO COPY NEMAME BRISENJE NA DINAMICKA MEMORIJA
        copy(other);
    }

    //operator=
    OperativenSistem &operator=(const OperativenSistem &other) {
        if (this != &other) {
            delete[]imeOP;
            copy(other);
        }
        return *this;
    }

    //destructor
    ~OperativenSistem() {
        delete[]imeOP;
    }

    int sporediVerzija(const OperativenSistem &os) {
        if (version == os.version) {
            return 0;
        } else if (version < os.version) {
            return -1;
        } else {
            return 1;
        }
    }

    bool ednakviSe(const OperativenSistem &os) {
        return (strcmp(imeOP, os.imeOP)==0 && (version == os.version) && (osType == os.osType) &&
                (goleminaGB == os.goleminaGB));
    }

    void pecati() {
        cout << "Ime: " << imeOP << " Verzija: " << version << " Tip: " << osType << " Golemina:" << goleminaGB << "GB"
             << endl;
    }

    bool istaFamilija(const OperativenSistem &sporedba) {
        return !strcmp(imeOP, sporedba.imeOP) && (osType == sporedba.osType);
    }
};

class Repozitorium {
private:
    char name[21];
    OperativenSistem *repoName;
    int brojOS;

    //copy
    void copy(const Repozitorium &r) {
        strcpy(this->name, r.name);
        this->repoName = new OperativenSistem[r.brojOS];
        for (int i = 0; i < brojOS; ++i) {
            this->repoName[i] = r.repoName[i];
        }
        this->brojOS = r.brojOS;
    }

public:
    //constructor, copy, operator=

    //KOGA IMAME DIMAICKA ALOKACIJA NA KOMPOZICIJA SEKOGAS SE STAVA "NULLPTR"!!!!
    Repozitorium(char *name = "", OperativenSistem *repoName = nullptr, int brojOS = 0) {
        strcpy(this->name, name);
        this->repoName = repoName;
        this->brojOS = brojOS;
    }

    //copy
    Repozitorium(const Repozitorium &other) {
        copy(other);
    }


    //operator=
    Repozitorium &operator=(const Repozitorium &r) {
        if (this != &r) {
            delete[]repoName;
            copy(r);
        }
    }

    void pecatiOperativniSistemi() {
        cout << "Repozitorium: " << name << endl;
        for (int i = 0; i < brojOS; ++i) {
            repoName[i].pecati();
        }

    }


    void izbrishi(const OperativenSistem &operativenSistem) {
        int flag = -1;
        for (int i = 0; i < brojOS; ++i) {
            if (repoName[i].ednakviSe(operativenSistem)) {
                flag = i;
                break;
            }
        }
        if (flag == -1) {
            return;
        } else {
            for (int i = flag; i < brojOS - 1; ++i) {
                repoName[i] = repoName[i + 1];
            }
            brojOS--;
        }
    }


    void dodadi(const OperativenSistem &nov) {
        int flag = 0;
        for (int i = 0; i < brojOS; ++i) {
            if (repoName[i].istaFamilija(nov)) {
                if (repoName[i].sporediVerzija(nov) == -1) {
                    repoName[i] = nov;
                    return;
                }
            }
        }
        OperativenSistem *temp = new OperativenSistem[brojOS + 1];
        for (int i = 0; i < brojOS; ++i) {
            temp[i] = repoName[i];
        }
        temp[brojOS++] = nov;
        delete[]repoName;
        this->repoName = new OperativenSistem[brojOS];
        for (int i = 0; i < brojOS; ++i) {
            this->repoName[i] = temp[i];
        }
        delete[]temp;
    }

};


int main() {
    char repoName[20];
    cin >> repoName;
    Repozitorium repozitorium = Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin >> brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i < brojOperativniSistemi; i++) {
        cin >> ime;
        cin >> verzija;
        cin >> tip;
        cin >> golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip) tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin >> ime;
    cin >> verzija;
    cin >> tip;
    cin >> golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip) tip, golemina);
    cout << "=====Brishenje na operativen sistem=====" << endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}