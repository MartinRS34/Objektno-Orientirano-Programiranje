//
// Created by mrozi on 5/18/2024.
//
#include <iostream>
#include <cstring>

using namespace std;

class Book {
protected:
    char ISBN[20];
    char Title[50];
    char Author[30];
    float Price;

    //void copy
    void copy(const Book &other) {
        strcpy(this->ISBN, other.ISBN);
        strcpy(this->Title, other.Title);
        strcpy(this->Author, other.Author);
        this->Price = other.Price;
    }

public:
    //argumetns
    Book(char *ISBN = (char *) "", char *Title = (char *) "", char *Author = (char *) "", float Price = 0.0) {
        strcpy(this->ISBN, ISBN);
        strcpy(this->Title, Title);
        strcpy(this->Author, Author);
        this->Price = Price;
    }

    //copy method
    Book(Book &other) {
        copy(other);
    }

    //abstarct func
    virtual float bookPrice() = 0;

    //operator <<
    friend ostream &operator<<(ostream &os, Book &book) {
        os << book.ISBN << ": " << book.Title << ", " << book.Author << " " << book.bookPrice() << endl;
        return os;
    }    //operatro >
    bool operator>(Book &other) {
        if (this->bookPrice() > other.bookPrice())
            return true;
        else
            return false;
    }
};

class OnlineBook : public Book {
protected:
    char *URL;
    int SizeMB;

    //void copy
    void copy(const OnlineBook &other) {
        Book::copy(other);
        this->URL = new char[strlen(other.URL) + 1];
        strcpy(this->URL, other.URL);
        this->SizeMB = other.SizeMB;
    }

public:
    //arguemtns
    OnlineBook(char *ISBN = (char *) "", char *Title = (char *) "", char *Author = (char *) "", float Price = 0.0,
               char *URL = (char *) "", int SizeMB = 0)
            : Book(ISBN, Title, Author, Price) {
        this->URL = new char[strlen(URL) + 1];
        strcpy(this->URL, URL);
        this->SizeMB = SizeMB;
    }

    //copy methid
    OnlineBook(OnlineBook &other) {
        copy(other);
    }

    //opetareo =
    OnlineBook &operator=(const OnlineBook &other) {
        if (this != &other) {
            delete[] URL;
            copy(other);
        }
        return *this;
    }

    //destructor
    ~OnlineBook() {
        delete[] URL;
    }

    //price
    float bookPrice() {
        if (SizeMB >= 20)
            return Price * 1.20;
        return Price;
    }

    //operator <<
    friend ostream &operator<<(ostream &os, OnlineBook &book) {
        os << book.ISBN << ": " << book.Title << ", " << book.Author << " " << book.bookPrice() << endl;
        return os;
    }

    //set
    void setISBN(char *isbn) {
        strcpy(this->ISBN, isbn);
    }
};

class PrintBook : public Book {
protected:
    float Weight;
    bool InStock; // 0-no 1-yes
    //void copy
    void copy(const PrintBook &other) {
        Book::copy(other);
        this->Weight = other.Weight;
        this->InStock = other.InStock;
    }

public:
    //arguments
    PrintBook(char *ISBN = (char *) "", char *Title = (char *) "", char *Author = (char *) "", float Price = 0.0,
              float Weight = 0.0, bool InStock = false)
            : Book(ISBN, Title, Author, Price) {
        this->Weight = Weight;
        this->InStock = InStock;
    }

    //copy method
    PrintBook(PrintBook &other) {
        copy(other);
    }

    //book price
    float bookPrice() {
        if (Weight >= 0.7)
            return Price * 1.15;
        return Price;
    }

    //operator <<
    friend ostream &operator<<(ostream &os, PrintBook &book) {
        os << book.ISBN << ": " << book.Title << ", " << book.Author << " " << book.bookPrice() << endl;
        return os;
    }
};

void mostExpensiveBook(Book **books, int n) {
    int TotalOnline = 0, TotalPrint = 0, maxI = -1;
    float MaxPrice = 0.0;
    for (int i = 0; i < n; i++) {
        PrintBook *temp = dynamic_cast<PrintBook *>(books[i]);
        if (temp) {
            TotalPrint++;
            if (temp->bookPrice() > MaxPrice) {
                MaxPrice = temp->bookPrice();
                maxI = i;
            }
        } else {
            OnlineBook *temp2 = dynamic_cast<OnlineBook *>(books[i]);
            TotalOnline++;
            if (temp2->bookPrice() > MaxPrice) {
                MaxPrice = temp2->bookPrice();
                maxI = i;
            }
        }
    }
    cout << "FINKI-Education" << endl;
    cout << "Total number of online books: " << TotalOnline << endl;
    cout << "Total number of print books: " << TotalPrint << endl;
    cout << "The most expensive book is: " << endl;
    cout << *books[maxI];
}

int main() {

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2) {
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3) {
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4) {
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            } else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i < n; i++) delete books[i];
    delete[] books;
    return 0;
}