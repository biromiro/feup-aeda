#ifndef ZOO_H_
#define ZOO_H_

#include "animal.h"
#include <vector>

class Zoo {
	std::vector<Animal *> animals;
	std::vector<Veterinary *> veterinarians;
public:
	unsigned numAnimals() const;
	unsigned numVeterinarians() const;
    void addAnimal(Animal *a1);
    std::string getInfo() const;
    bool isYoung(std::string nameA);
    void allocateVeterinarians(std::istream &isV);
    bool removeVeterinary(std::string nameV);
    bool operator < (Zoo& zoo2) const;
};


#endif /* ZOO_H_ */
