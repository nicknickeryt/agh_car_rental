#include <string>

#include "yaml-cpp/yaml.h"
using std::string;

class Client
{
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

    string getName();
    string getSurname();
    int getCredit();

    void printInfo();

    Client(string name, string surname);
    Client(string name, string surname, int credit);
    Client(YAML::Node client);
    
};