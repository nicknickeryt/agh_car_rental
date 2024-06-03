#ifndef MENU_H
#define MENU_H

#include <string>

#include "client.h"
#include "auth.h"

using std::string;

class Menu {
public:
    static Client client;
    static void showLoginScreen();
    static void showHomeScreen();
    static void logout();
    static void showProfile();
    static void showCars();
    static void showCarDetails(const int n);
    static void tryRent(const int n);
    static void tryUnrent();
    static int rentCar(Car &car);
    static void tryInit();
};

#endif // MENU_H