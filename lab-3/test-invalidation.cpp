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


	const int val_delete = 10;
    cout << "remove " << val_delete << endl;
    t1.remove(val_delete);


	//Display the tree
	cout << endl;
	cout << "T1 AFTER" << endl;
	t1.printTree();
	cout << endl;

    cout << "\nFinished testing" << endl;

	system("pause");
	return 0;
}
