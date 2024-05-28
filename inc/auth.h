#include "client.h"

#pragma once

class Auth {
public:
    static int showLogin(Client &client);
    static int showRegister();
    static void processRegister(string login, string pass, string name, string surname);
};