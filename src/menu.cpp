#include "yaml-cpp/yaml.h"
#include <iostream>
#include <map>
#include <vector>

#include "auth.h"
#include "car.h"
#include "menu.h"
#include "utils.h"
#include "conf.h"
#include "strings.h"

using std::cin, std::cout, std::endl, std::string, std::map, std::vector;

Client Menu::client = Client();

vector<Car> cars;

void Menu::tryInit()
{
    if (!Utils::checkFileDir(RES_DIR, 1))
        Utils::printErr(ERR_RES);
    if (!Utils::checkFileDir(CARS_FILE, 1))
        Utils::printErr(ERR_CARS);
    if (!Utils::checkFileDir(CLIENTS_DIR, 1))
        Utils::printErr(ERR_CLIENTS);
    if (!Utils::checkFileDir(REPORTS_FILE, 1))
        Utils::printErr(ERR_REPORTS);

    showLoginScreen();
}

void Menu::showLoginScreen()
{
    if (Car::getAllCars(cars))
        return;

    cout << "\n| Car sharing |\n\n";

    int sel = Utils::promptSel({{0, LOG_IN},
                                {1, REGISTER},
                                {9, QUIT}});
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
            Utils::printErr(ERR_WRONG_LOGIN);
            showLoginScreen();
            break;
        case 2:
            Utils::printErr(ERR_WRONG_PASS);
            showLoginScreen();
            break;
        }
        break;
    }
    case 1:
    {

        cout << rules << endl;

        int sel = Utils::promptSel({{0, ACCEPT_RULES},
                                    {9, QUIT}});
        switch (sel)
        {
        case 0:
        {
            if (Auth::showRegister())
                Utils::printErr(ERR_LOGIN_EXISTS);
            else
                cout << Utils::getMessage(ACCOUNT_CREATED);
            showLoginScreen();
            break;
        }
        default:
            exit(0);
        }
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

    map<int, string> promptMap{{1, Utils::getMessage(SHOW_PROFILE)},
                               {2, Utils::getMessage(BROWSE_CARS)},
                               {7, Utils::getMessage(REPORT_ISSUE)},
                               {8, Utils::getMessage(LOGOUT)},
                               {9, Utils::getMessage(QUIT)}};
    if (client.hasRented())
    {
        Car car = client.getRentCar();
        cout << Utils::getMessage(CAR_RENTED) << car.getBrand() << " " << car.getModel()
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
        Utils::reportIssue(client, Utils::promptInput(REPORT_ISSUE_PROMPT));
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

    int sel = Utils::promptSel({{9, BACK_MENU}});

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
    cout << Utils::getMessage(AVAIL_CARS);

    int i = 1;
    for (Car car : cars)
    {

        cout << "  [" << i << "] " << car.getBrand() << " " << car.getModel() << endl
             << "      " << Utils::getMessage(PRICE) << ": " << car.getPrice() << Utils::getMessage(CURRENCY) << "/min" << endl
             << "      " << Utils::getMessage(AVAIL_AMOUNT) << ": " << car.getQuantity() << endl;

        i++;
    }

    cout << endl;

    int sel = Utils::promptSel({{0, RENT},
                                {1, SEE_DETAILS},
                                {9, BACK_MENU}});
    switch (sel)
    {
    case 0:
        tryRent(Utils::promptNumInput(RENT_INPUT_NUM));
        break;
    case 1:
        showCarDetails(Utils::promptNumInput(RENT_INPUT_NUM));
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

    int sel = Utils::promptSel({{0, RENT},
                                {9, BACK_MENU}});

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
        Utils::printErr(ERR_ALREADY_RENTED);
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