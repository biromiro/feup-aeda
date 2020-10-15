#include "animal.h"

/**
 * Constructor of the animal class.
 *
 * @param name the name of the animal
 * @param age the age of the animal
 */
Animal::Animal(std::string name, int age) : name(name), age(age), vet(NULL){
    if(age<youngest){
        youngest = age;
    }
}

/**
 * Name getter
 *
 * @return returns the name of the animal
 */
std::string Animal::getName() const {
	return name;
}

/**
 * Youngest getter
 *
 * @return the yougest age of an existing animal
 */

int Animal::getYoungest() {
    return youngest;
}

int Animal::getAge() const {
    return age;
}

void Animal::setVeterinary(Veterinary *vet) {
    this->vet = vet;
}

Veterinary *Animal::getVeterinary() const {
    return vet;
}

std::string Animal::getInfo() const {
    if(vet != NULL)
        return name + ", " + std::to_string(age) + ", " + vet->getInfo();
    else
        return name + ", " + std::to_string(age);
}

Dog::Dog(std::string name, int age, std::string breed): Animal(name,age) {
    this->breed = breed;
}

bool Dog::isYoung() const {
    return (getAge() < 5);
}

std::string Dog::getInfo() const {
    return Animal::getInfo() + ", " + breed;
}

Flying::Flying(int maxv, int maxa): maxVelocity(maxv), maxAltitude(maxa) {}

std::string Flying::getInfo() const {
    return std::to_string(maxVelocity) + ", " + std::to_string(maxAltitude);
}

Bat::Bat(std::string name, int age, int maxv, int maxa): Animal(name, age), Flying(maxv, maxa){}

bool Bat::isYoung() const {
    return (getAge() < 4);
}

std::string Bat::getInfo() const {
    return Animal::getInfo() + ", " + Flying::getInfo();
}