#pragma once
#include "Account.h"

#ifndef ASS3_BSTREE_H
#define ASS3_BSTREE_H

class BSTree {
private:
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
	Node* root;
	bool recInsert(Node* current, Account* acnt); 
	void recPrint(Node *current)const;

public:
	BSTree();
	~BSTree();

	bool Insert(Account*);

	//Retrieve object, first parameter is the ID of the account
	//Second parameter holds pointer to found object, NULL if not found
	bool Retrieve(const int&, Account*&)const;

	//displays the contents of a tree to cout;
	void Display() const;
	void Empty();
	bool isEmpty();
	void delNode(Node*);
};

#endif //!ASS3_BSTREE_H
