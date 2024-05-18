//
// Created by mrozi on 5/18/2024.
//
#include<iostream>
#include<string.h>
#include<cstring>

using namespace std;

class OutOfBoundException {
private:
    char Message[100];
public:
    //2 in 1
    OutOfBoundException(char *Message = (char *) "") {
        strcpy(this->Message, Message);
    }

    //message
    void message() {
        cout << Message;
    }

    //desrucot
    ~OutOfBoundException() {}
};

class Karticka {
protected:
    char TransactionAdress[16];
    int Pin;
    bool ExtraPins;

    //void copy
    void copy(const Karticka &other) {
        strcpy(this->TransactionAdress, other.TransactionAdress);
        this->Pin = other.Pin;
        this->ExtraPins = other.ExtraPins;
    }

public:
    Karticka(char *TransactionAdress = (char *) "", int Pin = 0) {
        strcpy(this->TransactionAdress, TransactionAdress);
        this->Pin = Pin;
        this->ExtraPins = false;
    }

    //opeatior <<
    friend ostream &operator<<(ostream &out, Karticka &other) {
        out << other.TransactionAdress << ": " << other.tezinaProbivanje() << endl;
        return out;
    }

    //tezina
    virtual int tezinaProbivanje() {
        int counter = 0;
        int temp = Pin;
        while (temp != 0) {
            temp /= 10;
            counter++;
        }
        return counter;
    }

    //get dopolnitelen
    bool getDopolnitelenPin() {
        return ExtraPins;
    }

    //get TransactionAdress
    virtual char *getTransactionAdress() {
        return TransactionAdress;
    }
};

//вметнете го кодот за SpecijalnaKarticka
class SpecijalnaKarticka : public Karticka {
private:
    int *ExtraPin;
    int NumPin;
    int P;

    //void copy
    void copy(const SpecijalnaKarticka &other) {
        Karticka::copy(other);
        this->P = other.P;
        this->NumPin = other.NumPin;
        this->ExtraPin = new int[other.NumPin];
        for (int i = 0; i < NumPin; i++) {
            this->ExtraPin[i] = other.ExtraPin[i];
        }
    }

public:
    //2 in 1
    SpecijalnaKarticka(char *TransactionAdress = (char *) "", int Pin = 0, int *ExtraPin = nullptr, int NumPin = 0)
            : Karticka(TransactionAdress, Pin) {
        this->NumPin = NumPin;
        for (int i = 0; i < NumPin; i++) {
            this->ExtraPin[i] = ExtraPin[i];
        }
        this->P = 4;
        this->ExtraPins = true;
    }

    //copy method
    SpecijalnaKarticka(const SpecijalnaKarticka &other) {
        copy(other);
    }

    //opeator =
    SpecijalnaKarticka &operator=(const SpecijalnaKarticka &other) {
        if (this != &other) {
            delete[] ExtraPin;
            //Karticka::copy(other);
            copy(other);
        }
        return *this;
    }

    //destructor
    ~SpecijalnaKarticka() {
        delete[] ExtraPin;
    }

    //tezina
    int tezinaProbivanje() override {
        int counter = Karticka::tezinaProbivanje();
        return (counter + NumPin);
    }

    //opeatoir <<
    friend ostream &operator<<(ostream &out, SpecijalnaKarticka &other) {
        out << other.TransactionAdress << ": " << other.tezinaProbivanje() << endl;
        return out;
    }

    //operator +=
    SpecijalnaKarticka &operator+=(int &NewPin) {
        if (NumPin > P) {
            throw OutOfBoundException("Brojot na pin kodovi ne moze da go nadmine dozvolenoto");
        }

        int *NewPins = new int[NumPin + 1];

        for (int i = 0; i < NumPin; i++) {
            NewPins[i] = ExtraPin[i];
        }

        //cout<<"Added +1 pin"<<endl;
        NewPins[NumPin++] = NewPin;
        delete[] ExtraPin;
        ExtraPin = NewPins;
        return *this;
    }

