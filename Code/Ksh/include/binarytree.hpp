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
		uint64_t key;
		unsigned int count;
		bool mark;
		Node *left = NULL;
		Node *right = NULL;

		/* ====================  LIFECYCLE     ======================================= */
		Node () {
			this->mark = false;
			this->count = 0;
		}                             /* constructor      */
		Node (uint64_t key) {
			this->key = key;
			this->mark = false;
			this->count = 1;
		}                             /* constructor      */
		Node (uint64_t key, bool mark) {
			this->key = key;
			this->mark = mark;
			this->count = 1;
		}                             /* constructor      */
		Node (uint64_t key, Node *left, Node *right) {
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
		BST (uint64_t );                             /* constructor      */
		BST ( const BST &other );   /* copy constructor */
		~BST ();                           /* destructor       */

		/* ====================  ACCESSORS     ======================================= */

		Node *trav(uint64_t, Node * &);
		void setRootMark();
		void setMark( Node *);
		Node *getRoot();
		uint64_t getRootKey();
		void getKeys(Node *, std::vector<uint64_t> &);
		void getKeys( std::vector<uint64_t> & );

		/* ====================  MUTATORS      ======================================= */

		unsigned int add(uint64_t );

		void remove(uint64_t );

		Node * search(uint64_t );

		void copy(Node *);

		/* ====================  OPERATORS     ======================================= */

		void print(std::ostream &, Node *, uint64_t ) const;
		void print(Node *, uint64_t ) const;
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
