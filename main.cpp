//Project 5
//Asher Dang
//CSS 342
#include "JollyBanker.h"
using namespace std;

//Runs the bank application
int main() {
	JollyBanker bank;
	bank.readIn("BankTransIn.txt");//Reads the text file
	bank.createTrans();//Creates transactions according to the stored info
	bank.exeTransaction();//Executes the transactions
	bank.display();//Finally displays the total

	return 0;
}