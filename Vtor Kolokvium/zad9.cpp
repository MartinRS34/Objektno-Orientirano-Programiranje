//
// Created by mrozi on 5/18/2024.
//
#include <iostream>
#include <cstring>

using namespace std;

class Exception {
protected:
    char Message[120];
public:
    Exception(char *Message = (char *) "Kiro") {
        strcpy(this->Message, Message);
    }

    void print() {
        cout << Message << endl;
    }
};

class NotFound {
protected:
    int index;
public:
    NotFound(int index) {
        this->index = index;
    }

    void message() {
        cout << "Ne postoi PhD student so indeks " << index << endl;
    }
};


class Trud {
protected:
    char TypeOfTrud;
    int ReleaseYear;

    //void copy
    void copy(const Trud &other) {
        this->ReleaseYear = other.ReleaseYear;
        this->TypeOfTrud = other.TypeOfTrud;
    }

public:
    //2 in 1
    Trud(char TypeOfTrud = 'A', int ReleaseYear = 0) {
        this->ReleaseYear = ReleaseYear;
        this->TypeOfTrud = TypeOfTrud;
    }

    //copy construtor
    Trud(const Trud &other) {
        copy(other);
    }

    //get trud
    char getTrud() {
        return TypeOfTrud;
    }

    //destructior
    ~Trud() {}

    friend class Student;

    //operator >>
    friend istream &operator>>(istream &in, Trud &other) {
        in >> other.TypeOfTrud;
        in >> other.ReleaseYear;
        return in;
    }

    //get releaseyear
    int getYearReleased() {
        return ReleaseYear;
    }

    //set trud
    void settrud(char a) {
        TypeOfTrud = a;
    }
};

class Student {
protected:
    char StudentName[30];
    int Index;
    int YearEnrolled;
    int *ListOfMarks;
    int NumMarks;

    //void copy
    void copy(const Student &other) {
        strcpy(this->StudentName, other.StudentName);
        this->Index = other.Index;
        this->YearEnrolled = other.YearEnrolled;
        this->ListOfMarks = new int[other.NumMarks];
        this->NumMarks = other.NumMarks;
        for (int i = 0; i < other.NumMarks; i++) {
            this->ListOfMarks[i] = other.ListOfMarks[i];
        }
    }

public:
    //default
    Student() {
        this->StudentName[0] = '\0';
        this->Index = 0;
        this->YearEnrolled = 0;
        this->ListOfMarks = nullptr;
        this->NumMarks = 0;
    }

    //2 in 1
    Student(char *StudentName, int Index, int YearEnrolled, const int *ListOfMarks, int NumMarks) {
        strcpy(this->StudentName, StudentName);
        this->Index = Index;
        this->YearEnrolled = YearEnrolled;
        this->NumMarks = NumMarks;
        this->ListOfMarks = new int[NumMarks];
        for (int i = 0; i < NumMarks; i++) {
            this->ListOfMarks[i] = ListOfMarks[i];
        }
    }

    //copy construcotr
    Student(const Student &other) {
        copy(other);
    }

    //oeprator =
    Student &operator=(const Student &other) {
        if (this != &other) {
            delete[] ListOfMarks;
            copy(other);
        }
        return *this;
    }

    //rang()
    virtual float rang() {
        if (NumMarks == 0)
            return 0;
        int sum = 0;
        for (int i = 0; i < NumMarks; i++) {
            sum += ListOfMarks[i];
        }
        //cout<<endl<<"Sum:"<<sum<<" NumMarks: "<<NumMarks<<endl;
        return float(sum) / NumMarks;
    }

    //operator <<
    friend ostream &operator<<(ostream &out, Student &other) {
        out << other.Index << " " << other.StudentName << " " << other.YearEnrolled << " " << other.rang() << endl;
        return out;
    }

    //year ennorlee
    int getYearEnrolled() {
        return YearEnrolled;
    }

    //desctrutor
    ~Student() {
        delete[] ListOfMarks;
    }

    //get index
    int getIndex() {
        return Index;
    }
};

class PhDStudent : public Student {
protected:
    Trud *Labours;
    int NumLabours;
    static float C;
    static float J;

    //void copy
    void copy(const PhDStudent &other) {
        Student::copy(other);
        //Trud::copy(other);
        this->NumLabours = other.NumLabours;
        this->Labours = new Trud[other.NumLabours];
        for (int i = 0; i < other.NumLabours; i++) {
            this->Labours[i] = other.Labours[i];
        }
    }

public:
    //3 in 2
    PhDStudent(char *StudentName = (char *) "", int Index = 0, int YearEnrolled = 0, int *ListOfMarks = nullptr,
               int NumMarks = 0, Trud *Labours = nullptr, int NumLabours = 0)
            : Student(StudentName, Index, YearEnrolled, ListOfMarks, NumMarks) {
        this->Labours = new Trud[NumLabours];
        this->NumLabours = NumLabours;
        for (int i = 0; i < NumLabours; i++) {
            this->Labours[i] = Labours[i];
        }
    }

