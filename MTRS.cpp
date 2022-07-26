#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <algorithm>
#include <conio.h>
using namespace std;

int counter, selection_movie;
const int WIDTH = 77, MAXMOVIES = 15;
char name[50], icno[25], email[40], phone_number[25], acc_num[25], password[25], month[25], year[25];

vector<string> movie_name(25);
vector<string> movie_day(25); 
vector<string> showtime1(25);
vector<string> showtime2(25);
vector<string> showtime3(25);

class Movie
{
public:
    string name, day, time1, time2, time3;
};

class Customer
{
protected:
    string name, email, phone_number;

public:
    void setName()
    {
        cout << "                  Enter your name : ";
        cin.ignore();
        getline(cin, name);
        cout << endl;
    }

    void setEmail()
    {
        int valid_email = 0;
        char temp;
        cout << "                  Enter your email address: ";
        cin >> email;
        cout << endl;

        int email_length = email.length();

        for (int i = 0; i < email.length(); ++i)
        {
            temp = email.at(i);
            if (temp == '@')
            {
                valid_email = 1;
            }
        }

        while (valid_email != 1)
        {
            cout << "               Enter a valid email address: ";
            cin.ignore();
            cin >> email;
            cout << endl;

            for (int i = 0; i < email.length(); ++i)
            {
                temp = email.at(i);
                if (temp == '@')
                {
                    valid_email = 1;
                }
            }
        }
    }

    void setPhonenumber()
    {
        cout << "                  Enter your phone number : ";
        cin >> phone_number;

        int phone_length = phone_number.length();

        while (phone_length != 10)
        {
            cout << endl;
            cout << "                Enter a valid phone number: ";
            cin >> phone_number;
            phone_length = phone_number.length();
        }

        cout << endl;
    }

    string getName()
    {
        return name;
    }

    string getPhonenumber()
    {
        return phone_number;
    }

    string getEmail()
    {
        return email;
    }

    ~Customer(){}; // destructor (dlt the obj)
};

class Food
{
private:
    string fname[10];
    float fprice[10];

public:
    void setFood(string food, float price, int arrElmt)
    {
        fname[arrElmt] = food;
        fprice[arrElmt] = price;
        // cout << food << " " << price;
    }

    void getFoodMenu(int arrSize)
    {
        for (int i = 0; i < arrSize; i++)
        {
            cout << "\t\t" << i + 1 << ") " << fname[i] << "\t\t\t  " << fprice[i] << endl;
        }
    }

    float getFoodPrice(int arrElmt)
    {
        return fprice[arrElmt];
    }
};

class Drink
{
public:
    string dname[10];
    float dprice[10];

    void setDrink(string drink, float price, int arrElmt)
    {
        dname[arrElmt] = drink;
        dprice[arrElmt] = price;
    }

    string getDrinkMenu(int arrSize)
    {
        for (int i = 0; i < arrSize; i++)
        {
            cout << "\t\t" << i + 1 << ") " << dname[i] << "\t\t\t " << dprice[i] << endl;
        }
    }

    float getDrinkPrice(int arrElmt)
    {
        return dprice[arrElmt];
    }
};

using MOVIE = Movie[MAXMOVIES];

void title();
bool CompareNames(Movie movie1, Movie movie2);
int ReadFile(MOVIE &movies, int &movieCount);
void showmovielist(MOVIE &movies, const int movieCount);
void time_checking(int time[], int i);
void showTicket();
void payment(float pay);
void movie_booking();
void ticket_cancel();
void food_drinks();
void displayMenu();
void add_movie();
void delete_movie();
void update_movie();
void management();
string member_login();

int main()
{
    time_t now = time(0);
    char *dt = ctime(&now);
    char selection_role;
    system("CLS");
    title();
    cout << "                  The local date and time is: " << dt << endl;
    cout << "                  ========================        ===========================        =======================\n"
            "                  * (A)  MOVIE BOOKING   *        * (B) TICKET CANCELLATION *        * (C) SNACKS & DRINKS *\n"
            "                  ========================        ===========================        =======================\n\n"
            "                  ========================        ========================\n"
            "                  * (D) MANAGE MOVIES    *         * (E)     QUIT       *\n"
            "                  =======================         ========================\n\n";

    do
    {
        cout << "                                                       SELECT AN OPTION: ";
        cin >> selection_role;
        cin.ignore(10000, '\n');
        selection_role = tolower(selection_role);
        if (selection_role < 'a' || selection_role > 'f')
            cout << "                                         You have entered a wrong selection. Try again.\n\n";
    } while (selection_role < 'a' || selection_role > 'f');

    if (selection_role == 'a')
    {
        movie_booking();
    }
    else if (selection_role == 'b')
    {
        ticket_cancel();
    }
    else if (selection_role == 'c')
    {
        food_drinks();
    }
    else if (selection_role == 'd')
    {
        management();
    }
    else
    {
        exit(1);
    }
}

