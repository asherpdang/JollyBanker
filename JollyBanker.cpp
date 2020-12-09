#include "JollyBanker.h"
#include "Transaction.h"
#include "Account.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>

//Author: Asher Dang
//CSS 342: Program 5

//Default constructor
JollyBanker::JollyBanker() {}

//Destructor
JollyBanker::~JollyBanker() {}


/*
* Reads a file with premade transactions formatted already
* creates appropriate transaction objects for each transaction
* Stores the transaction in a queue
*/
void JollyBanker::readIn(string file){

	ifstream inFile; 
	inFile.open(file);
	string strLine;
	
	//Checking that file is not empty 
	if (!inFile) {
		cout << "Cannot Open File!" << endl;
	}

	while (getline(inFile,strLine)) {//Putting every line to a queue as strings
		tranStr.push(strLine);
	}
	inFile.close();//close file
}

/*
* Creates transactions from the queue of strings formatted
* Reads the first character and creates a transaction depending on what 
* type of transaction it is
* Stores these transactions in another queue of transactions to be executed
*/
void JollyBanker::createTrans() {
	while (!tranStr.empty()){//When string queue is not empty
		string makeTran = tranStr.front();//get the first item at fron of queue

		if (tranStr.empty()) break;

		istringstream parseLine(makeTran);//Parses line into char
		char transType;//stores a transaction type character
		parseLine >> transType;//Puts first char into transaction type

		//Make transaction objects depending on the transaction types
		if (transType == 'O' || transType == 'o') {
			//Create transaction to open an account
			string firstName, lastName;
			int acntID;
			parseLine >> firstName >> lastName >> acntID;
			Transaction addToQueue(transType, firstName, lastName, acntID);
			transactionList.push(addToQueue);
		}
		else if (transType == 'W' || transType == 'w' || transType == 'D' || transType == 'd') {
			//Creates transaction for withdraw or deposit type transactions
			int acntID, fundID, amnt;
			parseLine >> acntID >> amnt;
			fundID = acntID % 10;
			acntID = acntID / 10;
			Transaction addToQueue(transType, acntID, fundID, amnt);
			transactionList.push(addToQueue);
		}
		else if (transType == 'T' || transType == 't') {
			//Create a transaction of transfers from one type to another
			int acntID, fundID, amnt, transAcntID, transFundID;
			parseLine >> acntID >> amnt >> transAcntID;
			fundID = acntID % 10;
			acntID = acntID / 10;
			transFundID = transAcntID % 10;
			transAcntID = transAcntID / 10;
			Transaction addToQueue(transType, acntID, fundID, amnt, transAcntID, transFundID);
			transactionList.push(addToQueue);
		}
		else if(transType == 'H' || transType == 'h'){
			//A transaction to display the history of a specified account or fund
			int acntID;
			parseLine >> acntID;
			if (acntID >= 1000 || acntID <= 9999) {
				Transaction addToQueue(transType, acntID);
				transactionList.push(addToQueue);
			}
			else {
				int fundID = acntID % 10;
				int acntID = acntID / 10;
				Transaction addToQueue(transType, acntID, fundID);
				transactionList.push(addToQueue);
			}
		}
		else {
			cout << "ERROR: Reading Line" << endl;//Error from reading a line in the file
		}
		tranStr.pop();
	}
}

/*
* Takes the queue of transactions and executes them
* Open accounts, withdrawing/depositing money, transferring money, or displaying history
* of a pecified account or fund
*/
void JollyBanker::exeTransaction() {
	//When the transaction list is not empty
	while (!transactionList.empty()) {

		Transaction frontTrans = transactionList.front();

		if (frontTrans.getTransType() == 'O' || frontTrans.getTransType() == 'o') {
			//Create an account for a person
			Account* acnt = new Account(frontTrans.getFirstName(), frontTrans.getLastName(), frontTrans.getAccountID());
			accountList.Insert(acnt);
		}
		else if (frontTrans.getTransType() == 'D' || frontTrans.getTransType() == 'd') {
			//Deposit money into an account
			int acntID = frontTrans.getAccountID();
			int fundID = frontTrans.getFundID();
			int amnt = frontTrans.getAmount();
			Account* acnt;
			if (accountList.Retrieve(acntID, acnt)) {
				acnt->addToAccount(fundID, amnt);
				acnt->recordTrans(frontTrans, fundID);
			}
		}
		else if (frontTrans.getTransType() == 'W' || frontTrans.getTransType() == 'w') {
			//Withdraw money from an account
			int acntID = frontTrans.getAccountID();
			int fundID = frontTrans.getFundID();
			int amnt = frontTrans.getAmount();
			Account* acnt;

			/*********/
			if (accountList.Retrieve(acntID, acnt)) {
				acnt->minusFunds(fundID, amnt, frontTrans);
			}
		}
		else if (frontTrans.getTransType() == 'T' || frontTrans.getTransType() == 't') {
			//Transfer money from an account/fund to another account/fund
			int acntID = frontTrans.getAccountID();
			int fundID = frontTrans.getFundID();
			int transAcntID = frontTrans.getTransferAccountID();
			int transFundID = frontTrans.getTransferFundID();
			int amnt = frontTrans.getAmount();
			Account * to, * from;

			if (accountList.Retrieve(acntID, to) && accountList.Retrieve(transAcntID, from)) {
				if (to->minusFunds(fundID,amnt, frontTrans)) {
					from->addToAccount(transFundID, amnt);
					from->recordTrans(frontTrans, transFundID);
				}
				else {
					//Error message when the transaction is invalid, not enough money from an accound/fund
					cout << "ERROR: Not Enough Funds to Transfer " << to_string(amnt) << " from " << from->getAcntID();
					cout << fundID << " to " << to->getAcntID() << transAcntID << endl;
					Transaction addToHistory('T', acntID, fundID, amnt, transAcntID, transFundID, "Failed");
					from->recordTrans(addToHistory, transFundID);
				}
			}
		}
		else if (frontTrans.getTransType() == 'H' || frontTrans.getTransType() == 'h') {
			//Displays history of an account
			if (frontTrans.getAccountID() >= 10000 && frontTrans.getAccountID() <= 99999) {
				Account* acnt;
				int fundID = frontTrans.getAccountID() % 10;
				int acntID = frontTrans.getAccountID() / 10;
				if (accountList.Retrieve(acntID, acnt)) {
					acnt->printFundHistory(fundID);
					cout << endl;
				}
			}
			else if (frontTrans.getAccountID() >= 1000 && frontTrans.getAccountID() <= 9999) {
				Account* acnt;
				int acntID = frontTrans.getAccountID();
				if (accountList.Retrieve(acntID, acnt)) {
					acnt->printHistory();
					cout << endl;
				}
			}
		}
		transactionList.pop();
	}
}

//Displays all accounts and funds
void JollyBanker::display() {
	cout << endl;
	cout << "Proccessing Done. Final Balances:" << endl;
	accountList.Display();
}