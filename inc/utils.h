#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <map>

#include "client.h"
#include "messages.h"

using std::string, std::map, std::exception;

// This enum defines custom exceptions used in the project
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


// This class contains various functions
class Utils {
public:
    // Shows the selection input and returns it
    // Returns the input number
    static int promptSel();

    // Shows the selection input and displays a prompt map containing the possible options to select
    // Returns the input number
    static int promptSel(const map<int, string> promptMap);

    // Shows the selection input and displays a prompt map containing the possible options to select using Message enum
    // Returns the input number
    static int promptSel(const map<int, Message> promptMap);

    // Shows the input prompt
    // Returns the input string
    static string promptInput();

    // Shows the input prompt using a string as a prompt text
    // Returns the input string
    static string promptInput(const string promptText);

    // Shows the input prompt using a Message as a prompt text
    // Returns the input string
    static string promptInput(const Message message);

    // Shows the input prompt using a string as a prompt text
    // Returns the input number
    static int promptNumInput(const string promptText);

    // Shows the input prompt using Message enum as a prompt text
    // Returns the input number
    static int promptNumInput(const Message message);

    // Prints the error using string
    static void printErr(const string errText);

    // Prints the error using Message enum
    static void printErr(Message message);

    // Processes the custom ExceptionType exception
    static void processException(const ExceptionType extype);

    /*
     * Checks if the given directory or file exists. 
     * saveDef defines whether the default directory or file should be saved when missing
     */
    static bool checkFileDir(const FileDir fileDir, const bool saveDef);

    // Saves the default cars config
    static bool saveDefaultCarsConf();
    
    // Saves the default reports file
    static bool saveDefaultReportsFile();

    // Check if the user exists
    static bool loginExists(const string login);

    // Checks if the client rent time has reached the maximum rent time configured
    static void checkTime(Client &client);

    // Reports a user issue
    static void reportIssue(Client &client, const string issue);

    // Validates if a string can be parsed as an int
    static bool validateInt(const string &input);
};

#endif // UTILS_H