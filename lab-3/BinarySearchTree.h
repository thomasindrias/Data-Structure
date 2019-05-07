#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
	struct BinaryNode;
	
  public:
	  /**
	  * Class BiIterator
      */

	  class BiIterator
	  {
	  public:
		  BiIterator( BinaryNode *b = nullptr) : current { b } { };
		  Comparable& operator*() const
		  {
			  return current->element;
		  }
		  Comparable* operator->() const {
			  return &current->element;
		  }
		  bool operator==(const BiIterator &it) const {
			  return current == it.current;
		  }
		  bool operator!=(const BiIterator &it) const {
			  return current != it.current;
		  }
		  BiIterator& operator++() //pre-increment
		  {
			  current = find_successor(current);
			  return *this; 
		  }
		  BiIterator operator++(int a) //post-increment
		  {
			  BiIterator *temp = this;
			  current = find_successor(current);
			  return *temp;
		  }
		  BiIterator& operator--() //pre-decrement 
		  {
			  current = find_predecessor(current);
			  return *this; 
		  }
		  BiIterator operator--(int a) //post-decrement
		  {
			  BiIterator *temp = this;
			  current = find_predecessor(current);
			  return *temp;

		  }
	  private:
		  BinaryNode *current;
	  };

	BiIterator begin() const
	{
		if (isEmpty()) return end();
		return BiIterator(findMin(root));
	}
	BiIterator end() const
	{
		return BiIterator(nullptr);
	}


	BinarySearchTree() : root{ nullptr }
	{
	}

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment: copy and swap idiom
     */
    BinarySearchTree & operator=( BinarySearchTree _copy )
    {
        std::swap( root, _copy.root );
        return *this;
    }


    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
        {
            throw UnderflowException{ };
        }

        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
        {
            throw UnderflowException{ };
        }

        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    BiIterator contains( const Comparable & x ) const
    {
        return BiIterator(contains( x, root ));
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
        {
            out << "Empty tree" << endl;
        }
        else
        {
			pre_order(root, 0, out);
        }
    }


    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        root = makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        root = insert( x, root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        root = insert( std::move( x ), root );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        root = remove( x, root );
    }
	/**
	 * Get x parent from the tree. Nothing is done if x is not found.
	 */
	Comparable get_parent(Comparable x) const
	{
		BinaryNode* investigator = root;
		if (investigator->element == x)
			return Comparable();


		while (investigator != nullptr)
		{
			if (investigator->element > x)
				investigator = investigator->left;

			else if (investigator->element < x)
				investigator = investigator->right;

			else if (investigator->element == x)
				return investigator->parent->element;
		}

		return Comparable();
	}
	/**
	 * Find predcusser and succusser for x from the tree. 
	 */
	void find_pred_succ(const Comparable& x, Comparable& pred, Comparable& succ) const
	{
		BinaryNode* current = root;

		while (current != nullptr)
		{
			if (current->element == x)
			{
				BinaryNode* pre = find_predecessor(current);
				BinaryNode* suc = find_successor(current);

				if (pre != nullptr)
					pred = pre->element;

				if (suc != nullptr)
					succ = suc->element;

				return;
			}
			else if (current->element < x)
			{
				pred = current->element;
				current = current->right;
			}
			else
			{
				succ = current->element;
				current = current->left;
			}
		}
	}	


  private:

    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
		BinaryNode *parent; // parent

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *pt )
			: element{ theElement }, left{ lt }, right{ rt }, parent{ pt } { }

        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *pt )
			: element{ std::move(theElement) }, left{ lt }, right{ rt }, parent{ pt } { }
    };

    BinaryNode *root;


    /**
     * Private member function to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x.
     */
    BinaryNode* insert( const Comparable & x, BinaryNode* t )
    {
        if( t == nullptr )
        {
            t = new BinaryNode{ x, nullptr, nullptr, nullptr };
        }
        else if( x < t->element )
        {
            t->left = insert( x, t->left );
			t->left->parent = t;
        }
        else if( t->element < x )
        {
             t->right = insert( x, t->right );
			 t->right->parent = t;
        }
        else
        {
            ;  // Duplicate; do nothing
        }

        return t;
    }

    /**
     * Private member function to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x.
     */
    BinaryNode* insert( Comparable && x, BinaryNode* t )
    {
        if( t == nullptr )
        {
            t = new BinaryNode{ std::move( x ), nullptr, nullptr, nullptr };
        }
        else if( x < t->element )
        {
            t->left = insert( std::move( x ), t->left );
			t->left->parent = t;
        }
        else if( t->element < x )
        {
            t->right = insert( std::move( x ), t->right );
			t->right->parent = t;
        }
        else
        {
             ;  // Duplicate; do nothing
        }

        return t;
    }


    /**
     * Private member function to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Return a pointer to the new root of the subtree that had root x
     */
    BinaryNode* remove( const Comparable & x, BinaryNode *t )
    {
        if( t == nullptr )
        {
            return t;   // Item not found
        }
        if( x < t->element )
        {
            t->left = remove( x, t->left );
        }
        else if( t->element < x )
        {
             t->right = remove( x, t->right );
        }

        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            t->right = remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
			
			//Set new parent if subroot exists.
			if(t != nullptr)
				t->parent = oldNode->parent;

            delete oldNode;
        }

         return t;
    }


    /**
     * Private member function to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    static BinaryNode * findMin( BinaryNode *t ) 
    {
        if( t == nullptr )
        {
            return nullptr;
        }
        if( t->left == nullptr )
        {
           return t;
        }

        //Tail recursion can be easily replaced by a loop
        return findMin( t->left ); //recursive call
    }

    /**
     * Private member function to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    static BinaryNode * findMax( BinaryNode *t ) 
    {
        if( t != nullptr )
        {
            while( t->right != nullptr )
            {
                t = t->right;
            }
        }

        return t;
    }


    /**
     * Private member function to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x, if x is found
     * Otherwise, return nullptr
     */
    BinaryNode* contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
        {
            return t;
        }
        else if( x < t->element )
        {
            return contains( x, t->left );
        }
        else if( t->element < x )
        {
            return contains( x, t->right );
        }
        else
        {
            return t;    // Match
        }
    }
