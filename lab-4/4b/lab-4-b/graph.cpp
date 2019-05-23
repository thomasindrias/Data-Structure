/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFNT = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
// Graph G = (V,E), with V = abs(n) and E = abs(m)
// Time complexity: T(n, m) = O(n^2) for dense graphs
void Graph::mstPrim() const
{
    // *** TODO ***

	// Create specifications
	int* dist = new int[size + 1];
	int* path = new int[size + 1];
	bool* done = new bool[size + 1];

	// Set default.
	for (int v = 1; v <= size; v++) {
		dist[v] = INFNT;
		path[v] = 0;
		done[v] = false;
	}

	int start = 1;
	int totalWeight = 0;
	dist[start] = 0;
	done[start] = true;
	int v = start;

	while (true) {
		
		// for all (v,u)
		Node* u = array[v].getFirst();

		while (u != nullptr) {
			if (done[u->vertex] == false && u->weight < dist[u->vertex]) {
				dist[u->vertex] = u->weight;
				path[u->vertex] = v;
			}

			u = u->next;
		}

		//find min in array dist
		v = find_smallest_undone_distance_vertex(dist, done);

		if (v == 0) break; //exit the loop
		done[v] = true;

		totalWeight += dist[v]; // Adding distance to total weight

		cout << "(" << path[v] << ", " << v << ", " << dist[v] << ")" << endl; // printing edges of a minimum spanning
	}

	cout << "\nTotal weight: " << totalWeight << endl;

	//Delete specifications
	delete dist;
	delete path;
	delete done;
}

int Graph::find_smallest_undone_distance_vertex(int* dist, bool* done) const
{ 
	int smallest = INFNT;
	int v = 0;

	for (int i = 1; i <= size; i++) {
		if (done[i] == false && dist[i] < smallest) {
			smallest = dist[i];
			v = i;
		}
	}

	return v;
}

// Kruskal's minimum spanning tree algorithm
// Graph G = (V, E), with B = abs(n) and E = abs(m)
void Graph::mstKruskal() const
{
    // *** TODO ***

	Heap<Edge> H; // min-heap
	DSets D(size); // n trees with one node each

	int counter = 0, totalWeight = 0;

	// Build the heap with all the edges
	// T(m) = O(m) (E = abs(m))
	for (int v = 1; v <= size; v++) {
		
		Node *u = array[v].getFirst();

		// insert smallest weighted edge for vertex v into min-heap
		while (u != nullptr) {
			if (u->vertex < v) H.insert(Edge(u->vertex, v, u->weight));

			// continue to adjacent edge
			u = array[v].getNext();
		}
	}

	Edge e;
	while (counter < size - 1) { // n-1 edges
		e = H.deleteMin(); // edge with lowest cost - T(m) = O(log m). (E = abs(m))

		// (v: head, u: tail)
		// u and v in the same tree?
		if (D.find(e.head) != D.find(e.tail)) {

			cout << e << endl; //print out Edge

			totalWeight += e.weight;

			// merge the two trees
			D.join(D.find(e.head), D.find(e.tail));
			counter++;
		}
	}
	
	cout << "\nTotal weight: " << totalWeight << endl; // print out the total weight
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
