//
// Created by mrozi on 5/18/2024.
//
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

// TODO...

class Image {
protected:
    char *NameImage;
    char UserImage[50];
    int Width;
    int Height;

    //void copy
    void copy(const Image &other) {
        this->NameImage = new char[strlen(other.NameImage) + 1];
        strcpy(this->NameImage, other.NameImage);
        strcpy(this->UserImage, other.UserImage);
        this->Height = other.Height;
        this->Width = other.Width;
    }

public:
    //default
    Image() {
        NameImage = new char[11];
        strcpy(NameImage, "untitled");
        strcpy(UserImage, "unknown");
        Width = 800;
        Height = 800;
    }

    //arguments 1
    Image(char *NameImage) {
        this->NameImage = new char[strlen(NameImage) + 1];
        strcpy(this->NameImage, NameImage);
        strcpy(UserImage, "unknown");
        Width = 800;
        Height = 800;
    }

    //arguments 2
    Image(char *NameImage, char *UserImage) {
        this->NameImage = new char[strlen(NameImage) + 1];
        strcpy(this->NameImage, NameImage);
        strcpy(this->UserImage, UserImage);
        Width = 800;
        Height = 800;
    }

    //arguments 3
    Image(char *NameImage, char *UserImage, int Width, int Height) {
        this->NameImage = new char[strlen(NameImage) + 1];
        strcpy(this->NameImage, NameImage);
        strcpy(this->UserImage, UserImage);
        this->Height = Height;
        this->Width = Width;
    }

    //copy construcotr
    Image(const Image &other) {
        copy(other);
    }

    //opeator =
    Image &operator=(const Image &other) {
        if (this != &other) {
            delete[] NameImage;
            copy(other);
        }
        return *this;
    }

    //destrucor
    ~Image() {
        delete[] NameImage;
    }

    //file size
    virtual int fileSize() {
        return Width * Height * 3;
    }

    //opeator <<
    friend ostream &operator<<(ostream &out, Image &other) {
        out << other.NameImage << " " << other.UserImage << " " << other.fileSize() << endl;
        return out;
    }

    //opeator >
    bool operator>(Image &other) const {
        if ((this->Height * this->Width) > (other.Height * other.Width))
            return true;
        else
            return false;
    }
};

class TransparentImage : public Image {
protected:
    bool SupportsTrans; // 0-no 1-yes
    bool construct = false; // 0-no 2-yes
public:
    //defauutl
    TransparentImage() {
        NameImage = new char[strlen("untitled") + 1];
        strcpy(NameImage, "untitled");
        strcpy(UserImage, "unknown");
        Width = 800;
        Height = 800;
        SupportsTrans = false;
    }

    //arguments
    TransparentImage(char *NameImage, char *UserImage, int Width, int Height, bool SupportsTrans)
            : Image(NameImage, UserImage, Width, Height) {
        this->SupportsTrans = SupportsTrans;
        this->construct = true;
    }

    //file size
    int fileSize() {
        if (SupportsTrans == 0 && construct == 1)
            return (Width * Height) + (Width * Height) / 8;
        else
            return Width * Height * 4;
    }

    //opeator <<
    friend ostream &operator<<(ostream &out, TransparentImage &other) {
        out << other.NameImage << " " << other.UserImage << " " << other.fileSize() << endl;
        return out;
    }
};

class Folder {
private:
    char NameFolder[255];
    char UserName[50];
    Image **CollectionImages;
    int NumImages;

    //void copy
    void copy(const Folder *other) {
        strcpy(this->NameFolder, other->NameFolder);
        strcpy(this->UserName, other->UserName);
        this->NumImages = other->NumImages;
        this->CollectionImages = new Image *[other->NumImages];
        for (int i = 0; i < NumImages; i++) {
            this->CollectionImages[i] = other->CollectionImages[i];
        }
    }

public:
    //2 in 1
    Folder(char *NameFolder = (char *) "", char *UserName = (char *) "") {
        strcpy(this->NameFolder, NameFolder);
        strcpy(this->UserName, UserName);
        this->CollectionImages = nullptr;
        this->NumImages = 0;
    }

    //copy constrcotr
    Folder(const Folder &other) {
        copy(&other);
    }

