#include "Account.h"

/*
* Overloaded output operator
*/
ostream& operator<<(ostream& out, Account& acnt) {
	out << acnt.getFirstName() << " " << acnt.getLastName() << " ID: " << acnt.getAcntID() << endl;
	for (int i = 0; i < 10; i++)
	{
		out << " " << acnt.getFundName(i) << " :$" << acnt.getBal(i);
		out << endl;
	}

	return out;
}


//Default constructor 
Account::Account() {
	firstName = "";
	lastName = "";
	accountID = -1;

	string fundNames[] = {"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond",
	"500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "Value Fund", 
	"Value Stock Index"};
	
	for (int i = 0; i < 10; i++) {
		arrayFund[i].setName(fundNames[i]);
	}
}

//Constructor with parameters
Account::Account(string firstN, string lastN, int accountID) {
	firstName = firstN;
	lastName = lastN;
	this->accountID = accountID;

	string fundNames[] = { "Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond",
	"500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "Value Fund",
	"Value Stock Index" };

	for (int i = 0; i < 10; i++) {
		arrayFund[i].setName(fundNames[i]);
	}
}

//Destructor for the Account class
//Deletes items in the fund array first
//deletes the array last
Account::~Account() {
	for (int i = 0; i < 10; i++) {
		Fund *temp = &arrayFund[i];
		delete temp;
	}
}

/*
* Adds money to the fund account with the amount 
*/
void Account::addToAccount(int fundNum, int amnt) {
	arrayFund[fundNum].addAmount(amnt);
}


/*
* Method subtracts an amount from a specified fund account
* Reocords the transaction in the fund history
*/
bool Account::minusFunds(int fundNum, int amnt, Transaction &frontTrans) {
	//First check if the special cases for fundIDs 0-3
	if (fundNum >= 0 && fundNum <= 3) {//Check fund number id

		if(fundNum == 0 || fundNum == 1){//For money market accounts

			if (arrayFund[fundNum].balCheck(amnt)) {//check amount
				//subtract amount
				arrayFund[fundNum].subAmount(amnt);
				arrayFund[fundNum].recordTrans(frontTrans);//record transaction
				return true;
			}
			else if (arrayFund[0].getBal() + arrayFund[1].getBal() >= amnt) {
				//Withdrawing from account
				if (fundNum == 0) {
					withdFromSimmilarAcct(0, 1, amnt);
				}
				else {
					withdFromSimmilarAcct(1, 0, amnt);
				}
			}
			else {
				//Create error
				error(amnt, getFirstName(), getLastName(), fundNum);
				if (fundNum == 0) {
					withdFromSimmilarAcct(0, 1, amnt);
				}
				else {
					withdFromSimmilarAcct(1, 0, amnt);
				}
				return false;
			}
		}
		else if (fundNum == 2 || fundNum == 3) {//For bond accounts
			//Fund ID 2 or 3
			if (arrayFund[fundNum].balCheck(amnt)) {
				arrayFund[fundNum].subAmount(amnt);
				arrayFund[fundNum].recordTrans(frontTrans);
				return true;
			}
			else if (arrayFund[2].getBal() + arrayFund[3].getBal() >= amnt) {
				if (fundNum == 2) {
					withdFromSimmilarAcct(2, 3, amnt);
				}
				else {
					withdFromSimmilarAcct(3, 2, amnt);
				}
			}
			else {
				//create error
				error(amnt, getFirstName(), getLastName(), fundNum);
				if (fundNum == 2) {
					withdFromSimmilarAcct(2, 3, amnt);
				}
				else {
					withdFromSimmilarAcct(3, 2, amnt);
				}
				return false;
			}
		}
	}
	else {//For every other account from fundID 4-9
		//Checks balance
		if (arrayFund[fundNum].balCheck(amnt)) {
			arrayFund[fundNum].subAmount(amnt);
			arrayFund[fundNum].recordTrans(frontTrans);
			return true;
		}
		else {
			//Erroneous 
			error(amnt, getFirstName(), getLastName(), fundNum);
			return false;
		}
	}
	return false;
}

/*Records the transaction
* Put transaction in history of fund
*/
void Account::recordTrans(const Transaction &trans, int fundNum) {
	arrayFund[fundNum].recordTrans(trans);
}

/*
* Method is used to withdraw money from two linked accounts
* checks if the funds are enough to withdraw from
* Also stores the transaction to fund history
*/
void Account::withdFromSimmilarAcct(int firstFund, int secondFund, int amnt) {

	//If both account have enough money, more than the amnt
	if (arrayFund[firstFund].getBal() + arrayFund[secondFund].getBal() >= amnt) {
		
		int availBal = arrayFund[firstFund].getBal();
		arrayFund[firstFund].subAmount(availBal);//subtract amount
		Transaction addToHistory1('W', getAcntID(), firstFund, availBal);
		arrayFund[firstFund].recordTrans(addToHistory1);
		amnt -= availBal;

		arrayFund[secondFund].subAmount(amnt);
		Transaction addToHistory2('W', getAcntID(), secondFund, amnt);
		arrayFund[secondFund].recordTrans(addToHistory2);
	}
	else {
		
		int availBal = arrayFund[firstFund].getBal();
		if (availBal > amnt) {
			arrayFund[firstFund].subAmount(availBal);
			Transaction addToHistory1('W', getAcntID(), firstFund, availBal);
			arrayFund[firstFund].recordTrans(addToHistory1);
			amnt -= availBal;
		}

		if (arrayFund[secondFund].balCheck(amnt)) {
			arrayFund[secondFund].subAmount(amnt);
			Transaction addToHistory1('W', getAcntID(), secondFund, amnt);
			arrayFund[secondFund].recordTrans(addToHistory1);
		}
		else {
			cout << "ERROR: Not Enough Funds to Withdraw " << amnt << " from " << getFirstName();
			cout << " " << getLastName() << " " << getFundName(secondFund) << endl;
			Transaction addToHistory1('W', getAcntID(), secondFund, "Failed", amnt);
			arrayFund[secondFund].recordTrans(addToHistory1);
		}
	}
}

//Prints the account history
//Goes through each fund of account and prints the fund history
void Account::printHistory() {
	cout << "Transaction History For " << getFirstName() << " " << getLastName() << " By Fund." << endl;
	for (int i = 0; i < 10; i++) {
		arrayFund[i].printHistory();
	}
}

//Prints out transaction history of a specific fund
void Account::printFundHistory(int fundNum) {
	cout << "Transaction History For " << getFirstName() << " ";
	cout << getLastName() << endl;
	arrayFund[fundNum].printHistory();
}

//Prints out an error message for erronous transactions
//adds the transaction to the specified fund
void Account::error(int amnt, string firstN, string lastN, int fundNum) {
	cout << "ERROR: Not Enough Funds to Withdraw " << amnt << " from " << getFirstName();
	cout << " " << getLastName() << " " << getFundName(fundNum) << endl;
	Transaction addToHistory('W', getAcntID(), fundNum, "Failed", amnt);
	arrayFund[fundNum].recordTrans(addToHistory);
}

//Returns object class account ID
int Account::getAcntID() const {
	return accountID;
}

//Returns the specified fund balance
int Account::getBal(int fundNum) const {
	return arrayFund[fundNum].getBal();
}

//Returns the specified funds name
string Account::getFundName(int fundNum) const{
	return arrayFund[fundNum].getName();
}

//Returns the accounts first name
string Account::getFirstName() const{
	return firstName;
}

//Returns the accounts last name
string Account::getLastName() const {
	return lastName;
}