void title()
{
    const int WIDTH = 88;
    const int WIDTH1 = 18;
    const string heading = "MOVIE TICKET RESERVATION SYSTEM (MTRS)";
    cout << "\n\n ";
    for (int i = 0; i < WIDTH1; i++)
    {
        cout << ' ';
    }
    for (int i = 0; i < WIDTH; i++)
    {
        cout << '*';
    }
    cout << "\n\n";
    cout << "                                            " << heading;
    cout << "\n\n ";
    for (int i = 0; i < WIDTH1; i++)
    {
        cout << ' ';
    }
    for (int i = 0; i < WIDTH; i++)
    {
        cout << '*';
    }
    cout << "\n\n";
}

bool CompareNames(Movie movie1, Movie movie2)
{
    if (movie2.name > movie1.name)
        return true;
    return false;   
}

int ReadFile(MOVIE &movies, int &movieCount)
{

    string file_name = "Movies.txt";
    int i = 0;                       
    ifstream movies_file(file_name);

    if (!movies_file)
    {
        cout << "\n File "
             << "\"" << file_name << "\""
             << " did not open." << endl;
    }

    while (getline(movies_file, movies[i].name, '|'))
    {
        getline(movies_file, movies[i].day, '|');
        getline(movies_file, movies[i].time1, '|');
        getline(movies_file, movies[i].time2, '|');
        getline(movies_file, movies[i].time3);
        movies_file.clear();

        i++;
    }

    movieCount = i + 1; // added
}

void showmovielist(MOVIE &movies, const int movieCount)
{
    system("CLS");
    ifstream movie("Movies.txt");
    title();
    cout << "\n ";
    for (int i = 0; i < WIDTH; i++)
    {
        cout << '=';
    }
    cout << endl
         << "| SERIAL |";
    for (int i = 0; i < 55; i++)
    {
        cout << '=';
    }
    cout << "|  SHOWTIME  | " << '\n'
         << "| NUMBER |                 MOVIE NAME                    |  DAY  |  AVAILABLE | " << '\n'
         << ' ';
    for (int i = 0; i < WIDTH; i++)
    {
        cout << '=';
    }
    cout << endl;

    int j = 1;
    int i = 1;

    sort(movies, movies + movieCount, CompareNames);

    int m;
    for (m = 1; m < movieCount; m++)
    {
        if (movies[m + 1].name == movies[m].name)
        {
            cout << "   (" << m << ")     " << std::left << setw(40) << setw(45) << movies[m].name << "    " << setw(7) << movies[m].day << "(" << j << ") " << movies[m].time1 << "\n"
                 << setw(68) << "                                                                   (" << j + 1 << ") " << movies[m].time2 << "\n"
                 << setw(67) << "                                                                   (" << j + 2 << ") " << movies[m].time3 << "\n";
        }

        else
        {
            cout << "   (" << m << ")     " << std::left << setw(40) << setw(45) << movies[m].name << "    " << setw(7) << movies[m].day << "(" << j << ") " << movies[m].time1 << "\n"
                 << setw(68) << "                                                                   (" << j + 1 << ") " << movies[m].time2 << "\n"
                 << setw(68) << "                                                                   (" << j + 2 << ") " << movies[m].time3 << "\n";

            cout << ' ';
            for (int i = 0; i < WIDTH; i++)
            {
                cout << '=';
            }
            cout << endl;
        }

        movie_name[i] = movies[m].name;
        movie_day[i] = movies[m].day; // added
        showtime1[i] = movies[m].time1;
        showtime2[i] = movies[m].time2;
        showtime3[i] = movies[m].time3;
        i = i + 1;
        j = 1;
    }

    counter = m;
}

void time_checking(int time[], int i)
{
    while (!cin >> time[i])
    {
        cout << endl;
        cout << " Enter a valid time: ";
        cin.clear();
        cin.ignore(25, '\n');
        cin >> time[i];
    }

    while ((time[i] > 2400) || (time[i] < 0))
    {
        cout << endl;
        cout << " You have entered a wrong time for movie. Enter again!!" << endl;
        cout << " Enter the time for " << i << " show  (HHMM): ";
        cin >> time[i];
    }
}

void showTicket()
{

    int ticket_num;

    ticket_num = rand() % 9999999999 + 10000000000;
    cout << endl
         << "        --------------------------------------" << endl;
    cout << "        |              " << ticket_num << "             |" << endl;
    cout << "        --------------------------------------" << endl
         << endl;
    cout << " This is your ticket number !!! " << endl;
    cout << " Thank you !!!" << endl;
}

void payment(float pay)
{
    char resp;
    string card_type, card_num, ccv;
    cout << " Select the payment method: " << endl;
    cout << "                 (A) CASH  " << endl;
    cout << "                 (B) DEBIT CARD " << endl;
    cout << "                 (C) CREDIT CARD " << endl
         << endl;
    cout << " Your option [A, B, C] :  ";
    cin >> resp;
    while ((resp != 'A') && (resp != 'a') && (resp != 'B') && (resp != 'b') && (resp != 'C') && (resp != 'c'))
    {
        cout << " Please select a correct option [ a, b, c] : ";
        cin >> resp;
    }

    system("ClS");
    title();
    if (resp == 'A' || resp == 'a')
    {
        cout << " You have selected to pay on cash" << endl;
        cout << " The amount you need to pay is : RM " << pay << endl
             << endl;
    }

    else
    {
        if (resp == 'B' || resp == 'b')
        {
            card_type = "debit card";
        }
        else
        {
            card_type = "credit card";
        }

        cout << "You have selected " << card_type << " to pay !!" << endl
             << endl;
        cout << "The amount you need to pay is : RM " << pay << endl
             << endl;
        cout << "Enter your " << card_type << " number: ";
        cin >> card_num;
        cout << "\n Enter your CCV : ";
        cin >> ccv;
    }
}

