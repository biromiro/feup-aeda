#ifndef SRC_ANIMAL_H_
#define SRC_ANIMAL_H_

#include "veterinary.h"
#include <string>
class Animal {
protected:
    std::string name;
    int age;
    Veterinary *vet;
    inline static int youngest = 9999;
public:
    Animal(std::string name, int age);
    virtual ~Animal(){};
    std::string getName() const;
    int getAge() const;
    Veterinary *getVeterinary() const;
    void setVeterinary(Veterinary *vet);
    static int getYoungest();
    virtual std::string getInfo() const;  // info concerning name, age, name of the veterinary (if any)
    virtual bool isYoung() const = 0;
};


class Dog: public Animal {
    std::string breed;
public:
    Dog(std::string name, int age, std::string breed);
    bool isYoung() const;
    std::string getInfo() const;
};


class Flying {
    int maxVelocity;
    int maxAltitude;
public:
    Flying(int maxv, int maxa);
    std::string getInfo() const;
};


class Bat: public Animal, public Flying {
public:
    Bat(std::string name, int age, int maxv, int maxa);
    bool isYoung() const;
    std::string getInfo() const;
};

#endif /* SRC_ANIMAL_H_ */
