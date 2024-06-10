#ifndef AUTH_H
#define AUTH_H

#include "client.h"

// This class manages the user login.
class Auth {
public:
    // Shows the login dialogue
    static int showLogin(Client &client);

    // Shows the register dialogue
    static int showRegister();

    // Processes the registration
    static void processRegister(string login, string pass, string name, string surname);
};

#endif // AUTH_H