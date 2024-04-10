#include <string>
#include <iostream>

#include "client.hpp"

#include "yaml-cpp/yaml.h"

using std::string,std::cout,std::endl;

void Client::setName(string name)
{
    fName = name;
}

void Client::setSurname(string surname)
{
    fSurname = surname;
}

void Client::setCredit(int credit)
{
    fCredit = credit;
}

void Client::resetCredit()
{
    fCredit = fInitialCredit;
}

string Client::getName() { return fName; }
string Client::getSurname() { return fSurname; }
int Client::getCredit() { return fCredit; }

void Client::printInfo() {
    cout << " >---------------<" << endl;
    cout << " > Client details" << endl;
    cout << "  > Name: " << fName << endl;
    cout << "  > Surname: " << fSurname << endl;
    cout << "  > Current credit: " << fCredit << endl;
    cout << "  > Initial credit: " << fInitialCredit << endl;
    cout << " >---------------<" << endl;
}

Client::Client(string name, string surname)
{
    fInitialCredit = fCredit = defaultCredit;
    fName = name;
    fSurname = surname;
}

Client::Client(string name, string surname, int credit)
{
    fInitialCredit = fCredit = credit;
    fName = name;
    fSurname = surname;
}

Client::Client(YAML::Node client)
{
    string name = client["personal"]["name"].as<string>();
    string surname = client["personal"]["surname"].as<string>();
    int credit = client["credit"].as<int>();
    fInitialCredit = fCredit = credit;
    fName = name;
    fSurname = surname;
}
