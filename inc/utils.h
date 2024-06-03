#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <map>

#include "client.h"
#include "messages.h"

using std::string, std::map, std::exception;

enum ExceptionType {
    CLIENT_PARSE,
    CARS_PARSE,
    FILE_SAVE,
    DIR_CREATE
};

enum FileDir {
    RES_DIR,
    CARS_FILE,
    CLIENTS_DIR,
    REPORTS_FILE
};

class Utils {
public:
    static int promptSel();
    static int promptSel(const map<int, string> promptMap);
    static int promptSel(const map<int, Message> promptMap);

    static string promptInput();
    static string promptInput(const string promptText);
    static string promptInput(const Message message);
    static int promptNumInput(const string promptText);
    static int promptNumInput(const Message message);

    static void printErr(const string errText);
    static void printErr(Message message);

    static void processException(const ExceptionType extype);

    static bool checkFileDir(const FileDir fileDir, const bool saveDef);

    static bool saveDefaultCarsConf();
    static bool saveDefaultReportsFile();

    static bool loginExists(const string login);

    static void checkTime(Client &client);

    static void reportIssue(Client &client, const string issue);

    static bool validateInt(const string &input);
};

#endif // UTILS_H