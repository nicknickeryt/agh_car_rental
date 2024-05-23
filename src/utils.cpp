#include <iostream>
#include <string>
#include <map>

#include "utils.hpp"

using std::cout, std::cin, std::endl, std::string, std::map;

int Utils::promptSel()
{
    int ret{};
    cout << "» ";
    cin >> ret;
    return ret;
}

int Utils::promptSel(map<int, string> promptMap)
{
    for (auto x : promptMap)
    {
        cout << " [" << x.first << "] " << x.second << endl;
    }

    int ret{};
    cout << "» ";
    cin >> ret;
    return ret;
}

string Utils::promptInput()
{
    string ret{};
    cout << "» ";
    cin >> ret;
    return ret;
}

string Utils::promptInput(string promptText)
{
    cout << promptText << endl;

    string ret{};
    cout << "» ";
    cin >> ret;
    return ret;
}

void Utils::printErr(string errText)
{
    cout << "[ ! ] " << errText << endl;
}
