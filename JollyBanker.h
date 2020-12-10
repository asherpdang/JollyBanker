#pragma once
#include <queue>
#include "BSTree.h"
#include "Transaction.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#ifndef ASS3_JOLLYBANKER_H
#define ASS3_JOLLYBANKER_H

/*
* Bank class takes in a text file of good formatted
* Reads the file and stores the transactions
* Executes the transactions making accounts and moving around funds
*/
class JollyBanker {
private:
	queue<Transaction> transactionList;//stores transaction objects to be executed
	queue<string> tranStr;//takes from file and store transaction strings
	BSTree accountList;//bstree to hole accounts

public:
	JollyBanker();//constructor
	~JollyBanker();

	void readIn(string file);//Reads file, store each line in queue as strings
	void createTrans();//reads the queue and create queue of transactions to be done
	void exeTransaction();//reads the queue of transactions and executes them until nothing left in queue
	void display();//Finally display the balances and funds of all users
};

#endif //!ASS3_JOLLYBANKER_H
