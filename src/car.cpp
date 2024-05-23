#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "yaml-cpp/yaml.h"

#include "car.hpp"

using std::string, std::map, std::vector, std::cin, std::cout;

Car::Car() {}

Car::Car(string brand, string model, int price, int quantity, map<Spec, int> specs, int id) : brand(brand), model(model), price(price), quantity(quantity), specs(specs), id(id)
{
    // YAML::Node cars = YAML::LoadFile("../res/cars.yml");
    // YAML::Node root = cars["cars"];
    // id = root.size() + 1;
}

string Car::getBrand() const { return brand; }
string Car::getModel() const { return model; }
int Car::getPrice() const { return price; }
int Car::getQuantity() const { return quantity; }
map<Spec, int> Car::getSpecs() { return specs; }
int Car::getSpec(Spec s) { return specs[s]; }
int Car::getId() const { return id; }

// Car::updateFile()
// {
//     YAML::Node cars = YAML::LoadFile("../res/cars.yml");
//     YAML::Node root = cars["cars"];
//     int id = 0;
//     if (root.size() != 0)
//         id = root[root.end()].first.as<int>()
// }

Car Car::getCarById(int id)
{
    YAML::Node cars = YAML::LoadFile("../res/cars.yml");
    YAML::Node root = cars["cars"];
    YAML::Node car = root[id];

    string brand = car["brand"].as<string>();
    string model = car["model"].as<string>();
    int price = car["price"].as<int>();
    int quantity = car["quantity"].as<int>();

    map<Spec, int> specs{
        {Spec::YEAR, car["specs"]["year"].as<int>()},
        {Spec::HP, car["specs"]["hp"].as<int>()},
        {Spec::VMAX, car["specs"]["vmax"].as<int>()},
        {Spec::SEATS, car["specs"]["seats"].as<int>()},
        {Spec::DOOR, car["specs"]["doors"].as<int>()},
    };
    return Car(brand, model, price, quantity, specs, id);
}

bool Car::isNull()
{
    return brand == "" || model == "" || price == 0;
}

vector<Car> Car::getAllCars()
{
    vector<Car> ret;
    YAML::Node cars = YAML::LoadFile("../res/cars.yml");

    YAML::Node root = cars["cars"];

    for (auto x : root)
    {
        int i = x.first.as<int>();
        YAML::Node car = root[i];

        string brand = car["brand"].as<string>();
        string model = car["model"].as<string>();
        int price = car["price"].as<int>();
        int quantity = car["quantity"].as<int>();

        map<Spec, int> specs{
            {Spec::YEAR, car["specs"]["year"].as<int>()},
            {Spec::HP, car["specs"]["hp"].as<int>()},
            {Spec::VMAX, car["specs"]["vmax"].as<int>()},
            {Spec::SEATS, car["specs"]["seats"].as<int>()},
            {Spec::DOOR, car["specs"]["doors"].as<int>()},
        };

        ret.push_back(Car(brand, model, price, quantity, specs, i - 1));
    }
    return ret;
}

void Car::rent()
{
    quantity--;
}

void Car::unrent()
{
    quantity++;
}
