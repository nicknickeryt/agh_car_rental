#ifndef AUTH_H
#define AUTH_H

#include "client.h"

class Auth {
public:
    static int showLogin(Client &client);
    static int showRegister();
    static void processRegister(string login, string pass, string name, string surname);
};

#endif // AUTH_H