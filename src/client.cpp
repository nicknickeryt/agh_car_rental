#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>

#include "client.h"
#include "utils.h"
#include "conf.h"
#include "messages.h"

#include "yaml-cpp/yaml.h"

using std::string, std::cout, std::endl;

void Client::setName(const string name){ fName = name;}

void Client::setSurname(const string surname){ fSurname = surname; }

void Client::setCredit(const int credit){ fCredit = credit; }

void Client::resetCredit(){ fCredit = fInitialCredit; }

string Client::getLogin() { return fLogin; }
string Client::getName() { return fName; }
string Client::getSurname() { return fSurname; }
string Client::getFile() { return fClientFile; }
int Client::getCredit() { return fCredit; }
Car Client::getRentCar() { return Car::getCarById(fRentCarId); }
int Client::getRentTime() { return fRentTime; }

void Client::printInfo() {
    Messages::sendMessage(CL_INFO_TITLE);
    cout << Messages::getMessage(CL_INFO_LOGIN) << fLogin << endl;
    cout << Messages::getMessage(CL_INFO_NAME) << fName << endl;
    cout << Messages::getMessage(CL_INFO_SURNAME) << fSurname << endl;
    cout << Messages::getMessage(CL_INFO_CREDIT) << fCredit << "\n\n";

    string rentedCar = hasRented() ? getRentCar().getBrand() + " " + getRentCar().getModel() : Messages::getMessage(CL_INFO_RENTED_NONE);

    cout << Messages::getMessage(CL_INFO_RENTED) << rentedCar << "\n\n";
}

Client::Client() {
    fInitialCredit = fCredit = defaultCredit;
    fName = fSurname = "";
    fClientFile = "";
}

Client::Client(const string login, const string pass, const string name, const string surname) {
    fLogin = login;
    fPass = pass;
    fInitialCredit = fCredit = defaultCredit;
    fName = name;
    fSurname = surname;
    fClientFile = clientsPath + slash + login + ".yml";
}

Client::Client(const string login, const string pass, const string name, const string surname, const int credit) {
    fLogin = login;
    fPass = pass;
    fInitialCredit = fCredit = credit;
    fName = name;
    fSurname = surname;
    fClientFile = clientsPath + slash + login + ".yml";
    fRentCarId = 0;
}

Client::Client(const string login) {
    fClientFile = clientsPath + slash + login + ".yml";
    YAML::Node client = YAML::LoadFile(fClientFile);

    string pass = client["personal"]["pass"].as<string>();

    string name = client["personal"]["name"].as<string>();
    string surname = client["personal"]["surname"].as<string>();
    int credit = client["credit"].as<int>();
    int rentCarId = client["rentCar"].as<int>();
    int rentTime = client["rentTime"].as<int>();

    fLogin = login;
    fPass = pass;

    fName = name;
    fSurname = surname;
    fInitialCredit = fCredit = credit;
    fRentCarId = rentCarId;
    fRentTime = rentTime;
}

void Client::updateFile() {
    std::ofstream fout(fClientFile);
    YAML::Node clientYaml = YAML::LoadFile(fClientFile);

    clientYaml["personal"]["login"] = fLogin;
    clientYaml["personal"]["pass"] = fPass;

    clientYaml["personal"]["name"] = fName;
    clientYaml["personal"]["surname"] = fSurname;

    clientYaml["credit"] = fCredit;

    clientYaml["rentCar"] = fRentCarId;
    clientYaml["rentTime"] = fRentTime;

    fout << clientYaml;
}

bool Client::checkPass(string pass){ return fPass == pass; }

bool Client::isNull() { return fName == "" || fSurname == "" || fLogin == "" || fPass == ""; }

void Client::rent(Car car) {
    fRentCarId = car.getId();

    fRentTime = std::time(0) / 60;

    // this is the initial fee
    setCredit(fCredit - 1);
    car.rent();
    updateFile();
}

int Client::unrent() {
    if (fRentCarId == 0) return 1;
    Car car = Car::getCarById(fRentCarId);
    car.unrent();

    int now = std::time(0) / 60;

    int minutes = now - fRentTime;

    fCredit -= car.getPrice() * minutes;

    fRentCarId = 0;
    fRentTime = 0;

    updateFile();
    return 0;
}

bool Client::hasRented() { return fRentCarId != 0; }