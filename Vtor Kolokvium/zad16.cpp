//
// Created by mrozi on 5/18/2024.
//
#include <iostream>
#include <cstring>

using namespace std;

class Transport {
protected:
    char Destination[120];
    int OriginalPrice;
    float Distance;
public:
    //argumetns
    Transport(char *Destination = (char *) "Kiro", int OriginalPrice = 0, float Distance = 0.0) {
        strcpy(this->Destination, Destination);
        this->OriginalPrice = OriginalPrice;
        this->Distance = Distance;
    }

    //cena
    virtual float cenaTransport() {
        return OriginalPrice;
    }

    //opertaor <
    bool operator<(const Transport &other) {
        if (this->Distance < other.Distance)
            return true;
        else
            return false;
    }

    //operator <<
    friend ostream &operator<<(ostream &out, Transport &other) {
        out << other.Destination << " " << other.Distance << " " << other.cenaTransport();
        return out;
    }

    //get distance
    virtual float getDistance() {
        return Distance;
    }
};

class AvtomobilTransport : public Transport {
protected:
    bool PaidDriver; // 0-no 1-yes
public:
    //arguments
    AvtomobilTransport(char *Destination = (char *) "Kiro", int OriginalPrice = 0, float Distance = 0,
                       bool PaidDriver = false)
            : Transport(Destination, OriginalPrice, Distance) {
        this->PaidDriver = PaidDriver;
    }

    //cena
    float cenaTransport() {
        if (PaidDriver)
            return OriginalPrice * 1.20;
        else
            return OriginalPrice;
    }

    //operator <<
//    friend ostream &operator<<(ostream &out,AvtomobilTransport &other)
//    {
//        out<<other.Destination<<" "<<other.Distance<<" "<<other.cenaTransport();
//        return out;
//    }
    //opertaor <
    // bool operator<(AvtomobilTransport &other)
    // {
    //     if(this->cenaTransport()<other.cenaTransport())
    //         return true;
    //     else
    //         return false;
    // }
    //get distance
    float getDistance() {
        return Distance;
    }
};

class KombeTransport : public Transport {
protected:
    int NumPeopleCapacity;
public:
    //arguments
    KombeTransport(char *Destination = (char *) "Kiro", int OriginalPrice = 0, float Distance = 0,
                   int NumPeopleCapacity = 0)
            : Transport(Destination, OriginalPrice, Distance) {
        this->NumPeopleCapacity = NumPeopleCapacity;
    }

    //cena
    float cenaTransport() {
        int TotalPrice = OriginalPrice;
        for (int i = 0; i < NumPeopleCapacity; i++)
            TotalPrice -= 200;
        return TotalPrice;
    }

    //operator <<
//    friend ostream &operator<<(ostream &out,KombeTransport &other)
//    {
//        out<<other.Destination<<" "<<other.Distance<<" "<<other.cenaTransport();
//        return out;
//    }
    //opertaor <
    // bool operator<(KombeTransport &other)
    // {
    //     if(this->cenaTransport()<other.cenaTransport())
    //         return true;
    //     else
    //         return false;
    // }
    //get distance
    float getDistance() {
        return Distance;
    }
};

void pecatiPoloshiPonudi(Transport **Offers, int n, AvtomobilTransport &T) {
    int x = 0;
    Transport **New = new Transport *[n];
    for (int i = 0; i < n; i++) {
        if (Offers[i]->cenaTransport() > T.cenaTransport()) {
            New[x++] = Offers[i];
        }
    }

    for (int i = 0; i < x - 1; ++i) {
        for (int k = i; k < x; ++k) {
            if (*New[i] < *New[k]) {
                Transport *temp = New[i];
                New[i] = New[k];
                New[k] = temp;
            }
        }
    }
    for (int i = x - 1; i >= 0; --i) {
        cout << *New[i] << endl;
    }
}


// вашиот код треба да биде тука

int main() {

    char destinacija[20];
    int tip, cena, rastojanie, lugje;
    bool shofer;
    int n;
    cin >> n;
    Transport **ponudi;
    ponudi = new Transport *[n];

    for (int i = 0; i < n; i++) {

        cin >> tip >> destinacija >> cena >> rastojanie;
        if (tip == 1) {
            cin >> shofer;
            ponudi[i] = new AvtomobilTransport(destinacija, cena, rastojanie, shofer);

        } else {
            cin >> lugje;
            ponudi[i] = new KombeTransport(destinacija, cena, rastojanie, lugje);
        }


    }

    AvtomobilTransport nov("Ohrid", 2000, 600, false);
    pecatiPoloshiPonudi(ponudi, n, nov);

    for (int i = 0; i < n; i++)
        delete ponudi[i];
    delete[] ponudi;

    return 0;
}