    //get TransactionAdress
    char *getTransactionAdress() override {
        return TransactionAdress;
    }

    //get num pin
    int getNumPin() {
        return NumPin;
    }
};


class Banka {
private:
    char bankName[30];
    Karticka *Cards[20];
    int NumCards;
    static int LIMIT;

    //void copy
    void copy(const Banka &other) {
        strcpy(this->bankName, other.bankName);
        for (int i = 0; i < other.NumCards; i++) {
            //ako kartickata ima dopolnitelni pin kodovi
            if (other.Cards[i]->getDopolnitelenPin()) {
                this->Cards[i] = new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka *>(other.Cards[i]));
            } else
                this->Cards[i] = new Karticka(*other.Cards[i]);
        }
        this->NumCards = other.NumCards;
        //this->LIMIT=other->LIMIT;
    }

public:
    //argumebnts
    Banka(char *bankName, Karticka **Cards, int NumCards) {
        strcpy(this->bankName, bankName);
        for (int i = 0; i < NumCards; i++) {
            //ako kartickata ima dopolnitelni pin kodovi
            if (Cards[i]->getDopolnitelenPin()) {
                this->Cards[i] = new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka *>(Cards[i]));
            } else
                this->Cards[i] = new Karticka(*Cards[i]);
        }
        this->NumCards = NumCards;
        //this->LIMIT=7;
    }

    ~Banka() {
        for (int i = 0; i < NumCards; i++)
            delete Cards[i];
        //delete *Cards;
    }

    //copy method
    Banka(const Banka &other) {
        copy(other);
    }

    //oepatir =
    Banka &operator=(const Banka &other) {
        if (this != &other) {
            for (int i = 0; i < NumCards; i++)
                delete Cards[i];
            //delete *Cards;
            copy(other);
        }
        return *this;
    }

    //void pecati karticki
    void pecatiKarticki() {
        cout << "Vo bankata " << bankName << " moze da se probijat kartickite: " << endl;
        for (int i = 0; i < NumCards; i++) {
            if (Cards[i]->tezinaProbivanje() <= Banka::LIMIT) {
                SpecijalnaKarticka *temp = dynamic_cast<SpecijalnaKarticka *>(Cards[i]);
                if (temp)
                    cout << *temp;
                else
                    cout << *Cards[i];
            }
        }
    }

    //dodadipin
    void dodadiDopolnitelenPin(char *smetka, int novPin) {
        for (int i = 0; i < NumCards; i++) {
            if (strcmp(Cards[i]->getTransactionAdress(), smetka) == 0) {
                SpecijalnaKarticka *temp = dynamic_cast<SpecijalnaKarticka *>(Cards[i]);
                //cout<<endl<<"Num Pin: "<<temp->getNumPin()<<endl;
                if (temp) {
                    if (temp->getNumPin() >= 4)
                        throw OutOfBoundException("Brojot na pin kodovi ne moze da go nadmine dozvolenoto");
                    *temp += novPin;
                    //Cards[i]+=novPin;
                    //cout<<endl<<"pin added: 1"<<*temp<<endl;
                }
            }
        }
    }

    //set limit
    static void setLIMIT(int n) {
        LIMIT = n;
    }
};

int Banka::LIMIT = 7;

int main() {

    Karticka **niza;
    int n, m, pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin >> n;
    niza = new Karticka *[n];

    for (int i = 0; i < n; i++) {
        cin >> smetka;
        cin >> pin;
        cin >> daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i] = new Karticka(smetka, pin);
        else
            niza[i] = new SpecijalnaKarticka(smetka, pin);
    }

    Banka komercijalna("Komercijalna", niza, n);

    for (int i = 0; i < n; i++)
        delete niza[i];
    delete[] niza;

    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> smetka >> pin;
        komercijalna.dodadiDopolnitelenPin(smetka, pin);
    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}