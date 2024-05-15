//
// Created by mrozi on 4/7/2024.
//
#include<iostream>
#include<cstring>

using namespace std;
enum Extension {
    txt, pdf, exe

};

class File {
private:
    char *imeDatoteka;
    char *sopstevnik;
    Extension extension;
    int mb;

    void copy(const File &f) {
        this->imeDatoteka = new char[strlen(f.imeDatoteka) + 1];
        strcpy(this->imeDatoteka, f.imeDatoteka);
        this->sopstevnik = new char[strlen(f.sopstevnik) + 1];
        strcpy(this->sopstevnik, f.sopstevnik);
        this->extension = f.extension;
        this->mb = f.mb;
    }

public:
    //constructor 2in1
    File(const char *imeDatoteka = "", const char *sopstvenik = "", int mb = 0,
         Extension extension = txt) {//        File file(fileName, fileOwner, fileSize, (Extension) ext);
        this->imeDatoteka = new char[strlen(imeDatoteka) + 1];
        strcpy(this->imeDatoteka, imeDatoteka);
        this->sopstevnik = new char[strlen(sopstvenik) + 1];
        strcpy(this->sopstevnik, sopstvenik);
        this->extension = extension;
        this->mb = mb;
    }

    //SEKOGAS KOGA GO KREIRAME COPY CONSTRUCTOR VO PRIVATE SE POVIKUVA I VO PUBLIC!!!!
    File(const File &f) {
        copy(f);
    }

    ~File() {
        delete[]imeDatoteka;
        delete[]sopstevnik;
    }

    //operator=
    File operator=(const File &f) {
        if (this != &f) {
            delete[]imeDatoteka;
            copy(f);
        }
        return *this;
    }

    char *getImeDatoteka() const {
        return imeDatoteka;
    }

    char *getSopstevnik() const {
        return sopstevnik;
    }

    Extension getExtension() const {
        return extension;
    }

    int getMb() const {
        return mb;
    }

    void print() {
        cout << "File name: " << imeDatoteka << ".";
        switch (extension) {
            case Extension::pdf://namesto da imame case 0
                cout << "txt" << endl;
                break;
            case Extension::txt://case 1
                cout << "pdf" << endl;
                break;
            case Extension::exe://case 2
                cout << "exe" << endl;

        }


        cout << "File owner: " << sopstevnik << endl
             << "File size: " << mb << endl;
    }

    bool equals(const File &that) {
        return (strcmp(imeDatoteka, that.imeDatoteka) == 0) && (extension == that.extension) &&
               (strcmp(sopstevnik, that.sopstevnik) == 0);
    }

    bool equalsType(const File &that) {
        return (equals(that)) && (mb = that.mb);
    }
};

class Folder {
private:
    char *name;
    int brojDatoteki;
    File *file;

    //copy
    void copy(const Folder &f) {
        this->name = new char[strlen(f.name) + 1];
        strcpy(this->name, f.name);
        this->brojDatoteki = f.brojDatoteki;
        this->file = f.file;
    }

public:
    //constructor, copy, operator=
    //constructor
    Folder(char *name = "", int brojDatoteki = 0, File *file = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->brojDatoteki = brojDatoteki;
        this->file = file;
    }

    //copy
    Folder(const Folder &f) {
        copy(f);
    }

    //operator=
    Folder &operator=(const Folder &f) {
        if (this != &f) {
            delete[]name;
            delete[]file;
            copy(f);
        }
        return *this;
    }

    ~Folder() {
        delete[]name;
        delete[]file;
    }

    void print() {
        cout << "Folder name: " << name << endl;
        for (int i = 0; i < brojDatoteki; ++i) {
            cout << "File name: " << file[i].getImeDatoteka() << ".";
            switch (file->getExtension()) {
                case Extension::pdf://namesto da imame case 0
                    cout << "exe" << endl;
                    break;
                case Extension::txt://case 1
                    cout << "pdf" << endl;
                    break;
                case Extension::exe://case 2
                    cout << "txt" << endl;

            }
            cout << "File owner: " << file[i].getSopstevnik() << endl;
            cout << "File size: " << brojDatoteki << endl;
        }

    }

    //popravi
    void remove(const File &files) {
        for (int i = 0; i < brojDatoteki; ++i) {
            if (file[i].equals(files)) {
                // Move the last file to the position of the file to be removed
                file[i] = file[brojDatoteki - 1];
                brojDatoteki--;
                break; // Exit the loop after removing the first matching file
            }
        }
    }

    void add(File &files) {
        File *tempFiles = new File[brojDatoteki + 1];
        for (int i = 0; i < brojDatoteki; ++i) {
            tempFiles[i] = file[i];
        }
        tempFiles[brojDatoteki] = files;
        delete[] file;
        file = tempFiles;
        ++brojDatoteki;
    }

    //dodadeno
    void print1() {
        for (int i = 0; i < brojDatoteki; ++i) {
            file[i].print();
        }
    }
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    } else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    } else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
//    else {
//        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
//        char name[20];
//        cin >> name;
//        Folder folder(name);
//
//        int iter;
//        cin >> iter;
//
//        while (iter > 0) {
//            cin >> fileName;
//            cin >> fileOwner;
//            cin >> fileSize;
//            cin >> ext;
//
//            File file(fileName, fileOwner, fileSize, (Extension) ext);
//            folder.add(file);
//            iter--;
//        }
//        cin >> fileName;
//        cin >> fileOwner;
//        cin >> fileSize;
//        cin >> ext;
//
//        File file(fileName, fileOwner, fileSize, (Extension) ext);
//        folder.remove(file);
//        folder.print();
//    }
    return 0;
}
