#pragma once
#include "Transaction.h"
#include <string>
#include <vector>
#include <iostream>

#ifndef ASS3_FUND_H
#define ASS3_FUND_H

/*Fund class stores a fund name, balance, and a vector of transactions
* Tracks the transactions related to this fund
*/
class Fund {

private:
	string fundName;
	int balance;
	vector<Transaction> history;

public:
	Fund();
	~Fund();

	bool addAmount(int amntIn);//adds money to balance
	bool subAmount(int numToSub);//subtracts amount of balance
	bool balCheck(int numToSub);//checks if fund has enough funds
	bool recordTrans(const Transaction &trans);//stores the transaction
	void printHistoryOfFund();//prints history
	void printHistory();
	void setName(string name);//sets the fund name
	int getBal() const;//gets the balance
	string getName() const;//retrieves name
};

#endif //!ASS3_FUND_H
