#include <vector>
#include <map>
#include <string>

#pragma once

using std::string, std::map, std::vector;

enum Spec
{
    YEAR,
    HP,
    VMAX,
    SEATS,
    DOOR
};

class Car
{
private:
    string brand;
    string model;
    int price;
    int quantity;

    int id;

    map<Spec, int> specs;

public:
    Car();
    Car(string brand, string model, int price, int quantity, map<Spec, int> specs, int id);
    string getBrand() const;
    string getModel() const;
    int getPrice() const;
    int getQuantity() const;
    int getId() const;
    map<Spec, int> getSpecs();
    int getSpec(Spec s);
    static vector<Car> getAllCars();

    static Car getCarById(int id);

    bool isNull();

    void rent();
    void unrent();
};
