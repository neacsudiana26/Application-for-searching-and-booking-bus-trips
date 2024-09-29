#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <sstream>
#include <vector>

using namespace std;

// algoritm RSA criptare parola
int gcd(int a, int h)
{
    int temp;
    while (1)
    {
        temp = a % h;
        if (temp == 0)
            return h;
        a = h;
        h = temp;
    }
}

string RSA(string message)
{
    double p = 67;
    double q = 13;

    string encryptedMessage;

    double n = p * q;

    double e = 2;
    double phi = (p - 1) * (q - 1);
    while (e < phi)
    {
        if (gcd(e, phi) == 1)
            break;
        else
            e++;
    }

    for (int i = 0; i < message.length(); i++)
    {
        double msg = static_cast<double>(message[i]);

        double c = pow(msg, e);
        c = fmod(c, n);

        char encryptedLetter = static_cast<char>(c);

        encryptedMessage.push_back(encryptedLetter);
    }

    return encryptedMessage;
}

bool isChar(char c)
{

    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool isDigit(const char c)
{

    return (c >= '0' && c <= '9');
}

bool isBigChar(const char c)
{

    return (c >= 'A' && c <= 'Z');
}

bool isValid(string email)
{

    if (!isChar(email[0]))
    {
        return 0;
    }

    int at = -1, dot = -1;

    for (int i = 0; i < email.length(); i++)
    {
        if (email[i] == '@')
            at = i;
        else if (email[i] == '.')
            dot = i;
    }

    if (at == -1 || dot == -1)
        return 0;

    if (at > dot)
        return 0;

    return !(dot >= (email.length() - 1));
}

bool containsNumbers(const string &str)
{
    for (char c : str)
    {
        if (isDigit(c))
        {
            return true;
        }
    }
    return false;
}

bool containsBigChar(const string &str)
{
    for (char c : str)
    {
        if (isBigChar(c))
        {
            return true;
        }
    }
    return false;
}

string departureStation(bool cf)
{

    ifstream cities;
    string oras;
    bool oras_gasit;

    cities.open("Romania_orase.txt");
    string oras_plecare;

    bool dep = false, dest = false;
    cout << "Orasul in care doriti sa ajungeti este :";
    while (dep == false)
    {
        cin >> oras_plecare;
        try
        {
            while (getline(cities, oras))
                if (!oras.compare(oras_plecare))
                    throw dep;
            oras_gasit = true;
            dep = true;
        }

        catch (bool dep)
        {
            cout << " Nu exista in baza de date! Mai incercati!" << endl;
            oras_plecare = departureStation(oras_gasit);
        }
    }
    cities.close();

    return oras_plecare;
}

string destinationStation(bool cf)
{

    ifstream cities;
    string oras;
    bool oras_gasit;

    cities.open("Romania_orase.txt");

    string oras_sosire;
    bool dep = false, dest = false;
    cout << "Orasul in care doriti sa ajungeti este : ";

    while (dep == false)
    {
        cin >> oras_sosire;
        try
        {
            while (getline(cities, oras))
                if (!oras.compare(oras_sosire))
                    throw dep;
            oras_gasit = true;
            dep = true;
        }

        catch (bool dep)
        {
            cout << " Nu exista in baza de date! Mai incercati!" << endl;
            oras_sosire = destinationStation(oras_gasit);
        }
    }

    cities.close();
    return oras_sosire;
}

// clasa autocarului in care vedem daca mai sunt locuri cand e la ce ora
class Autocar
{

public:
    string departure, destination, fumat;
    string zi, luna, an, ora;

    int gasireAutocar(vector<Autocar> &availableAutocar)
    {

        int k = 0;
        string departure, destination, an, luna, zi, ora, fumat;
        bool destFound = false, depFound = false;
        cout << "Optiunile dumneavostra sunt urmatoarele" << endl;
        ifstream f;

        f.open("autocar.csv");

        while (getline(f, departure, ','))
        {
            getline(f, destination, ',');
            getline(f, zi, ',');
            getline(f, luna, ',');
            getline(f, an, ',');
            getline(f, ora, ',');
            getline(f, fumat);
            if (!departure.compare(departure) && !destination.compare(destination))
            {
                depFound = true;
                destFound = true;

                availableAutocar[k].departure = departure;
                availableAutocar[k].destination = destination;
                availableAutocar[k].zi = zi;
                availableAutocar[k].luna = luna;
                availableAutocar[k].an = an;
                availableAutocar[k].ora = ora;
                availableAutocar[k].fumat = fumat;

                cout << "\nOptiunea  " << k + 1 << endl;
                cout << "De la  " << departure << " la " << destination << endl;
                cout << "Data plecarii " << zi << '/' << luna << '/' << an << " la ora " << ora << "\n";
                cout << "In acest autocar se poate fuma dispozitiv electronic? " << fumat << endl;

                k++;
            }
        }
        if (!depFound || !destFound)
        {

            cout << "Nu exista ruta! Mai incercati!\n\n";
            availableAutocar.clear();
            return gasireAutocar(availableAutocar);
        }

        return k;
    }
};

// realizarea clasei administrator cu verificare user, parola si adaugare sau stergere de rute de tren
class Operator
{
public:
    string username, password;
    string departure, destination, fumat;
    string zi, luna, an, ora;
    bool access;

    Operator()
    {
        access = 0;
    }

    void login()
    {
        cout << "Username: ";
        cin >> username;

        string line, user, pass;
        ifstream operators;
        string s;
        bool userFound = false;

        operators.open("operator.csv");

        while (getline(operators, user, ','))
        {
            getline(operators, pass);
            if (!user.compare(username))
            {
                userFound = true;
                cout << "Password: ";
                cin >> password;
                if (!pass.compare(password))
                {
                    cout << "Te-ai autentificat cu succes!\n\n";
                    return;
                }
                else
                {
                    cout << "Parola este incorecta, mai incearca!\n\n";
                    login();
                }
            }
        }
        if (!userFound)
        {
            cout << "Username-ul nu a fost gasit in baza de date!\n\n";
            login();
        }
    }

    void adaugare_Autocar()
    {
        int z, l, a, h;
        string f;
        bool d1 = false, d2 = false;

        departure = departureStation(d1);
        destination = destinationStation(d2);

        cout << "Data in care doriti sa calatoriti este :\n";
        cout << "Ziua: ";
        cin >> z;

        while (z < 1 || z > 30)
        {
            cout << "Ziua nu corespunde\n";
            cout << "Ziua: ";
            cin >> z;
        }

        cout << "Luna: ";
        cin >> l;
        while (l < 0 || l > 12)
        {
            cout << "Luna nu corespunde!\n";
            cout << "Luna: ";
            cin >> l;
        }

        cout << "An: ";
        cin >> a;
        while (a < 2023)
        {
            cout << "Anul nu corespunde!\n";
            cout << "An: ";
            cin >> a;
        }

        cout << "Ora: ";
        cin >> h;
        while (h > 23 || h < 0)
        {
            cout << "Ora nu corespunde\n";
            cout << "Ora:  ";
            cin >> h;
        }

        cout << "In acest autocar se poate fuma dispozitiv electronic :";
        cin >> f;

        ofstream autocarout;
        ifstream autocarin;
        autocarin.open("autocar.csv");
        autocarout.open("autocar.csv", ios::app);

        if (autocarin.is_open())
            autocarout << departure << ',' << destination << ',' << z << ',' << l << ',' << a << ',' << h << ',' << f << endl;

        cout << "Autocarul a fost introdus in baza de date\n";

        autocarin.close();
        autocarout.close();
    }

    void deleteAutocar()
    {

        cout << "Introduceti rutele autocarului pe care doriti sa-l stergeti din baza de date\n ";
        cin >> departure >> destination;

        string depart, dest;
        bool autocar_gasit = false;
        ifstream autocar;
        ofstream temp;

        temp.open("temp.csv");
        autocar.open("autocar.csv");

        while (getline(autocar, depart, ','))
        {
            getline(autocar, dest);
            if (depart.compare(departure) && dest.compare(destination))
            {
                temp << depart << ',' << dest << endl;
            }
            else
            {
                autocar_gasit = true;
            }
        }

        temp.close();
        autocar.close();
        remove("autocar.csv");
        rename("temp.csv", "autocar.csv");

        if (autocar_gasit)
        {
            cout << "Autocar sters din baza de date\n";
        }
        else
        {
            cout << "Autocarul nu fost gasit!\n\n";
            deleteAutocar();
        }
    }
};

// realizarea clasei utilizator care ori isi face cont nou, ori se logheaza, cauta o cursa sau isi face o rezervare
class Utilizator
{

public:
    string password, username;
    bool access;
    Utilizator()
    {
        access = 0;
    }

    void login()
    {
        cout << "username: ";
        cin >> username;

        string line, user, pass;
        ifstream util;
        string s;
        bool userFound = false;

        util.open("utilizatori.csv");

        while (getline(util, user, ','))
        {
            getline(util, pass);
            if (!user.compare(username))
            {
                userFound = true;
                cout << "Password: ";
                cin >> password;
                if (!pass.compare(RSA(password)))
                {
                    cout << "Te-ai autentificat cu succes!\n\n";
                    return;
                }
                else
                {
                    cout << "Parola este incorecta, mai incercati!\n\n";
                    login();
                }
            }
        }
        if (!userFound)
        {
            cout << "Username-ul nu a fost gasit in baza de date!\n\n";
            login();
        }
    }

    void sign_up()
    {
        string line, pass, user, passConfirm;
        string s;
        bool userFound = false;

        ofstream utilizatoriout;
        ifstream utilizatoriin;
        utilizatoriin.open("utilizatori.csv");
        utilizatoriout.open("utilizatori.csv", ios::app);

        cout << "Introduceti email-ul dumneavoastra(username): ";
        cin >> username;

        bool ans = isValid(username);

        if (ans)
        {
            while (getline(utilizatoriin, user, ','))
            {
                getline(utilizatoriin, pass);
                if (!user.compare(username))
                {
                    userFound = true;
                    cout << "In baza de date exista acest username! Incercati altul! \n Introduceti email-ul dumneavoastra(username):";
                    cin >> username;
                    utilizatoriin.clear();
                    utilizatoriin.seekg(0, ios::beg);
                }
            }

            cout << "Introduceti o parola ";
            cin >> password;

            while (!containsNumbers(password) && !containsBigChar(password))
            {
                cout << "Introduceti o parola mai puternica ";
                cin >> password;
            }

            cout << "Confirmati parola ";
            cin >> passConfirm;

            while (password != passConfirm)
            {

                cout << "\nParolele nu corespund! Mai incercati\n";
                cout << "Introduceti o parola ";
                cin >> password;
                cout << "Confirmati parola ";
                cin >> passConfirm;
            }

            if (utilizatoriin.is_open())
                utilizatoriout << username << ',' << RSA(password) << endl;
            else
                utilizatoriin.close();
            utilizatoriout.close();

            cout << "V-ati inregistrat cu succes\n";
        }
        else
        {
            cout << "\nVa rugam introduceti o adresa de email corespunzatoare formatului de tip mail !\n\n";
            sign_up();
        }
    }

    void reservare(string user)
    {
        string username = user;
        vector<Autocar> availableAutocar(200);
        Autocar search;
        int n;
        int choice;

        n = search.gasireAutocar(availableAutocar);

        bool ok = false;
        while (!ok)
        {
            cout << "Selectati ce autocar doriti\n";
            cin >> choice;
            choice--;
            if (choice > n - 1)
            {

                cout << choice + 1 << " Din pacate nu este o alegere valida! Mai incercati!\n";
            }
            else
            {

                ofstream reservare;
                reservare.open("reservari.csv", ios::app);
                reservare << username << ',' << availableAutocar[choice].departure << ',' << availableAutocar[choice].destination << ',' << availableAutocar[choice].zi << ',' << availableAutocar[choice].luna << ',' << availableAutocar[choice].an << ',' << availableAutocar[choice].ora << ',' << availableAutocar[choice].fumat << endl;
                cout << "Rezervarea a fost facuta cu succes! Va mai asteptam!\n\n";
                ok = true;
            }
        }
    }
};

void interfataPrincipala();
void meniuOperator();
int optiune_invalida(int);
void meniuUtilizator();
void operatorAfterLogin();
void utilizatorAfterLogin(string);

int optiune_invalida(int opt)
{
    int option;
    cout << "\nTe rugam sa introduci o alta optiune valida!\n";
    cout << "\nOptiunea ta este ___";
    cin >> option;
    return option;
}

void meniuOperator()
{

    int choice;
    Operator operator1;
    Autocar auto1;

    cout << "*************************************************************\n";
    cout << "*                                                           *\n";
    cout << "*      ==========================================           *\n";
    cout << "*                      Operator                             *\n";
    cout << "*      ==========================================           *\n";
    cout << "*                                                           *\n";
    cout << "*   1. Login                                                *\n";
    cout << "*   2. Revino la meniul principal                           *\n";
    cout << "*   3. Exit                                                 *\n";
    cout << "*                                                           *\n";
    cout << "*   Optiunea ta este ___                                    *\n";
    cout << "*                                                           *\n";
    cout << "*************************************************************\n";

    cin >> choice;

    while (choice < 1 || choice > 3)
    {
        choice = optiune_invalida(choice);
    }

    if (choice == 1)
    {

        cout << endl;
        operator1.login();
        operatorAfterLogin();
    }
    if (choice == 2)
    {
        interfataPrincipala();
    }

    if (choice == 3)
        return;
}

void meniuUtilizator()
{

    int choice;
    Utilizator utilizator1;
    Autocar auto1, auto22[100];
    string user;

    cout << "*************************************************************\n";
    cout << "*                                                           *\n";
    cout << "*      ==========================================           *\n";
    cout << "*                      Utilizator                           *\n";
    cout << "*      ==========================================           *\n";
    cout << "*                                                           *\n";
    cout << "*   1. Login                                                *\n";
    cout << "*   2. Inregistreaza-te aici                                *\n";
    cout << "*   3. Revino la meniul principal                           *\n";
    cout << "*   4. Exit                                                 *\n";
    cout << "*                                                           *\n";
    cout << "*   Optiunea ta este ___                                    *\n";
    cout << "*                                                           *\n";
    cout << "*************************************************************\n";

    cin >> choice;

    while (choice < 1 || choice > 4)
    {
        choice = optiune_invalida(choice);
    }

    if (choice == 1)
    {

        cout << endl;
        utilizator1.login();
        user = utilizator1.username;
        utilizatorAfterLogin(user);
    }

    if (choice == 2)
    {

        cout << endl;
        utilizator1.sign_up();

        meniuUtilizator();
    }

    if (choice == 3)
    {

        interfataPrincipala();
    }
    if (choice == 4)
        return;
}

void interfataPrincipala()
{

    int opt, choice;
    Utilizator utilizator1;

    cout << "*************************************************************\n";
    cout << "*                                                           *\n";
    cout << "*      ==========================================           *\n";
    cout << "*        Bine ai venit pe platforma unde poti               *\n";
    cout << "*          rezerva online un loc intr-unul din              *\n";
    cout << "*              autocarele noastre MAGIC                     *\n";
    cout << "*      ==========================================           *\n";
    cout << "*                                                           *\n";
    cout << "*   1. Sunt administrator MAGIC                             *\n";
    cout << "*   2. Sunt client MAGIC                                    *\n";
    cout << "*   3. Poate alta data :)                                   *\n";
    cout << "*                                                           *\n";
    cout << "*   Optiunea ta este ___                                    *\n";
    cout << "*                                                           *\n";
    cout << "*************************************************************\n";

    cin >> opt;

    while (opt < 0 || opt > 3)
    {
        opt = optiune_invalida(opt);
    }

    switch (opt)
    {

    case 1:
        meniuOperator();
        break;
    case 2:
        meniuUtilizator();
        break;
    case 3:
        return;
    }
}

void operatorAfterLogin()
{

    Operator auto1;
    Operator operator1;
    int choice;

    cout << "*************************************************************\n";
    cout << "*                                                           *\n";
    cout << "*      ==========================================           *\n";
    cout << "*                      Operator                             *\n";
    cout << "*      ==========================================           *\n";
    cout << "*                                                           *\n";
    cout << "*   1. Adauga o ruta                                        *\n";
    cout << "*   2. Sterge o ruta                                        *\n";
    cout << "*   3. Revino la meniul operatorului                        *\n";
    cout << "*   4. Exit                                                 *\n";
    cout << "*                                                           *\n";
    cout << "*   Optiunea ta este ___                                    *\n";
    cout << "*                                                           *\n";
    cout << "*************************************************************\n";

    cin >> choice;

    while (choice < 1 || choice > 4)
    {

        choice = optiune_invalida(choice);
    }

    if (choice == 1)
    {

        cout << endl;
        auto1.adaugare_Autocar();
        operatorAfterLogin();
    }

    if (choice == 2)
    {

        cout << endl;
        auto1.deleteAutocar();
        operatorAfterLogin();
        cout << "*      ||          *\n";
    }

    if (choice == 3)
    {
        meniuOperator();
    }

    if (choice == 4)
        return;
}

void utilizatorAfterLogin(string username)
{
    string user = username;
    int choice;
    Autocar auto1;
    vector<Autocar> auto2(100);
    Utilizator utilizator1;

    cout << "*************************************************************\n";
    cout << "*                                                           *\n";
    cout << "*      ==========================================           *\n";
    cout << "*                      Utilizator                           *\n";
    cout << "*      ==========================================           *\n";
    cout << "*                                                           *\n";
    cout << "*   1. Cauta un autocar aici                                *\n";
    cout << "*   2. Rezerva-ti un loc aici                               *\n";
    cout << "*   3. Revino la meniul utilizatorului                      *\n";
    cout << "*   4. Exit                                                 *\n";
    cout << "*                                                           *\n";
    cout << "*   Optiunea ta este ___                                    *\n";
    cout << "*                                                           *\n";
    cout << "*************************************************************\n";

    cin >> choice;

    while (choice < 1 || choice > 4)
    {
        choice = optiune_invalida(choice);
    }

    if (choice == 1)
    {

        cout << endl;
        auto1.gasireAutocar(auto2);
        utilizatorAfterLogin(user);
    }

    if (choice == 2)
    {

        cout << endl;
        utilizator1.reservare(user);
        utilizatorAfterLogin(user);
    }

    if (choice == 3)
    {
        meniuUtilizator();
    }

    if (choice == 4)
        return;
}

int main()
{
    interfataPrincipala();
}