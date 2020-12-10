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
	void addToAccount(int fundNum, int amnt);//add money to account
	bool minusFunds(int fundNum, int amnt, Transaction &frontTrans);//subtract money from account
	void recordTrans(const Transaction &trans, int fundNum);//records transacion in specified fundID history
	void withdFromSimmilarAcct(int primaryFund, int secondaryFund, int amnt);//Takes money from 1 fund and another fund if not enough funds
	void printHistory();//prints whole history
	void printFundHistory(int fundNumber);//prints specified history fund
	void error(int amnt, string firstN, string lastN, int fundNum);//error 

	//Getters 
	int getAcntID() const;//gets account id
	int getBal(int fundNum)const;//gets balance of account
	string getFundName(int fundNum) const;//gets fund name
	string getFirstName()const;//gets first name
	string getLastName()const;//gets last name
};

#endif //!ASS3_ACCOUNT_H