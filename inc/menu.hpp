#include <string>

#include "client.hpp"
#include "auth.hpp"

using std::string;

class Menu
{
public:
    static Client client;
    static void showLoginScreen();
    static void showHomeScreen();
    static void logout();
    static void deleteProfile();
    static void showProfile();
    static void showCars();
    static void tryRent(int n);
    static void tryUnrent();
    static int rentCar(int n);
};
