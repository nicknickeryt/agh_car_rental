#include <string>
#include <map>
#include <vector>
#include "yaml-cpp/yaml.h"
#include <iostream>

#include "car.hpp"

using std::string, std::map, std::vector, std::cin, std::cout;


    string Car::getBrand() { return brand; }
    string Car::getModel() { return model; }
    int Car::getPrice() { return price; }
    int Car::getQuantity() { return quantity; }
    map<Spec, int> Car::getSpecs() { return specs; }
    int Car::getSpec(Spec s) { return specs[s]; }


std::vector<Car> loadCarsFromYaml(std::string file)
{   
    vector<Car> ret;
    YAML::Node cars = YAML::LoadFile(file);
    
    YAML::Node root = cars["cars"];
    
    for (auto x : root) {
        int i = x.first.as<int>();
        YAML::Node car = root[i];

        string brand = car["brand"].as<string>();
        string model = car["model"].as<string>();
        int price = car["price"].as<int>();
        int quantity = car["quantity"].as<int>();
        
        map<Spec,int> specs {
            {Spec::YEAR, car["specs"]["year"].as<int>()},
            {Spec::HP, car["specs"]["hp"].as<int>()},
            {Spec::VMAX, car["specs"]["vmax"].as<int>()},
            {Spec::SEATS, car["specs"]["seats"].as<int>()},
            {Spec::DOOR, car["specs"]["door"].as<int>()},
        };


        ret.push_back(Car(brand, model, price, quantity, specs));
    }
    return ret;
}