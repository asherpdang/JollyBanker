#include "BSTree.h"

//Initalizing the BSTree constructor
BSTree::BSTree() {
	root = NULL;
}

//Destructor that cleans up memory 
BSTree::~BSTree() {
	Empty();//clear memory
}

//Inserts an account item into the bstree
bool BSTree::Insert(Account *acnt) {

	int acntID = acnt->getAcntID();
	//Catch invalid type of making an account
	if (acntID < 1000 || acntID > 9999) {
		cout << "ERROR: Account Number Not Valid!" << endl;
		return false;
	}

	//Creates account when the root is null
	if (root == NULL) {
		root = new Node(acnt);
		return true;
	}
	else {
		//traverse the bstree until at its rightful place
		//create an account
		Node* current = root;
		recInsert(current, acnt);//recursion
	}
	return false;//if can't be inserted
}

/*Recursively inserts the account into the bstree
* Used by Insert()
* traverses the tree to insert account
*/
bool BSTree::recInsert(Node* current, Account* acnt) {

	//Check if account ID is less than bstree current ID
	if (acnt->getAcntID() < current->pAcct->getAcntID()) {

		//Create a new account to the left 
		if (current->left == NULL) {
			Node* newAcnt = new Node(acnt);
			current->left = newAcnt;
			return true;
		}
		else {
			//keep going left
			return recInsert(current->left, acnt);
		}
	}//Go right
	else if(acnt->getAcntID() > current->pAcct->getAcntID())
	{
		//Create a new account object on the right
		if(current->right == NULL){
			Node* newAcnt = new Node(acnt);
			current->right = newAcnt;
			return true;
		}
		else {
			//Go right again
			return recInsert(current->right, acnt);
		}
	}
	else {
		//If account is already open then error transaction
		cout << "ERROR: Account " << acnt->getAcntID() << " is already open. Transaction Refused." << endl;
		return false;
	}
}

//Retrieves an account from the bstree with the corresponding account number
bool BSTree::Retrieve(const int& acNum, Account*& acnt) const{
	Node* current = root;
	bool search = false;

	while (!search) {
		if (current != NULL && acNum == current->pAcct->getAcntID()) {
			//Found account
			acnt = current->pAcct;//set account pointer
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
	//Cant find account so print out an error
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
	if (root == NULL) return;//Empty bstree

	if (current->left == NULL && current->right == NULL) {
		delete current;//delete the current 
	}
	else if(current->left != NULL && current->right != NULL) {
		delNode(current->left);//go left and right
		delNode(current->right);
		delete current;
	}
	else if(current->left != NULL && current->right == NULL) {
		delNode(current->left);//go left
		delete current;
	}
	else if (current->right != NULL && current->left == NULL) {
		delNode(current->right);//go right
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

	if (current->left == NULL && current->right == NULL) {
		delete current;//Delete current
	}
	else if (current->left != NULL && current->right != NULL) {
		delNode(current->left);//go left and right
		delNode(current->right);
		delete current;
	}
	else if (current->left != NULL && current->right == NULL) {
		delNode(current->left);//go left
		delete current;
	}
	else if (current->left == NULL && current->right != NULL) {
		delNode(current->right);//go right
		delete current;
	}
}
