#include <iostream>
#include <cstring>

using namespace std;


class Gitara {
private:
    char seriski[26];
    float cena;
    int godina;
    char tip[41];
public:
    //constructor
    Gitara(char *tip, char *seriski, int godina, float cena) {
        strcpy(this->tip, tip);
        strcpy(this->seriski, seriski);
        this->godina = godina;
        this->cena = cena;
    }

    Gitara(Gitara &g) {
        strcpy(this->seriski, g.seriski);
        strcpy(this->tip, g.tip);
        this->cena = g.cena;
        this->godina = g.godina;
    }

    char *getSeriski() {
        return seriski;
    }

    float getNabavna() {
        return cena;
    }

    int getGodina() {
        return godina;
    }

    char *getTip() {
        return tip;
    }

    //destructor
    ~Gitara() {}

    bool daliIsti(Gitara &g) {
        return (strcmp(this->seriski, g.seriski) == 0);
    }

    void pecati() {
        cout << seriski << " " << tip << " " << cena << endl;
    }

    Gitara() {
    }
};

class Magacin {
private:
    char imeMagacin[31];
    char lokacijaMagacin[61];
    Gitara *gitara;
    int brojObjekti;
    int godinaOtvoranje;
public:
    Magacin(char *imeMagacin = "", char *lokacijaMagacin = "", int godinaOtvoranje = 0, Gitara *gitara = nullptr,
            int brojObjekti = 0) {
        strcpy(this->imeMagacin, imeMagacin);
        strcpy(this->lokacijaMagacin, lokacijaMagacin);
        this->brojObjekti = brojObjekti;
        this->godinaOtvoranje = godinaOtvoranje;
        this->gitara = gitara;//0
    }

//    //constructor
//    Magacin(char *imeMagacin, char *lokacijaMagacin) {
//        strcpy(this->imeMagacin, imeMagacin);
//        strcpy(this->lokacijaMagacin, lokacijaMagacin);
//        brojObjekti = 0;
//        godinaOtvoranje = 0;
//        gitara = new Gitara[0];//0
//    }
//
//    Magacin() {
//        this->brojObjekti = 0;
//        this->godinaOtvoranje = 0;
//        this->gitara = new Gitara[0];
//    }
//
//    Magacin(char *imeMagacin, char *lokacijaMagacin, int godina) {
//        strcpy(this->imeMagacin, imeMagacin);
//        strcpy(this->lokacijaMagacin, lokacijaMagacin);
//        godinaOtvoranje = godina;
//        brojObjekti = 0;
//        gitara = new Gitara[0];//0
//    }

    //copy construcctor
    Magacin(Magacin &m) {
        strcpy(this->imeMagacin, m.imeMagacin);
        strcpy(this->lokacijaMagacin, m.lokacijaMagacin);
        this->godinaOtvoranje = m.godinaOtvoranje;
        this->brojObjekti = m.brojObjekti;
        this->gitara = new Gitara[m.brojObjekti];
        //dinamicka alokacija ima for loop
        for (int i = 0; i < m.brojObjekti; ++i) {
            this->gitara[i] = m.gitara[i];
        }
    }

    Magacin &operator=(const Magacin &m) {
        if (this != &m) {
            //kopirame od copy constructor cel del !!!!
            delete[]gitara;//briseme stara alocirana niza
            strcpy(this->imeMagacin, m.imeMagacin);
            strcpy(this->lokacijaMagacin, m.lokacijaMagacin);
            this->godinaOtvoranje = m.godinaOtvoranje;
            this->brojObjekti = m.brojObjekti;
            this->gitara = new Gitara[brojObjekti];
            for (int i = 0; i < m.brojObjekti; ++i) {
                gitara[i] = m.gitara[i];
            }
            brojObjekti = m.brojObjekti;
//            return *this;
        }
        return *this;
    }

    //destructor
    ~Magacin() {
        delete[]gitara;
    }

    double vrednost() {
        //presmetuvame momentalnata bluza na gitarite
        double sum = 0;
        for (int i = 0; i < brojObjekti; ++i) {
            sum += gitara[i].getNabavna();
        }
        return sum;
    }

    void dodadi(Gitara d) {
        //doodavanje na nov objekt od klasa Gitara vo dimalicka alocirana memorija
        Gitara *tmp = new Gitara[brojObjekti + 1];//kreirame nova niza za + 1 oblejkt
        for (int i = 0; i < brojObjekti; ++i) {
            tmp[i] = gitara[i];//gi prefrluvame objektite vo novata niza

//            tmp= nullptr;
        }
        tmp[brojObjekti++] = d;
        delete[]gitara;
        gitara = tmp;
    }

    void prodadi(Gitara p) {
        //TODO THIS METHOD =-
        //PAZI UBAVO GLEDAJ

        int newCount = 0;
        for (int i = 0; i < brojObjekti; ++i) {
            if (!gitara[i].daliIsti(p)) {
                gitara[newCount++] = gitara[i];
            }
        }
        Gitara *tmp = new Gitara[newCount];
        for (int i = 0; i < newCount; ++i) {
            tmp[i] = gitara[i];
        }
        delete[] gitara;
        gitara = tmp;
        brojObjekti = newCount;
    }



        void pecati(bool daliNovi) {
        cout << imeMagacin << " " << lokacijaMagacin << endl;
        for (int i = 0; i < brojObjekti; ++i) {
            //proveriva koi gitari se ponovi
            if (daliNovi == true && gitara[i].getGodina() > godinaOtvoranje) {
                gitara[i].pecati();
            } else if (daliNovi == false) {
                gitara[i].pecati();
            }
        }
    }

};


int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50], tip[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin >> tip;
        cin >> seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip, seriski, godina, cena);
        cout << g.getTip() << endl;
        cout << g.getSeriski() << endl;
        cout << g.getGodina() << endl;
        cout << g.getNabavna() << endl;
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1");
        kb.pecati(false);
    } else if (testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2005);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip, seriski, godina, cena);
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    } else if (testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2012);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    } else if (testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2011);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout << "Po brisenje:" << endl;
        Magacin kb3;
        kb3 = kb;
        kb3.pecati(true);
    } else if (testCase == 6) {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2011);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            kb.dodadi(g);
        }
        cout << kb.vrednost() << endl;
        kb.prodadi(brisi);
        cout << "Po brisenje:" << endl;
        cout << kb.vrednost();
        Magacin kb3;
        kb3 = kb;
    }
    return 0;
}
