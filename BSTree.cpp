#include "BSTree.h"

//Initalizing the BSTree constructor
BSTree::BSTree() {
	root = NULL;
}

//Destructor that cleans up memory 
BSTree::~BSTree() {
	Empty();
}

//Inserts an account item into the bstree
bool BSTree::Insert(Account *acnt) {

	int acntID = acnt->getAcntID();
	if (acntID < 1000 || acntID > 9999) {
		cout << "ERROR: Account Number Not Valid!" << endl;
		return false;
	}

	if (root == NULL) {
		root = new Node(acnt);
		return true;
	}
	else {
		Node* current = root;
		recInsert(current, acnt);
	}
	return false;
}

/*Recursively inserts the account into the bstree*/
bool BSTree::recInsert(Node* current, Account* acnt) {

	if (acnt->getAcntID() < current->pAcct->getAcntID()) {

		if (current->left == NULL) {
			Node* newAcnt = new Node(acnt);
			current->left = newAcnt;
			return true;
		}
		else {
			return recInsert(current->left, acnt);
		}
	}
	else if(acnt->getAcntID() > current->pAcct->getAcntID())
	{
		if(current->right == NULL){
			Node* newAcnt = new Node(acnt);
			current->right = newAcnt;
			return true;
		}
		else {
			return recInsert(current->right, acnt);
		}
	}
	else {
		cout << "ERROR: Account " << acnt->getAcntID() << " is already open. Transaction Refused." << endl;
		return false;
	}
}

//Retrieves an item from the bstree
bool BSTree::Retrieve(const int& acNum, Account*& acnt) const{
	Node* current = root;
	bool search = false;
	while (!search) {
		if (current != NULL && acNum == current->pAcct->getAcntID()) {
			//Found account
			acnt = current->pAcct;
			search = true;
			return search;
		}
		else if (current != NULL && acNum > current->pAcct->getAcntID()) {
			current = current->right;//Go right
		}
		else if (current != NULL && acNum < current->pAcct->getAcntID()) {
			current = current->left; //Go left
		}
		else {
			search = true;
		}
	}
	cout << "ERROR: Account Number: " << acNum << " Cannot Be Found!" << endl;
	return false;
}


/*Displays the bstree account items*/
void BSTree::Display() const {
	if (root == NULL) {
		cout << "The Account List is Empty!" << endl;
		return;
	}
	recPrint(root);
}

/*Recursively traverses through the bstree and prints the account information*/
void BSTree::recPrint(Node* current) const{

	if (current->left != NULL && current->right != NULL) {
		//Go left, print, go right
		recPrint(current->left);
		cout << *(current->pAcct) << endl;
		recPrint(current->right);
	}
	else if (current->left != NULL && current->right == NULL) {
		//go left, print current
		recPrint(current->left);
		cout << *(current->pAcct) << endl;
	}
	else if (current->right != NULL && current->left == NULL) {
		//print current, go right
		cout << *(current->pAcct) << endl;
		recPrint(current->right);
	}
	else {
		//Print current
		cout << *(current->pAcct) << endl;
	}
}

//Clears up the memory of the BSTree
//Deletes everything
void BSTree::Empty() {
	Node* current = root;
	if (root == NULL) return;

	if (current->left == NULL && current->right == NULL) {
		delete current;
	}
	else if(current->left != NULL && current->right != NULL) {
		delNode(current->left);
		delNode(current->right);
		delete current;
	}
	else if(current->left != NULL && current->right == NULL) {
		delNode(current->left);
		delete current;
	}
	else if (current->right != NULL && current->left == NULL) {
		delNode(current->right);
		delete current;
	}

}

//Sees if the bstree is empty
bool BSTree::isEmpty() {
	return root == NULL;
}

//Deletes the nodes from the left and right side of the trees
//traverse through the entire tree and everything is deleted
void BSTree::delNode(Node* current) {
	if (current->left != NULL && current->right != NULL) {
		delNode(current->left);
		delNode(current->right);
		delete current;
	}
	else if (current->left != NULL && current->right == NULL) {
		delNode(current->left);
		delete current;
	}
	else if (current->right != NULL && current->left == NULL) {
		delNode(current->right);
		delete current;
	}
	else {
		delete current;
	}
}
