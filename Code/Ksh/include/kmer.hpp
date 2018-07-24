/*
 * =====================================================================================
 *
 *       Filename:  kmer.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/04/2018 07:43:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andres Chamorro (ach), andresdavidchamorro@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef  KMER_INC
#define  KMER_INC
#define  BASE_MASK 0x3 /* binary: 11 */

#include <stdint.h>
#include <string>
#include <vector>
#include <binarytree.hpp>
#include <matrix.hpp>

enum
{
    BASE_A = 1, /* binary: 001 */
    BASE_C = 2, /* binary: 010 */
    BASE_G = 3, /* binary: 011 */
    BASE_T = 4, /* binary: 100 */
};
/*
 * =====================================================================================
 *        Class:  Kmer
 *  Description:  
 * =====================================================================================
 */
class Kmer
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		Kmer ();                            /* constructor      */
		Kmer (unsigned int );                   /* constructor      */
		Kmer ( const Kmer &other );   			/* copy constructor */
		~Kmer ();                           /* destructor       */

		/* ====================  ACCESSORS     ======================================= */

		unsigned int getNs();

		/* ====================  MUTATORS      ======================================= */

		void setK(unsigned int );

		unsigned int fromSequence(std::string , unsigned int);

		unsigned int getKs(std::string);

		std::vector<BST> BSTForest(std::string, unsigned int, unsigned int);

		/* ====================  OPERATORS     ======================================= */

		std::string toSeq(unsigned int );

		unsigned int toBin(std::string );

		MatrixRow getSim();

		Kmer& operator = ( const Kmer &other ); /* assignment operator */

	protected:
		/* ====================  METHODS       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */

	private:
		/* ====================  METHODS       ======================================= */

		unsigned int bitSet(std::string );
		double hammitDist(std::string, std::string);

		/* ====================  DATA MEMBERS  ======================================= */

		BST * _kmer;
		unsigned int _ns;

}; /* -----  end of class Kmer  ----- */
#endif   /* ----- #ifndef KMER_INC  ----- */
