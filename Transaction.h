#pragma once
#include <string>
#include <iostream>
using namespace std;

#ifndef ASS3_TRANSACTION_H
#define ASS3_TRANSACTION_H

/*
* Creates transactions from strings
* stores first/last names, transaction type, id's, and amount
*/
class Transaction {
	friend ostream& operator<<(ostream &out, const Transaction &trans);

private:
	char transType;
	string firstName;
	string lastName;
	string fail;
	string transaction;
	int accountID, fundID, transferAccountID, transferFundID, amount;

public:
	//Constructors
	Transaction();
	~Transaction();
	Transaction(char type, string firstName, string lastName, int accountNum);//open account
	Transaction(char type, int accountNum, int fundNum, int amnt);//withdraw/desposit account
	Transaction(char type, int accountNum, int fundNum, int amnt, int transferAcntNum, int transferFundNum);//transfer account
	Transaction(char type, int accountNum);//display account
	Transaction(char type, int accountNum, int fundNum);//display fund

	//Constructors create a failed transaction processing
	Transaction(char type, int accountNum, int fundNum, int amount, int transferAcntNum, int transFundNum, string failString);
	Transaction(char type, int accountNum, int fundNum, string failString, int amnt);

	//Getters for data items
	char getTransType() const;
	string getFirstName() const;
	string getLastName() const;
	int getAccountID() const;
	int getFundID() const;
	int getTransferAccountID() const;
	int getTransferFundID() const;
	int getAmount() const;
	string getTransaction()const;
};

#endif //!ASS3_TRANSACTION_H