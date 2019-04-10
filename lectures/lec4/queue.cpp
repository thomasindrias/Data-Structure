/***************************************************************************
* TND004: Fö 4                                                             *
* Implementation of a template class Queue                                 *
* Array-based implementation is used                                       *
* **************************************************************************/

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;


template<class T>
class Queue
{
public:
    static const int DefaultCapacity = 100;

    //Constructor
    explicit Queue(int n = DefaultCapacity)
      : capacity(n), counter(0),  back(n-1), front(0), theArray( new T[capacity] )
    { }

    //Destructor
    ~Queue()
    {
        delete theArray;
    }

    //Copy constructor -- disabled!!
    Queue(const Queue& ) = delete;

    //Assignment operator -- disabled!!
    const Queue& operator=(const Queue& ) = delete;


    bool isFull() const
    {
        return (counter == capacity);
    }

    bool isEmpty() const
    {
        return (!counter);
    }

    const T& getFront() const
    {
        assert(!isEmpty());

        return theArray[front];
    }

    int size() const
    {
        return counter;
    }

    void makeEmpty()
    {
        counter = 0;
        front = 0;
        back = capacity - 1;
    }

    void enqueue(const T& E)
    {
        if (!isFull())
        {
            back = (++back)%capacity;
            theArray[back] = E;
            ++counter;
        }
    }

     const T& dequeue()
    {
        assert(!isEmpty());

        if (!isEmpty())
        {

            const T& temp = theArray[front];
            front = (++front)%capacity;
            --counter;

            return temp;
        }
    }

private:
    int capacity;   //maximum number of elements that can be stored in the queue
    int counter;    //how many elements are stored in the queue
    int front;
    int back;

    T* theArray;   //pointer to an array allocated dynamically
};



int main() //simple test program
{
    Queue<int> Q(4);

    cout << "Enqueue: " << 5 << endl;
    Q.enqueue(5);
    cout << "Enqueue: " << 6 << endl;
    Q.enqueue(6);
    cout << "Enqueue: " << 7 << endl;
    Q.enqueue(7);
    cout << "Enqueue: " << 8 << endl;
    Q.enqueue(8);

    if (Q.isFull())
        cout << "Q is full!" << endl;

    cout << "Q has " <<  Q.size() << " elements." << endl;

    cout << "Dequeue: " << Q.dequeue() << endl;
    cout << "Enqueue: " << 9 << endl;
    Q.enqueue(9);

    //Q.makeEmpty();

    cout << "Dequeue: " << Q.dequeue() << endl;
    cout << "Dequeue: " << Q.dequeue() << endl;
    cout << "Dequeue: " << Q.dequeue() << endl;
    cout << "Dequeue: " << Q.dequeue() << endl;

    if (Q.isEmpty())
        cout << "Q is empty!" << endl;

    return 0;

}
