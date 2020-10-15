#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <string>

class  Vehicle {
protected:
    std::string brand;
   int month, year;
public:
   Vehicle(std::string b, int m, int y);
   //virtual ~Vehicle(){};
   int getYear() const;
   int getMonth() const;
   std::string getBrand() const;
   virtual int info() const;
   virtual int info(std::ostream &o) const;
   bool operator < (const Vehicle & v) const;
   virtual float calculateTax() const = 0;
};

class MotorVehicle: public Vehicle {
    std::string fuel; int cylinder;
public:
    MotorVehicle(std::string b1, int m1, int y1, std::string f, int cyl);

    std::string getFuel() const;
    virtual int info() const;
    virtual int info(std::ostream &o) const;
    float calculateTax() const;
};


class Car: public MotorVehicle {
public:
    Car(std::string b, int m, int y, std::string f, int cyl);
    int info() const;
    int info(std::ostream &o) const;
};


class Truck: public MotorVehicle {
    int maximumLoad;
public:
    Truck(std::string b, int m, int y,std::string f, int cyl,int ml);
    int info() const;
    int info(std::ostream &o) const;
};


class Bicycle: public Vehicle {
    std::string type;
public:
    Bicycle(std::string b, int m, int y, std::string t);
    int info() const;
    int info(std::ostream &o) const;
    float calculateTax() const;
};


#endif /* VEHICLE_H_ */
