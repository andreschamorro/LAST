/*
 * =====================================================================================
 *
 *       Filename:  binarytree.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/02/2018 10:03:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andres Chamorro (ach), andresdavidchamorro@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <binarytree.hpp>

/*
 *--------------------------------------------------------------------------------------
 *       Class:  BST
 *      Method:  BST
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
BST::BST ()
{
	_root = NULL;
}  /* -----  end of method BST::BST  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  BST
 *      Method:  BST
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
BST::BST (uint64_t key)
{
	_root = new Node(key);
}  /* -----  end of method BST::BST  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  BST
 *      Method:  BST
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
BST::BST ( const BST &other )
{
	_root = NULL;
	copy(other._root);
}  /* -----  end of method BST::BST  (copy constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  BST
 *      Method:  ~BST
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
BST::~BST ()
{
	makeEmpty(_root);
}  /* -----  end of method BST::~BST  (destructor)  ----- */



	Node *
BST::trav ( uint64_t key, Node * & par )
{
	Node * curr = _root;
	par = NULL;
	
	while ( curr && (curr->key != key) ) {
		par = curr;
		if (key < curr->key) {
			curr = curr->left;
		} else if ( key > curr->key ) {
			curr = curr->right;
		}
	}
	return curr;
}		/* -----  end of method BST::trav  ----- */

	void
BST::setRootMark ( )
{
	_root->mark = true;
	return ;
}		/* -----  end of method BST::setRootMark  ----- */

	void
BST::setMark ( Node * n )
{
	n->mark = true;
	return ;
}		/* -----  end of method BST::setMark  ----- */

	Node *
BST::getRoot ( )
{
	return _root;
}		/* -----  end of method BST::getRoot  ----- */

	uint64_t
BST::getRootKey ( )
{
	return _root->key;
}		/* -----  end of method BST::getRoot  ----- */

	void
BST::getKeys ( Node * n, std::vector<uint64_t> & keys )
{
	if (n) {
		keys.push_back(n->key);
		getKeys(n->left, keys);
		getKeys(n->right, keys);
	}
	return ;
}		/* -----  end of method BST::getKeys  ----- */

	void
BST::getKeys ( std::vector<uint64_t> & keys )
{
	return getKeys(_root, keys);
}		/* -----  end of method BST::getKeys  ----- */


	Node *
BST::search ( uint64_t key )
{
	Node * par = NULL;
	Node * curr = trav(key, par);
	return curr;
}		/* -----  end of method BST::find  ----- */


	unsigned int
BST::add ( uint64_t key )
{
	Node * par = NULL;
	Node * curr = trav(key, par);
	if (!curr) {
		curr = new Node(key);
		if (!par) {
			_root = curr;
		} else if (key < par->key){
			par->left = curr;
		} else {
			par->right = curr;
		}
	} else {
		curr->count += 1;
	}
	return curr->count;
}		/* -----  end of method BST::add  ----- */

	void
BST::copy ( Node * n )
{
	if (n) {
		add(n->key);
		copy(n->left);
		copy(n->right);
	}
	return ;
}		/* -----  end of method BST::copy  ----- */


	void
BST::makeEmpty ( Node * n )
{
	if (n) {
		makeEmpty(n->left);
		makeEmpty(n->right);
		delete n;
	}
	return ;
}		/* -----  end of method BST::makeEmpty  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  BST
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
	const BST&
BST::operator = ( const BST &other )
{
	if ( this != &other ) {
		makeEmpty(_root);
		_root = NULL;
		copy(other._root);
	}
	return *this;
}  /* -----  end of method BST::operator =  (assignment operator)  ----- */


	void
BST::print ( Node * curr, uint64_t level ) const
{
	if (curr) {
		print(curr->right, level+1);
		std::cout << std::setw(level*WIDTHUNIT) << curr->key << std::endl;
		print(curr->left, level+1);
	}
	return ;
}		/* -----  end of method BST::print  ----- */

	void
BST::print ( std::ostream & ost, Node * curr, uint64_t level ) const
{
	if (curr) {
		print(curr->right, level+1);
		ost << std::setw(level*WIDTHUNIT) << curr->key << std::endl;
		print(curr->left, level+1);
	}
	return ;
}		/* -----  end of method BST::print  ----- */

	void
BST::print ( ) const
{
	return print(_root, 1);
}		/* -----  end of method BST::print  ----- */


std::ostream & operator<<(std::ostream &ost, const BST & t)
{
     t.print(ost, t._root, 1);
     return ost;
}
