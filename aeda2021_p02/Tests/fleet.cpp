#include "fleet.h"
#include <string>
#include <algorithm>

using namespace std;

vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}

void Fleet::addVehicle(Vehicle *v1){
    vehicles.push_back(v1);
}

int Fleet::numVehicles() const {
    return vehicles.size();
}

bool opminor(Vehicle* const v1, Vehicle* const v2){
    if(v1->getYear() == v2->getYear())
        return v1->getMonth() < v2->getMonth();
    else
        return v1->getYear() < v2->getYear();
}

int Fleet::lowestYear() const {
    if(numVehicles() == 0)
        return 0;
    auto oldervehicle = std::min_element(vehicles.begin(), vehicles.end(), opminor);
    return (*oldervehicle)->getYear();
}


vector<Vehicle*> Fleet::operator()(int y1) const {
    vector<Vehicle*> vecToRet;
    for(const auto& vehicle: vehicles){
        if(vehicle->getYear() == y1)
            vecToRet.push_back(vehicle);
    }
    return vecToRet;
}

float Fleet::totalTax() const{
    float totaltax = 0;
    for(const auto& vehicle: vehicles){
        totaltax += vehicle->calculateTax();
    }
    return totaltax;
}

bool isLower(Vehicle* v1,int y1){

}

unsigned int Fleet::removeOldVehicles(int y1) {
    unsigned int initialSize = vehicles.size();
    auto end = std::remove_if(vehicles.begin(),vehicles.end(), [&y1](const Vehicle* v1){return v1->getYear() <= y1;});
    vehicles.erase(end,vehicles.end());
    return initialSize-vehicles.size();
}

ostream& operator<<(ostream & o, const Fleet & f){
    for(const auto& vehicle: f.vehicles){
        vehicle->info(o);
    }
    return o;
}