#include "set.h"

/*****************************************************
* Implementation of the member functions             *
******************************************************/

//Default constructor
Set::Set ()
	: counter{ 0 }
{
	//IMPLEMENT before HA session on week 15
	Set::createSet();
}


//Conversion constructor
Set::Set (int n)
	: Set()
{
	//IMPLEMENT before HA session on week 15

	//Add newNode 
	Set::insert(tail, n);
}


//Constructor to create a Set from a SORTED array
Set::Set (int a[], int n) // a is sorted
	: Set()
{
	for (int i = 0; i < n; i++) {

		//Add newNode 
		Set::insert(tail, a[i]);
	}
}


//Make the set empty
void Set::make_empty()
{
	//IMPLEMENT before HA session on week 15

	Node* p = head->next;

	while (p->next) {

		Node* pNext = p->next;

		p->prev->next = p->next;
		p->next->prev = p->prev;
		
		delete p;

		p = pNext;
		counter--;
	}
}


Set::~Set()
{
	//Member function make_empty() can be used to implement the desctructor
	//IMPLEMENT before HA session on week 15

	//Remove all Nodes
	Set::make_empty();

	// cout << "failed to remove: " << this->counter << endl;

	//Remove Head and Tail	
	delete head;
	delete tail;

}


//Copy constructor
Set::Set (const Set& source)
	: counter{ source.counter }
{
	//IMPLEMENT before HA session on week 15
	
	Set::createSet();

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

	Set newSet(source);

	swap(head, newSet.head);
	swap(tail, newSet.tail);
	swap(counter, newSet.counter);

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

	Node* p = head->next;

	while (p->next) {
		
		if (p->value == val) return true;

		p = p->next;
	}

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

	Node* p1 = S.head->next;
	Node* p2 = head->next;

	Set c;

	//test and insert the union elements of nodes
	while (p1 != S.tail && p2 != tail) {
		if (p1->value < p2->value) {
			c.insert(c.tail, p1->value);
			p1 = p1->next;
		}
		else if (p1->value > p2->value) {
			c.insert(c.tail, p2->value);
			p2 = p2->next;
		}
		else if (p1->value == p2->value) {
			c.insert(c.tail, p1->value);
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	//if p1 or p2 has remaining elements of nodes, insert to set
	while (p1 != nullptr && p1 != S.tail) {
		c.insert(c.tail, p1->value);
		p1 = p1->next;
	}

	while (p2 != nullptr && p2 != tail) {
		c.insert(c.tail, p2->value);
		p2 = p2->next;
	}

	*this = c;

	return *this;
}


//Modify Set *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S)
{
	//IMPLEMENT
	Set c;

	Node* p = head->next;
	Node* ps = S.head->next;

	while (p != tail && ps != S.tail) {
		if (p->value > ps->value) {
			ps = ps->next;
		}
		else if (p->value < ps->value) {
			p = p->next;
		}
		else {
			c.insert(c.tail, p->value);
			p = p->next;
			ps = ps->next;
		}
	}

	*this = c;

	return *this;
}


//Modify Set *this such that it becomes the Set difference between *this and Set S
Set& Set::operator-=(const Set& S)
{
	Set t(*this);

	Node* pt = t.head->next;
	Node* pb = S.head->next;

	while (pt != t.tail && pb != S.tail) {
		if (pt->value > pb->value) {
			pb = pb->next;
		}
		else if (pt->value < pb->value) {
			pt = pt->next;
		}
		else {
			pt->prev->next = pt->next;

			pt = pt->next;
			pb = pb->next;
			// skip this node in t
			t.counter--;
			
		}
	}

	*this = std::move(t);

	return *this;
}

//Return true, if the set is a subset of b, otherwise false
//a <= b iff every member of a is a member of b
bool Set::operator<=(const Set& b) const
{
	//IMPLEMENT

	return (*this * b).counter == counter;
}


//Return true, if the set is equal to set b
//a == b, iff a <= b and b <= a
bool Set::operator==(const Set& b) const
{
	//IMPLEMENT

	return (*this <= b && b <= *this);
}


//Return true, if the set is different from set b
//a == b, iff a <= b and b <= a
bool Set::operator!=(const Set& b) const
{
	//IMPLEMENT

	return !(*this <= b && b <= *this);
}


//Return true, if the set is a strict subset of S, otherwise false
//a == b, iff a <= b but not b <= a
bool Set::operator<(const Set& b) const
{
	//IMPLEMENT

	return *this <= b && !(b <= *this);
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


