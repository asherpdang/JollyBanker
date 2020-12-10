#include "Transaction.h"

/*
* Overloaded output operator to print out the transaction
*/
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

/*
* Open account transaction
* stores type, first/last name, and account number
*/
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

/*
* Makes a transaction for withdrawing and depositing transactions
* stores transaction type, accountID, fundID, and amount
*/
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

	transaction = transType + " " + to_string(accountID) + to_string(fundID) + " " + to_string(amount);
}

/*
* Makes transactions for transfer transactions
* stores transaction type, accountID, fundID, amount, transferAccountID, transferFundID
*/
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

	transaction = transType + " " + to_string(accountID) + to_string(fundID) + " " + to_string(amount) + " "
		+ to_string(transferAccountID) + to_string(transferFundID);

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

	transaction = transType + " " + to_string(accountID);
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

	transaction = transType + " " + to_string(accountID) + to_string(fundID);

}


//ERROR transaction creation for transfer transactions
//Takes an added failstring from transfer transaction
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


//ERROR transaction creation for account not found
//Takes and extra failstring from transaction
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
//returns a character
char Transaction::getTransType() const {
	return transType;
}

//Returns the first name
//retrieves first name string
string Transaction::getFirstName() const {
	return firstName;
}

//Returns the last name
//retrieves last name string
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

//Returns the string of the transaction
string Transaction::getTransaction() const {
	return transaction;
}
