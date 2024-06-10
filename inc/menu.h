#ifndef MENU_H
#define MENU_H

#include <string>

#include "client.h"
#include "auth.h"

using std::string;


// This class manages the main menu and submenus
class Menu {
public:
    static Client client;                       // Current logged user object
    static void showLoginScreen();              // Shows the login screen
    static void showHomeScreen();               // Shows the home screen
    static void logout();                       // Logs out the user
    static void showProfile();                  // Shows the user profile
    static void showCars();                     // Shows the listing of file
    static void showCarDetails(const int n);    // Shows the given car details 
    static void tryRent(const int n);           // Tries to rent a car
    static void tryUnrent();                    // Tries to return a car
    static int rentCar(Car &car);               // Rents the car
    static void tryInit();                      // Tries to init the main menu
};

#endif // MENU_H