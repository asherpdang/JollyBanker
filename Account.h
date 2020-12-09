#pragma once
#include "Transaction.h"
#include "Fund.h"
#include <iostream>
#include <string>
using namespace std;

#ifndef ASS3_ACCOUNT_H
#define ASS3_ACCOUNT_H

/*
* Creates account classes that store 10 funds
* handles subtracting/adding/transferring money
*/
class Account {
	friend ostream& operator<<(ostream& out, Account& acnt);

private:
	string firstName, lastName;
	int accountID;
	Fund arrayFund[10];

public:
	//Constructors
	Account();
	Account(string firstName, string lastName, int accountID);
	~Account();

	//Methods 
	void addToAccount(int fundNum, int amnt);
	bool minusFunds(int fundNum, int amnt, Transaction &frontTrans);
	void recordTrans(const Transaction &trans, int fundNum);
	void withdFromSimmilarAcct(int primaryFund, int secondaryFund, int amnt);
	void printHistory();
	void printFundHistory(int fundNumber);
	void error(int amnt, string firstN, string lastN, int fundNum);

	//Getters 
	int getAcntID() const;
	int getBal(int fundNum)const;
	string getFundName(int fundNum) const;
	string getFirstName()const;
	string getLastName()const;
};

#endif //!ASS3_ACCOUNT_H