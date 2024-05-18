//
// Created by mrozi on 5/18/2024.
//
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

//место за вашиот код

class Oglas {
private:
    char Title[50];
    char Category[50];
    char Description[100];
    float PriceEuro;

    //void copy
    void copy(const Oglas &other) {
        strcpy(this->Title, other.Title);
        strcpy(this->Category, other.Category);
        strcpy(this->Description, other.Description);
        this->PriceEuro = other.PriceEuro;
    }

public:
    //2 in 1
    Oglas(char *Title = (char *) "", char *Category = (char *) "", char *Description = (char *) "",
          float PriceEuro = 0.0) {
        strcpy(this->Title, Title);
        strcpy(this->Category, Category);
        strcpy(this->Description, Description);
        this->PriceEuro = PriceEuro;
    }

    //copy constructor
    Oglas(const Oglas &other) {
        copy(other);
    }

    //destructor
    ~Oglas() {}

    //operator <<
    friend ostream &operator<<(ostream &out, Oglas &other) {
        out << other.Title << endl;
        out << other.Description << endl;
        out << other.PriceEuro << " evra" << endl;
        return out;
    }

    //oeprator <
    bool operator>(Oglas &other) const {
        if (this->PriceEuro > other.PriceEuro)
            return true;
        else
            return false;
    }

    //get price
    float getPrice() {
        return PriceEuro;
    }

    //get title
    char *getCategory() {
        return Category;
    }
};


class NegativnaVrednost {
private:
    char Message[100];
public:
    //2 in 1
    NegativnaVrednost() {
        strcpy(this->Message, "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!");
    }

    //void message
    void message() {
        cout << Message << endl;
    }

    //destrcuor
    ~NegativnaVrednost() {}
};


class Oglasnik : public Oglas {
private:
    char NameOglas[20];
    Oglas *ListOglasi;
    int NumOglasi;

    //void copy
    void copy(const Oglasnik &other) {
        strcpy(this->NameOglas, other.NameOglas);
        this->NumOglasi = other.NumOglasi;
        this->ListOglasi = new Oglas[other.NumOglasi];
    }

public:
    //2 in 1
    Oglasnik(char *NameOglas = (char *) "") {
        strcpy(this->NameOglas, NameOglas);
        this->ListOglasi = new Oglas[0];
        this->NumOglasi = 0;
    }

    //copy construcotr
    Oglasnik(const Oglasnik &other) {
        copy(other);
    }

    //operaetor =
    Oglasnik &operator=(const Oglasnik &other) {
        if (this != &other) {
            delete[] ListOglasi;
            copy(other);
        }
        return *this;
    }

    //opeator +=
    Oglasnik &operator+=(Oglas &other) {
        int flag = 1;
        //try{
        if (other.getPrice() < 0) {
            //TODO add class NegativnaVrednost with char constrotr and print the message
            //throw NegativnaVrednost e("Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!");
            NegativnaVrednost e;
            e.message();
            //cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
        } else {
            Oglas *NewOglas = new Oglas[NumOglasi + 1];
            for (int i = 0; i < NumOglasi; i++) {
                NewOglas[i] = ListOglasi[i];
            }
            NewOglas[NumOglasi++] = other;
            delete[] ListOglasi;
            ListOglasi = NewOglas;
        }
        // }
        //catch(NegativnaVrednost e){
        //    e.message();
        //}

        return *this;
    }

    //opeator <<
    friend ostream &operator<<(ostream &out, Oglasnik &other) {
        out << other.NameOglas << endl;
        for (int i = 0; i < other.NumOglasi; i++)
            cout << other.ListOglasi[i] << endl;
        return out;
    }

    //void oglasiOdKategorija
    void oglasiOdKategorija(const char *k) {
        for (int i = 0; i < NumOglasi; i++) {
            if (strcmp(ListOglasi[i].getCategory(), k) == 0)
                cout << ListOglasi[i] << endl;
        }
    }

    // void najniskaCena()
    void najniskaCena() {
        float MinPrice = ListOglasi[0].getPrice();
        Oglas temp = ListOglasi[0];
        for (int i = 0; i < NumOglasi; i++) {
            if (MinPrice > ListOglasi[i].getPrice()) {
                MinPrice = ListOglasi[i].getPrice();
                temp = ListOglasi[i];
            }
        }
        cout << temp;
    }
    //friend class NegativnaVrednost;
};


int main() {

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin >> tip;

    if (tip == 1) {
        cout << "-----Test Oglas & operator <<-----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout << o;
    } else if (tip == 2) {
        cout << "-----Test Oglas & operator > -----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1 > o2) cout << "Prviot oglas e poskap." << endl;
        else cout << "Prviot oglas ne e poskap." << endl;
    } else if (tip == 3) {
        cout << "-----Test Oglasnik, operator +=, operator << -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << ogl;
    } else if (tip == 4) {
        cout << "-----Test oglasOdKategorija -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

    } else if (tip == 5) {
        cout << "-----Test Exception -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << ogl;

    } else if (tip == 6) {
        cout << "-----Test najniskaCena -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    } else if (tip == 7) {
        cout << "-----Test All -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << ogl;

        cin.get();
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    }

    return 0;
}