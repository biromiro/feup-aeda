#include "veterinary.h"
#include <sstream>


Veterinary::Veterinary(std::string name, int cod): name(name), codOrder(cod) {}

std::string Veterinary::getName() const {
    return name;
}

std::string Veterinary::getInfo() const {
    return name + ", " + std::to_string(codOrder);
}

