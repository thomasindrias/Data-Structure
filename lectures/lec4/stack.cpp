/***************************************************************************
* TND004: Fö 4                                                             *
* Implementation of a template class Stack                                 *
* Array-based implementation is used                                       *
* **************************************************************************/

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;


template<class T>
class Stack
{
public:
    static const int DefaultCapacity = 100;

    //Constructor
    explicit Stack(int n = DefaultCapacity)
        : topOfStack(-1), capacity(n), theArray( new T[capacity] )
    { }

    //Destructor
    ~Stack()
    {
        delete theArray;
    }

    //Copy constructor -- disabled!!
    Stack(const Stack& ) = delete;

    //Assignment operator -- disabled!!
    const Stack& operator=(const Stack& ) = delete;



    bool isFull() const
    {
        return (topOfStack == capacity - 1);
    }

    bool isEmpty() const { return (topOfStack == -1); }

    const T& top() const
    {
        assert(!isEmpty());

        return theArray[topOfStack];
    }

    void makeEmpty()
    {
        topOfStack = -1;
    }

    void push(const T& E)
    {
        if (!isFull())
        {
            theArray[++topOfStack] = E;
        }
    }

    void pop()
    {
        assert(!isEmpty());

        topOfStack--;
    }

private:
    int topOfStack;
    int capacity;    //maximum number of elements that can be stored in the stack

    T* theArray;     //pointer to an array allocated dynamically
};




//Program that tests whether braces ')' and '(' are
//correctly used in an expression, e.g. (3+4)*(a+b)
//Note: square brackets, "[" and "]", not considered
int main() //see sec. 3.6.3 of course book, page 123
{
    Stack<char> S;

    string exp;
    bool warned = false;

    cout << "Enter a mathematical expression: ";
    getline(cin, exp);

    cout << endl;

    for(auto i = 0; i < exp.size(); ++i)
    {
        if (exp[i] == '(')
            S.push(exp[i]);

        if (exp[i] == ')')
        {
            if (S.isEmpty() && !warned)
            {
                cout << exp << " is not well-formed!!" << endl;
                warned = true;
            }
            else
                S.pop();
        }
    }

    if (!S.isEmpty() && !warned)
        cout << exp  << " is not well-formed." << endl;
    else if (!warned)
        cout << exp << " is well-formed!!" << endl;

    return 0;
}
