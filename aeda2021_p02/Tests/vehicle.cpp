#include "vehicle.h"
#include <iostream>
#include <string>

Vehicle::Vehicle(std::string b, int m, int y) : brand(b), month(m), year(y){}

MotorVehicle::MotorVehicle(std::string b1, int m1, int y1, std::string f, int cyl) : Vehicle(b1, m1, y1) {
    fuel = f;
    cylinder = cyl;
}

Car::Car(std::string b, int m, int y, std::string f, int cyl) : MotorVehicle(b,m,y,f,cyl){}

Truck::Truck(std::string b, int m, int y, std::string f, int cyl, int ml) : MotorVehicle(b,m,y,f,cyl){
    maximumLoad = ml;
}

Bicycle::Bicycle(std::string b, int m, int y, std::string t) : Vehicle(b,m,y){
    type = t;
}

std::string Vehicle::getBrand() const {
    return brand;
}

int Vehicle::getYear() const {
    return year;
}

int Vehicle::getMonth() const{
    return month;
}

bool Vehicle::operator<(const Vehicle &v) const {
    if(getYear() == v.getYear())
        return getMonth() < v.getMonth();
    else
        return getYear() < v.getYear();
}

std::string MotorVehicle::getFuel() const {
    return fuel;
}

int Vehicle::info() const {
    std::cout << "Brand: " << brand << ", Month: " << month << ", Year: " << year << std::endl;
    return 3;
}

int Vehicle::info(std::ostream &o) const {
    o << "Brand: " << brand << ", Month: " << month << ", Year: " << year;
    return 3;
}

int MotorVehicle::info() const {
    std::cout << "Fuel: " << fuel << ", Cylinder: " << cylinder << ", ";
    return Vehicle::info() + 2;
}

int MotorVehicle::info(std::ostream &o) const {
    o << "Fuel: " << fuel << ", Cylinder: " << cylinder << ", ";
    return Vehicle::info() + 2;
}

int Car::info() const {
    return MotorVehicle::info();
}

int Car::info(std::ostream &o) const {
    return MotorVehicle::info();
}

int Truck::info() const {
    std::cout << "Maximum Load: " << maximumLoad << ", ";
    return MotorVehicle::info() + 1;
}

int Truck::info(std::ostream &o) const {
    o << "Maximum Load: " << maximumLoad << ", ";
    return MotorVehicle::info() + 1;
}

int Bicycle::info() const {
    std::cout << "Type: " << type << ", ";
    return Vehicle::info() + 1;
}

int Bicycle::info(std::ostream &o) const {
    o << "Type: " << type << ", ";
    return Vehicle::info() + 1;
}

float MotorVehicle::calculateTax() const {
    if(fuel == "gas")
        switch (cylinder) {
            case 0 ... 1000:
                if (getYear() > 1995)
                    return 14.56;
                else
                    return 8.1;
            case 1001 ... 1300:
                if (getYear() > 1995)
                    return 29.06;
                else
                    return 14.56;
            case 1301 ... 1750:
                if (getYear() > 1995)
                    return 45.15;
                else
                    return 22.65;
            case 1751 ... 2600:
                if (getYear() > 1995)
                    return 113.98;
                else
                    return 54.89;
            case 2601 ... 3500:
                if (getYear() > 1995)
                    return 181.17;
                else
                    return 87.13;
            default:
                if (getYear() > 1995)
                    return 320.89;
                else
                    return 148.37;
        }
    else{
        switch (cylinder) {
            case 0 ... 1500:
                if (getYear() > 1995)
                    return 14.56;
                else
                    return 8.1;
            case 1501 ... 2000:
                if (getYear() > 1995)
                    return 29.06;
                else
                    return 14.56;
            case 2001 ... 3000:
                if (getYear() > 1995)
                    return 45.15;
                else
                    return 22.65;
            default:
                if (getYear() > 1995)
                    return 113.98;
                else
                    return 54.89;
        }
    }
}

float Bicycle::calculateTax() const {
    return 0;
}