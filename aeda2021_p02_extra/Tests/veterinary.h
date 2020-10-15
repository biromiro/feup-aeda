#ifndef SRC_VETERINARY_H_
#define SRC_VETERINARY_H_

#include <string>

class Veterinary {
    std::string name;
    long codOrder;
public:
    Veterinary(std::string name, int cod);
    std::string getName() const;
    std::string getInfo() const;
};


#endif /* SRC_VETERINARY_H_ */
