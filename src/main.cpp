#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

#include "main.h"
#include "menu.h"

#include "yaml-cpp/yaml.h"

using std::cin, std::cout, std::endl, std::string, std::map, std::vector;

int main()
{
    /* TODO
     * clean up this mess
     * hash passwords and remove Client#getPassword
     * add car location with dummy gps function
     * add rules in menu and while registering
     */
    Menu::tryInit();
}