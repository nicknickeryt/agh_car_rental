#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "yaml-cpp/yaml.h"

#include "car.h"
#include "utils.h"
#include "conf.h"

using std::string, std::map, std::vector;

Car::Car() {}

Car::Car(string brand, string model, float price, int quantity, map<Spec, int> specs, int id) : brand(brand), model(model), price(price), quantity(quantity), specs(specs), id(id) {}

string Car::getBrand() const { return brand; } 
string Car::getModel() const { return model; }
float Car::getPrice() const { return price; }
int Car::getQuantity() const { return quantity; }
map<Spec, int> Car::getSpecs() { return specs; }
int Car::getSpec(Spec s) { return specs[s]; }
int Car::getId() const { return id; }

Car Car::getCarById(const int id) {
    YAML::Node cars = YAML::LoadFile(carsConf);
    YAML::Node root = cars["cars"];
    YAML::Node car = root[id];

    string brand = car["brand"].as<string>();
    string model = car["model"].as<string>();
    float price = car["price"].as<float>();
    int quantity = car["quantity"].as<int>();

    map<Spec, int> specs{
        {SPEC_YEAR, car["specs"]["year"].as<int>()},
        {SPEC_HP, car["specs"]["hp"].as<int>()},
        {SPEC_VMAX, car["specs"]["vmax"].as<int>()},
        {SPEC_SEATS, car["specs"]["seats"].as<int>()},
        {SPEC_DOOR, car["specs"]["doors"].as<int>()},
    };
    return Car(brand, model, price, quantity, specs, id);
}

bool Car::isNull() {
    return brand == "" || model == "" || price == 0;
}

bool Car::getAllCars(vector<Car> &carsV) {
    try {
        vector<Car> ret;
        YAML::Node cars = YAML::LoadFile(carsConf);

        YAML::Node root = cars["cars"];

        for (auto x : root) {
            int i = x.first.as<int>();
            YAML::Node car = root[i];

            string brand = car["brand"].as<string>();
            string model = car["model"].as<string>();
            float price = car["price"].as<float>();
            int quantity = car["quantity"].as<int>();

            map<Spec, int> specs{
                {SPEC_YEAR, car["specs"]["year"].as<int>()},
                {SPEC_HP, car["specs"]["hp"].as<int>()},
                {SPEC_VMAX, car["specs"]["vmax"].as<int>()},
                {SPEC_SEATS, car["specs"]["seats"].as<int>()},
                {SPEC_DOOR, car["specs"]["doors"].as<int>()},
            };

            ret.push_back(Car(brand, model, price, quantity, specs, i));
        }
        carsV = ret;
        return 0;
    }
    catch (exception const&) {
        Utils::processException(CARS_PARSE);
    }
    return 1;
}

void Car::rent() { quantity--; }

void Car::unrent() { quantity++; }
