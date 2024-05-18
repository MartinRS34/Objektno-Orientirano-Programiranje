//
// Created by mrozi on 5/18/2024.
//
#include <iostream>
#include <cstring>

using namespace std;

enum tip {
    Mobilen, //0
    Laptop //1
};

class Device {
private:
    char ModelInfo[100];
    tip Type;
    static float HoursRequiered;
    float HoursRequieredNon;
    int YearProduced;
public:
    //2 in 1
    Device(char *ModelInfo = (char *) "", tip Type = Mobilen, int YearProduced = 0) {
        strcpy(this->ModelInfo, ModelInfo);
        this->Type = Type;
        this->YearProduced = YearProduced;
        HoursRequieredNon = calculate();

    }

    //calcualte
    float calculate() {
        if (this->YearProduced > 2015 && this->Type == 0)
            HoursRequieredNon = HoursRequiered + 2;
        else
            HoursRequieredNon = HoursRequiered;
        if (this->Type == 1) {
            if (this->YearProduced >= 2015) {
                HoursRequieredNon = HoursRequiered + 4;
            } else
                HoursRequieredNon = HoursRequiered + 2;
        }
        return HoursRequieredNon;
    }

    //copy
    Device(const Device &other) {
        strcpy(this->ModelInfo, other.ModelInfo);
        this->Type = other.Type;
        this->YearProduced = other.YearProduced;
        this->HoursRequieredNon = other.HoursRequieredNon;
    }

    //operator =
    friend ostream &operator<<(ostream &out, Device &other) {
        out << other.ModelInfo << endl;
        if (other.Type == 0)
            cout << "Mobilen " << other.calculate() << endl;
        else
            cout << "Laptop " << other.calculate() << endl;
        return out;
    }

    friend class MobileServis;

    //set
    static void setPocetniCasovi(float n) {
        HoursRequiered = n;
    }
};

float Device::HoursRequiered = 1;

class InvalidProductionDate {
private:
    char Message[100];
public:
    //default
    InvalidProductionDate(char *Message = (char *) "") {
        strcpy(this->Message, Message);
    }

    //void message
    void message() {
        cout << Message << endl;
    }

    //destructor
    ~InvalidProductionDate() {}
};

class MobileServis {
private:
    char Adress[100];
    Device *ListOfDevices;
    int NumDevices;

    //void copy
    void copy(const MobileServis &other) {
        strcpy(this->Adress, other.Adress);
        this->NumDevices = other.NumDevices;
        this->ListOfDevices = new Device[other.NumDevices];
        for (int i = 0; i < NumDevices; i++) {
            this->ListOfDevices[i] = other.ListOfDevices[i];
        }
    }

public:
    //2 in 1
    MobileServis(char *Adress = (char *) "") {
        strcpy(this->Adress, Adress);
        this->ListOfDevices = new Device[0];
        this->NumDevices = 0;
    }

    //copy dontrutor
    MobileServis(const MobileServis &other) {
        copy(other);
    }

    //opeator =
    MobileServis &operator=(const MobileServis &other) {
        if (this != &other) {
            delete[] ListOfDevices;
            copy(other);
        }
        return *this;
    }

    //operator +=
    MobileServis &operator+=(Device &other) {
        if (other.YearProduced < 2000 || other.YearProduced > 2019) {
            throw InvalidProductionDate("Невалидна година на производство");
        }
        Device *NewDevice = new Device[NumDevices + 1];
        for (int i = 0; i < NumDevices; i++) {
            NewDevice[i] = ListOfDevices[i];
        }
        NewDevice[NumDevices++] = other;
        delete[] ListOfDevices;
        ListOfDevices = NewDevice;
        return *this;
    }

    //void pecatiCasovi
    void pecatiCasovi() {
        cout << "Ime: " << Adress << endl;
        for (int i = 0; i < NumDevices; i++) {
            cout << ListOfDevices[i];
        }
    }

    //destrucotr
    ~MobileServis() {
        delete[] ListOfDevices;
    }


};

int main() {
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (tip) tipDevice, godina);
        cin >> ime;
        MobileServis t(ime);
        cout << ig;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            t += tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &e) {
                e.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4) {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &e) {
                e.message();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &e) {
                e.message();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6) {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &e) {
                e.message();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}
