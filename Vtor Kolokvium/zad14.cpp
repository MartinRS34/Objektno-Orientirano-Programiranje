//
// Created by mrozi on 5/18/2024.
//
#include <iostream>
#include <cstring>

using namespace std;

class SMS {
protected:
    double Price160;
    char NumUser[15];
public:
    //constrcutor
    SMS(char *NumUser = (char *) "", double Price160 = 0.0) {
        strcpy(this->NumUser, NumUser);
        this->Price160 = Price160;
    }

    //sms cena
    virtual double SMS_cena() = 0;

    //operator <<
    friend ostream &operator<<(ostream &out, SMS &other) {
        out << "Tel: " << other.NumUser << " - cena: " << other.SMS_cena() << "den." << endl;
        return out;
    }
};

class RegularSMS : public SMS {
protected:
    bool Roaming; // 0-not used 1-used
    char MsgText[1000];
    static double Discount1;
    static double Tax;
public:
    //constructor
    RegularSMS(char *NumUser = (char *) "", float Price160 = 0.0, char *MsgText = (char *) "", bool Roaming = false)
            : SMS(NumUser, Price160) {
        strcpy(this->MsgText, MsgText);
        this->Roaming = Roaming;
    }

    //sms ena
    double SMS_cena() override {
        double newprice = Price160;
        int lenght = strlen(MsgText);
        //cout<<"The lenght of the MSG is: "<<lenght<<endl;
        if (lenght >= 320)
            newprice *= 3;
        else if (lenght >= 160)
            newprice *= 2;
        if (Roaming)
            newprice += (newprice * Discount1);
        else
            newprice += (newprice * Tax);
        //cout<<"The new price is: "<<newprice<<endl;
        return newprice;
    }

    //set discoutn
    static void set_rProcent(int p) {
        Discount1 = (double) p / 100;
    }

    //oeptore <<
    friend ostream &operator<<(ostream &out, RegularSMS &other) {
        cout << "Tel: " << other.NumUser << " - cena:" << other.SMS_cena() << endl;
        return out;
    }
};

double RegularSMS::Discount1 = 3.0;
double RegularSMS::Tax = 0.18;

class SpecialSMS : public SMS {
protected:
    bool Humanitarian; // 0-no 1-yes
    static double Discount2;
    static double Tax;
public:
    //constrtor
    SpecialSMS(char *NumUser = (char *) "", double Price160 = 0.0, bool Humanitarian = false)
            : SMS(NumUser, Price160) {
        this->Humanitarian = Humanitarian;
    }

    //sms
    double SMS_cena() {
        if (Humanitarian)
            return Price160;
        else
            return Price160 + (Price160 * Discount2);
    }

    //set discount
    static void set_sProcent(int p) {
        Discount2 = (double) p / 100;
    }

    //oeptore <<
    friend ostream &operator<<(ostream &out, SpecialSMS &other) {
        cout << "Tel: " << other.NumUser << " - cena:" << other.SMS_cena() << endl;
        return out;
    }
};

double SpecialSMS::Discount2 = 1.5;
double SpecialSMS::Tax = 0.18;

void vkupno_SMS(SMS **poraka, int n) {
    int NumRegular = 0, NumSpecial = 0;
    double TotalPriceReg = 0.0, TotalPriceSpe = 0.0;
    for (int i = 0; i < n; i++) {
        SpecialSMS *temp = dynamic_cast<SpecialSMS *>(poraka[i]);
        if (temp) {
            NumSpecial++;
            TotalPriceSpe += temp->SMS_cena();
        } else {
            RegularSMS *temp2 = dynamic_cast<RegularSMS *>(poraka[i]);
            NumRegular++;
            //cout<<"Total price of Regular before add: "<<TotalPriceReg<<endl;
            TotalPriceReg += temp2->SMS_cena();
            //cout<<"Total price of Regular after add: "<<TotalPriceReg<<endl;
        }
    }
    cout << "Vkupno ima " << NumRegular << " regularni SMS poraki i nivnata cena e: " << TotalPriceReg << endl;
    cout << "Vkupno ima " << NumSpecial << " specijalni SMS poraki i nivnata cena e: " << TotalPriceSpe << endl;
}


int main() {

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i < n; i++)
            delete sms[i];
        delete[] sms;
    }
    if (testCase == 2) {
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3) {
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            } else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4) {
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5) {
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}