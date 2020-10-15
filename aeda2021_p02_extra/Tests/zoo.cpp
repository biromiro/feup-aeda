#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <numeric>

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1) {
    animals.push_back(a1);
}

std::string Zoo::getInfo() const {
    std::string info = "";
    for(const auto& elem: animals){
        info += elem->getInfo() + ";";
    }
    return info;
}

bool Zoo::isYoung(std::string nameA){
    auto it = std::find_if(animals.begin(), animals.end(), [nameA](const Animal* a){return a->getName() == nameA;});
    if(it != animals.end()){
        return (*it)->isYoung();
    }else{
        return false;
    }
}

/**
 * Allocates the veterinarians of a text file to the respective vector
 *
 * @param isV the input stream containing the vectors
 */

void Zoo::allocateVeterinarians(std::istream &isV) {
    std::string name,line;
    long code;
    while(std::getline(isV,line)){
        if(isalpha(line[0]))
            name = line.substr(0,line.size()-1);
        else{
            code = stoi(line);
            veterinarians.push_back(new Veterinary(name,code));
        }
    }
    size_t vet = 0;
    for(const auto& elem: animals){
        elem->setVeterinary(veterinarians[vet]);
        vet += 1 % veterinarians.size();
    }
}

bool Zoo::removeVeterinary(std::string nameV) {
    auto it = std::find_if(veterinarians.begin(),veterinarians.end(),[nameV](Veterinary *vet){return vet->getName() == nameV;});
    size_t index = std::distance(veterinarians.begin(), it);
    if(it != veterinarians.end()){
        for(const auto& elem: animals){
            if(veterinarians.size() > 1)
                if(elem->getVeterinary() == (*it))
                    elem->setVeterinary(veterinarians[(index + 1)%veterinarians.size()]);
                else
                    elem->setVeterinary(NULL);
        }
        veterinarians.erase(it);
        return true;
    }else
        return false;
}

bool Zoo::operator<(Zoo &zoo2) const {
    size_t sumZoo1 = std::accumulate(this->animals.begin(),this->animals.end(),0,
                                     [](size_t acc, Animal *animal){return acc + animal->getAge();});
    size_t sumZoo2 = std::accumulate(zoo2.animals.begin(),zoo2.animals.end(),0,
                                     [](size_t acc, Animal *animal){return acc + animal->getAge();});
    return  sumZoo1 < sumZoo2;
}
