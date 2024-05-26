#include "yaml-cpp/yaml.h"
#include <iostream>
#include <map>
#include <vector>

#include "auth.h"
#include "car.h"
#include "menu.h"
#include "utils.h"
#include "conf.h"

using std::cin, std::cout, std::endl, std::string, std::map, std::vector;

Client Menu::client = Client();

vector<Car> cars;

void Menu::tryInit()
{
    if (!Utils::checkFileDir(RES_DIR, 1))
        Utils::printErr("Nie znaleziono katalogu zasobów. Utworzono domyślny.");
    if (!Utils::checkFileDir(CARS_FILE, 1))
        Utils::printErr("Nie znaleziono pliku konfiguracji samochodów. Utworzono domyślny.");
    if (!Utils::checkFileDir(CLIENTS_DIR, 1))
        Utils::printErr("Nie znaleziono katalogu danych klientów. Utworzono domyślny.");
    if (!Utils::checkFileDir(REPORTS_FILE, 1))
        Utils::printErr("Nie znaleziono pliku dziennika zgłoszeń. Utworzono domyślny.");
    showLoginScreen();
}

void Menu::showLoginScreen()
{
    if (Car::getAllCars(cars))
        return;

    cout << "\n| Car sharing |\n\n";

    int sel = Utils::promptSel({{0, "Zaloguj się"},
                                {1, "Utwórz nowy profil"},
                                {9, "Wyjdź"}});
    switch (sel)
    {
    case 0:
    {
        int ret = Auth::showLogin(client);
        switch (ret)
        {
        case 0:
            showHomeScreen();
            break;
        case 1:
            Utils::printErr("Nieprawidłowy login");
            showLoginScreen();
            break;
        case 2:
            Utils::printErr("Nieprawidłowe hasło");
            showLoginScreen();
            break;
        }
        break;
    }
    case 1:
    {
        if (Auth::showRegister())
            Utils::printErr("Konto z takim loginem już istnieje.");
        else
            cout << "Konto zostało utworzone. Możesz się teraz zalogować.\n\n";
        showLoginScreen();
        break;
    }
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

    Utils::checkTime(client);

    map<int, string> promptMap{{1, "Wyświetl swój profil"},
                               {2, "Przeglądaj ofertę"},
                               {7, "Zgłoś usterkę"},
                               {8, "Wyloguj"},
                               {9, "Wyjdź"}};
    if (client.hasRented())
    {
        Car car = client.getRentCar();
        cout << " Wypożyczony samochód: " << car.getBrand() << " " << car.getModel()
             << " [" << time(0) / 60 - client.getRentTime() << " min/" << maxRentTime << "min]\n";

        promptMap[3] = "Zwróć: " + car.getBrand() + " " + car.getModel();
    }

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
    case 7:
    {
        Utils::reportIssue(client, Utils::promptInput("Opisz swój problem i zatwierdź [enter]."));
        showHomeScreen();
        break;
    }
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

void Menu::showProfile()
{
    client.printInfo();

    int sel = Utils::promptSel({{9, "Powrót do menu"}});

    switch (sel)
    {
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
             << "      Cena: " << car.getPrice() << "zł/min" << endl
             << "      Dostępna ilość: " << car.getQuantity() << endl;

        i++;
    }

    cout << endl;

    int sel = Utils::promptSel({{0, "Wypożycz samochód"},
                                {1, "Wyświetl szczegóły o samochodzie"},
                                {9, "Powrót do menu"}});
    switch (sel)
    {
    case 0:
        tryRent(Utils::promptNumInput("Podaj numer samochodu."));
        break;
    case 1:
        showCarDetails(Utils::promptNumInput("Podaj numer samochodu."));
        break;
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
    client.unrent() ? cout << "Nie masz samochodu do zwrócenia.\n" : cout << "Zwrócono samochód.\n";
    showHomeScreen();
}

void Menu::showCarDetails(const int n)
{
    Car car = cars[n - 1];
    cout << car.getBrand() << " " << car.getModel() << endl
         << "  Cena: " << car.getPrice() << "zł/min" << endl
         << "  Dostępna ilość: " << car.getQuantity() << endl
         << "  Rok produkcji: " << car.getSpec(YEAR) << endl
         << "  Moc [KM]: " << car.getSpec(HP) << endl
         << "  Prędkość maksymalna: " << car.getSpec(VMAX) << endl
         << "  Miejsca: " << car.getSpec(SEATS) << endl
         << "  Drzwi: " << car.getSpec(DOOR) << endl
         << endl;

    int sel = Utils::promptSel({{0, "Wypożycz ten samochód"},
                                {9, "Powrót do menu"}});

    switch (sel)
    {
    case 0:
        tryRent(n);
        break;
    case 9:
        showHomeScreen();
        break;
    default:
        showCarDetails(n);
        break;
    }
}

void Menu::tryRent(const int n)
{
    int o = rentCar(cars[n - 1]);

    switch (o)
    {
    case 0:
        cout << "Wypożyczono samochód " << cars[n - 1].getBrand() << " " << cars[n - 1].getModel() << ".\n";
        break;
    case 1:
        Utils::printErr("Ten samochód nie jest aktualnie dostępny.");
        break;
    case 2:
        Utils::printErr((string) "Nie masz minimalnej ilości pieniędzy, by wypożyczyć samochód.\n" +
                        "Dla bezpieczeństwa minimalna ilość pieniędzy to: \n" +
                        "cena wypożyczenia samochodu * " +
                        std::to_string(maxRentTime) +
                        " minut + " +
                        std::to_string(notReturnedFine));
        break;
    case 3:
        Utils::printErr("Już masz wypożyczony samochód.");
        break;
    }
    showHomeScreen();
}

int Menu::rentCar(Car &car)
{
    if (car.getQuantity() <= 0)
        return 1;

    // Note that for safety reasons the client must have a minimum amount of credits on their account.
    // That is (car price per minute) * (maximum rent time from conf.h) + (fine for not returning the car)
    int requiredCredits = car.getPrice() * maxRentTime + notReturnedFine;
    if (Menu::client.getCredit() < requiredCredits)
        return 2;
    if (Menu::client.hasRented())
        return 3;

    Menu::client.rent(car);
    Menu::client.updateFile();
    return 0;
}