#pragma once
#include "Transaction.h"
#include <string>
#include <vector>
#include <iostream>

#ifndef ASS3_FUND_H
#define ASS3_FUND_H

class Fund {

private:
	string fundName;
	int balance;
	vector<Transaction> history;

public:
	Fund();
	~Fund();

	bool addAmount(int amntIn);
	bool subAmount(int numToSub);
	bool balCheck(int numToSub);
	bool recordTrans(const Transaction &trans);
	void printHistoryOfFund();
	void printHistory();
	void setName(string name);
	int getBal() const;
	string getName() const;
};

#endif //!ASS3_FUND_H