void displayMenu()
{
    Food *pfood = new Food;
    Drink *pdrink = new Drink;

    int lines;
    char foodname[25], foodprice[25], drinkname[25], drinkprice[25], r;
    string fname_string, dname_string;
    float fprice_float, dprice_float;

foodmenu:
    fstream food, drink;
    food.open("Food.txt", ios::in);
    drink.open("Drink.txt", ios::in);

    if (!food || !drink)
    {
        cout << "Cannot open input files\n";
        return;
    }

    cout << setw(57) << setfill('-') << '\n';
    cout << "|                  SNACKS AND DRINKS                   | \n";
    cout << setw(57) << setfill('-') << '\n';
    cout << "|              SNACKS AVAILABLE                | PRICE | \n";
    cout << setw(57) << setfill('-') << '\n';

    char count = '0';
    string line;

    ifstream file("Food.txt");
    while (!file.eof())
    {
        getline(file, line);
        count++;
    }

    lines = count - 48;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    int i = 0;
    while (i < lines)
    {
        food.getline(foodname, 25, '|');
        food.getline(foodprice, 25);
        fname_string = foodname;
        sscanf(foodprice, "%f", &fprice_float);

        pfood->setFood(fname_string, fprice_float, i);
        i++;
    }

    pfood->getFoodMenu(lines);

    cout << setw(57) << setfill('-') << '\n';
    cout << "|              DRINKS AVAILABLE                | PRICE | \n";
    cout << setw(57) << setfill('-') << '\n';

    int j = 0;
    while (j < lines)
    {
        drink.getline(drinkname, 25, '|');
        drink.getline(drinkprice, 25);
        dname_string = drinkname;
        sscanf(drinkprice, "%f", &dprice_float);

        pdrink->setDrink(dname_string, dprice_float, j);
        j++;
    }

    pdrink->getDrinkMenu(lines);

    char fod; // food or drink
    int fchoice, fqty, dchoice, dqty;
    float fprice, dprice, pay;

    cout << "\nDo you want to buy Food OR Drink? [f/d]: ";
    cin >> fod;
    fod = tolower(fod);

    while (fod != 'f' && fod != 'd')
    {
        cout << "\nWrong input. Please  enter again. \nDo you want to buy Food OR Drink? [f/d]: ";
        cin >> fod;
    }

    if (fod == 'f')
    {
        cout << "\nYou want to buy Food. Which Food do you want to buy? : ";
        while (!(cin >> fchoice) || fchoice > lines || fchoice < 1)
        {
            cout << "Enter a valid input: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << endl;
        cout << "Enter its quantity that you want to buy: ";
        while (!(cin >> fqty) || fqty < 1)
        {
            cout << "Enter a valid input: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        fprice = pfood->getFoodPrice(fchoice - 1);
        pay = fqty * fprice;
    }
    else
    {
        cout << "\nYou want to buy Drink. Which Drink do you want to buy? : ";
        while (!(cin >> dchoice) || dchoice > lines || dchoice < 1)
        {
            cout << "Enter a valid input: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << endl;
        cout << "Enter its quantity that you want to buy: ";
        while (!(cin >> dqty) || dqty < 1)
        {
            cout << "Enter a valid input: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        dprice = pdrink->getDrinkPrice(dchoice - 1);
        pay = dqty * dprice;
    }

    cout << "\nWould you wish to [B]ack, [P]roceed or [R]eselect? :";
    cin >> r;
    r = tolower(r);

    while (r != 'b' && r != 'p' && r != 'r')
    {
        cout << "\nSorry! You have entered a wrong selection. Please try again.\n\n";
        cout << "Would you wish to [B]ack, [P]roceed or [R]eselect? :";
        cin >> r;
    }

    if (r != 'b')
    {
        if (r != 'p')
        {
            fchoice = 0;
            fqty = 0;
            dchoice = 0;
            dqty = 0;
            system("CLS");
            goto foodmenu;
        }
        else
        {
            payment(pay);
            showTicket();
        }
    }
    else
    {
        fchoice = 0;
        fqty = 0;
        dchoice = 0;
        dqty = 0;
        system("CLS");
        main();
    }
    cout << endl;
}

void food_drinks()
{
    char r;

    system("CLS");
    title();
    displayMenu();

    cout << "\nPress 'b' or 'B' to return to the main menu:";
    cin >> r;
    r = tolower(r);

    while (r != 'b')
    {
        cout << "\nSorry! You have entered a wrong selection. Please try again.\n\n";
        cout << "\nPress 'b' or 'B' to return to the main menu:";
        cin >> r;
    }

    system("CLS");
    main();

    cout << endl;
}

void movie_booking()
{
    Customer *c1 = new Customer;
    fstream movie;
    movie.open("Movies.txt", ios::in);
    string showtime;
    int seat_price, lines, select_movie, selection_show;
    char response, r, r2, pay_res, reuse_response, seat_type, temp, seat_row[10], seat_column[10], response1;
    float remaining = 0, cash = 0;
    srand(time(0));
    int ticket_num; 

login:
    ticket_num = (rand() % 99999) + 10000;
    system("CLS");
    title();
    cout << "\n\t\t\t\t*************************\n"
         << "\t\t\t\t   *    LOGIN PAGE   * \n"
         << "\t\t\t\t************************* \n\n\n";

    cout << "\t\t\tPRESS ANY KEY TO CONTINUE: ";
    cin >> response;
    response = tolower(response);
    system("CLS");
    title();

    c1->setName();
    c1->setEmail();
    c1->setPhonenumber();

movies:
    int movieCount{}, readStatus{};
    MOVIE movies;
    if (readStatus = ReadFile(movies, movieCount))
        showmovielist(movies, movieCount);
    cout << endl
         << endl;
    int p = sizeof(movie_name) / sizeof(movie_name[0]);

    cout << " Please select a movie [1,2,3....]: ";
    cin >> select_movie;
    cout << endl;

    while ((!cin >> select_movie) || (select_movie > counter - 1) || (select_movie < 1))
    {
        cout << " TRY AGAIN [1,2,3....]: ";
        cin.clear();
        cin.ignore(25, '\n');
        cin >> select_movie;
    }

    cout << "============== You have selected " << movie_name[select_movie] << ".=====================\n"
         << "\nWhich show you want to select for [SHOW(1) / SHOW(2) / SHOW(3)]: ";
    cin >> selection_show;

    while ((!cin >> selection_show) || (selection_show > 3) || (selection_show < 1))
    {
        cout << " TRY AGAIN [1,2,3....]: ";
        cin.clear();
        cin.ignore(25, '\n');
        cin >> selection_show;
    }

    if (selection_show == 1)
    {
        cout << "============== You have selected " << showtime1[select_movie] << ".=====================" << endl;
        showtime = showtime1[select_movie];
    }
    else if (selection_show == 2)
    {
        cout << "============== You have selected " << showtime2[select_movie] << ".=====================" << endl;
        showtime = showtime2[select_movie];
    }
    else
    {
        cout << "============== You have selected " << showtime3[select_movie] << ".=====================" << endl;
        showtime = showtime3[select_movie];
    }

    cout << "\nWould you wish to [B]ack, [P]roceed or [R]eselect? :";
    cin >> r;
    r = tolower(r);

    while (r != 'b' && r != 'p' && r != 'r')
    {
        cout << "\nSorry! You have entered a wrong selection. Please try again.\n\n";
        cout << "Would you wish to [B]ack, [P]roceed or [R]eselect? :";
        cin >> r;
    }

    if (r != 'b')
    {
        if (r != 'p')
        {
            int i = 0;
            select_movie = 0;
            selection_show = i;
            system("CLS");
            goto movies;
        }
        else
        {
            system("CLS");
            goto seats;
        }
    }
    else
    {
        int i = 0;
        selection_show = i;
        system("CLS");
        goto movies;
    }
    cout << endl;

seats:
    system("CLS");
    title();
    cout << "\t\t    ____________________________________________________________________________________\n"
         << "\t\t\t\t\t\t           SCREEN\n"
         << "\t\t    ____________________________________________________________________________________\n\n\n"
         << "\t\t    [A,1]          [A,2]          [A,3]          [A,4]          [A,5]          [A,6]\n\n"
         << "\t\t    [B,1]          [B,2]          [B,3]          [B,4]          [B,5]          [B,6]\n\n"
         << "\t\t    [C,1]          [C,2]          [C,3]          [C,4]          [C,5]          [C,6]\n\n"
         << "\t\t    [D,1]          [D,2]          [D,3]          [D,4]          [D,5]          [D,6]\n\n"
         << "\t\t    [E,1]          [E,2]          [E,3]          [E,4]          [E,5]          [E,6]\n\n\n\n";

    int seat_no = 0;
    cout << "Enter the number of seats you want to book [Maximum : 10 seats] : ";
    cin >> seat_no;

    while ((!cin >> seat_no) || (seat_no > 10) || (seat_no < 1))
    { // added
        cout << "\nError: Invalid seat numbers";
        cout << "\nEnter the number of seats you want to book: ";
        cin.clear();
        cin.ignore();
        cin >> seat_no;
    }

    bool check = false;
    for (int i = 0; i < seat_no; i++)
    {

        cout << "\nEnter the row of seat you would like to book for [ROW : A,B,C...]: ";
        cin >> seat_row[i];
        seat_row[i] = tolower(seat_row[i]);

        while (seat_row[i] != 'a' && seat_row[i] != 'b' && seat_row[i] != 'c' && seat_row[i] != 'd' && seat_row[i] != 'e')
        {
            cout << "Sorry! You have entered a wrong selection. Please try again.\n\n"
                 << "Enter the row of seat you would like to book for [ROW : A,B,C...]: ";
            cin >> seat_row[i];
        }

        cout << "\nEnter the column of seat you would like to book for [COLUMN : 1,2,3...]:  ";
        cin >> seat_column[i];

        while (seat_column[i] < '1' || seat_column[i] > '6')
        {
            cout << "Sorry! You have entered a wrong selection. Please try again.\n\n"
                 << "Enter the column of seat you would like to book for [COLUMN : 1,2,3...]:  ";
            cin >> seat_column[i];
        }
        for (int j = 0; j < i; j++)
        {
            if (seat_row[j] == seat_row[i] && seat_column[j] == seat_column[i])
            {
                check = true;
            }
            else
            {
                check = false;
            }
        }
        while (check)
        {
            cout << "Sorry, this seat has already been chosen.\n";
            cout << "Choose another seat again\n";

            cout << "Enter the row of seat you would like to book for [ROW : A,B,C...]: ";
            cin >> seat_row[i];
            seat_row[i] = tolower(seat_row[i]);

            while (seat_row[i] != 'a' && seat_row[i] != 'b' && seat_row[i] != 'c' && seat_row[i] != 'd' && seat_row[i] != 'e')
            {
                cout << "Sorry! You have entered a wrong selection. Please try again.\n\n"
                     << "Enter the row of seat you would like to book for [ROW : A,B,C...]: ";
                cin >> seat_row[i];
            }

            cout << "\nEnter the column of seat you would like to book for [COLUMN : 1,2,3...]:  ";
            cin >> seat_column[i];

            while (seat_column[i] < '1' || seat_column[i] > '6')
            {
                cout << "Sorry! You have entered a wrong selection. Please try again.\n\n"
                     << "Enter the column of seat you would like to book for [COLUMN : 1,2,3...]:  ";
                cin >> seat_column[i];
            }

            for (int j = 0; j < i; j++)
            {
                if (seat_row[j] == seat_row[i] && seat_column[j] == seat_column[i])
                {
                    check = true;
                }
                else
                {
                    check = false;
                }
            }
        }
    }

    cout << "\nYour selection of seat(s) is : ";
    for (int i = 0; i < seat_no; i++)
    {
        cout << "(" << seat_row[i] << "," << seat_column[i] << ")";
        if (i < (seat_no - 1))
        {
            cout << ", ";
        }
    }

    cout << "\nThere are two types of seats available:  (A) DELUXE (RM 18) \n"
         << "\t\t\t\t\t (B) NORMAL (RM 13)\n\n\n"
         << "Do you want further explanation about the type of seats available in our cinemas before selecting it? (Y/N) :";
    cin >> response1;
    response1 = tolower(response1);

    while (response1 != 'y' && response1 != 'n')
    {
        cout << "Sorry! You have entered a wrong selection. Please try again.\n\n"
             << "Do you want further explanation about the type of seats available in our cinemas before selecting it? (Y/N) :";
        cin >> response1;
    }

    if (response1 == 'y' || response1 == 'Y')
    {
        cout << "\n- 'DELUXE' seats provides a unique experience to the customers where they will be provided with food during the showtime.";
        cout << "\n- 'NORMAL' seats does not include the special privileges.\n";
    }

    cout << endl;
    cout << "Please select the type of seat (A/B): ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin >> seat_type;
    seat_type = tolower(seat_type);

    while (seat_type != 'a' && seat_type != 'b')
    {
        cout << "Sorry! You have entered a wrong selection. Please try again.\n\n"
             << "Please select the type of seat (A/B): ";
        cin >> seat_type;
    }

    if (seat_type == 'a')
        seat_price = 18.00 * seat_no;

    else
        seat_price = 13.00 * seat_no;

    cout << "Would you wish to [B]ack, [P]roceed or [R]eselect?\n";
    cin >> r2;

    while (r2 != 'b' && r2 != 'p' && r2 != 'r')
    {
        cout << "Sorry! You have entered a wrong selection. Please try again.\n\n"
             << "Would you wish to [B]ack, [P]roceed or [R]eselect? :";
        cin >> r2;
    }

    if ((r2 != 'b'))
        if ((r2 != 'p'))
        {
            char seat_row = 0, seat_column = 0, response = 0, seat_type = 0;
            int i = 0;
            selection_show = i;
            system("CLS");
            goto seats;
        }
        else
        {
            system("CLS");
            goto receipt;
        }
    else
    {
        char seat_row = 0, seat_column = 0, response = 0, seat_type = 0;
        system("CLS");
        goto movies;
    }
    cout << endl;

receipt:
    system("CLS");
    cout << "=========================================================\n"
         << "=                         RECEIPT                       =\n"
         << "---------------------------------------------------------\n"
         << "=                       MOVIE TICKET                    =\n"
         << "=========================================================\n\n"
         << "\nTicket No. : " << ticket_num << endl
         << "\nTo Mr/Ms " << c1->getName() << ",\n"
         << "\nYou have booked " << movie_name[select_movie] << " at " << showtime << ", " << movie_day[select_movie];

    cout << "\nYour selection of seat(s) is : ";
    for (int i = 0; i < seat_no; i++)
    {
        cout << "(" << seat_row[i] << "," << seat_column[i] << ")";
        // The comma will not be print out after last seat
        if (i < (seat_no - 1))
        {
            cout << ", ";
        }
    }

    cout << "\nPrice of seat(s) : "
         << "RM " << seat_price << endl
         << endl;
    cout << "---------------------------------------------------------" << endl
         << left << setw(15) << "\nAmount to PAY : RM " << seat_price << endl;

    payment(seat_price);

    fstream booking;
    booking.open("Booking.txt", ios::app);

    booking << ticket_num << '|' << c1->getName() << '|' << c1->getPhonenumber() << '|' << c1->getEmail() << '|';
    booking << movie_name[select_movie] << '|' << movie_day[select_movie] << '|' << showtime << '|' << seat_type << '|';

    for (int i = 0; i < seat_no; i++)
    {
        booking << '(' << seat_row[i] << ',' << seat_column[i] << ')';
    }
    booking << '\n';

    cout << endl
         << endl;
    movie.close();

    cout << "\nDo you wish to use it again, [y]es or [n]o ?\n";
    cout << "\nResponse : ";
    cin >> reuse_response;
    reuse_response = tolower(reuse_response);

    while (reuse_response != 'y' && reuse_response != 'n')
    {
        cout << "\nWrong selection. Enter Again !!"
             << "\nResponse : ";
        cin >> reuse_response;
    }
    booking.close();
    if (reuse_response == 'n')
    {
        delete c1;
        char seat_row = 0, seat_column = 0, response = 0, seat_type = 0, MTRS_response = 0;
        system("CLS");
        main();
    }
    else

    {
        goto login;
    }
}

void add_movie()
{
    system("CLS");
    char name[25], day[25];
    int time[3] = {}, i = 0;
    fstream movie;
    movie.open("Movies.txt", ios::app);

    title();
    cout << "Adding new movie!!" << endl
         << endl;

    cin.ignore();
    cout << " Enter the movie name: ";
    cin.getline(name, 25);
    cout << endl;
    cout << " Enter the day of the showtime: ";
    cin.getline(day, 25);
    cout << endl;
    cout << " Enter the time for First show  (HHMM): ";
    cin >> time[0];
    cout << endl;
    time_checking(time, i);
    i = 1;

    cout << " Enter the time for Second show (HHMM): ";
    cin >> time[1];
    cout << endl;
    time_checking(time, i);
    i = 2;

    cout << " Enter the time for Third show  (HHMM): ";
    cin >> time[2];
    cout << endl;
    time_checking(time, i);

    movie << name << '|' << day << '|' << std::setfill('0') << std::setw(4) << time[0] << '|' << std::setfill('0')
     << std::setw(4) << time[1] << '|' << std::setfill('0') << std::setw(4) << time[2] << '\n';
    cout << endl;
    cout << "You are done, Manager!";
    movie.close();
}

void delete_movie()
{
    fstream movie, extra, deleted_movies;
    int lines, select_movie;
    char day[25], name[25], time1[25], time2[25], time3[25];
    movie.open("Movies.txt", ios::in);
    extra.open("Extra.txt", ios::out);
    deleted_movies.open("deleted_movies.txt", ios::out);

    int movieCount{}, readStatus{};
    MOVIE movies;
    if (readStatus = ReadFile(movies, movieCount))
        showmovielist(movies, movieCount);

    char count = '0';
    string line;

    ifstream file("Movies.txt");
    while (!file.eof())
    {
        getline(file, line);
        count++;
    }

    lines = count - 48;

    cout << " Please select a movie [1,2,3....]: ";
    cin >> select_movie;
    cout << endl;

    while ((select_movie > counter - 1) || (select_movie < 1) || (!cin >> select_movie))
    {
        cout << " TRY AGAIN [1,2,3....]: ";
        cin.clear();
        cin.ignore(25, '\n');
        cin >> select_movie;
    }

    cout << "============== You have selected to delete " << movie_name[select_movie] << " (" 
    << movie_day[select_movie] << ") "
         << "=====================\n";

    int i = 0;

    for (int i = 0; i < lines; i++)
    {
        movie.getline(name, 25, '|');
        movie.getline(day, 25, '|');
        movie.getline(time1, 25, '|');
        movie.getline(time2, 25, '|');
        movie.getline(time3, 25);

        if (name == movie_name[select_movie] && day == movie_day[select_movie] && 
        time1 == showtime1[select_movie] && time2 == showtime2[select_movie] && time3 == showtime3[select_movie])
        {
            deleted_movies << movie_name[select_movie] << " (" << movie_day[select_movie] << ") " << showtime1[select_movie] 
            << " " << showtime2[select_movie] << " " << showtime1[select_movie] << '\n';
            continue;
        }
        else
        {
            extra << name << '|' << day << '|' << time1 << '|' << time2 << '|' << time3 << '\n';
        }
    }

    extra.close();
    movie.close();
    movie.open("Movies.txt", ios::out);
    extra.open("Extra.txt", ios::in);

    for (int y = 0; y < (lines - 2); y++)
    {
        extra.getline(name, 25, '|');
        extra.getline(day, 25, '|');
        extra.getline(time1, 25, '|');
        extra.getline(time2, 25, '|');
        extra.getline(time3, 25);
        movie << name << '|' << day << '|' << time1 << '|' << time2 << '|' << time3 << '\n';
    }

    extra.close();
    movie.close();
    deleted_movies.close();

    cout << "\n You have done deleting the showtime manager!!! \n";
    remove("Extra.txt");
}

void update_movie()
{
    fstream movie;
    int lines;
    char selection_movie1, name[25], day[25], time1[25], time2[25], time3[25];
    int select_movie;

    movie.open("Movies.txt", ios::in);
    int movieCount{}, readStatus{};
    MOVIE movies;
    if (readStatus = ReadFile(movies, movieCount))
        showmovielist(movies, movieCount);
    cin.ignore();
    cout << endl;
    

    char count = '0';
    string line;

    ifstream file("Movies.txt");
    while (!file.eof())
    {
        getline(file, line);
        count++;
    }

    lines = count - 48;

    int p = sizeof(movie_name) / sizeof(movie_name[0]);

    cout << " Please select a movie [1,2,3....]: ";
    cin >> select_movie;
    cout << endl;

    while (!cin >> select_movie)
    {
        cout << " TRY AGAIN [1,2,3....]: ";
        cin.clear();
        cin.ignore(25, '\n');
        cin >> select_movie;
    }

    while ((select_movie > counter - 1) || (select_movie < 1))
    {
        cout << " TRY AGAIN [1,2,3....]: ";
        cin >> select_movie;
    }

    cout << "============== You have selected to update " << movie_name[select_movie] << " (" 
    << movie_day[select_movie] << ") "
         << "=====================\n";
    cout << endl;

    for (int i = 0; i <= lines; i++)
    {
        movie.getline(name, 25, '|');
        movie.getline(day, 25, '|');
        movie.getline(time1, 25, '|');
        movie.getline(time2, 25, '|');
        movie.getline(time3, 25);

        if (name == movie_name[select_movie] && day == movie_day[select_movie] && time1 == showtime1[select_movie] 
        && time2 == showtime2[select_movie] && time3 == showtime3[select_movie])
        {
            cout << "Enter the day of the showtime: ";
            cin.ignore();
            string day1;
            cin >> day1;

            int time[3] = {}, x = 0;
            cout << " \nEnter the time for First show  (HHMM): ";
            cin >> time[0];
            time_checking(time, x);
            x = 1;

            cout << " \nEnter the time for Second show (HHMM): ";
            cin >> time[1];
            time_checking(time, x);
            x = 2;

            cout << " \nEnter the time for Third show  (HHMM): ";
            cin >> time[2];
            time_checking(time, x);
        }
    }
    movie.close();

    cout << "\n You have done editing the showtime manager!!! \n";
}

void management()
{
    system("CLS");
    title();
    string userName;
    string pass = "password";
    char userPassword[50];

    int loginAttempt = 0;

    cout << endl
         << endl;
    while (loginAttempt < 5)
    {
        cout << "\t\t\t\tPlease enter your user name: ";
        cin >> userName;
        cout << endl;
        cout << "\t\t\t\tPlease enter your user password: ";
        int a = 0;
        while (userPassword[a - 1] != '\r')
        {
            userPassword[a] = getch();
            if (userPassword[a - 1] != '\r')
            {
                cout << "*";
            }
            a++;
        }
        userPassword[a - 1] = '\0';

        if (userName == "Swathi" && userPassword == pass)
        {
            cout << "Welcome Swathi!" << endl;
            break;
        }
        else if (userName == "Sunidhi" && userPassword == pass)
        {
            cout << "Welcome Sunidhi!" << endl;
            break;
        }
        else
        {
            cout << "\n\n\t\t\t\tInvalid login attempt. Please try again.\n"
                 << '\n';
            loginAttempt++;
        }
    }

    if (loginAttempt == 5)
    {
        cout << "Too many login attempts! The program will now terminate.";
    }

    bool flag = true;

    while (flag)
    {
        system("CLS");
        title();
        cout << endl
             << endl
             << endl;
        cout << "                                          (1) Enter a new movie " << endl
             << endl
             << endl;
        cout << "                                          (2) Update the showtime for a movie" << endl
             << endl
             << endl;
        cout << "                                          (3) Delete a movie " << endl
             << endl
             << endl;

        char c;
        cout << "Enter your selection manager: ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> c;

        switch (c)
        {
        case '1':
            add_movie();
            break;
        case '2':
            update_movie();
            break;
        case '3':
            delete_movie();
            break;

        default:
            cout << endl;
            cout << "Please input a correct selection\n";
            cout << "If you continue to use program press ' y ',if no please press any input to restart\n ";
        }

        cout << " if you continue to use program press ' y ', if no please press any key to go back to the main menu \n ";
        char f;
        cin >> f;
        f = tolower(f);
        if (f != 'y')
        {
            main();
        }
    }
}

void ticket_cancel(){

    fstream booking, cancelled_tickets;

    string search_receipt;
    char ticket_num[25], name[25], phone[25], email[40], seat_type[25], movie[25], day[25], showtime[25], seat_booked[60];
    bool isExist = 0, isFound = 0;
    char response;

    do{
        int lines = 0;
        system("CLS");
        title();

        cout << "\t\t\t\t\t\tTICKET CANCELLATION\n\n";
        cout << "\n\t\tEnter your ticket no. : ";
        cin >> search_receipt;

        booking.open("Booking.txt", ios::in);
        while(!booking.eof())
        {
            booking.getline(ticket_num,25,'|');
            booking.getline(name,25,'|');
            booking.getline(phone,25,'|');
            booking.getline(email,40,'|');
            booking.getline(movie,25,'|');
            booking.getline(day,25,'|');
            booking.getline(showtime,25,'|');
            booking.getline(seat_type,25,'|');
            booking.getline(seat_booked,60);

            if(ticket_num == search_receipt){
                isExist = 1;
                break;
            }
            else{
                isExist=0;
            }
        }
        booking.close();

        if(!isExist){
            cout << "\t\tRecord do not exist!" << endl;
        }
        else{
            booking.open("Booking.txt", ios::in);
            cancelled_tickets.open("cancelled_tickets.txt", ios::out);

            while(!booking.eof())
            {
                booking.getline(ticket_num,25,'|');
                booking.getline(name,25,'|');
                booking.getline(phone,25,'|');
                booking.getline(email,40,'|');
                booking.getline(movie,25,'|');
                booking.getline(day,25,'|');
                booking.getline(showtime,25,'|');
                booking.getline(seat_type,25,'|');
                booking.getline(seat_booked,60);

                if(ticket_num == search_receipt){

                    string s_type;
                    for(int i=0; i<1;i++){
                        if(seat_type[i] == 'a'){
                            s_type = "Deluxe";
                        }
                        if(seat_type[i] == 'b'){
                            s_type = "Normal";
                        }
                    }

                    cout << "\t\tRecord is found!\n\n"
                         << "\t\t=========================================================\n"
                         << "\t\t=                  BOOKING RECORD                       =\n"
                         << "\t\t=========================================================\n"
                         << "\n\t\tTicket No.     : " << ticket_num
                         << "\n\t\tName           : " << name
                         << "\n\t\tPhone no.      : " << phone
                         << "\n\t\tE-mail         : " << email
                         << "\n\t\tMovie selected : " << movie
                         << "\n\t\tDay            : " << day
                         << "\n\t\tShowtime       : " << showtime
                         << "\n\t\tSeat selected  : " << seat_booked
                         << "\n\t\tSeat type      : " << s_type << " seat\n"
                         << "\n\t\t---------------------------------------------------------" << endl;
                }
                else{
                    cancelled_tickets << ticket_num << '|' << name << '|' << phone << '|' << email << '|' << movie << '|'
                         << day << '|' << showtime << '|' << seat_type << '|' << seat_booked << '\n';
                }
                lines++;  // Count number of lines in the file
            }
            // Uncomment the next line to count the number of lines in .txt file (FOR TESTING PURPOSE ONLY)
            //cout << "Lines = " << lines << endl;;
            cancelled_tickets.close();
            booking.close();


            char ch;
            cout << "\t\tAre you sure you want to cancel your ticket booking?[Y/n]: ";
            cin >> ch;
            tolower(ch);

            while(ch!='y' && ch !='n'){
                cout << "\t\tWrong input! Are you sure you want to cancel your ticket booking?[Y/n]: ";
                cin >> ch;
                tolower(ch);
            }

            if(ch=='y'){
                lines = lines - 2;                  
                booking.open("Booking.txt",ios::out);
                cancelled_tickets.open("cancelled_tickets.txt",ios::in);
                for(int i=0; i<lines; i++){
                    cancelled_tickets.getline(ticket_num,25,'|');
                    cancelled_tickets.getline(name,25,'|');
                    cancelled_tickets.getline(phone,25,'|');
                    cancelled_tickets.getline(email,40,'|');
                    cancelled_tickets.getline(movie,25,'|');
                    cancelled_tickets.getline(day,25,'|');
                    cancelled_tickets.getline(showtime,25,'|');
                    cancelled_tickets.getline(seat_type,25,'|');
                    cancelled_tickets.getline(seat_booked,60);

                    booking << ticket_num << '|' << name << '|' << phone << '|' << email << '|' << movie << '|'
                            << day << '|' << showtime << '|' << seat_type << '|' << seat_booked << '\n';
                }
                cancelled_tickets.close();
                booking.close();
                cout << "\n\t\tTicket cancel successfully !!!";
            }
            else{
                cout << "\n\t\tTicket is not being cancelled." << endl;
            }

        }

        cout << "\n\n\t\tDo you want to use it again?[Y/n]: ";
        cin >> response;
        tolower(response);

        while(response!='y' && response!='n'){
            cout << "\n\t\tWrong selection. Enter Again !!"
                 << "\n\t\tResponse : ";
            cin >> response;
        }

    }while(response=='y');

    system("CLS");
    main();
}