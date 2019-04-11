#include "set.h"

/*****************************************************
* Implementation of the member functions             *
******************************************************/

//Default constructor
Set::Set ()
	: counter{ 0 }
{
	Set::createSet();
}


//Conversion constructor
Set::Set (int n)
	: Set()
{
	//Add newNode 
	this->insert(tail, n);
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
	Node* p = head->next;
	Node* temp;


	while (p != nullptr && p != tail) {
		
		//exclude current p from Set
		p->prev->next = p->next;
		p->next->prev = p->prev;
		temp = p->next;
		delete p;
		counter--;
		p = temp;
	}
}


Set::~Set()
{
	//Member function make_empty() can be used to implement the desctructor

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

	Node* p = head->next;

	while (p->next) {
		
		if (p->value == val) return true;

		p = p->next;
	}

	return false; 
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

	Node* pa = head->next;
	Node* pb = S.head->next;

	//cout << "pa: " << *this << "   pb: " << S << endl;

	//test and insert the union elements of nodes
	while (pb != S.tail && pa != tail) {
		if (pb->value < pa->value) {
			insert(pa, pb->value);
			pb = pb->next;
		}
		else if (pb->value > pa->value) {
			pa = pa->next;
		}
		else if (pb->value == pa->value) {
			pb = pb->next;
			pa = pa->next;
		}
	}

	//if pb or pa has remaining elements of nodes, insert to set

	while (pb && pb != S.tail) {
		insert(pa, pb->value);
		pb = pb->next;
	}

	return *this;
}


//Modify Set *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S)
{
	//IMPLEMENT

	Node* p = head->next;
	Node* ps = S.head->next;

	// cout << "this: " << *this << "   S: " << S << endl;

	while (p != tail && ps != S.tail) {
		if (p->value > ps->value) {
			ps = ps->next;
		}
		else if (p->value < ps->value) {
			p = p->next;
			Set::erase(p->prev);
		}
		else {
			p = p->next;
			ps = ps->next;
		}
	}

	while (ps == S.tail && p != tail) {
		p = p->next;
		Set::erase(p->prev);

		
	}

	return *this;
}


//Modify Set *this such that it becomes the Set difference between *this and Set S
Set& Set::operator-=(const Set& S)
{
	Node* p = head->next;
	Node* ps = S.head->next;

	// cout << "this: " << *this << "   S: " << S << endl;

	while (p != tail && ps != S.tail) {
		if (p->value > ps->value) {
			ps = ps->next;
		}
		else if (p->value < ps->value) {
			p = p->next;
		}
		else {
			p = p->next;
			ps = ps->next;

			Set::erase(p->prev);
		}
	}

	return *this;
}

//Return true, if the set is a subset of b, otherwise false
//a <= b iff every member of a is a member of b
bool Set::operator<=(const Set& b) const
{
	//Node* p1 = b.head->next;
	Node* p2 = head->next;

	while (p2 != nullptr && p2 != tail) {
		if (!b.is_member(p2->value)) {
			return false;
		}
		p2 = p2->next;
	}
	
	return true;
}


//Return true, if the set is equal to set b
//a == b, iff a <= b and b <= a
bool Set::operator==(const Set& b) const
{
	Node* p1 = b.head->next;
	Node* p2 = head->next;
	if (b.counter != counter) {
		return false;
	}
	while (p1 != b.tail && p2 != tail) {
		if (p1->value != p2->value) {
			return false;
		}
		p1 = p1->next;
		p2 = p2->next;
	}
	return true;
}


//Return true, if the set is different from set b
//a == b, iff a <= b and b <= a
bool Set::operator!=(const Set& b) const
{
	if (this->operator==(b)) {
		return false;
	}
	return true; 

}


//Return true, if the set is a strict subset of S, otherwise false
//a == b, iff a <= b but not b <= a
bool Set::operator<(const Set& b) const
{
	if (this->operator<=(b)){
		return true;
	}
	return false; 
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


