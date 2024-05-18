//
// Created by mrozi on 5/18/2024.
//
#include <cstring>
#include <iostream>

using namespace std;

// Your Code goes here

enum Size {
    small, //0
    medium, //1
    family //2
};

class Pizza {
protected:
    char NamePizza[20];
    char Ingridients[100];
    float BasePrice;
public:
    //arguemtns
    Pizza(char *NamePizza = (char *) "Kiro", char *Ingridients = (char *) "Martadela", float BasePrice = 0.0) {
        strcpy(this->NamePizza, NamePizza);
        strcpy(this->Ingridients, Ingridients);
        this->BasePrice = BasePrice;
    }
    //copy
    /*Pizza(const Pizza &other)
    {
        strcpy(this->Ingridients,other.Ingridients);
        strcpy(this->NamePizza,NamePizza);
        this->BasePrice=other.BasePrice;
    }*/
    //price methos
    virtual float price() = 0;

    //opeator <
    bool operator<(Pizza &other) {
        if (this->price() < other.price())
            return true;
        else
            return false;
    }

    //operator <<
    friend ostream &operator<<(ostream &out, Pizza &other) {
        out << other.NamePizza << ": " << other.Ingridients << " " << other.price();
        return out;
    }

    //print
    virtual void print() = 0;
};

class FlatPizza : public Pizza {
protected:
    Size PizzaSize;
public:
    FlatPizza(char *NamePizza = (char *) "Kiro", char *Ingridients = (char *) "Martadela", float BasePrice = 0.0,
              Size PizzaSize = small)
            : Pizza(NamePizza, Ingridients, BasePrice) {
        this->PizzaSize = PizzaSize;
    }

    //count price
    float price() {
        if (PizzaSize == 0)
            return BasePrice * 1.10;
        else if (PizzaSize == 1)
            return BasePrice * 1.20;
        else
            return BasePrice * 1.30;
    }

    //opeatror <<
    friend ostream &operator<<(ostream &out, FlatPizza &other) {
        out << other.NamePizza << ": " << other.Ingridients;
        if (other.PizzaSize == 0)
            out << ", small - " << other.price() << endl;
        else if (other.PizzaSize == 1)
            out << ", medium - " << other.price() << endl;
        else
            out << ", family - " << other.price() << endl;
        return out;
    }

    //print
    void print() {
        cout << *this;
    }
};

class FoldedPizza : public Pizza {
protected:
    bool FlowerWhite; // 0-no 1-yes
public:
    //argumetns
    FoldedPizza(char *NamePizza = (char *) "Kiro", char *Ingridients = (char *) "Martadela", float BasePrice = 0.0)
            : Pizza(NamePizza, Ingridients, BasePrice) {
        this->FlowerWhite = true;
    }

    //cpnt price
    float price() {
        if (FlowerWhite == 1)
            return BasePrice * 1.10;
        else
            return BasePrice * 1.30;
    }

    //opeatir <<
    friend ostream &operator<<(ostream &out, FoldedPizza &other) {
        out << other.NamePizza << ": " << other.Ingridients;
        if (other.FlowerWhite == 1)
            out << ", wf - " << other.price() << endl;
        else
            out << ", nwf - " << other.price() << endl;
        return out;
    }

    //set flower
    void setWhiteFlour(bool change) {
        this->FlowerWhite = change;
    }

    //print
    void print() {
        cout << *this;
    }
};

void expensivePizza(Pizza **Pizzas, int n) {
    int MaxI = 0, flag = 1;
    float MaxPrice = 0;
    for (int i = 0; i < n; i++) {
        if (flag) {
            MaxPrice = Pizzas[i]->price();
            MaxI = i;
            flag = 0;
        } else if (MaxPrice < Pizzas[i]->price()) {
            MaxPrice = Pizzas[i]->price();
            MaxI = i;
        }
    }
    Pizza *Print = Pizzas[MaxI];
    Print->print();
}

// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        int s;
        cin >> s;
        FlatPizza fp(name, ingredients, inPrice, (Size) s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp1;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp2;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout << "Lower price: " << endl;
        if (*fp1 < *fp2)
            cout << fp1->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp1 < *fp3)
            cout << fp1->price() << endl;
        else cout << fp3->price() << endl;

        if (*fp4 < *fp2)
            cout << fp4->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp3 < *fp4)
            cout << fp3->price() << endl;
        else cout << fp4->price() << endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name, 20);

                cin.getline(ingredients, 100);
                cin >> inPrice;
                int s;
                cin >> s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size) s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name, 20);
                cin.getline(ingredients, 100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza(name, ingredients, inPrice);
                if (j % 2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi, num_p);


    }
    return 0;
}