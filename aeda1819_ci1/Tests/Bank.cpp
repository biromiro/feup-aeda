/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

double Bank::getWithdraw(string cod1) const{
    double ammount = 0;
    for(auto elem: accounts){
        if(elem->getCodH() == cod1)
            ammount += elem->getWithdraw();
    }
	return ammount;
}


vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res;
	for(auto elem: bankOfficers){
	    if(elem.getName() == name) {
	        auto elemAcc = elem.getAccounts();
            for(const auto& acc: elemAcc) res.push_back(acc);
        }
	}
	bankOfficers.erase(remove_if(bankOfficers.begin(),bankOfficers.end(),[name](const BankOfficer& b1){
	    return b1.getName() == name;
	}),bankOfficers.end());
	return res;
}

const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    for(auto& elem: bankOfficers){
        if(elem.getName() == name){
            elem.addAccount(ac);
            return elem;
        }
    }
    throw NoBankOfficerException(name);
}

void Bank::sortAccounts() {
    sort(accounts.begin(),accounts.end(),[](Account* acc1,Account* acc2){
        if(acc1->getBalance() == acc2->getBalance()){
            return acc1->getCodIBAN() < acc2->getCodIBAN();
        }
        return acc1->getBalance() < acc2->getBalance();
    });
}

const string &NoBankOfficerException::getName() const {
    return name;
}
