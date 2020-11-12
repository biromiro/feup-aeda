#ifndef SRC_HOTEL_H_
#define SRC_HOTEL_H_

#include <vector>
#include <list>

template <class Chamber>
class Hotel {
	std::vector<Chamber *> chambers;
	const unsigned int maxCapacity;
	const std::string city;
    std::list<Chamber> reservationsDone;
public:
	Hotel(int size, std::string municipality);
	~Hotel();
	std::vector<Chamber *> getChambers() const;
	void setChambers(std::vector<Chamber *> chambers);
	int getCapacity() const;
    std::list<Chamber> getReservationsDone() const;
	bool addChamber(Chamber *chamber);
    void addReservationDone(Chamber chamber);
    Chamber* removeChamber(std::string code, int floor);
	float avgArea(int floor) const;
	void sortChambers();
	bool doReservation(std::string code, int floor);
    std::list<Chamber> roomsNeverReserved() const;
};

class NoSuchChamberException {
public:
	NoSuchChamberException() { }
};

class NoSuchFloorException {
private:
    int floor;
public:
    NoSuchFloorException(int floor) : floor(floor){};

    int getFloor() const {return floor;}
};

template <class Chamber>
Hotel<Chamber>::Hotel(int size, std::string municipality) : maxCapacity(size), city(municipality) {
}

template <class Chamber>
Hotel<Chamber>::~Hotel(){
	typename std::vector<Chamber *>::const_iterator it;
	for (it=chambers.begin(); it!=chambers.end(); it++) {
		delete *it;
	}
}

template<class Chamber>
std::vector<Chamber *> Hotel<Chamber>::getChambers() const {
	return chambers;
}

template<class Chamber>
void Hotel<Chamber>::setChambers(std::vector<Chamber*> chambers) {
	this->chambers = chambers;
}

template<class Chamber>
int Hotel<Chamber>::getCapacity() const {
	return maxCapacity;
}

template<class Chamber>
void Hotel<Chamber>::addReservationDone(Chamber chamber) {
    reservationsDone.push_back(chamber);
}

template<class Chamber>
std::list<Chamber> Hotel<Chamber>::getReservationsDone() const {
    return reservationsDone;
}

template<class Chamber>
bool Hotel<Chamber>::addChamber(Chamber *chamber) {
    for(const auto elem: chambers){
        if((*elem) == (*chamber))
            return false;
    }
    if (maxCapacity > chambers.size()){
        chambers.push_back(chamber);
        return true;
    }
    return false;
}

template<class Chamber>
void Hotel<Chamber>::sortChambers() {
    sort(chambers.begin(),chambers.end(),[](Chamber* chamber1, Chamber* chamber2)
    {return (*chamber1)<(*chamber2);});
}

template<class Chamber>
Chamber* Hotel<Chamber>::removeChamber(std::string code, int floor) {
    for(const auto elem: chambers){
        if(elem->getCode() == code && elem->getFloor() == floor){
            chambers.erase(remove(chambers.begin(),chambers.end(),elem),chambers.end());
            return elem;
        }
    }
    throw NoSuchChamberException();
}

template<class Chamber>
float Hotel<Chamber>::avgArea(int floor) const {
    float avgArea = 0.0;
    size_t numOfChambers = 0;
    for(const auto elem: chambers){
        if(elem->getFloor() == floor){
            avgArea += elem->getArea();
            numOfChambers++;
        }
    }
    if(avgArea == 0.0){
        throw NoSuchFloorException(floor);
    }
    return avgArea/numOfChambers;
}

template<class Chamber>
bool Hotel<Chamber>::doReservation(std::string code, int floor){
    for(const auto elem: chambers){
        if(elem->getFloor() == floor && elem->getCode() == code
        && elem->getReservation() == false){
            elem->setReservation(true);
            addReservationDone(*elem);
            return true;
        }
    }
    return false;
}

template<class Chamber>
std::list<Chamber> Hotel<Chamber>::roomsNeverReserved() const {
    std::list<Chamber> res;
    for(const auto elem: chambers){
        if(find(reservationsDone.begin(),reservationsDone.end(),*elem) == reservationsDone.end()){
            res.push_back(*elem);
        }
    }
    return res;
}


#endif /* SRC_HOTEL_H_ */
