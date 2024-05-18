//
// Created by mrozi on 5/18/2024.
//
#include<iostream>
#include<string.h>

using namespace std;

class NoCourseException {
    int Index;
public:
    //arguments
    NoCourseException(int Index = 101010) {
        this->Index = Index;
    }

    //medage
    void message() {
        cout << "Demonstratorot so indeks " << Index << " ne drzi laboratoriski vezbi" << endl;
    }
};

class Kurs {
private:
    char ime[20];
    int krediti;
public:
    //argumnets
    Kurs(char *ime, int krediti) {
        strcpy(this->ime, ime);
        this->krediti = krediti;
    }

    //default
    Kurs() {
        strcpy(this->ime, "Kiro");
        krediti = 0;
    }

    // operator ==
    bool operator==(const char *ime) const {
        return strcmp(this->ime, ime) == 0;
    }

    //get mwthod
    char const *getIme() const {
        return ime;
    }

    //pecati()
    void pecati() const {
        cout << ime << " " << krediti << "ECTS";
    }
};

class Student {
private:
    int *ocenki;
    int brojOcenki;
    bool IsDemo;
protected:
    int indeks;

public:
    Student(int indeks, int *ocenki, int brojOcenki) {
        this->indeks = indeks;
        this->brojOcenki = brojOcenki;
        this->ocenki = new int[brojOcenki];
        for (int i = 0; i < brojOcenki; i++)
            this->ocenki[i] = ocenki[i];
        this->IsDemo = false;
    }

    Student(const Student &k) {
        this->indeks = k.indeks;
        this->brojOcenki = k.brojOcenki;
        this->IsDemo = k.IsDemo;
        this->ocenki = new int[k.brojOcenki];
        for (int i = 0; i < k.brojOcenki; i++)
            this->ocenki[i] = k.ocenki[i];
    }

    Student &operator=(const Student &k) {
        if (this != &k) {
            delete[] ocenki;
            this->indeks = k.indeks;
            this->brojOcenki = k.brojOcenki;
            this->IsDemo = k.IsDemo;
            this->ocenki = new int[k.brojOcenki];
            for (int i = 0; i < k.brojOcenki; i++)
                this->ocenki[i] = k.ocenki[i];
        }
        return *this;
    }

    ~Student() {
        delete[] ocenki;
    }

    //dopolni ja klasata

    //pecati()
    virtual void pecati() {
        cout << indeks << endl;
    }

    //getbodovi
    virtual int getBodovi() {
        int sum = 0, numPass = 0, Total = 0;
        for (int i = 0; i < brojOcenki; i++) {
            if (ocenki[i] > 5) {
                numPass++;
            }
            Total += ocenki[i];
        }
        return (float(numPass) / brojOcenki) * 100;
    }
};

class Predavach {
private:
    Kurs kursevi[10];
    int brojKursevi;

protected:
    char *imeIPrezime;

public:
    Predavach(char *imeIPrezime, Kurs *kursevi, int brojKursevi) {
        this->brojKursevi = brojKursevi;
        for (int i = 0; i < brojKursevi; i++) this->kursevi[i] = kursevi[i];
        this->imeIPrezime = new char[strlen(imeIPrezime) + 1];
        strcpy(this->imeIPrezime, imeIPrezime);
    }

    Predavach(const Predavach &p) {
        this->brojKursevi = p.brojKursevi;
        for (int i = 0; i < p.brojKursevi; i++) this->kursevi[i] = p.kursevi[i];
        this->imeIPrezime = new char[strlen(p.imeIPrezime) + 1];
        strcpy(this->imeIPrezime, p.imeIPrezime);
    }

    Predavach &operator=(const Predavach &p) {
        if (this != &p) {
            this->brojKursevi = p.brojKursevi;
            for (int i = 0; i < p.brojKursevi; i++) this->kursevi[i] = p.kursevi[i];
            this->imeIPrezime = new char[strlen(p.imeIPrezime) + 1];
            delete[] imeIPrezime;
            strcpy(this->imeIPrezime, p.imeIPrezime);
        }
        return *this;
    }

    ~Predavach() {
        delete[] imeIPrezime;
    }

    int getBrojKursevi() const {
        return brojKursevi;
    }

    char *const getImeIPrezime() const {
        return imeIPrezime;
    }

    Kurs operator[](int i) const {
        if (i < brojKursevi && i >= 0)
            return kursevi[i];
        else
            return Kurs();
    }


    void pecati() const {
        cout << imeIPrezime << " (";
        for (int i = 0; i < brojKursevi; i++) {
            kursevi[i].pecati();
            if (i < brojKursevi - 1) cout << ", "; else cout << ")";
        }
    }
};


//mesto za vashiot kod

class Demonstrator : public Student, public Kurs {
protected:
    int Index;
    int Grades[20];
    int NumGrades;
    char NameAndSurname[100];
    Kurs Courses[15];
    int NumCourses;
    int NumHours;
    //        Demonstrator d(indeks,ocenki,brojOcenki,
    //        imeIPrezime,kursevi,brojKursevi,brojCasovi);
    bool IsDemo;
public:
    //arguments
    Demonstrator(int Index, int *Grades, int NumGrades, char *NameAndSurname, Kurs *Courses, int NumCourses,
                 int NumHours)
            : Student(Index, Grades, NumGrades) {
        this->Index = Index;
        this->NumGrades = NumGrades;
        for (int i = 0; i < NumGrades; i++) {
            this->Grades[i] = Grades[i];
        }
        strcpy(this->NameAndSurname, NameAndSurname);
        this->NumCourses = NumCourses;
        for (int i = 0; i < NumCourses; i++) {
            this->Courses[i] = Courses[i];
        }
        this->NumHours = NumHours;
        this->IsDemo = true;
    }

