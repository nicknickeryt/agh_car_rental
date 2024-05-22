#include <vector>
#include <map>


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
    std::string brand;
    std::string model;
    int price;
    int quantity;

    std::map<Spec, int> specs;

public:
    Car (string brand, string model, int price, int quantity, map<Spec, int> specs) : brand(brand), model(model), price(price), quantity(quantity), specs(specs) {}
    std::string getBrand();
    std::string getModel();
    int getPrice();
    int getQuantity();
    std::map<Spec, int> getSpecs();
    int getSpec(Spec s);
};

std::vector<Car> loadCarsFromYaml(std::string file);
