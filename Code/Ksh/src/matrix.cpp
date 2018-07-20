/*
 * =====================================================================================
 *
 *       Filename:  matrix.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/12/2018 08:54:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andres Chamorro (ach), andresdavidchamorro@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <matrix.hpp>


/*
 *--------------------------------------------------------------------------------------
 *       Class:  MatrixRow
 *      Method:  MatrixRow
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
MatrixRow::MatrixRow ( unsigned int rows, unsigned int cols)
{
	_sizeR = rows;
	_sizeC = cols;
	_data = new double[_sizeR * _sizeC];
}  /* -----  end of method MatrixRow::MatrixRow  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MatrixRow
 *      Method:  MatrixRow
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
MatrixRow::MatrixRow ( const MatrixRow &other )
{
	_sizeR = other._sizeR;
	_sizeC = other._sizeC;
	_data = new double[_sizeR * _sizeC];

	for (unsigned int i = 0; i < _sizeR * _sizeC; ++i) {
		_data[i] = other._data[i];
	}

}  /* -----  end of method MatrixRow::MatrixRow  (copy constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MatrixRow
 *      Method:  ~MatrixRow
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
MatrixRow::~MatrixRow ()
{
	if (_data) {
		delete [] _data;
	}
}  /* -----  end of method MatrixRow::~MatrixRow  (destructor)  ----- */

	unsigned int
MatrixRow::rows ( ) const
{
	return _sizeR;
}		/* -----  end of method MatrixRow::rows  ----- */

	unsigned int
MatrixRow::cols ( ) const
{
	return _sizeC;
}		/* -----  end of method MatrixRow::cols  ----- */

	double
MatrixRow::get ( unsigned int m, unsigned int n ) const
{
	if (m >= _sizeR || n >= _sizeC ) 
	{
		throw std::out_of_range("Matix position arguments are out of range");
	}

	return _data[(m * _sizeC) + n];
}		/* -----  end of method MatrixRow::get  ----- */

	void
MatrixRow::set ( unsigned int m, unsigned int n, double val )
{
	if (m >= _sizeR || n >= _sizeC ) 
	{
		throw std::out_of_range("Matix position arguments are out of range");
	}

	_data[(m * _sizeC) + n] = val;
	return ;
}		/* -----  end of method MatrixRow::set  ----- */

	void
MatrixRow::clear ( )
{
	_sizeR = 0;
	_sizeC = 0;

	delete [] _data;
	_data = new double[0];
	return ;
}		/* -----  end of method MatrixRow::clear  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MatrixRow
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
	MatrixRow&
MatrixRow::operator = ( const MatrixRow &other )
{
	if (other._sizeR == _sizeR && other._sizeC == _sizeC)
	{
		for (unsigned int i = 0; i < _sizeR * _sizeC; i++)
		{
			_data[i] = other._data[i];
		}

		return *this;
	}

	delete [] _data;

	_sizeR = other._sizeR;
	_sizeC = other._sizeC;
	_data = new double [_sizeR * _sizeC];

	for (unsigned int i = 0; i < _sizeR * _sizeC; i++)
	{
		_data[i] = other._data[i];
	}

	return *this;
}  /* -----  end of method MatrixRow::operator =  (assignment operator)  ----- */

	double
MatrixRow::operator () ( unsigned int m, unsigned int n ) const
{
	return get(m, n);
}		/* -----  end of method MatrixRow::operator ()  ----- */

