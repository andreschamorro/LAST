/*
 * =====================================================================================
 *
 *       Filename:  binarytree.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/02/2018 09:03:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andres Chamorro (ach), andresdavidchamorro@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  BINARYTREE_INC
#define  BINARYTREE_INC

#define WIDTHUNIT 5

#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

/*
 * =====================================================================================
 *        Class:  Node
 *  Description:  Binary Node
 * =====================================================================================
 */
class Node
{
	public:
		unsigned int key;
		unsigned int count;
		bool mark;
		Node *left = NULL;
		Node *right = NULL;

		/* ====================  LIFECYCLE     ======================================= */
		Node () {
			this->mark = false;
			this->count = 0;
		}                             /* constructor      */
		Node (unsigned int key) {
			this->key = key;
			this->mark = false;
			this->count = 1;
		}                             /* constructor      */
		Node (unsigned int key, bool mark) {
			this->key = key;
			this->mark = mark;
			this->count = 1;
		}                             /* constructor      */
		Node (unsigned int key, Node *left, Node *right) {
			this->key = key;
			this->mark = true;
			this->count = 1;
			this->left = left;
			this->right = right;
		}
		~Node (){}                            /* destructor       */
}; /* -----  end of class Node  ----- */

/*
 * =====================================================================================
 *        Class:  BST
 *  Description:  Binary Search Tree Data Structure
 * =====================================================================================
 */
class BST
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		BST ();                             /* constructor      */
		BST (unsigned int );                             /* constructor      */
		BST ( const BST &other );   /* copy constructor */
		~BST ();                           /* destructor       */

		/* ====================  ACCESSORS     ======================================= */

		Node *trav(unsigned int, Node * &);
		void setRootMark();
		void setMark( Node *);
		Node *getRoot();
		unsigned int getRootKey();
		void getKeys(Node *, std::vector<unsigned int> &);
		void getKeys( std::vector<unsigned int> & );

		/* ====================  MUTATORS      ======================================= */

		unsigned int add(unsigned int );

		void remove(unsigned int );

		Node * search(unsigned int );

		void copy(Node *);

		/* ====================  OPERATORS     ======================================= */

		void print(std::ostream &, Node *, unsigned int ) const;
		void print(Node *, unsigned int ) const;
		void print( ) const;

		const BST& operator = ( const BST &other ); /* assignment operator */
		friend std::ostream & operator << (std::ostream &, const BST &);

	protected:
		/* ====================  METHODS       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */

	private:
		/* ====================  METHODS       ======================================= */

		void makeEmpty(Node* );

		/* ====================  DATA MEMBERS  ======================================= */

		Node *_root;

}; /* -----  end of class BST  ----- */

#endif   /* ----- #ifndef BINARYTREE_INC  ----- */
