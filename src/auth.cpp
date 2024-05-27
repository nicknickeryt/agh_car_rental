#include <iostream>
#include <vector>
#include <filesystem>

#include "auth.h"
#include "client.h"
#include "utils.h"
#include "conf.h"
#include "strings.h"

using std::cin, std::cout, std::endl, std::string, std::map, std::vector;

int Auth::showLogin(Client &client)
{
    Client retClient = Client();
    string login = Utils::promptInput(INPUT_LOGIN);

    if (!Utils::loginExists(login))
        return 1;
    else
    {
        try
        {
            retClient = Client(login);
        }
        catch (exception e)
        {
            Utils::processException(CLIENT_PARSE);
        }

        if (!retClient.checkPass(Utils::promptInput(INPUT_PASS)))
            return 2;
    }
    client = retClient;
    return 0;
}

static int processRegister(string login, string pass, string name, string surname)
{
    Client client(login, pass, name, surname);
    client.updateFile();
    return 0;
}

int Auth::showRegister()
{
    string login = Utils::promptInput(INPUT_LOGIN);

    if (Utils::loginExists(login))
        return 1;

    string pass = Utils::promptInput(INPUT_PASS);
    string name = Utils::promptInput(INPUT_NAME);
    string surname = Utils::promptInput(INPUT_SURNAME);

    processRegister(login, pass, name, surname);

    return 0;
}