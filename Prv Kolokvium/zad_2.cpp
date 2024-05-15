#include <iostream>
#include <cstring>

using namespace std;

class List {
private:
    int *nizaBroevi;
    int brojBroevi;

    void copy(const List &l) {
        this->brojBroevi = l.brojBroevi;
        this->nizaBroevi = new int[l.brojBroevi];
        for (int i = 0; i < l.brojBroevi; ++i) {
            nizaBroevi[i] = l.nizaBroevi[i];
        }
    }

public:
    //constructor, sopy, operator =
    List() {
        brojBroevi = 0;
        nizaBroevi = nullptr;
    }

    //constructor
    List(int nizaBroevi[], int brojBroevi) {
        this->brojBroevi = brojBroevi;
        this->nizaBroevi = new int[brojBroevi];
        for (int i = 0; i < brojBroevi; ++i) {
            this->nizaBroevi[i] = nizaBroevi[i];
        }
    }

    //copy
    List(const List &l) {
        copy(l);
    }

    //operator=
    List &operator=(const List &l) {
        if (this != &l) {
            delete[]nizaBroevi;
            copy(l);
        }
        return *this;
    }

    void pecati() {
        cout << brojBroevi << ": ";
        for (int i = 0; i < brojBroevi; i++) {
            cout << nizaBroevi[i] << " ";
        }
        cout << "sum: " << sum() << " average: " << average() << "\n";
    }

    int sum() {
        int sum = 0;
        for (int i = 0; i < brojBroevi; ++i) {
            sum += nizaBroevi[i];
        }
        return sum;
    }

    double average() {
        return (double) sum() / brojBroevi;
    }

    ~List() {
        delete[]nizaBroevi;
    }
};

class ListContainer {
private:
    List *nizaListi;
    int brojElementi;
    int counter;

    //copy
    void copy(const ListContainer &l) {
        this->brojElementi = l.brojElementi;
        this->counter = l.counter;
        this->nizaListi = new List[l.brojElementi];
        for (int i = 0; i < brojElementi; ++i) {
            nizaListi[i] = l.nizaListi[i];
        }
    }

public:
    ListContainer() {
        this->nizaListi = new List[0];
        this->brojElementi = 0;
        this->counter = 0;
    }

    //copy
    ListContainer(const ListContainer &l) {
        copy(l);
    }

    //operator=
    ListContainer &operator=(const ListContainer &l) {
        if (this != &l) {
            delete[] nizaListi;
            copy(l);
        }
        return *this;
    }

    ~ListContainer() {
        delete[]nizaListi;
    }

    void print() {
        if (brojElementi <= 0) {
            cout << "The list is empty";
        }
        for (int i = 0; i < brojElementi; ++i) {
            nizaListi[i].pecati();
        }
        cout << "Sum: " << sum() << " Average: " << average() << "\n";
        cout << "Successful attempts: " << brojElementi << " Failed attempts: " << (counter - brojElementi) << "\n";
    }

    void addNewList(List l) {
        counter++;
        int sum = 0;
        List *temp = new List[brojElementi + 1];
        for (int i = 0; i < brojElementi; ++i) {
            if (nizaListi[i].sum() == l.sum()) {
                return;
            }
            temp[i] = nizaListi[i];
        }
        temp[brojElementi++] = l;
        delete[] nizaListi;
        nizaListi = temp;
    }

    int sum() {
        int sum = 0;
        for (int i = 0; i < brojElementi; ++i) {
            sum += nizaListi[i].sum();
        }
        return sum;
    }

    double average() {
        double average = 0;
        for (int i = 0; i < brojElementi; ++i) {
            average = nizaListi[i].sum();
        }
        return (double) sum() / average;
    }

};

int main() {

    ListContainer lc;
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int n;
        int niza[100];

        cin >> n;

        for (int j = 0; j < n; j++) {
            cin >> niza[j];

        }

        List l = List(niza, n);

        lc.addNewList(l);
    }


    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "Test case for operator =" << endl;
        ListContainer lc1;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1 = lc;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1.sum();
        lc1.average();

    } else {
        lc.print();
    }
}