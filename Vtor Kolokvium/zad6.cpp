//
// Created by mrozi on 5/18/2024.
//
#include <iostream>
#include <cstring>

using namespace std;


class ExistingGame {
protected:
    char Message[100];
public:
    //deafuitlt
    ExistingGame() {
        strcpy(this->Message, "The game is already in the collection");
    }

    //message
    void message() {
        cout << Message << endl;
    }
};

class Game {
public:
    char NameGame[100];
    float Price;
    bool BoughtOnDiscount;
public:
    //argumetns
    Game(char *NameGame = (char *) "", float Price = 0.0, bool BoughtOnDiscount = false) {
        strcpy(this->NameGame, NameGame);
        this->Price = Price;
        this->BoughtOnDiscount = BoughtOnDiscount;
    }

    //oepatrotr <<
    friend ostream &operator<<(ostream &out, Game &other) {
        if (other.BoughtOnDiscount)
            out << "Game: " << other.NameGame << ", regular price: $" << other.Price << ", bought on sale" << endl;
        else
            out << "Game: " << other.NameGame << ", regular price: $" << other.Price << endl;
        return out;
    }

    //opeator >>
    friend istream &operator>>(istream &in, Game &other) {
        in.get();
        in.getline(other.NameGame, 100);
        in >> other.Price >> other.BoughtOnDiscount;
        return in;
    }

    //price
    virtual int price() {
        if (BoughtOnDiscount)
            return Price * 0.3F;
        return Price;
    }

    friend class User;
};

class SubscriptionGame : public Game {
protected:
    float MonthlyFee;
    int Month;
    int Year;
public:
    //arguemtns
    SubscriptionGame(char *NameGame = (char *) "", float Price = 0.0, bool BoughtOnDiscount = false,
                     float MonthlyFee = 0.0, int Month = 1, int Year = 2012)
            : Game(NameGame, Price, BoughtOnDiscount) {
        this->MonthlyFee = MonthlyFee;
        this->Month = Month;
        this->Year = Year;
    }

    //opearotr <<
    friend ostream &operator<<(ostream &out, SubscriptionGame &other) {
        if (other.BoughtOnDiscount)
            out << "Game: " << other.NameGame << ", regular price: $" << other.Price << ", bought on sale"
                << ", monthly fee: $" << other.MonthlyFee << ", purchased: " << other.Month << "-" << other.Year
                << endl;
        else
            out << "Game: " << other.NameGame << ", regular price: $" << other.Price << ", monthly fee: $"
                << other.MonthlyFee << ", purchased: " << other.Month << "-" << other.Year << endl;
        return out;
    }

    //opeator >>
    friend istream &operator>>(istream &in, SubscriptionGame &other) {
        in.get();
        in.getline(other.NameGame, 100);
        in >> other.Price >> other.BoughtOnDiscount;
        in >> other.MonthlyFee;
        in >> other.Month >> other.Year;
        return in;
    }

    //price
    int price() {
        int StatingPrice = Game::price();
        int Months;
        if (Year < 2018)
            Months = (12 - Month) + (2017 - Year) * 12 + 5;
        else
            Months = 5 - Month;
        return StatingPrice + (Months * MonthlyFee);
    }

    friend class User;
};

class User {
protected:
    char UserName[100];
    Game **Games;
    int NumGames;

    //void copy
    void copy(const User &other) {
        strcpy(this->UserName, other.UserName);
        this->NumGames = other.NumGames;
        this->Games = new Game *[other.NumGames];
        for (int i = 0; i < NumGames; i++) {
            this->Games[i] = other.Games[i];
        }
    }

public:
    //arguments
    User(char *UserName = (char *) "Kiro") {
        strcpy(this->UserName, UserName);
        Games = nullptr;
        NumGames = 0;
    }

    //copy method
    User(const User &other) {
        copy(other);
    }

    //operator =
    User &operator=(const User &other) {
        if (this != &other) {
            for (int i = 0; i < NumGames; i++)
                delete Games[i];
            delete[] Games;
            copy(other);
        }
        return *this;
    }

