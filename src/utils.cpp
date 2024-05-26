#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <map>
#include <sstream>

#include "yaml-cpp/yaml.h"

#include "utils.h"
#include "conf.h"
#include "car.h"
#include "defaultCarsConf.h"
#include "client.h"

using std::cout, std::cin, std::endl, std::string, std::map;

bool Utils::checkFileDir(const FileDir fileDir, const bool saveDef)
{
    bool ret = 0;
    switch (fileDir)
    {
    case RES_DIR:
        ret = std::filesystem::exists(resPath);

        if (!ret && saveDef)
        {
            if (!std::filesystem::create_directory(resPath) || !std::filesystem::create_directory(clientsPath))
                processException(DIR_CREATE);
        }
        break;
    case CLIENTS_DIR:
        ret = std::filesystem::exists(clientsPath);

        if (!ret && saveDef)
            if (!std::filesystem::create_directory(clientsPath))
                processException(DIR_CREATE);
        break;
    case CARS_FILE:
        ret = std::filesystem::exists(carsConf);

        if (!ret && saveDef)
            if (saveDefaultCarsConf())
                Utils::processException(FILE_SAVE);
        break;
    case REPORTS_FILE:
        ret = std::filesystem::exists(reportsPath);

        if (!ret && saveDef)
            if (saveDefaultReportsFile())
                Utils::processException(FILE_SAVE);
        break;
    }
    return ret;
}

bool Utils::saveDefaultCarsConf()
{
    std::ofstream file(carsConf);
    if (file)
    {
        file << defaultCarsConf;
        file.close();
        return 0;
    }
    return 1;
}
bool Utils::saveDefaultReportsFile()
{
    std::ofstream file(reportsPath);
    if (file)
    {
        file << "# This file contains user reports.\n";
        file.close();
        return 0;
    }
    return 1;
}

int Utils::promptSel()
{
    int ret;

    string input{};

    while (1)
    {
        cout << "» ";
        cin >> input;
        if (validateInt(input))
        {
            std::istringstream(input) >> ret;
            break;
        }
        printErr("Podaj poprawny znak [cyfrę].");
    }
    return ret;
}

int Utils::promptSel(const map<int, string> promptMap)
{
    for (auto x : promptMap)
    {
        cout << " [" << x.first << "] " << x.second << endl;
    }

    int ret;

    string input{};

    while (1)
    {
        cout << "» ";
        cin >> input;
        if (validateInt(input))
        {
            std::istringstream(input) >> ret;
            break;
        }
        printErr("Podaj poprawny znak [cyfrę].");
    }
    return ret;
}

bool Utils::validateInt(const std::string &input)
{
    std::istringstream iss(input);
    int value;
    return (iss >> value) && (iss.eof());
}

string Utils::promptInput()
{
    string ret{};
    cout << "» ";
    cin >> ret;
    return ret;
}

string Utils::promptInput(const string promptText)
{
    cout << promptText << endl;

    string ret{};
    cout << "» ";
    cin >> ret;
    return ret;
}

int Utils::promptNumInput(const string promptText)
{
    cout << promptText << endl;

    int ret{};
    cout << "» ";
    cin >> ret;
    return ret;
}

string Utils::promptInput(const PredefPromptType type)
{
    cout << predefPromptText[type] << endl;

    string ret{};
    cout << "» ";
    cin >> ret;
    return ret;
}

void Utils::printErr(const string errText)
{
    cout << "[ ! ] " << errText << endl;
}

bool Utils::loginExists(const string login)
{
    return std::filesystem::exists(clientsPath + login + ".yml");
}

void Utils::processException(const ExceptionType extype)
{
    switch (extype)
    {
    case CLIENT_PARSE:
        printErr("Nie można załadować danych użytkownika. Sprawdź konfigurację.");
        break;
    case CARS_PARSE:
        printErr("Nie można załadować danych samochodów. Sprawdź konfigurację.");
        break;
    case FILE_SAVE:
        printErr("Nie można zapisać niektórych plików. Sprawdź konfigurację.");
        break;
    case DIR_CREATE:
        printErr("Nie można utworzyć niektórych katalogów. Sprawdź konfigurację.");
        break;
    default:
        printErr("Wystąpił nieznany błąd.");
        break;
    }
    exit(1);
}

void Utils::checkTime(Client &client)
{
    int now = std::time(0) / 60;
    if (client.hasRented() && now - client.getRentTime() > maxRentTime)
    {
        client.setCredit(client.getCredit() - notReturnedFine);
        client.unrent();
        client.updateFile();
        Utils::printErr((string) "Przekroczono maksymalny czas wypożyczenia. Kara w wysokości " + std::to_string(notReturnedFine) + (string) "zł została pobrana z konta. a pojazd został zablokowany.");
    }
}

void Utils::reportIssue(Client &client, const string issue)
{
    std::ofstream file(reportsPath, std::ios_base::app);
    if (file.is_open())
    {
        file << client.getLogin() << ": " << issue << std::endl;
        file.close();
    }
    else
        processException(FILE_SAVE);
}