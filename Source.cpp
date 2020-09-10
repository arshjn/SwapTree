#include "BST.h"

int main()
{
	TreeType<char> T1;
	T1.addItem('F');
	T1.addItem('A');
	T1.addItem('I');
	T1.addItem('R');
	T1.addItem('O');
	T1.addItem('W');
	//T1.addItem('G');
	//T1.addItem('H');
	T1.printTree();
	T1.swapTree();
	cout << "After Swap: \n";
	T1.printTree();
	cout << endl << endl;
	TreeType<int> T2;
	T2.addItem(3);
	T2.addItem(12);
	T2.addItem(6);
	T2.addItem(1);
	T2.addItem(0);
	T2.addItem(14);
	T2.addItem(2);
	
	T2.printTree();
	T2.swapTree();
	cout << "After Swap: \n";
	T2.printTree();
	

	return 0;
}