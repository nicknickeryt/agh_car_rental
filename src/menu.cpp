#include "yaml-cpp/yaml.h"
#include <iostream>
#include <map>
#include <vector>
#include <filesystem>

#include "auth.hpp"
#include "car.hpp"
#include "menu.hpp"
#include "utils.hpp"

using std::cin, std::cout, std::endl, std::string, std::map, std::vector;

Client Menu::client = Client();
vector<Car> cars = Car::getAllCars();

void Menu::showLoginScreen()
{
    cout << "\n| Car sharing |\n\n";

    int sel = Utils::promptSel({{0, "Zaloguj się"},
                                {1, "Utwórz nowy profil"},
                                {9, "Wyjdź"}});
    switch (sel)
    {
    case 0:
        Auth::showLogin(client) == 1 ? showLoginScreen() : showHomeScreen();
        break;
    case 1:
        Auth::showRegister();
        showLoginScreen();
        break;
    case 9:
        return;
        break;
    default:
        showLoginScreen();
        break;
    }
}

void Menu::showHomeScreen()
{
    cout << "Witaj " << client.getName() << " " << client.getSurname() << "!\n";

    map<int, string> promptMap{{1, "Wyświetl swój profil"},
                               {2, "Przeglądaj ofertę"},
                               {8, "Wyloguj"},
                               {9, "Wyjdź"}};
    if (client.hasRented())
        promptMap[3] = "Zwróć: " + client.getRentCar().getBrand() + " " + client.getRentCar().getModel();

    int sel = Utils::promptSel(promptMap);

    switch (sel)
    {
    case 1:
        showProfile();
        break;
    case 2:
        showCars();
        break;
    case 3:
        tryUnrent();
        break;
    case 8:
        logout();
        break;
    case 9:
        return;
        break;
    default:
        showHomeScreen();
        break;
    }
}

void Menu::logout()
{
    client = Client();
    showLoginScreen();
}

void Menu::deleteProfile()
{
    client.deleteProfile();
    showLoginScreen();
}

void Menu::showProfile()
{
    client.printInfo();

    int sel = Utils::promptSel({{0, "Usuń profil"},
                                {9, "Powrót do menu"}});

    switch (sel)
    {
    case 0:
        deleteProfile();
        logout();
        break;
    case 9:
        showHomeScreen();
        break;
    default:
        showProfile();
        break;
    }
}

void Menu::showCars()
{
    cout << "\nDostępne samochody\n\n";

    int i = 1;
    for (Car car : cars)
    {

        cout << "  [" << i << "] " << car.getBrand() << " " << car.getModel() << endl
             << "      Cena: " << car.getPrice() << "zł/h" << endl
             << "      Dostępna ilość: " << car.getQuantity() << endl;

        i++;
    }

    cout << endl;

    int sel = Utils::promptSel({{0, "Wypożycz samochód"},
                                {9, "Powrót do menu"}});
    switch (sel)
    {
    case 0:
    {
        cout << "» Podaj numer samochodu, który chcesz wypożyczyć:" << endl;
        int n{};
        cin >> n;

        tryRent(n);

        break;
    }
    case 9:
        showHomeScreen();
        break;
    default:
        showCars();
        break;
    }
}

void Menu::tryUnrent()
{
    cout << "Zwrócono samochód.\n";
    showHomeScreen();
}
void Menu::tryRent(int n)
{
    int o = rentCar(n);

    switch (o)
    {
    case 0:
        cout << "Wypożyczono samochód.\n";
        break;
    case 1:
        Utils::printErr("Ten samochód nie jest aktualnie dostępny.");
        break;
    case 2:
        Utils::printErr("Nie masz pieniędzy, by wypożyczyć samochód.");
        break;
    case 3:
        Utils::printErr("Już masz wypożyczony samochód.");
        break;
    }
    showHomeScreen();
}

int Menu::rentCar(int n)
{
    Car car = cars[n];
    if (car.getQuantity() <= 0)
        return 1;
    if (Menu::client.getCredit() < 10)
        return 2;
    if (Menu::client.hasRented())
        return 3;

    Menu::client.rent(car);
    Menu::client.updateFile();
    return 0;
}