/****** NONRECURSIVE VERSION*************************
    Node* contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
        {
            if( x < t->element )
            {
                t = t->left;
            }
            else if( t->element < x )
            {
                t = t->right;
            }
            else
            {
                return t;    // Match
            }
        }

        return t;   // No match
    }
*****************************************************/

    /**
     * Private member function to make subtree empty.
     */
    BinaryNode* makeEmpty( BinaryNode *t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }

        return nullptr;
    }

    /**
     * Private member function to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            
			pre_order(t, 0, out);
			//printTree( t->left, out );
            //out << t->element << endl;
            //printTree( t->right, out );
        }
    }


	/**
	 * private  member  function  to  display  the  tree  using  pre-order
	 * with indentation
	 */
	void pre_order(BinaryNode* t, int indentation, ostream & out) const
	{
		if (t != nullptr)
		{
			cout << setw(indentation) << t->element << endl;

			if (indentation == 0)
				indentation += 4;
			else
				indentation += 2;

			pre_order(t->left, indentation, out);
			pre_order(t->right, indentation, out);
		}
	}

    /**
     * Private member function to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
        {
            return nullptr;
        }
        else
        {
            BinaryNode* temp = new BinaryNode{ t->element, clone( t->left ), clone( t->right ), nullptr };

			if (temp->left != nullptr) temp->left->parent = temp;
			if (temp->right != nullptr) temp->right->parent = temp;

			return temp;
        }
    }

	static BinaryNode * find_successor(BinaryNode *t)  
	{
		if (t == nullptr)
			return nullptr;

		else if (t->right)
		{
			t = t->right;
			return findMin(t);
		}

		while (t->parent != nullptr && t->parent->left != t)
		{
			t = t->parent;
		}
		return t->parent;
	}

	static BinaryNode*  find_predecessor(BinaryNode *t) 
	{
		if (t == nullptr)
			return nullptr;

		else if (t->left)
		{
			t = t->left;
			return findMax(t);
		}

		while (t->parent != nullptr && t->parent->right != t)
		{
			t = t->parent;
		}
		return t->parent;
	}
};

#endif
