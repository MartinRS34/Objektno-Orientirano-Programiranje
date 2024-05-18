//
// Created by mrozi on 5/18/2024.
//
#include<iostream>
#include<cstring>

using namespace std;

//место за вашиот код
class Delo {
protected:
    char DeloName[50];
    int WrittenYear;
    char OriginCountry[50];

    //void copy
    void copy(const Delo &other) {
        strcpy(this->DeloName, other.DeloName);
        this->WrittenYear = other.WrittenYear;
        strcpy(this->OriginCountry, other.OriginCountry);
    }

public:
    //2 in 1
    Delo(char *DeloName = (char *) "", int WrittenYear = 0, char *OriginCountry = (char *) "") {
        strcpy(this->DeloName, DeloName);
        this->WrittenYear = WrittenYear;
        strcpy(this->OriginCountry, OriginCountry);
    }

    //copy constructor
    Delo(const Delo &other) {
        copy(other);
    }

    //operator =
    Delo &operator=(const Delo &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    //opeator ==
    bool operator==(Delo &other) {
        if (strcmp(this->DeloName, other.DeloName) == 0)
            return true;
        else
            return false;
    }

    //getime
    char *getIme() {
        return DeloName;
    }
};


class Pretstava : public Delo {
protected:
    Delo *Delos;
    int NumSoldCards;
    char ShowData[15];

    //void copy
    void copy(const Pretstava &other) {
        Delo::copy(other);
        this->NumSoldCards = other.NumSoldCards;
        strcpy(this->ShowData, other.ShowData);
        this->Delos = other.Delos;
    }

public:
    //2 in 1
    Pretstava(const Delo &other, int NumSoldCards = 0, char *ShowData = (char *) "")
            : Delo(other) {
        this->Delos = new Delo(other);
        this->NumSoldCards = NumSoldCards;
        strcpy(this->ShowData, ShowData);
    }

    //copy mehtod
    Pretstava(const Pretstava &other) {
        copy(other);
    }

    //opeartror =
    Pretstava &operator=(const Pretstava &other) {
        if (this != &other) {
            delete[] Delos;
            copy(other);
        }
        return *this;
    }

    //price
    virtual int cena() {
        int yearmade = 0, placemade = 0;
        if (WrittenYear / 100 == 19 || WrittenYear / 100 == 20) {
            yearmade = 50;
        } else if (WrittenYear / 100 == 18) {
            yearmade = 75;
        } else if (WrittenYear / 100 < 18) {
            yearmade = 100;
        }
        if (strcmp(OriginCountry, "Italija") == 0) {
            placemade = 100;
        } else if (strcmp(OriginCountry, "Rusija") == 0) {
            placemade = 150;
        } else {
            placemade = 80;
        }
        return yearmade + placemade;
    }

    //get delo
    Delo getDelo() {
        return *Delos;
    }

    //get sold card
    int getSoldCards() {
        return NumSoldCards;
    }

    //destrucotr
    ~Pretstava() {
        delete[] Delos;
    }
};

class Balet : public Pretstava {
private:
    static int AdditionalFee;
public:
    //2 in 1
    Balet(const Delo &other, int NumSoldCards = 0, char *ShowData = (char *) "")
            : Pretstava(other, NumSoldCards, ShowData) {}

    //cena
    int cena() override {
        return Pretstava::cena() + AdditionalFee;
    }

    //set add
    static void setCenaBalet(int Add) {
        AdditionalFee = Add;
    }
};

int Balet::AdditionalFee = 150;

class Opera : public Pretstava {
protected:
public:
    Opera(const Delo &other, int NumSoldCards = 0, char *ShowData = (char *) "")
            : Pretstava(other, NumSoldCards, ShowData) {}
};

//prihod prihod(pole,n)
int prihod(Pretstava **Prestavi, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += Prestavi[i]->getSoldCards() * Prestavi[i]->cena();
    }
    return sum;
}

//brojPretstaviNaDelo(pole,n,f)
int brojPretstaviNaDelo(Pretstava **Prestavi, int n, Delo &d) {
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (Prestavi[i]->getDelo() == d)
            counter++;
    }
    return counter;
}

//citanje na delo
Delo readDelo() {
    char ime[50];
    int godina;
    char zemja[50];
    cin >> ime >> godina >> zemja;
    return Delo(ime, godina, zemja);
}

//citanje na pretstava
Pretstava *readPretstava() {
    int tip; //0 za Balet , 1 za Opera
    cin >> tip;
    Delo d = readDelo();
    int brojProdadeni;
    char data[15];
    cin >> brojProdadeni >> data;
    if (tip == 0)
        return new Balet(d, brojProdadeni, data);
    else
        return new Opera(d, brojProdadeni, data);
}

int main() {
    int test_case;
    cin >> test_case;

    switch (test_case) {
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout << "======TEST CASE 1=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->getDelo().getIme() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->getDelo().getIme() << endl;
        }
            break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout << "======TEST CASE 2=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->cena() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->cena() << endl;
        }
            break;

        case 3:
            //Testiranje na operator ==
        {
            cout << "======TEST CASE 3=======" << endl;
            Delo f1 = readDelo();
            Delo f2 = readDelo();
            Delo f3 = readDelo();

            if (f1 == f2) cout << "Isti se" << endl; else cout << "Ne se isti" << endl;
            if (f1 == f3) cout << "Isti se" << endl; else cout << "Ne se isti" << endl;

        }
            break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout << "======TEST CASE 4=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();

            }
            cout << prihod(pole, n);
        }
            break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout << "======TEST CASE 5=======" << endl;
            int cenaBalet;
            cin >> cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }
            cout << prihod(pole, n);
        }
            break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout << "======TEST CASE 6=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }

            Delo f = readDelo();
            cout << brojPretstaviNaDelo(pole, n, f);
        }
            break;

    };


    return 0;
}