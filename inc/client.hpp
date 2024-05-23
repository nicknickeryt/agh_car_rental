#include <string>

#include "yaml-cpp/yaml.h"

#include "car.hpp"

#pragma once

using std::string;

class Client
{
    string fLogin;
    string fPass;
    string fName;
    string fSurname;
    int fCredit;
    int fInitialCredit;

    string fClientFile;

    int fRentCarId = 0;

    static const int defaultCredit = 1000;

public:
    void setName(string name);
    void setSurname(string surname);
    void setCredit(int credit);
    void resetCredit();

    string getLogin();
    string getPass(); /// TODO REMOVE IT!
    string getName();
    string getFile();
    string getSurname();
    int getCredit();

    void printInfo();
    bool checkPass(string pass);
    void deleteProfile();

    bool isNull();

    void rent(Car car);
    void unrent();
    bool hasRented();
    Car getRentCar();

    Client();
    Client(string login, string pass, string name, string surname);
    Client(string login, string pass, string name, string surname, int credit);
    Client(string login);
    void updateFile();
};