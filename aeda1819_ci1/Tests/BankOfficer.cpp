/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"


BankOfficer::BankOfficer(): id(0) {}

unsigned int BankOfficer::currentID = 1;

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

BankOfficer::BankOfficer(string name) {
    id = currentID;
    currentID++;
    myAccounts = vector<Account*>();
}

bool BankOfficer::operator>(const BankOfficer &b1) const {
    if(myAccounts.size()==b1.getAccounts().size()){
        return name > b1.getName();
    }
    return myAccounts.size() > b1.getAccounts().size();
}



