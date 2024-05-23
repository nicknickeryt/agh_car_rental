#include <iostream>
#include <vector>
#include <filesystem>

#include "auth.hpp"
#include "client.hpp"
#include "utils.hpp"

using std::cin, std::cout, std::endl, std::string, std::map, std::vector;

string carsFile = "../res/cars.yml";

int loginExists(string login)
{
    return std::filesystem::exists("../res/clients/" + login + ".yml");
}

bool Auth::showLogin(Client &client)
{
    Client retClient = Client();
    string login = Utils::promptInput("Podaj login");

    if (!loginExists(login))
    {
        Utils::printErr("Nieprawidłowy login");
        return 1;
    }
    else
    {
        retClient = Client(login);
        if (!retClient.checkPass(Utils::promptInput("Podaj hasło")))
        {
            Utils::printErr("Nieprawidłowe hasło");
            cout << "Prawidłowe to:" << retClient.getPass();
            return 1;
        }
    }
    client = retClient;
    return 0;
}

static int processRegister(string login, string pass, string name, string surname)
{
    Client client(login, pass, name, surname);
    client.updateFile();
    return 0;
}

int Auth::showRegister()
{
    string login, pass, name, surname{};

    cout << "Wprowadź dane nowego profilu:\n\n";

    cout << "Podaj login:\n» ";
    cin >> login;

    if (loginExists(login))
    {
        Utils::printErr("Konto z takim loginem już istnieje");
        return 1;
    }

    cout << "Podaj hasło:\n» ";
    cin >> pass;
    cout << " Podaj imię:\n» ";
    cin >> name;
    cout << " Podaj nazwisko:\n» ";
    cin >> surname;

    processRegister(login, pass, name, surname);

    cout << "Konto " << name << " " << surname << " zostało utworzone. Możesz się teraz zalogować.\n\n";
    return 0;
}