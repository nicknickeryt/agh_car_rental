#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "client.hpp"

#include "yaml-cpp/yaml.h"

using std::string, std::cout, std::endl;

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

string Client::getLogin() { return fLogin; }
string Client::getPass() { return fPass; }
string Client::getName() { return fName; }
string Client::getSurname() { return fSurname; }
int Client::getCredit() { return fCredit; }

void Client::printInfo()
{
    cout << "\nProfil\n";
    cout << "  Login: " << fLogin << endl;
    cout << "  Imię: " << fName << endl;
    cout << "  Nazwisko: " << fSurname << endl;
    cout << "  Kredyt: " << fCredit << "\n\n";
}

Client::Client()
{
    fInitialCredit = fCredit = defaultCredit;
    fName = fSurname = "";
}

Client::Client(string login, string pass, string name, string surname)
{
    fLogin = login;
    fPass = pass;
    fInitialCredit = fCredit = defaultCredit;
    fName = name;
    fSurname = surname;
}

Client::Client(string login, string pass, string name, string surname, int credit)
{
    fLogin = login;
    fPass = pass;
    fInitialCredit = fCredit = credit;
    fName = name;
    fSurname = surname;
}

Client::Client(string clientFile)
{
    YAML::Node client = YAML::LoadFile(clientFile);

    string login = client["personal"]["login"].as<string>();
    string pass = client["personal"]["pass"].as<string>();

    string name = client["personal"]["name"].as<string>();
    string surname = client["personal"]["surname"].as<string>();
    int credit = client["credit"].as<int>();

    fLogin = login;
    fPass = pass;

    fName = name;
    fSurname = surname;
    fInitialCredit = fCredit = credit;
}

bool Client::writeToYaml(string file)
{

    std::ofstream fout(file);
    YAML::Node clientYaml = YAML::LoadFile(file);

    clientYaml["personal"]["login"] = fLogin;
    clientYaml["personal"]["pass"] = fPass;

    clientYaml["personal"]["name"] = fName;
    clientYaml["personal"]["surname"] = fSurname;

    clientYaml["credit"] = fCredit;

    fout << clientYaml;

    return 0;
}

bool Client::checkPass(string pass)
{
    return fPass == pass;
}

void Client::deleteProfile(string file) { std::filesystem::remove(file); };

bool Client::isNull()
{
    return fName == "" || fSurname == "" || fLogin == "" || fPass == "";
}
