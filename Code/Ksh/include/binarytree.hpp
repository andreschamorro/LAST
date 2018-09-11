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

#ifndef __dna_h__
#define __dna_h__

#include <cstring>   /* std::memset */
#include <stdexcept> /* std::invalid_argument */

#define BASE_MASK 0x3 /* binary: 11 */

/* useful constants */
enum
{
    BASE_A = 0x0, /* binary: 00 */
    BASE_C = 0x1, /* binary: 01 */
    BASE_G = 0x2, /* binary: 10 */
    BASE_T = 0x3, /* binary: 11 */
};

class DnaBitset
{
public:
    /**
     * @brief Constructs a compressed representation of a DNA sequence.
     * @param dna_str A string holding a DNA sequence (e.g. "ATGCACG").
     * @param dna_len The length of the DNA sequence.
     */
		DnaBitset()
		{
    	m_data = NULL;
    	m_len = 0;
		}
    DnaBitset(const char* dna_str, const size_t dna_len)
		{
			Set(dna_str, dna_len);
		}
    void Set(const char* dna_str, const size_t dna_len)
    {
			if(m_data)
				delete [] m_data;

        m_len = dna_len;

        /* number of bytes necessary to store dna_str as a bitset */
        size_t dna_bytes = (dna_len / 4) + (dna_len % 4 != 0);

        m_data = new uint8_t[dna_bytes];

        std::memset(m_data, 0, dna_bytes);

        /* for each base of the DNA sequence */
        for (size_t i = 0; i < dna_len; ++i)
        {
            uint8_t shift = 6 - 2 * (i % 4);

            switch (dna_str[i])
            {
                case 'A':
                    m_data[i / 4] |= BASE_A << shift;
                    break;
                case 'C':
                    m_data[i / 4] |= BASE_C << shift;
                    break;
                case 'G':
                    m_data[i / 4] |= BASE_G << shift;
                    break;
                case 'T':
                    m_data[i / 4] |= BASE_T << shift;
                    break;
                default:
                    throw std::invalid_argument("invalid DNA base");
            }

            shift = (shift == 0) ? 6 : shift - 2;
        }
    }

    /**
     * @brief Destructor.
     */
    ~DnaBitset()
    {
        delete[] m_data;
    }

    /**
     * @brief Returns the stored DNA sequence as an ASCII string.
     */
    char* to_string() const
    {
        char* dna_str = new char[m_len + 1];

        /* for each base of the DNA sequence */
        for (size_t i = 0; i < m_len; ++i)
        {
            uint8_t shift = 6 - 2 * (i % 4);
            uint8_t mask = BASE_MASK << shift;

            /* get the i-th DNA base */
            uint8_t base = (m_data[i / 4] & mask) >> shift;

            switch (base)
            {
                case BASE_A:
                    dna_str[i] = 'A';
                    break;
                case BASE_C:
                    dna_str[i] = 'C';
                    break;
                case BASE_G:
                    dna_str[i] = 'G';
                    break;
                case BASE_T:
                    dna_str[i] = 'T';
                    break;
                default:
                    throw std::runtime_error("invalid DNA base");
            }
        }

        dna_str[m_len] = '\0';
        return dna_str;
    }

		friend bool operator< (const DnaBitset& lhs, const DnaBitset& rhs)
		{
			if (lhs.m_len < rhs.m_len) {
				return true;
			}
			if (lhs.m_len > rhs.m_len) {
				return false;
			}
			bool t_v = true;
      for (size_t i = 0; i < lhs.m_len; ++i){
				if (lhs.m_data[i] > rhs.m_data[i]) {
					t_v = false;
					break;
				}
			}
			return t_v;
		}
		inline friend bool operator> (const DnaBitset& lhs, const DnaBitset& rhs){ return rhs < lhs; }
		inline friend bool operator<=(const DnaBitset& lhs, const DnaBitset& rhs){ return !(lhs > rhs); }
		inline friend bool operator>=(const DnaBitset& lhs, const DnaBitset& rhs){ return !(lhs < rhs); }
		friend bool operator==(const DnaBitset& lhs, const DnaBitset& rhs){ 
			if (lhs.m_len != rhs.m_len) {
				return false;
			}
			bool t_v = true;
      for (size_t i = 0; i < lhs.m_len; ++i){
				if (lhs.m_data[i] != rhs.m_data[i]) {
					t_v = false;
					break;
				}
			}
			return t_v;
		}
		inline friend bool operator!=(const DnaBitset& lhs, const DnaBitset& rhs){ return !(lhs == rhs); }

private:
    uint8_t* m_data;
    size_t m_len;
};

#endif /* __dna_h__ */

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
		DnaBitset key;
		unsigned int count;
		bool mark;
		Node *left = NULL;
		Node *right = NULL;

		/* ====================  LIFECYCLE     ======================================= */
		Node () {
			this->mark = false;
			this->count = 0;
		}                             /* constructor      */
		Node (DnaBitset key) {
			this->key = key;
			this->mark = false;
			this->count = 1;
		}                             /* constructor      */
		Node (DnaBitset key, bool mark) {
			this->key = key;
			this->mark = mark;
			this->count = 1;
		}                             /* constructor      */
		Node (DnaBitset key, Node *left, Node *right) {
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
		BST (DnaBitset );                             /* constructor      */
		BST ( const BST &other );   /* copy constructor */
		~BST ();                           /* destructor       */

		/* ====================  ACCESSORS     ======================================= */

		Node *trav(DnaBitset, Node * &);
		void setRootMark();
		void setMark( Node *);
		Node *getRoot();
		DnaBitset getRootKey();
		void getKeys(Node *, std::vector<DnaBitset> &);
		void getKeys( std::vector<DnaBitset> & );
		void getCounts( Node *, std::vector<unsigned int> &);
		void getCounts( std::vector<unsigned int> &);

		/* ====================  MUTATORS      ======================================= */

		unsigned int add(DnaBitset );

		void remove(DnaBitset );

		Node * search(DnaBitset );

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
