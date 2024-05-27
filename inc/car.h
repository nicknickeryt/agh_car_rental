#pragma once

#include <vector>
#include <map>
#include <string>

using std::string, std::map, std::vector;

enum Spec {
    SPEC_YEAR,
    SPEC_HP,
    SPEC_VMAX,
    SPEC_SEATS,
    SPEC_DOOR
};

class Car {
private:
    string brand;
    string model;
    float price;
    int quantity;

    int id;

    map<Spec, int> specs;

public:
    Car();
    Car(string brand, string model, float price, int quantity, map<Spec, int> specs, int id);
    string getBrand() const;
    string getModel() const;
    float getPrice() const;
    int getQuantity() const;
    int getId() const;
    map<Spec, int> getSpecs();
    int getSpec(Spec s);
    static bool getAllCars(vector<Car> &cars);

    static Car getCarById(const int id);

    bool isNull();

    void rent();
    void unrent();
};
