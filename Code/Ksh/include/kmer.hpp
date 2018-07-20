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
    BASE_A = 0x0, /* binary: 00 */
    BASE_C = 0x1, /* binary: 01 */
    BASE_G = 0x2, /* binary: 10 */
    BASE_T = 0x3, /* binary: 11 */
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
		Kmer (uint64_t );                   /* constructor      */
		Kmer ( const Kmer &other );   			/* copy constructor */
		~Kmer ();                           /* destructor       */

		/* ====================  ACCESSORS     ======================================= */

		unsigned int getNs();

		/* ====================  MUTATORS      ======================================= */

		void setK(uint64_t );

		unsigned int fromSequence(std::string , unsigned int);

		unsigned int getKs(std::string);

		std::vector<BST> BSTForest(std::string, unsigned int, unsigned int);

		/* ====================  OPERATORS     ======================================= */

		std::string toSeq(uint64_t );

		uint64_t toBin(std::string );

		MatrixRow getSim();

		Kmer& operator = ( const Kmer &other ); /* assignment operator */

	protected:
		/* ====================  METHODS       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */

	private:
		/* ====================  METHODS       ======================================= */

		uint64_t bitSet(std::string );
		double hammitDist(std::string, std::string);

		/* ====================  DATA MEMBERS  ======================================= */

		BST * _kmer;
		unsigned int _ns;

}; /* -----  end of class Kmer  ----- */
#endif   /* ----- #ifndef KMER_INC  ----- */
