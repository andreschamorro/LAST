/*
 * =====================================================================================
 *
 *       Filename:  matrix.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/12/2018 08:43:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andres Chamorro (ach), andresdavidchamorro@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  MATRIX_INC
#define  MATRIX_INC

#include <cstddef>
#include <stdexcept>

/*
 * =====================================================================================
 *        Class:  MatrixRow
 *  Description:  
 * =====================================================================================
 */
class MatrixRow
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		MatrixRow () : _data(0), _sizeR(0), _sizeC(0) { }                            /* constructor      */
		MatrixRow (unsigned int, unsigned int);                             /* constructor      */
		MatrixRow ( const MatrixRow &other );   /* copy constructor */
		~MatrixRow ();                            /* destructor       */

		/* ====================  ACCESSORS     ======================================= */

		unsigned int rows () const;
		unsigned int cols () const;

		double get ( unsigned int, unsigned int ) const;

		/* ====================  MUTATORS      ======================================= */

		void set ( unsigned int, unsigned int, double );
		void clear ();

		/* ====================  OPERATORS     ======================================= */

		MatrixRow& operator = ( const MatrixRow &other ); /* assignment operator */
		double operator ()( unsigned int, unsigned int ) const;

	protected:
		/* ====================  METHODS       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */

	private:
		/* ====================  METHODS       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */

		double * _data;
		size_t _sizeR;
		size_t _sizeC;

}; /* -----  end of class MatrixRow  ----- */


#endif   /* ----- #ifndef matrix_INC  ----- */
