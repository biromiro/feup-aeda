/*
 * BankOfficer.h
 */

#ifndef SRC_BANKOFFICER_H_
#define SRC_BANKOFFICER_H_

#include "Account.h"
#include <string>
#include <vector>

class BankOfficer {
	unsigned int id;
	string name;
	vector<Account *> myAccounts;
	static unsigned int currentID;
public:
	BankOfficer();
	void setName(string nm);
	void addAccount(Account *a);
	void addAccount(vector<Account *> accounts);
	string getName() const;
	vector<Account *> getAccounts() const;
	unsigned int getID() const;
	bool operator>(const BankOfficer& b1) const;

	//-------
	BankOfficer(string nm);
	vector<Account *> removeBankOfficer(string name);
};

#endif /* SRC_BANKOFFICER_H_ */
