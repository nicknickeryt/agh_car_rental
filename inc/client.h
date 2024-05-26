#include <string>

#include "yaml-cpp/yaml.h"

#include "car.h"

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
    int fRentTime = 0;

    static const int defaultCredit = 10000;

public:
    void setName(const string name);
    void setSurname(const string surname);
    void setCredit(const int credit);
    void resetCredit();

    string getLogin();
    string getName();
    string getFile();
    string getSurname();
    int getCredit();
    int getRentTime();

    void printInfo();
    bool checkPass(string pass);

    bool isNull();

    void rent(Car car);
    int unrent();
    bool hasRented();
    Car getRentCar();

    Client();
    Client(const string login, const string pass, const string name, const string surname);
    Client(const string login, const string pass, const string name, const string surname, const int credit);
    Client(const string login);
    void updateFile();
};