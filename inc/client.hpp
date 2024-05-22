#include <string>

#include "yaml-cpp/yaml.h"
using std::string;

class Client
{
    string fLogin;
    string fPass;
    string fName;
    string fSurname;
    int fCredit;
    int fInitialCredit;

    static const int defaultCredit = 1000;

public:
    void setName(string name);
    void setSurname(string surname);
    void setCredit(int credit);
    void resetCredit();

    string getLogin();
    string getPass(); /// TODO REMOVE IT!
    string getName();
    string getSurname();
    int getCredit();

    void printInfo();
    bool checkPass(string pass);
    void deleteProfile(string file);

    bool isNull();

    Client();
    Client(string login, string pass, string name, string surname);
    Client(string login, string pass, string name, string surname, int credit);
    Client(string clientFile);

    bool writeToYaml(string file);
};