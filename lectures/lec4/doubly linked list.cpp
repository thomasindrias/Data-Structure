/***************************************************************************
* TND004: Fö 4                                                             *
* Doubly linked list: nodes are sorted increasingly by the value they store*
* Dummy nodes at the beginning and end of the list are used                *
* Repeated values are not allowed                                          *
* **************************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;


class List
{
public:

	//constructor: create an empty list
	List();

	//copy constructor
	List(const List &L); //Implement

	//destructor
	~List();

	//assignment operator
	List& operator=(List L);

	//Remove all values from the list
	bool isEmpty() const;    //Implement

	bool _find(int x) const;  //Implement

	//Subscript operator
	//Return the value store in the index+1 position of the list
	int operator[](int index) const;

	void makeEmpty();

	List& _insert(int x);
	List& _remove(int x);

	friend ostream& operator<<(ostream& os, const List& L);

private:

	//Define a node of the doubly linked list
	class Node
	{
	public:

		//Constructor
		Node(int nodeVal = 0, Node* nextPtr = nullptr, Node* prevPtr = nullptr)
			: value(nodeVal), next(nextPtr), prev(prevPtr)
		{  }

		//Data members
		int value;
		Node* next; //pointer to the next Node
		Node* prev; //pointer to the previous Node
	};


	Node *front;	//first node
	Node *tail;     //last node

	//Insert a new Node storing val before the Node pointed by p
	void _insert(Node *p, int val);

	//Remove the Node pointed by p
	void _erase(Node *p);

	void display(ostream& os) const;
};

/*******************************************
* List member functions implementation     *
********************************************/

// constructor: create an empty list
List::List()
{
	front = new Node();
	tail = new Node(0, nullptr, front);

	front->next = tail;
}

//copy constructor
List::List(const List &L)
{
	//ADD CODE
}

//destructor
List::~List()
{
	makeEmpty();

	delete front;
	delete tail;
}


//Assignment operator
//Copy-and-swap idiom
List& List::operator=(List L) //note that call by value is used for L
{
	//Uses the copy constructor and the destructor

	//swap the nodes of L with *this
	//by swapping the pointers
	swap(front, L.front);
	swap(tail, L.tail);

	return *this;

	//the destructor is called to deallocate the memory of the nodes in L
}


bool List::isEmpty() const
{
	return (front->next == tail);
}


bool List::_find(int x) const
{
	//ADD CODE
	return false;
}

void List::makeEmpty()
{
	//ADD CODE
}

int List::operator[](int index) const
{
	Node* p = front->next;

	for (int i = 0; p != tail && i < index; i++, p = p->next);

	return p->value;
}


List& List::_insert(int x) //list is sorted
{
	Node* p = front->next;

	//search for insertion point in the list
	while (p != tail && p->value < x)
		p = p->next;

	if (p == tail || p->value != x)
		_insert(p, x); //insert a new Node storing x, before p


	return *this;
}


List& List::_remove(int x)
{
	Node* p = front->next;

	//search for node storing x in the list
	while (p != tail && p->value < x)
		p = p->next;

	if (p != tail && p->value == x) //p points to node storing x
		_erase(p); //delete the node pointed by p

	return *this;
}


//Insert a new Node storing val before the Node pointed by p
void List::_insert(Node *p, int val)
{
	p->prev = p->prev->next = new Node(val, p, p->prev);
}

//Remove the Node pointed by p
void List::_erase(Node *p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;

	delete p; //deallocate the memory
}

void List::display(ostream& os) const
{
	for (Node* p = front->next; p != tail; p = p->next)
		os << p->value << " ";

}


ostream& operator<<(ostream& os, const List& L)
{
	if (L.isEmpty())
		os << "List is empty!!";
	else
		L.display(os);

	os << endl;

	return os;
}


/*******************************************
* Test: main()                             *
********************************************/

int main()
{
	List L;

	cout << "L: " << L << endl;

	cout << "Inserting ..." << endl;
	L._insert(10)._insert(5)._insert(15)._insert(8)._insert(5);

	cout << "L: " << L << endl;

	cout << "L[0] = " << L[0] << endl;
	cout << "L[1] = " << L[1] << endl;
	cout << "L[2] = " << L[2] << endl;
	cout << "L[3] = " << L[3] << endl;

	cout << "\nRemoving ..." << endl;
	L._remove(8)._remove(10)._remove(20);

	cout << "L: " << L << endl;

	List L1(L); //copy constructor

	cout << "L1: " << L << endl;

	return 0;
}
