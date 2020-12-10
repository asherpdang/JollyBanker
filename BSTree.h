#pragma once
#include "Account.h"

#ifndef ASS3_BSTREE_H
#define ASS3_BSTREE_H

/*
* Data structure that stores account objects
* sorts accounts by account id, 4 digits
*/
class BSTree {
private:
	//Nodes structure to create the bs tree
	struct Node {
		Node* left = NULL;
		Node* right = NULL;
		Account* pAcct;
		
		Node(Account* acnt) {
			pAcct = acnt;
			left = NULL;
			right = NULL;
		}
	};
	Node* root;//root to start the bs tree
	bool recInsert(Node* current, Account* acnt); //recursively inserts account
	void recPrint(Node *current)const;// prints out the bstree

public:
	BSTree();//constructors
	~BSTree();

	bool Insert(Account*);//inserts an account object

	//Retrieve object, first parameter is the ID of the account
	//Second parameter holds pointer to found object, NULL if not found
	bool Retrieve(const int&, Account*&)const;

	//displays the contents of a tree to cout;
	void Display() const;//display account/ history of the bstree
	void Empty();//frees memory in tree
	bool isEmpty();//checks if the tree is empty
	void delNode(Node*);//deletes node
};

#endif //!ASS3_BSTREE_H
