//Project 5
//Asher Dang
//CSS 342
#include "JollyBanker.h"
using namespace std;

int main() {
	JollyBanker bank;
	bank.readIn("BankTransIn.txt");
	bank.createTrans();
	bank.exeTransaction();
	bank.display();

	return 0;
}