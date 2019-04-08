#include "set.h"

/*****************************************************
* Implementation of the member functions             *
******************************************************/

//Default constructor
Set::Set ()
	: counter{ 0 }
{
	//IMPLEMENT before HA session on week 15
	Set::initSet();
}


//Conversion constructor
Set::Set (int n)
	: Set()
{
	//IMPLEMENT before HA session on week 15

	//Add newNode 
	Node* newNode = new Node(n, tail, tail->prev);

	tail->prev = tail->prev->next = newNode;

	//count size
	counter++;
}


//Constructor to create a Set from a SORTED array
Set::Set (int a[], int n) // a is sorted
	: Set()
{
	for (int i = 0; i < n; i++) {

		//Add newNode 
		Node* newNode = new Node(a[i], tail, tail->prev);

		tail->prev = tail->prev->next = newNode;

		//count size
		counter++;
	}
}


//Make the set empty
void Set::make_empty()
{
	//IMPLEMENT before HA session on week 15

	Node* p = head->next;

	while (p->next) {
		
		//exclude current p from Set
		p = p->next;
		
		Set::erase(p->prev);
	}
}


Set::~Set()
{
	//Member function make_empty() can be used to implement the desctructor
	//IMPLEMENT before HA session on week 15

	//Remove all Nodes
	Set::make_empty();

	//Remove Head and Tail	
	delete head, tail;

}


//Copy constructor
Set::Set (const Set& source)
	: counter{ source.counter }
{
	//IMPLEMENT before HA session on week 15
	
	initSet();

	Node* p = source.head->next;

	while (p->next) {

		//Add newNode 
		Node* newNode = new Node(p->value, tail, tail->prev);

		tail->prev = tail->prev->next = newNode;

		p = p->next;
	}
}


//Copy-and-swap assignment operator
//Note that call-by-value is used for source parameter
Set& Set::operator=(Set source)
{
	//IMPLEMENT before HA session on week 15

	return *this;
}


//Test whether a set is empty
bool Set::_empty () const
{
	return (!counter);
}


//Test set membership
bool Set::is_member (int val) const
{
	//IMPLEMENT before HA session on week 15

	return false; //remove this line
}



//Return number of elements in the set
unsigned Set::cardinality() const
{
	return counter;
}



//Modify Set *this such that it becomes the union of *this with Set S
//Add to Set *this all elements in Set S (repeated elements are not allowed)
//Algorithm used in exercise 5, of lesson 1 in TNG033 is useful to implement this function
Set& Set::operator+=(const Set& S)
{
	//IMPLEMENT before HA session on week 15

	return *this;
}


//Modify Set *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S)
{
	//IMPLEMENT

	return *this;
}


//Modify Set *this such that it becomes the Set difference between *this and Set S
Set& Set::operator-=(const Set& S)
{
	//IMPLEMENT

	return *this;
}

//Return true, if the set is a subset of b, otherwise false
//a <= b iff every member of a is a member of b
bool Set::operator<=(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


//Return true, if the set is equal to set b
//a == b, iff a <= b and b <= a
bool Set::operator==(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


//Return true, if the set is different from set b
//a == b, iff a <= b and b <= a
bool Set::operator!=(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


//Return true, if the set is a strict subset of S, otherwise false
//a == b, iff a <= b but not b <= a
bool Set::operator<(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


// Overloaded operator<<
ostream& operator<<(ostream& os, const Set& b)
{
	if (b._empty())
	{
		os << "Set is empty!" << endl;
	}	
	else
	{
		auto temp = b.head->next;

		os << "{ ";
		while (temp != b.tail)
		{
			os << temp->value << " ";
			temp = temp->next;
		}

		os << "}" << endl;
	}

	return os;
}


