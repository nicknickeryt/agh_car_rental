#ifndef CAR_H
#define CAR_H

#include <vector>
#include <map>
#include <string>

using std::string, std::map, std::vector;

// Car specs enumerator
enum Spec {
    SPEC_YEAR,
    SPEC_HP,
    SPEC_VMAX,
    SPEC_SEATS,
    SPEC_DOOR
};


// This class hold info about a specific car model
class Car {
private:
    string brand;
    string model;
    float price;
    int quantity;

    map<Spec, int> specs;
    
    int id;


public:
    Car();
    Car(string brand, string model, float price, int quantity, map<Spec, int> specs, int id);

    // Gets the car brand
    string getBrand() const;

    // Gets the car model
    string getModel() const;

    // Gets the car rent price
    float getPrice() const;

    // Gets the available quantity
    int getQuantity() const;

    // Gets the car model unique ID
    int getId() const;

    // Gets all the car specs as a map
    map<Spec, int> getSpecs();

    // Gets a specific spec value
    int getSpec(Spec s);

    // Converts all cars from the file to vector
    static bool getAllCars(vector<Car> &cars);

    // Gets the car model object by unique ID
    static Car getCarById(const int id);

    // Checks if the car model objct is empty of wrong
    bool isNull();

    // These rents and returns the car, changing the quantity value accordingly
    void rent();
    void unrent();
};

#endif // CAR_H