    //opeator +=
    User &operator+=(Game &other) {
        for (int i = 0; i < NumGames; i++) {
            if (!strcmp(Games[i]->NameGame, other.NameGame))
                throw ExistingGame();
        }

        Game **Newgame = new Game *[NumGames + 1];

        for (int i = 0; i < NumGames; i++) {
            Newgame[i] = Games[i];
        }

        SubscriptionGame *temp = dynamic_cast<SubscriptionGame *>(&other);

        if (temp)
            Newgame[NumGames++] = temp;
        else
            Newgame[NumGames++] = &other;

        delete[] Games;
        Games = Newgame;

        return *this;
    }

    //operator <<
    friend ostream &operator<<(ostream &out, User &other) {
        out << endl << "User: " << other.UserName << endl;
        for (int i = 0; i < other.NumGames; i++) {
            SubscriptionGame *temp = dynamic_cast<SubscriptionGame *>(other.Games[i]);
            if (temp)
                out << "- " << *temp;
            else
                out << "- " << *other.Games[i];
        }
        out << endl;
        return out;
    }

    //total_spent
    int total_spent() {
        int sum = 0;
        for (int i = 0; i < NumGames; i++) {
            sum += Games[i]->price();
        }
        return sum;
    }

    //destruccotr
    ~User() {
        for (int i = 0; i < NumGames; i++)
            delete Games[i];
        delete[] Games;
    }
};


int main() {
    int test_case_num;

    cin >> test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1) {
        cout << "Testing class Game and operator<< for Game" << std::endl;
        cin.get();
        cin.getline(game_name, 100);
        //cin.get();
        cin >> game_price >> game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout << g;
    } else if (test_case_num == 2) {
        cout << "Testing class SubscriptionGame and operator<< for SubscritionGame" << std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin >> game_price >> game_on_sale;

        cin >> sub_game_monthly_fee;
        cin >> sub_game_month >> sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout << sg;
    } else if (test_case_num == 3) {
        cout << "Testing operator>> for Game" << std::endl;
        Game g;

        cin >> g;

        cout << g;
    } else if (test_case_num == 4) {
        cout << "Testing operator>> for SubscriptionGame" << std::endl;
        SubscriptionGame sg;

        cin >> sg;

        cout << sg;
    } else if (test_case_num == 5) {
        cout << "Testing class User and operator+= for User" << std::endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >> num_user_games;

        try {

            for (int i = 0; i < num_user_games; ++i) {

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1) {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin >> game_price >> game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                } else if (game_type == 2) {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin >> game_price >> game_on_sale;

                    cin >> sub_game_monthly_fee;
                    cin >> sub_game_month >> sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                                             sub_game_year);
                }

                //cout<<(*g);


                u += (*g);
            }
        } catch (ExistingGame &ex) {
            ex.message();
        }

        cout << u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    } else if (test_case_num == 6) {
        cout << "Testing exception ExistingGame for User" << std::endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >> num_user_games;

        for (int i = 0; i < num_user_games; ++i) {

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1) {
                cin.get();
                cin.getline(game_name, 100);

                cin >> game_price >> game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            } else if (game_type == 2) {
                cin.get();
                cin.getline(game_name, 100);

                cin >> game_price >> game_on_sale;

                cin >> sub_game_monthly_fee;
                cin >> sub_game_month >> sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                                         sub_game_year);
            }

            //cout<<(*g);

            try {
                u += (*g);
            }
            catch (ExistingGame &ex) {
                ex.message();
            }
        }

        cout << u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    } else if (test_case_num == 7) {
        cout << "Testing total_spent method() for User" << std::endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >> num_user_games;

        for (int i = 0; i < num_user_games; ++i) {

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1) {
                cin.get();
                cin.getline(game_name, 100);

                cin >> game_price >> game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            } else if (game_type == 2) {
                cin.get();
                cin.getline(game_name, 100);

                cin >> game_price >> game_on_sale;

                cin >> sub_game_monthly_fee;
                cin >> sub_game_month >> sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                                         sub_game_year);
            }

            //cout<<(*g);


            u += (*g);
        }

        cout << u;

        cout << "Total money spent: $" << u.total_spent() << endl;
    }
}