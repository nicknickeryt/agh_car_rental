#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "client.hpp"

#include "yaml-cpp/yaml.h"

using std::string, std::cout, std::endl;

void Client::setName(string name)
{
    fName = name;
}

void Client::setSurname(string surname)
{
    fSurname = surname;
}

void Client::setCredit(int credit)
{
    fCredit = credit;
}

void Client::resetCredit()
{
    fCredit = fInitialCredit;
}

string Client::getLogin() { return fLogin; }
string Client::getPass() { return fPass; }
string Client::getName() { return fName; }
string Client::getSurname() { return fSurname; }
string Client::getFile() { return fClientFile; }
int Client::getCredit() { return fCredit; }
Car Client::getRentCar() { return Car::getCarById(fRentCarId); }

void Client::printInfo()
{
    cout << "\nProfil\n";
    cout << "  Login: " << fLogin << endl;
    cout << "  Imię: " << fName << endl;
    cout << "  Nazwisko: " << fSurname << endl;
    cout << "  Kredyt: " << fCredit << "\n\n";

    string rentedCar = hasRented() ? getRentCar().getBrand() + " " + getRentCar().getModel() : "brak";

    cout << "  Wypożyczony samochód: " << rentedCar << "\n\n";
}

Client::Client()
{
    fInitialCredit = fCredit = defaultCredit;
    fName = fSurname = "";
    fClientFile = "";
}

Client::Client(string login, string pass, string name, string surname)
{
    fLogin = login;
    fPass = pass;
    fInitialCredit = fCredit = defaultCredit;
    fName = name;
    fSurname = surname;
    fClientFile = "../res/clients/" + login + ".yml";
}

Client::Client(string login, string pass, string name, string surname, int credit)
{
    fLogin = login;
    fPass = pass;
    fInitialCredit = fCredit = credit;
    fName = name;
    fSurname = surname;
    fClientFile = "../res/clients/" + login + ".yml";
    fRentCarId = 0;
}

Client::Client(string login)
{
    fClientFile = "../res/clients/" + login + ".yml";
    YAML::Node client = YAML::LoadFile(fClientFile);

    string pass = client["personal"]["pass"].as<string>();

    string name = client["personal"]["name"].as<string>();
    string surname = client["personal"]["surname"].as<string>();
    int credit = client["credit"].as<int>();
    int rentCarId = client["rentCar"].as<int>();

    fLogin = login;
    fPass = pass;

    fName = name;
    fSurname = surname;
    fInitialCredit = fCredit = credit;
    fRentCarId = rentCarId;
}

void Client::updateFile()
{
    std::ofstream fout(fClientFile);
    YAML::Node clientYaml = YAML::LoadFile(fClientFile);

    clientYaml["personal"]["login"] = fLogin;
    clientYaml["personal"]["pass"] = fPass;

    clientYaml["personal"]["name"] = fName;
    clientYaml["personal"]["surname"] = fSurname;

    clientYaml["credit"] = fCredit;

    clientYaml["rentCar"] = fRentCarId;

    fout << clientYaml;
}

bool Client::checkPass(string pass)
{
    return fPass == pass;
}

void Client::deleteProfile()
{
    std::filesystem::remove(fClientFile);
    *this = Client();
}

bool Client::isNull()
{
    return fName == "" || fSurname == "" || fLogin == "" || fPass == "";
}

void Client::rent(Car car)
{
    fRentCarId = car.getId();
    setCredit(fCredit - 10);
    car.rent();
    updateFile();
}

void Client::unrent()
{
    Car::getCarById(fRentCarId).unrent();
    fRentCarId = 0;
    updateFile();
    // remove (credit/h) * time
}

bool Client::hasRented()
{
    return fRentCarId != 0;
}