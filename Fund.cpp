#include "Fund.h"
//Default constructor
Fund::Fund()
{
	balance = 0;
	fundName = "";
}

//destructor for fund class
Fund::~Fund() {}

//Adds money to the fund balance
bool Fund::addAmount(int amntIn) {
	if (amntIn <= 0) return false;
	balance += amntIn;
	return true;
}

//Subtracts money from fund
bool Fund::subAmount(int numToSub) {
	if (numToSub <= 0) return false;
	balance -= numToSub;
	return true;
}

//Checks if the balance has enough to subtract from
//subtract the number parameter
bool Fund::balCheck(int numToSub){
	if (numToSub < 0) return false;
	if (this->balance >= numToSub) return true;
	return false;
}

//Adds the transaction to a vector to store history of transactions
bool Fund::recordTrans(const Transaction &trans) {
	this->history.push_back(trans);
	return true;
}

//Prints the funds history of transactions
void Fund::printHistory() {
	if (history.size() == 0) return;

	cout << fundName << ": $" << balance << endl;
	for (int i = 0; i < history.size(); i++) {
		cout << "  " << history[i] << endl;
	}
}

//Prints out the history of a specified fund
void Fund::printHistoryOfFund() {
	cout << fundName << ": $" << balance << endl;
	for (int i = 0; i < history.size(); i++) {
		cout << "  " << history[i] << endl;
	}
}

//sets the fund name
void Fund::setName(string name) {
	this->fundName = name;
}

//Retrieves the balance of the fund
int Fund::getBal() const{
	return balance;
}

//Retrieves the name of the fund
string Fund::getName() const {
	return fundName;
}