    //pecati
    void pecati() {
        cout << indeks << ": " << NameAndSurname << " (";
        for (int i = 0; i < NumCourses; i++) {
            Courses[i].pecati();
            if (i < NumCourses - 1)
                cout << ", ";
        }
        cout << ")";
    }

    //getoceni
    int getBodovi() {
        try {
            if (NumCourses == 0)
                throw NoCourseException(indeks);
        } catch (NoCourseException &e) {
            e.message();
            return 0;
        }
        int Base = Student::getBodovi();
        int LabsSum = ((NumHours * 20) / NumCourses);
        return (Base + LabsSum);
    }

    char const *getCourse(int i) {
        return Courses[i].getIme();
    }
};

Student &vratiNajdobroRangiran(Student **studenti, int n) {
    Student *temp = studenti[0];
    for (int i = 1; i < n; i++) {
        if (temp->getBodovi() < studenti[i]->getBodovi())
            temp = studenti[i];
    }
    return (*temp);
}

void pecatiDemonstratoriKurs(char *kurs, Student **studenti, int n) {
    for (int i = 0; i < n; i++) {
        Demonstrator *temp = dynamic_cast<Demonstrator *>(studenti[i]);
        if (temp) {
            if (strcmp(temp->getCourse(i), kurs) == 0)
                temp->pecati();
            cout << endl;
        }
    }
}


int main() {

    Kurs kursevi[10];
    int indeks, brojKursevi, ocenki[20], ocenka, brojOcenki, tip, brojCasovi, krediti;
    char ime[20], imeIPrezime[50];

    cin >> tip;

    if (tip == 1) //test class Demonstrator
    {
        cout << "-----TEST Demonstrator-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;

        Demonstrator d(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi, brojCasovi);
        cout << "Objekt od klasata Demonstrator e kreiran";

    } else if (tip == 2) //funkcija pecati vo Student
    {
        cout << "-----TEST pecati-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }

        Student s(indeks, ocenki, brojOcenki);
        s.pecati();

    } else if (tip == 3) //funkcija getVkupnaOcenka vo Student
    {
        cout << "-----TEST getVkupnaOcenka-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        Student s(indeks, ocenki, brojOcenki);
        cout << "Broj na bodovi: " << s.getBodovi() << endl;

    } else if (tip == 4) //funkcija getVkupnaOcenka vo Demonstrator
    {
        cout << "-----TEST getVkupnaOcenka-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;

        Demonstrator d(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi, brojCasovi);
        cout << "Broj na bodovi: " << d.getBodovi() << endl;

    } else if (tip == 5) //funkcija pecati vo Demonstrator
    {
        cout << "-----TEST pecati -----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;

        Demonstrator d(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi, brojCasovi);
        d.pecati();

    } else if (tip == 6) //site klasi
    {
        cout << "-----TEST Student i Demonstrator-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;

        Student *s = new Demonstrator(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi, brojCasovi);
        s->pecati();
        cout << "\nBroj na bodovi: " << s->getBodovi() << endl;
        delete s;


    } else if (tip == 7) //funkcija vratiNajdobroRangiran
    {
        cout << "-----TEST vratiNajdobroRangiran-----" << endl;
        int k, opt;
        cin >> k;
        Student **studenti = new Student *[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Student 2 Demonstrator
            cin >> indeks >> brojOcenki;
            for (int i = 0; i < brojOcenki; i++) {
                cin >> ocenka;
                ocenki[i] = ocenka;
            }
            if (opt == 1) {
                studenti[j] = new Student(indeks, ocenki, brojOcenki);
            } else {
                cin >> imeIPrezime >> brojKursevi;
                for (int i = 0; i < brojKursevi; i++) {
                    cin >> ime >> krediti;
                    kursevi[i] = Kurs(ime, krediti);
                }
                cin >> brojCasovi;
                studenti[j] = new Demonstrator(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi,
                                               brojCasovi);
            }
        }
        Student &najdobar = vratiNajdobroRangiran(studenti, k);
        cout << "Maksimalniot broj na bodovi e:" << najdobar.getBodovi();
        cout << "\nNajdobro rangiran:";
        najdobar.pecati();

        for (int j = 0; j < k; j++) delete studenti[j];
        delete[] studenti;
    } else if (tip == 8) //funkcija pecatiDemonstratoriKurs
    {
        cout << "-----TEST pecatiDemonstratoriKurs-----" << endl;
        int k, opt;
        cin >> k;
        Student **studenti = new Student *[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Student 2 Demonstrator
            cin >> indeks >> brojOcenki;
            for (int i = 0; i < brojOcenki; i++) {
                cin >> ocenka;
                ocenki[i] = ocenka;
            }
            if (opt == 1) {
                studenti[j] = new Student(indeks, ocenki, brojOcenki);
            } else {
                cin >> imeIPrezime >> brojKursevi;
                for (int i = 0; i < brojKursevi; i++) {
                    cin >> ime >> krediti;
                    kursevi[i] = Kurs(ime, krediti);
                }
                cin >> brojCasovi;
                studenti[j] = new Demonstrator(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi,
                                               brojCasovi);
            }
        }
        char kurs[20];
        cin >> kurs;
        cout << "Demonstratori na " << kurs << " se:" << endl;
        pecatiDemonstratoriKurs(kurs, studenti, k);
        for (int j = 0; j < k; j++) delete studenti[j];
        delete[] studenti;

    }


    return 0;
}
