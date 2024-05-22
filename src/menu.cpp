#include "menu.hpp"
#include "yaml-cpp/yaml.h"
#include <iostream>
#include <map>
#include "car.hpp"
#include <vector>

using std::cin,std::cout,std::endl,std::string,std::map, std::vector;

YAML::Node cars = YAML::LoadFile(carsFile);

void showMenu() {
    cout << "» Wypożyczalnia «" << endl;
    
    vector<Car> cars = loadCarsFromYaml(carsFile);
    
    int i = 0;
    for (Car car : cars) {
        

        cout << " [" << i << "] " << 
        "Samochód: " << car.getBrand() << " " << car.getModel() << endl <<
        "     Cena: " << car.getPrice() << endl <<
        "     Dostępna ilość: " << car.getQuantity() << endl;

        i++;
    }
    
    cout << "» Podaj numer samochodu, który chcesz wypożyczyć:" << endl;
    int n {};
    cin >> n;


}