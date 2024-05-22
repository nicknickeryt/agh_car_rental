#include "yaml-cpp/yaml.h"
#include <iostream>
#include <map>
#include <vector>
#include <filesystem>

#include "car.hpp"
#include "menu.hpp"
#include "client.hpp"
#include "utils.hpp"

using std::cin, std::cout, std::endl, std::string, std::map, std::vector;

string carsFile = "../res/cars.yml";

YAML::Node cars = YAML::LoadFile(carsFile);

Client client{};

string clientFile{};

void showAuth()
{
    cout << "\n| Car sharing |\n\n";

    int sel = promptSel({{0, "Zaloguj się"},
                         {1, "Utwórz nowy profi"},
                         {9, "Wyjdź"}});

    switch (sel)
    {
    case 0:
        showLogin();
        break;
    case 1:
        showRegister();
        break;
    case 9:
        return;
        break;
    default:
        showAuth();
        break;
    }
}

void showLogin()
{
    string login = promptInput("Podaj login");
    clientFile = "../res/clients/" + login + ".yml";

    if (!std::filesystem::exists(clientFile))
    {
        printErr("Nieprawidłowy login");
        showAuth();
    }
    else
    {

        Client client(clientFile);

        if (!client.checkPass(promptInput("Podaj hasło")))
        {
            printErr("Nieprawidłowe hasło");
            cout << client.getPass();
            showAuth();
        }
        else
            showHome();
    }
}

void showRegister()
{
    string login, pass, name, surname{};

    cout << "Wprowadź dane nowego profilu:\n\n";

    cout << "Podaj login:\n» ";
    cin >> login;

    if (std::filesystem::exists("../res/clients/" + login + ".yml"))
    {
        printErr("Konto z takim loginem już istnieje");
        showAuth();
    }

    cout << "Podaj hasło:\n» ";
    cin >> pass;

    cout << " Podaj imię:\n» ";
    cin >> name;
    cout << " Podaj nazwisko:\n» ";
    cin >> surname;

    client = Client(login, pass, name, surname);

    clientFile = "../res/clients/" + login + ".yml";

    client.writeToYaml(clientFile);
    cout << "Konto " << name << " " << surname << " zostało utworzone. Możesz się teraz zalogować.\n\n";
}

void showHome()
{
    if (client.isNull())
        client = Client(clientFile);

    cout << "Witaj " << client.getName() << " " << client.getSurname() << "!\n";

    int sel = promptSel({{1, "Wyświetl swój profil"},
                         {2, "Przeglądaj ofertę"},
                         {3, "Zarządzaj wypożyczonymi pojazdami"},
                         {8, "Wyloguj"},
                         {9, "Wyjdź"}});

    switch (sel)
    {
    case 1:
        showProfile();
        break;
    case 8:
        logout();
        break;
    case 9:
        return;
        break;
    default:
        showHome();
        break;
    }
}

void logout()
{
    clientFile = {};
    showAuth();
}

void deleteProfile()
{
    client.deleteProfile(clientFile);
    showAuth();
}

void showProfile()
{
    client.printInfo();

    int sel = promptSel({{0, "Usuń profil"},
                         {1, " Powrót do menu"}});

    switch (sel)
    {
    case 0:
        deleteProfile();
        logout();
        break;
    case 1:
        showHome();
        break;
    default:
        showProfile();
        break;
    }
}

void showMenu()
{

    vector<Car> cars = parseCarsFromYaml(carsFile);

    int i = 0;
    for (Car car : cars)
    {

        cout << " [" << i << "] " << "Samochód: " << car.getBrand() << " " << car.getModel() << endl
             << "     Cena: " << car.getPrice() << endl
             << "     Dostępna ilość: " << car.getQuantity() << endl;

        i++;
    }

    cout << "» Podaj numer samochodu, który chcesz wypożyczyć:" << endl;
    int n{};
    cin >> n;
}