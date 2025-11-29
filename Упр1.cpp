#include <iostream>
#include <string>

using namespace std;

class Vehicle {
protected:
    string manufacturer;
    int year;
public:
    Vehicle(const string& manuf, int y) : manufacturer(manuf), year(y) {}
    virtual ~Vehicle() {}

    virtual string getInfo() const {
        return manufacturer + " (" + to_string(year) + ")";
    }
};

class GroundVehicle : virtual public Vehicle {
protected:
    int wheelCount;
    int maxSpeed;
public:
    GroundVehicle(const string& manuf, int y, int wheels, int speed)
        : Vehicle(manuf, y), wheelCount(wheels), maxSpeed(speed) {
    }

    string getInfo() const override {
        return Vehicle::getInfo() + ", Колес: " + to_string(wheelCount) +
            ", Макс. скорость: " + to_string(maxSpeed) + " км/ч";
    }

    void drive() const {
        cout << "Едет по дороге со скоростью до " << maxSpeed << " км/ч" << endl;
    }
};

class WaterVehicle : virtual public Vehicle {
protected:
    double displacement;
    bool hasSail;
public:
    WaterVehicle(const string& manuf, int y, double disp, bool sail)
        : Vehicle(manuf, y), displacement(disp), hasSail(sail) {
    }

    string getInfo() const override {
        return Vehicle::getInfo() + ", Водоизмещение: " + to_string(displacement) +
            " т, " + (hasSail ? "Парусное" : "Моторное");
    }

    void sail() const {
        cout << "Плывет по воде" << (hasSail ? " под парусом" : " на моторе") << endl;
    }
};

class AmphibiousVehicle : public GroundVehicle, public WaterVehicle {
private:
    bool isInWater;
public:
    AmphibiousVehicle(const string& manuf, int y, int wheels, int speed,
        double disp, bool sail)
        : Vehicle(manuf, y),
        GroundVehicle(manuf, y, wheels, speed),
        WaterVehicle(manuf, y, disp, sail),
        isInWater(false) {
    }

    string getInfo() const override {
        return "АМФИБИЯ: " + Vehicle::getInfo() +
            ", Колес: " + to_string(wheelCount) +
            ", Скорость: " + to_string(maxSpeed) + " км/ч" +
            ", Водоизмещение: " + to_string(displacement) + " т";
    }

    void switchMode() {
        isInWater = !isInWater;
        if (isInWater) {
            cout << "Переключается в водный режим" << endl;
        }
        else {
            cout << "Переключается в наземный режим" << endl;
        }
    }

    void demonstrateAbilities() {
        cout << "\n--- Демонстрация возможностей амфибии ---" << endl;

        cout << "1. Амфибия на суше:" << endl;
        drive();

        cout << "2. Заезжает в воду и переключается:" << endl;
        switchMode();

        cout << "3. Плавает по воде:" << endl;
        sail();

        cout << "4. Выходит на сушу:" << endl;
        switchMode();
        drive();
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    cout << "=== МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ: Транспортные средства ===" << endl;

    GroundVehicle car("Toyota", 2022, 4, 180);
    WaterVehicle boat("Yamaha", 2020, 2.5, false);

    cout << "\n1. Обычный автомобиль:" << endl;
    cout << car.getInfo() << endl;
    car.drive();

    cout << "\n2. Обычная лодка:" << endl;
    cout << boat.getInfo() << endl;
    boat.sail();

    cout << "\n3. АМФИБИЯ (множественное наследование):" << endl;
    AmphibiousVehicle amphibian("Gibbs", 2023, 6, 120, 3.2, false);
    cout << amphibian.getInfo() << endl;

    amphibian.demonstrateAbilities();

    return 0;
}