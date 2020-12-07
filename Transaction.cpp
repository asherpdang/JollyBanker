#include "Transaction.h"

ostream& operator<<(ostream& out, const Transaction& trans) {
	if (trans.fail.empty()) {
		if (trans.transType == 'D' || trans.transType == 'd' || trans.transType == 'W' || trans.transType == 'w') {
			out << " " << trans.transType << " " << trans.accountID << trans.fundID << " " << trans.amount;
		}
		else if (trans.transType == 'T' || trans.transType == 't') {
			out << " " << trans.transType << " " << trans.accountID << trans.fundID << " " << trans.amount;
			out << " " << trans.transferAccountID << trans.fundID;
		}

	}
	else {
		if (trans.transType == 'D' || trans.transType == 'd' || trans.transType == 'W' || trans.transType == 'w') {
			out << " " << trans.transType << " " << trans.accountID << trans.fundID << " " << trans.amount << " (FAILED)";
		}
		else if (trans.transType == 'T' || trans.transType == 't') {
			out << " " << trans.transType << " " << trans.accountID << trans.fundID << " " << trans.amount;
			out << " " << trans.transferAccountID << trans.fundID << " (FAILED)";
		}
	}
	return out;
}

//Default constructor
Transaction::Transaction() {}

//destructor
Transaction::~Transaction() {};

Transaction::Transaction(char type, string firstName, string lastName, int accountNum) {
	transType = type;
	this->firstName = firstName;
	this->lastName = lastName;
	this->accountID = accountNum;
	string fail = "";
	fundID = -1;
	transferAccountID = -1;
	transferFundID = -1; 
	amount = -1;
	transaction = transType + " " + firstName + " " + lastName + " " + to_string(accountID);
}

Transaction::Transaction(char type, int accountNum, int fundNum, int amnt) {
	transType = type;
	this->accountID = accountNum;
	this->fundID = fundNum;
	amount = amnt;
	firstName = "";
	lastName = "";
	fail = "";
	transferAccountID = -1;
	transferFundID = -1;

	if (type == 'W' || type == 'w') {
		transaction = "Withdraw $" + to_string(amnt) + " from fundID: " + to_string(fundNum)
			+ " in accountID: " + to_string(accountNum);
	}
	else {
		transaction = "Desposit $" + to_string(amnt) + " to fundID: " + to_string(fundNum)
			+ " in accountID: " + to_string(accountNum);
	}
	
}

Transaction::Transaction(char type, int accountNum, int fundNum, int amnt, int transferAcntNum, int transferFundNum) {
	transType = type;
	accountID = accountNum;
	fundID = fundNum;
	amount = amnt;
	transferAccountID = transferAcntNum;
	transferFundID = transferFundNum;
	firstName = "";
	lastName = "";
	fail = "";

	string fundNames[] = { "Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond",
	"500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "Value Fund",
	"Value Stock Index" };

	int acntNum1 = accountNum / 10;
	int acntNum2 = transferAcntNum / 10;

	int fundIndex1 = accountNum % 10;
	int fundIndex2 = transferAccountID % 10;

	if (acntNum1 == acntNum2) {
		transaction = "Transfer $" + to_string(amnt) + " from Client: " + to_string(accountNum) + "'s "
			+ fundNames[fundIndex1] + " to " + fundNames[fundIndex2];
	}
	else {
		transaction = "Transfer $" + to_string(amnt) + " from Client: " + to_string(accountNum) + "'s "
			+ fundNames[fundIndex1] + " to Client: " + to_string(transferAcntNum) + " " +fundNames[fundIndex2];
	}
}

//This constructor stores the transaction that displays all all transactions of an accountID
Transaction::Transaction(char type, int accountNum) {
	transType = type;
	accountID = accountNum;
	fundID = -1;
	amount = -1;
	transferAccountID = -1;
	transferFundID = -1;
	firstName = "";
	lastName = "";
	fail = "";

	transaction = "Display the History of all transactions of all accounts for client  " + to_string(accountNum);
}


//This constructor keeps track of a display hisotry transaction of a
//specified fund from the client
Transaction::Transaction(char type, int accountNum, int fundNum) {
	fundID = fundNum;
	transType = type;
	accountID = accountNum;
	amount = -1;
	transferAccountID = -1;
	transferFundID = -1;
	firstName = "";
	lastName = "";
	fail = "";

	string fundNames[] = { "Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond",
	"500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "Value Fund",
	"Value Stock Index" };

	transaction = "Display the History for all transactions on the " + fundNames[fundNum] + " for client " + to_string(accountNum);
}


//ERROR transaction
Transaction::Transaction(char type, int accountNum, int fundNum, int amount, int transAcntNum, int transFundNum, string failString) {
	transType = type;
	accountID = accountNum;
	fundID = fundNum;
	this->amount = amount;
	transferAccountID = transAcntNum;
	transferFundID = transFundNum;
	firstName = "";
	lastName = "";
	fail = failString;

	transaction = fail;
}


//ERROR transaction
Transaction::Transaction(char type, int accountNum, int fundNum, string failString, int amnt) {
	transType = type;
	accountID = accountNum;
	fundID = fundNum;
	this->amount = amnt;
	transferAccountID = -1;
	transferFundID = -1;
	firstName = "";
	lastName = "";
	fail = failString;

	transaction = fail;
}


//Retrieves the transaction type character
char Transaction::getTransType() const {
	return transType;
}

//Returns the first name
string Transaction::getFirstName() const {
	return firstName;
}

//Returns the last name
string Transaction::getLastName() const {
	return lastName;
}

//Returns the accountID
int Transaction::getAccountID() const{
	return accountID;
}

//Returns the fundId of transaction
int Transaction::getFundID() const {
	return fundID;
}

//returns the transfer account id
int Transaction::getTransferAccountID() const {
	return transferAccountID;
}

//returns the transfer fund ID
int Transaction::getTransferFundID()const {
	return transferFundID;
}

//Returns the amount of the transaction
int Transaction::getAmount() const {
	return amount;
}

string Transaction::getTransaction() const {
	return transaction;
}