    //operator =
    Folder &operator=(const Folder &other) {
        if (this != &other) {
//            for(int i=0;i<NumImages;i++)
//                delete CollectionImages[i];
            delete[] CollectionImages;
            copy(&other);
        }
        return *this;
    }

    //operrator +=
    Folder &operator+=(Image &other) {
        TransparentImage *temp2 = dynamic_cast<TransparentImage *>(&other);
        if (temp2) {
            //cout<<"entered a Transperent image in += opeartor - - -- - -"<<endl;
            Image **NewGame = new Image *[NumImages + 1];
            for (int i = 0; i < NumImages; i++) {
                NewGame[i] = CollectionImages[i];
            }
            NewGame[NumImages++] = temp2;
            delete[] CollectionImages;
            CollectionImages = NewGame;
            return *this;
        } else {
            //cout<<"entered a Normal image in += opeartor - - -- - -"<<endl;
            Image **NewImage = new Image *[NumImages + 1];
            for (int i = 0; i < NumImages; i++) {
                NewImage[i] = CollectionImages[i];
            }
            NewImage[NumImages++] = &other;
            delete[] CollectionImages;
            CollectionImages = NewImage;
            return *this;
        }
    }

    //folder size
    int folderSize() {
        int sum = 0;
        for (int i = 0; i < NumImages; i++)
            sum += CollectionImages[i]->fileSize();
        return sum;
    }

    //opeaor <<
    friend ostream &operator<<(ostream &out, Folder &other) {
        out << other.NameFolder << " " << other.UserName << endl;
        out << "--" << endl;
        for (int i = 0; i < other.NumImages; i++) {
            TransparentImage *temp = dynamic_cast<TransparentImage *>(other.CollectionImages[i]);
            if (temp)
                out << *temp;
            else
                out << *other.CollectionImages[i];
        }
        out << "--" << endl;
        out << "Folder size: " << other.folderSize() << endl;
        return out;
    }

    //dewtrutor
    ~Folder() {
        for (int i = 0; i < NumImages; i++) {
            delete CollectionImages[i];
        }
        delete[] CollectionImages;
    }

    //get max
    Image *getMaxFile() {
        Image *temp = CollectionImages[0];
        for (int i = 0; i < NumImages; i++) {
            if (temp->fileSize() < CollectionImages[i]->fileSize())
                temp = CollectionImages[i];
        }
        return temp;
    }

    //opeartro []
    Image *operator[](int x) {
        return CollectionImages[x];
    }

    friend void max_folder_size(Folder *Folders, int n);
};

void max_folder_size(Folder *Folders, int n) {
    int MaxI = 0, MaxSize = Folders[0].folderSize();
    for (int i = 1; i < n; i++) {
        if (MaxSize < Folders[i].folderSize()) {
            MaxSize = Folders[i].folderSize();
            MaxI = i;
        }
    }
    cout << Folders[MaxI].NameFolder << " " << Folders[MaxI].UserName << endl;
    cout << "--" << endl;
    for (int i = 0; i < Folders[MaxI].NumImages; i++) {
        cout << *Folders[MaxI].CollectionImages[i];

    }
    cout << "--" << endl;
    cout << "Folder size: " << MaxSize;
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc == 1) {
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout << f1;

        Image f2(name);
        cout << f2;

        Image f3(name, user_name);
        cout << f3;

        Image f4(name, user_name, w, h);
        cout << f4;
    } else if (tc == 2) {
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout << tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout << tf4;
    } else if (tc == 3) {
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout << f3;
    } else if (tc == 4) {
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout << dir;
    } else if (tc == 5) {
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout << *(dir.getMaxFile());
    } else if (tc == 6) {
        // Testing operator [] for folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout << *dir[sub];
    } else if (tc == 7) {
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i = 0; i < folders_num; ++i) {
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image *f;
            TransparentImage *tf;

            int sub, fileType;

            while (1) {
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >> fileType;
                if (fileType == 1) { // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name, user_name, w, h);
                    dir += *f;
                } else if (fileType == 2) {
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name, user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }
        //Trgnano e taj << operator ziti marulata ne rabote so nego
        //cout<<max_folder_size(dir_list, folders_num);
        max_folder_size(dir_list, folders_num);
    }
    return 0;
};