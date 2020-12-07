#pragma once
#include "stdafx.h"
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

class JollyBanker {
private:
	queue<Transaction> transactionList;
	queue<string> tranStr;
	BSTree accountList;

public:
	JollyBanker();
	~JollyBanker();
	void readIn(string file);
	void createTrans();
	void exeTransaction();
	void display();
};

#endif //!ASS3_JOLLYBANKER_H