    //copy contrutor
    PhDStudent(const PhDStudent &other) {
        copy(other);
    }

    //operator =
    PhDStudent &operator=(const PhDStudent &other) {
        if (this != &other) {
            delete[] Labours;
            copy(other);
        }
        return *this;
    }

    //rang()
    float rang() override {
        if (NumLabours == 0)
            return 0;
        float sum = Student::rang();
        for (int i = 0; i < NumLabours; i++) {
            //Student *temp=dynamic_cast<Student*>(Labours[i]);
            if (Labours[i].getTrud() == 'c' || Labours[i].getTrud() == 'C')
                sum += C;
            else if (Labours[i].getTrud() == 'j' || Labours[i].getTrud() == 'J')
                sum += J;
            else
                continue;
            //cout<<endl<<"Labours type: "<<Labours[i].getTrud()<<endl;
        }
        //cout<<endl<<"Sum:"<<sum<<" NumMarks: "<<NumMarks<<endl;
        return sum;
    }

    //oeprator =
    friend ostream &operator<<(ostream &out, PhDStudent &other) {
        out << other.Index << " " << other.StudentName << " " << other.YearEnrolled << " " << other.rang() << endl;
        return out;
    }

    //operator +=
    PhDStudent &operator+=(Trud &other) {
        if (YearEnrolled > other.getYearReleased())
            throw Exception("Ne moze da se vnese dadeniot trud");

        Trud *NewTrud = new Trud[NumLabours + 1];

        for (int i = 0; i < NumLabours; i++) {
            NewTrud[i] = Labours[i];
        }

        NewTrud[NumLabours++] = other;
        delete[] Labours;
        Labours = NewTrud;

        return *this;
    }

    //get labout
    Trud getTrud(int n) {
        return Labours[n];
    }

    //destrutor
    ~PhDStudent() {
        delete[] Labours;
    }

    //set for static
    static void setC(float X) {
        C = X;
    }

    static void setJ(float X) {
        J = X;
    }
};

float PhDStudent::C = 1;
float PhDStudent::J = 3;


int main() {
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;
        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        int flag = 0;
        for (int i = 0; i < n_tr; i++) {
            if (niza[i]->getIndex() == indeks) {
                PhDStudent *tmp = dynamic_cast<PhDStudent *>(niza[i]);
                if (tmp) {
                    try {
                        *tmp += t;
                        flag = 1;
                    } catch (Exception &e) {
                        e.print();
                    }
                }
            }
        }
        if (flag == 0)
            cout << "Ne postoi PhD student so indeks " << indeks << endl;
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        for (int i = 0; i < n_tr; i++) {
            if (niza[i]->getIndex() == indeks) {
                PhDStudent *tmp = dynamic_cast<PhDStudent *>(niza[i]);
                if (tmp) {
                    try {
                        *tmp += t;
                    } catch (Exception &e) {
                        e.print();
                    }
                }
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        int flag = 1;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];

        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            try {
                if (god_tr > god) {
                    flag = 0;
                    throw Exception("Ne moze da se vnese dadeniot trud");
                }
            } catch (Exception &e) {
                e.print();
            }
            if (flag == 0) {
                tip = 'x';
                Trud t(tip, god_tr);
                trud[j] = t;
            } else {
                Trud t(tip, god_tr);
                trud[j] = t;
            }
        }
//        try {
//            for(int i=0;i<n_tr;i++)
//            {
//                if(trud[i].getYearReleased()<god)
//                {
//                    trud[i].settrud('X');
//                    throw Exception("Ne moze da se vnese dadeniot trud");
//                }
//            }
//        }catch(Exception &e) {
//            e.print();
//        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
//        try{
//            for (int i = 0; i < n_tr; i++) {
//                if (t.getYearReleased() > niza[i]->getYearEnrolled())
//                {
//                    throw Exception("Ne moze da se vnese dadeniot trud");
//                }
//            }
//        }catch (Exception &e){
//            e.print();
//            t.settrud('x');
//        }
        for (int i = 0; i < n_tr; i++) {
            if (niza[i]->getIndex() == indeks) {
                PhDStudent *tmp = dynamic_cast<PhDStudent *>(niza[i]);
                if (tmp) {
                    try {
                        *tmp += t;
                    } catch (Exception &e) {
                        e.print();
                    }
                }
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setC(conf);
        PhDStudent::setJ(journal);
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}