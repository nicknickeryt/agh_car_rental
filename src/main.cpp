#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

#include "main.hpp"
#include "menu.hpp"
#include "client.hpp"

#include "yaml-cpp/yaml.h"


using std::cin,std::cout,std::endl,std::string,std::map,std::vector;


int main() {
    showMenu();

    // YAML::Node client = YAML::LoadFile(clientFile);

    // string test = client["personal"]["name"].as<string>();

    // client["lastlogin"] = 129;

    // std::ofstream fout(clientFile);

    // fout << client;

    // fout.close();   

    // cout << test << endl;

    // Client client1 = Client("Jasiek", "Junak");

    // client1.setCredit(100);

    // client1.printInfo();

    // Client client2 = Client(client);

    // client2.printInfo();


}