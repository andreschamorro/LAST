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
#include <vector>
#include <iostream>

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
		std::vector<double> getRow(unsigned int) const;
		void print(std::ostream &) const;

		/* ====================  MUTATORS      ======================================= */

		void set ( unsigned int, unsigned int, double );
		void shape ( unsigned int, unsigned int );
		void clear ();
		void read(std::istream &);

		/* ====================  OPERATORS     ======================================= */

		friend std::ostream& operator <<(std::ostream & os, const MatrixRow & M )
		{
			M.print(os);
			return os;
		}
		friend std::istream& operator >>(std::istream & is, MatrixRow & M )
		{
			M.read(is);
			return is;
		}
		MatrixRow& operator = ( const MatrixRow & ); /* assignment operator */
		double operator ()( unsigned int, unsigned int ) const;
    MatrixRow operator + ( const MatrixRow & ) const;
		MatrixRow operator - ( const MatrixRow & ) const;
    MatrixRow operator + ( const double & ) const;
		MatrixRow operator - ( const double & ) const;
    MatrixRow operator * ( const double & ) const;

		friend MatrixRow operator + ( const double & scalar, const MatrixRow & M)
		{
			return M + scalar;
		}
		friend MatrixRow operator - ( const double & scalar, const MatrixRow & M)
		{
			return M*(-1.0) + scalar;
		}
		friend MatrixRow operator * ( const double & scalar, const MatrixRow & M)
		{
			return M * scalar;
		}

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


/*
 * =====================================================================================
 *        Class:  MatrixUnit
 *  Description:  
 * =====================================================================================
 */
class MatrixUnit
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		MatrixUnit () : _data(0), _sizeR(0), _sizeC(0) { }                            /* constructor      */
		MatrixUnit (unsigned int, unsigned int);                             /* constructor      */
		MatrixUnit ( const MatrixUnit &other );   /* copy constructor */
		~MatrixUnit ();                            /* destructor       */

		/* ====================  ACCESSORS     ======================================= */

		unsigned int rows () const;
		unsigned int cols () const;

		double get ( unsigned int, unsigned int ) const;
		unsigned int get ( unsigned int ) const;
		std::vector<double> getRow(unsigned int) const;
		void print(std::ostream &) const;
		/* ====================  MUTATORS      ======================================= */

		void set ( unsigned int, unsigned int, double );
		void set ( unsigned int, unsigned int );
		void shape ( unsigned int, unsigned int );
		void clear ();
		void read (std::istream &);

		/* ====================  OPERATORS     ======================================= */

		friend std::ostream& operator <<(std::ostream & os, const MatrixUnit & M )
		{
			M.print(os);
			return os;
		}
		friend std::istream& operator >>(std::istream & is, MatrixUnit & M )
		{
			M.read(is);
			return is;
		}
		MatrixUnit& operator = ( const MatrixUnit & ); /* assignment operator */
		double operator ()( unsigned int, unsigned int ) const;
		unsigned int operator ()( unsigned int ) const;

	protected:
		/* ====================  METHODS       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */

	private:
		/* ====================  METHODS       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */

		unsigned int * _data;
		size_t _sizeR;
		size_t _sizeC;

}; /* -----  end of class MatrixUnit  ----- */

#endif   /* ----- #ifndef matrix_INC  ----- */
