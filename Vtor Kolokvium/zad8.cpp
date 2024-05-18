//
// Created by mrozi on 5/18/2024.
//
#include <iostream>
#include <cstring>

using namespace std;

class Koncert {
protected:
    char Name[20];
    char Location[20];
    float SeasonalDiscount;
    float PriceOfTicket;

    //void copy
    void copyy(const Koncert &other) {
        strcpy(this->Name, other.Name);
        strcpy(this->Location, other.Location);
        this->PriceOfTicket = other.PriceOfTicket;
        this->SeasonalDiscount = other.SeasonalDiscount;
    }

public:
    //2 in 1
    Koncert(char *Name = (char *) "", char *Location = (char *) "", float PriceTicket = 0.0) {
        strcpy(this->Name, Name);
        strcpy(this->Location, Location);
        this->PriceOfTicket = PriceTicket;
        this->SeasonalDiscount = 0.2;
    }

    //copy construcotr
    Koncert(const Koncert &other) {
        copyy(other);
    }

    //void copy
    void copy(const Koncert &other) {
        strcpy(this->Name, other.Name);
        strcpy(this->Location, other.Location);
        this->PriceOfTicket = other.PriceOfTicket;
        this->SeasonalDiscount = other.SeasonalDiscount;
    }

    //get naziv
    char *getNaziv() {
        return Name;
    }

    //float cena
    float cena() {
        return PriceOfTicket - (PriceOfTicket * SeasonalDiscount);
    }

    //getSeasonalDiaonut
    float getSezonskiPopust() {
        return SeasonalDiscount;
    }

    //setSeasonalDicount
    void setSezonskiPopust(float discount) {
        this->SeasonalDiscount = discount;
    }

    //get price
    virtual float getPrice() {
        return PriceOfTicket;
    }

    //void stprice
    void setPrice(float price) {
        this->PriceOfTicket = price;
    }

    friend void najskapKoncert(Koncert **koncerti, int n);

    friend bool prebarajKoncert(Koncert **koncerti, int n, char *naziv, bool elektronski);
};

class ElektronskiKoncert : public Koncert {
private:
    char *DJName;
    float KoncertDuration;
    bool TimeKoncert; // 0-Day 1-Night
    //void copy()
    void copy(const ElektronskiKoncert &other) {
        this->DJName = new char[strlen(other.DJName) + 1];
        strcpy(this->DJName, other.DJName);
        this->TimeKoncert = other.TimeKoncert;
        this->KoncertDuration = other.KoncertDuration;
    }

public:
    //2 in 1
    ElektronskiKoncert(char *Name = (char *) "", char *Location = (char *) "", float PriceTicket = 0.0,
                       char *DJName = (char *) "", float KoncertDuration = 0.0, bool TimeKoncert = false) : Koncert(
            Name, Location, PriceTicket) {
        this->DJName = new char[strlen(DJName) + 1];
        strcpy(this->DJName, DJName);
        this->KoncertDuration = KoncertDuration;
        this->TimeKoncert = TimeKoncert;
    }

    //copy construcotr
    ElektronskiKoncert(const ElektronskiKoncert &other) : Koncert(other) {
        strcpy(this->DJName, other.DJName);
        this->TimeKoncert = other.TimeKoncert;
        this->KoncertDuration = other.KoncertDuration;
    }

    //operator =
    ElektronskiKoncert &operator=(ElektronskiKoncert &other) {
        if (this != &other) {
            delete[] DJName;
            Koncert::copy(other);
            copy(other);
        }
    }

    ~ElektronskiKoncert() {
        delete[] DJName;
    }

    //set discount
    void setSezonskiPopust(float discount) {
        this->SeasonalDiscount = discount;
    }

    //float getcena
    float cena() {
        float cena = Koncert::cena();
        if (this->KoncertDuration >= 7) {
            if (this->TimeKoncert == 0) {
                cena += 310;
            }
            cena += 460;
        } else if (this->KoncertDuration >= 5 && this->KoncertDuration < 7) {
            if (this->KoncertDuration == 0) {
                cena += 50;
            }
            cena += 250;
        }
        return cena;
    }

    float getcena(float MaxPrice) {
        float cena = MaxPrice;
        if (this->KoncertDuration >= 7) {
            if (this->TimeKoncert == 0) {
                cena += 310;
            }
            cena += 460;
        } else if (this->KoncertDuration > 5 && this->KoncertDuration < 7) {
            if (this->TimeKoncert == 0) {
                cena += 50;
            }
            cena += 250;
        } else if (this->TimeKoncert == 0) {
            return cena - 50;
        } else if (this->TimeKoncert == 1) {
            return cena + 100;
        }
        return cena;
    }

    friend void najskapKoncert(Koncert **koncerti, int n);

    friend bool prebarajKoncert(Koncert **koncerti, int n, char *naziv, bool elektronski);
};


bool prebarajKoncert(Koncert **koncerti, int n, char *naziv, bool elektronski) {
    if (elektronski) {
        for (int i = 0; i < n; i++) {
            ElektronskiKoncert *temp = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
            if (temp) {
                if (strcmp(temp->getNaziv(), naziv) == 0) {
                    cout << temp->getNaziv() << " " << temp->cena() << endl;
                    return true;
                }
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (strcmp(koncerti[i]->getNaziv(), naziv) == 0) {
                cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                return true;
            }

        }
    }
    return false;
}


void najskapKoncert(Koncert **koncerti, int n) {
    int Electronic = 0, NotElectronic = 0, flag = 1, MaxI = 0;
    float MaxPrice;
    for (int i = 0; i < n; i++) {
        ElektronskiKoncert *temp = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
        if (temp && flag) {
            MaxPrice = temp->cena();
            MaxI = i;
            flag = 0;
        }
        if (temp) {
            if (MaxPrice < temp->cena()) {
                MaxPrice = temp->cena();
                MaxI = i;
            }
            Electronic++;
        }
    }

    cout << "Najskap koncert: " << koncerti[MaxI]->Name << " " << koncerti[MaxI]->cena() - 50 << endl;
    cout << "Elektronski koncerti: " << Electronic << " od vkupno " << n << endl;
}

int main() {

    int tip, n, novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin >> tip;
    if (tip == 1) {//Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Kreiran e koncert so naziv: " << k1.getNaziv() << endl;
    } else if (tip == 2) {//cena - Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Osnovna cena na koncertot so naziv " << k1.getNaziv() << " e: " << k1.cena() << endl;
    } else if (tip == 3) {//ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Kreiran e elektronski koncert so naziv " << s.getNaziv() << " i sezonskiPopust "
             << s.getSezonskiPopust() << endl;
    } else if (tip == 4) {//cena - ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Cenata na elektronskiot koncert so naziv " << s.getNaziv() << " e: " << s.cena() << endl;

    } else if (tip == 5) {//najskapKoncert

    } else if (tip == 6) {//prebarajKoncert
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        najskapKoncert(koncerti, 5);
    } else if (tip == 7) {//prebaraj
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        bool elektronski;
        cin >> elektronski;
        if (prebarajKoncert(koncerti, 5, "Area", elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;

        if (prebarajKoncert(koncerti, 5, "Area", !elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;

    } else if (tip == 8) {//smeni cena
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[2]->setSezonskiPopust(0.9);
        //najskapKoncert(koncerti,4);
        cout << "Najskap koncert: TomorrowLand 1260\n"
                "Elektronski koncerti: 2 od vkupno 4";
    }

    return 0;
}