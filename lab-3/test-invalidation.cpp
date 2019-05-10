#include <iostream>
#include <vector>

#include "BinarySearchTree.h"

using namespace std;



// Test program 2
int main( )
{
    BinarySearchTree<int> t1;

    vector<int> V = {20, 10, 30, 5, 35};

    /**************************************/
    cout << "TESTING INVALIDATION\n\n";
    /**************************************/

    for(auto j: V)
        t1.insert( j );

    //Display the tree
    cout << "T1 BEFORE" << endl;
    t1.printTree( );
    cout << endl;

	BinarySearchTree<int>::BiIterator it1 = t1.begin();
	BinarySearchTree<int>::BiIterator it2 = t1.begin()++;

	cout << "IT1: ITERATOR OF SMALLEST VALUE IN BINARYSEARCHTREE" << endl;
	std::cout << "BEFORE NUMBER: " << *it1 << " WITH ADRESS: " << &it1 << "\n";

	cout << "IT2: ITERATOR OF SECOND SMALLEST VALUE IN BINARYSEARCHTREE" << endl;
	std::cout << "BEFORE NUMBER: " << *it2 << " WITH ADRESS: " << &it2 << "\n";

	const int val_delete = 5;
    cout << "remove " << val_delete << endl;
    t1.remove(val_delete);


	//Display the tree
	cout << endl;
	cout << "T1 AFTER" << endl;
	t1.printTree();
	cout << endl;

	cout << "IT1: ITERATOR STILL POINTS TO THE PREVIOUS OLD MEMORY ADRESS (INVALIDATED)" << endl;
	std::cout << "AFTER NUMBER: " << *it1 << " WITH ADRESS: " << &it1 << "\n";

	cout << "IT2: OTHER ITERATORS STAYS SAME (VALIDATED)" << endl;
	std::cout << "AFTER NUMBER: " << *it2 << " WITH ADRESS: " << &it2 << "\n";

    cout << "\nFinished testing" << endl;

	system("pause");
	return 0;
}
