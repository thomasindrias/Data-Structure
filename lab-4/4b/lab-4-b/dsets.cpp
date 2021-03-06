/*********************************************
* file:	~\tnd004\lab\lab4b\dsets.cpp         *
* remark: implementation of disjoint sets    *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>

#include <cassert>

using namespace std;

#include "dsets.h"

// -- CONSTRUCTORS

DSets::DSets(int theSize)
{
    assert(theSize > 0);
    size = theSize;
    array = new int[size + 1];
    init();
}

// -- DESTRUCTOR

DSets::~DSets()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// create initial sets
void DSets::init()
{
    for (int i = 1; i <= size; i++)
    {
        array[i] = -1;
    }
}


/*
*************** Example illustration ***************
		+----+----+----+---+----+---+---+---+
size:	| -1 | -1 | -1 | 4 | -5 | 4 | 4 | 6 |
		+----+----+----+---+----+---+---+---+
vertex:	| 0  | 1  | 2  | 3 | 4  | 5 | 6 | 7 |
		+----+----+----+---+----+---+---+---+
		
		* tree with root 4 contains 4 vertices (-5 including root)
		* trees with root 0, 1 and 2 contains 0 vertices (-1 including root)
*/

// join sets named r and s where r != s
// i.e. join trees with roots r and s
void DSets::join(int r, int s)
{
	assert(r != s);
	assert(r >= 1 && r <= size);
	assert(s >= 1 && s <= size);
	assert(array[r] < 0);
	assert(array[s] < 0);

    // *** TODO ***
    // weighted union (by size)
	
	if (array[r] < array[s]) {

		array[r] += array[s];
		array[s] = r;
	}
	else {

		array[s] += array[r];
		array[r] = s;
	}

	// cout << "tree 1 (size): " << array[r] << "-" << r << " tree 2 (size): " << array[s] << ":" << s << endl;
}

// return name of current set for x
// i.e. return root of tree for x
int DSets::find(int x)
{
    assert(x >= 1 && x <= size);

    // *** TODO ***
    // find with path compression

	// recursively set array[x] equal to  the value returned by find. 
	// x's parent link references it.
	if (array[x] < 0){
	    return x;
	}
	else{
	    return array[x] = find(array[x]);
	}
}

// just in case ...
void DSets::print() const
{
    cout << endl;
    for (int i = 1; i <= size; i++)
    {
        cout << setw(4) << i;
    }
    cout << endl;
    for (int i = 1; i <= size; i++)
    {
        cout << setw(4) << array[i];
    }
    cout << endl;
}
