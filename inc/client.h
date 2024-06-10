#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "yaml-cpp/yaml.h"

#include "car.h"

using std::string;


// This class holds the client info
class Client {
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
    
    // Sets the name of the user
    void setName(const string name);

    // Sets the surname of the user
    void setSurname(const string surname);

    // Sets the credit of the user
    void setCredit(const int credit);

    // Resets the user's credit
    void resetCredit();

    // Gets user login
    string getLogin();

    // Gets user name
    string getName();

    // Gets user file name
    string getFile();

    // Gets user surname
    string getSurname();

    // Gets user's credit
    int getCredit();

    // Gets the time since the user has rented a car
    int getRentTime();

    // Prints the user info
    void printInfo();

    // A wrapper to check user's password
    bool checkPass(string pass);

    // Checks if the client model objct is empty of wrong
    bool isNull();

    // Rents the given car
    void rent(Car car);

    // Returns the rented car
    int unrent();

    // Checks if the user has a car rented
    bool hasRented();

    // Gets the rented car
    Car getRentCar();

    Client();
    Client(const string login, const string pass, const string name, const string surname);
    Client(const string login, const string pass, const string name, const string surname, const int credit);
    Client(const string login);

    // Updates the user file
    void updateFile();
};

#endif // CLIENT_H