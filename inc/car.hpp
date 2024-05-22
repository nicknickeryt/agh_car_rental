#include <vector>
#include <map>
#include <string>

using std::string, std::map, std::vector;

enum Spec
{
    YEAR,
    HP,
    VMAX,
    SEATS,
    DOOR
};

class Car {
private:
    string brand;
    string model;
    int price;
    int quantity;

    map<Spec, int> specs;

public:
    Car(string brand, string model, int price, int quantity, map<Spec, int> specs);
    string getBrand() const;
    string getModel() const;
    int getPrice() const;
    int getQuantity() const;
    map<Spec, int> getSpecs();
    int getSpec(Spec s);
};

vector<Car> parseCarsFromYaml(string& file);
