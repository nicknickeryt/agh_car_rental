#include <string>
#include <map>

#include "client.h"

using std::string, std::map, std::exception;

enum ExceptionType
{
    CLIENT_PARSE,
    CARS_PARSE,
    FILE_SAVE,
    DIR_CREATE
};

enum FileDir
{
    RES_DIR,
    CARS_FILE,
    CLIENTS_DIR,
    REPORTS_FILE
};

enum PredefPromptType
{
    INPUT_LOGIN,
    INPUT_PASS,
    INPUT_NAME,
    INPUT_SURNAME
};

inline map<PredefPromptType, string> predefPromptText = {
    {INPUT_LOGIN, "Podaj login"},
    {INPUT_PASS, "Podaj hasło"},
    {INPUT_NAME, "Podaj imię"},
    {INPUT_SURNAME, "Podaj nazwisko"}};

class Utils
{
public:
    static int promptSel();
    static int promptSel(const map<int, string> promptMap);

    static string promptInput();
    static string promptInput(const string promptText);
    static int promptNumInput(const string promptText);
    static string promptInput(const PredefPromptType type);

    static void printErr(const string errText);

    static void processException(const ExceptionType extype);

    static bool checkFileDir(const FileDir fileDir, const bool saveDef);

    static bool saveDefaultCarsConf();
    static bool saveDefaultReportsFile();

    static bool loginExists(const string login);

    static void checkTime(Client &client);

    static void reportIssue(Client &client, const string issue);

    static bool validateInt(const string &input);
};
