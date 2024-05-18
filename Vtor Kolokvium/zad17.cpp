//
// Created by mrozi on 5/18/2024.
//
#include <iostream>
#include <cstring>

using namespace std;

// vashiot kod ovde

class FudbalskaEkipa {
protected:
    char Coach[100];
    int GoalsScored[10];
public:
    //arguments
    FudbalskaEkipa(char *Coach = (char *) "Kiro", const int *GoalsScored = nullptr) {
        strcpy(this->Coach, Coach);
        for (int i = 0; i < 10; i++) {
            this->GoalsScored[i] = GoalsScored[i];
        }
    }

    // <<
    friend ostream &operator<<(ostream &out, FudbalskaEkipa &other) {
        out << other.Coach << endl << other.uspeh() << endl;
        return out;
    }

    // +=
    FudbalskaEkipa &operator+=(int Goal) {
        for (int i = 0; i < 9; i++) {
            GoalsScored[i] = GoalsScored[i + 1];
        }
        GoalsScored[9] = Goal;
        return *this;
    }

    //uspeh
    virtual int uspeh() {
        return 1;
    }

    // >
    bool operator>(FudbalskaEkipa &other) {
        if (this->uspeh() > other.uspeh())
            return true;
        else
            return false;
    }
};

class Klub : public FudbalskaEkipa {
protected:
    char TeamName[100];
    int NumTitles;
public:
    //argumetnes
    Klub(char *Coach = (char *) "Kiro", int *GoalsScored = nullptr, char *TeamName = (char *) "Bayern",
         int NumTitles = 15)
            : FudbalskaEkipa(Coach, GoalsScored) {
        strcpy(this->TeamName, TeamName);
        this->NumTitles = NumTitles;
    }

    // <<
    friend ostream &operator<<(ostream &out, Klub &other) {
        out << other.TeamName << endl << other.Coach << endl << other.uspeh() << endl;
        return out;
    }

    //uspeh
    int uspeh() {
        int sum = 0, sumTitles;
        for (int i = 0; i < 10; i++) {
            sum += GoalsScored[i];
        }
        sum *= 3;
        sumTitles = 1000 * NumTitles;
        return sum + sumTitles;
    }
};

class Reprezentacija : public FudbalskaEkipa {
protected:
    char Country[100];
    int TotalInternational;
public:
    //argumtns
    Reprezentacija(char *Coach = (char *) "Kiro", int *GoalsScored = nullptr, char *Country = (char *) "Svicarska",
                   int TotalInternational = 10)
            : FudbalskaEkipa(Coach, GoalsScored) {
        strcpy(this->Country, Country);
        this->TotalInternational = TotalInternational;
    }

    // <<
    friend ostream &operator<<(ostream &out, Reprezentacija &other) {
        out << other.Country << endl << other.Coach << endl << other.uspeh() << endl;
        return out;
    }

    //uspeh()
    int uspeh() {
        int sum = 0, totalInterantioanl = 0;
        for (int i = 0; i < 10; i++) {
            sum += GoalsScored[i];
        }
        sum *= 3;
        totalInterantioanl += TotalInternational * 50;
        return sum + totalInterantioanl;
    }
};

void najdobarTrener(FudbalskaEkipa **Teams, int NumTeams) {
    FudbalskaEkipa *temp = Teams[0];
    for (int i = 1; i < NumTeams; i++) {
        if (temp->uspeh() < Teams[i]->uspeh()) {
            temp = Teams[i];
        }
    }
    Klub *temp2 = dynamic_cast<Klub *>(temp);
    if (temp2)
        cout << *temp2;
    else {
        Reprezentacija *temp3 = dynamic_cast<Reprezentacija *>(temp);
        cout << *temp3;
    }
    //cout<<*temp;
}


int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa *[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        Klub *temp = dynamic_cast<Klub *>(ekipi[i]);
        if (temp)
            cout << *temp;
        else {
            Reprezentacija *temp2 = dynamic_cast<Reprezentacija *>(ekipi[i]);
            cout << *temp2;
        }
        //cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        Klub *temp = dynamic_cast<Klub *>(ekipi[i]);
        if (temp)
            cout << *temp;
        else {
            Reprezentacija *temp2 = dynamic_cast<Reprezentacija *>(ekipi[i]);
            cout << *temp2;
        }
        //cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete[] ekipi;
    return 0;
}