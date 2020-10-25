#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>
using namespace std;

bool InfoCard::operator==(const InfoCard &card) const {
    return this->name == card.name;
}

bool InfoCard::operator<(const InfoCard &card) const {
    if (this->frequency == card.frequency)
        return this->name < card.name;
    else
        return card.frequency <  this->frequency;

}

CarPark::CarPark(unsigned cap, unsigned nMaxCli): capacity(cap), numMaxClients(nMaxCli)
{
    freePlaces=cap;
}

vector<InfoCard> CarPark::getClients() const
{
    return clients;
}

unsigned CarPark::getNumPlaces() const
{
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const
{
    return capacity-freePlaces;
}

unsigned CarPark::getNumMaxClients() const
{
    return numMaxClients;
}

unsigned CarPark::getNumClients() const
{
    return clients.size();
}


int CarPark::clientPosition(const string & name) const
{
    InfoCard card;
    card.name = name;
    return sequentialSearch(clients,card);
}

int CarPark::clientPosition(int frequency) const {
    auto it = std::find_if(clients.begin(),clients.end(),[frequency](const InfoCard& card){return card.frequency == frequency;});
    if(it != clients.end()){
        return std::distance(clients.begin(), it);
    }
    return -1;
}

unsigned CarPark::getFrequency(const string &name) const{
    size_t i = clientPosition(name);
    if(i != -1)
        return clients.at(i).frequency;
    else
        throw ClientDoesNotExist(name);
}

bool CarPark::addClient(const string & name)
{
    if (clients.size() == numMaxClients) return false;
    size_t i=clientPosition(name);
    if (i != -1){
        return false;
    } else{
        InfoCard info;
        info.name=name;
        info.present=false;
        clients.push_back(info);
        return true;
    }

}

// TODO: to modify
bool CarPark::removeClient(const string & name)
{
    for (vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++)
        if ( (*it).name == name ) {
            if ( (*it).present == false ) {
                clients.erase(it);
                return true;
            }
            else return false;
        }
    return false;
}

bool CarPark::enter(const string & name)
{
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == true) return false;
    clients[pos].present = true;
    clients[pos].frequency++;
    freePlaces--;
    return true;
}

bool CarPark::leave(const string & name)
{
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == false) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}


InfoCard CarPark::getClientAtPos(unsigned p) const
{
    if(clients.size()<= p)
        throw PositionDoesNotExist(p);
    return clients.at(p);
}


void CarPark::sortClientsByFrequency()
{
    insertionSort(clients);
}

void CarPark::sortClientsByName()
{
    std::sort(clients.begin(),clients.end(),[](const InfoCard& card1, const InfoCard& card2){return card1.name < card2.name;});
}

vector<string> CarPark::clientsBetween(unsigned f1, unsigned f2)
{
    vector<string> names;
    insertionSort(clients);
    for(const auto& elem: clients){
        if(elem.frequency>=f1 && elem.frequency<=f2)
            names.push_back(elem.name);
    }
    return names;

}


ostream & operator<<(ostream & os, const CarPark & cp)
{
    for(const auto& elem: cp.clients){
        os << elem.name << ((elem.present) ? "Present" : "Not Present") << elem.frequency << '\n';
    }
    return os;
}


