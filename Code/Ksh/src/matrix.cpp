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
	_data = new double[_sizeR * _sizeC]();
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
	_data = new double[_sizeR * _sizeC]();

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
		throw std::out_of_range("In get :: Matrix position arguments are out of range");
	}

	return _data[(m * _sizeC) + n];
}		/* -----  end of method MatrixRow::get  ----- */


	std::vector<double>
MatrixRow::getRow ( unsigned int row ) const
{
	std::vector<double> drow(&_data[row * _sizeC], &_data[row * _sizeC] + _sizeC);
	return drow;
}		/* -----  end of method MatrixRow::getRow  ----- */

	void
MatrixRow::print ( std::ostream & os ) const
{
	os << _sizeR << std::endl;
	os << _sizeC << std::endl;
	for ( unsigned int i = 0; i < _sizeR; ++i ) {
		for ( unsigned int j = 0; j < _sizeC; ++j ) {
			os << _data[(i * _sizeC) + j] << " ";
		}
		os << std::endl;
	}
	return ;
}		/* -----  end of method MatrixRow::print  ----- */


	void
MatrixRow::set ( unsigned int m, unsigned int n, double val )
{
	if (m >= _sizeR || n >= _sizeC ) 
	{
		throw std::out_of_range("In set :: Matrix position arguments are out of range");
	}

	_data[(m * _sizeC) + n] = val;
	return ;
}		/* -----  end of method MatrixRow::set  ----- */

	void
MatrixRow::shape ( unsigned int rows, unsigned int cols )
{
	_sizeR = rows;
	_sizeC = cols;

	if (_data) {
		delete [] _data;
	}
	_data = new double[_sizeR * _sizeC]();
	return ;
}		/* -----  end of method MatrixRow::shape  ----- */

	void
MatrixRow::clear ( )
{
	_sizeR = 0;
	_sizeC = 0;

	if (_data) {
		delete [] _data;
	}
	_data = new double[0]();
	return ;
}		/* -----  end of method MatrixRow::clear  ----- */

	void
MatrixRow::read ( std::istream & is )
{
	is >> _sizeR >> _sizeC;
	if (_data) {
		delete [] _data;
	}
	_data = new double[_sizeR * _sizeC]();

	for ( unsigned int i = 0; i < _sizeR; ++i ) {
		for ( unsigned int j = 0; j < _sizeC; ++j ) {
			is >> _data[(i * _sizeC) + j];
		}
	}
	return ;
}		/* -----  end of method MatrixRow::read  ----- */

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
	_data = new double [_sizeR * _sizeC]();

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

	MatrixRow
MatrixRow::operator + ( const MatrixRow &other ) const
{
	MatrixRow R;
	R.shape(_sizeR, _sizeC);
	for (unsigned int i = 0; i < _sizeR * _sizeC; ++i) {
		R._data[i] = _data[i] + other._data[i];
	}
	return R;
}		/* -----  end of method MatrixRow::operator +  ----- */

	MatrixRow
MatrixRow::operator - ( const MatrixRow &other ) const
{
	MatrixRow R;
	R.shape(_sizeR, _sizeC);
	for (unsigned int i = 0; i < _sizeR * _sizeC; ++i) {
		R._data[i] = _data[i] - other._data[i];
	}
	return R;
}		/* -----  end of method MatrixRow::operator -  ----- */

	MatrixRow
MatrixRow::operator + ( const double &scalar ) const
{
	MatrixRow R;
	R.shape(_sizeR, _sizeC);
	for (unsigned int i = 0; i < _sizeR * _sizeC; ++i) {
		R._data[i] = _data[i] + scalar;
	}
	return R;
}		/* -----  end of method MatrixRow::operator +  ----- */

	MatrixRow
MatrixRow::operator - ( const double &scalar ) const
{
	MatrixRow R;
	R.shape(_sizeR, _sizeC);
	for (unsigned int i = 0; i < _sizeR * _sizeC; ++i) {
		R._data[i] = _data[i] - scalar;
	}
	return R;
}		/* -----  end of method MatrixRow::operator -  ----- */

	MatrixRow
MatrixRow::operator * ( const double &scalar ) const
{
	MatrixRow R;
	R.shape(_sizeR, _sizeC);
	for (unsigned int i = 0; i < _sizeR * _sizeC; ++i) {
		R._data[i] = _data[i] * scalar;
	}
	return R;
}		/* -----  end of method MatrixRow::operator -  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  MatrixUnit
 *      Method:  MatrixUnit
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
MatrixUnit::MatrixUnit ( unsigned int rows, unsigned int cols)
{
	_sizeR = rows;
	_sizeC = cols;
	_data = new unsigned int[_sizeR]();
}  /* -----  end of method MatrixUnit::MatrixUnit  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MatrixUnit
 *      Method:  MatrixUnit
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
MatrixUnit::MatrixUnit ( const MatrixUnit &other )
{
	_sizeR = other._sizeR;
	_sizeC = other._sizeC;
	_data = new unsigned int[_sizeR]();

	for (unsigned int i = 0; i < _sizeR; ++i) {
		_data[i] = other._data[i];
	}

}  /* -----  end of method MatrixUnit::MatrixUnit  (copy constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MatrixUnit
 *      Method:  ~MatrixUnit
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
MatrixUnit::~MatrixUnit ()
{
	if (_data) {
		delete [] _data;
	}
}  /* -----  end of method MatrixUnit::~MatrixUnit  (destructor)  ----- */

	unsigned int
MatrixUnit::rows ( ) const
{
	return _sizeR;
}		/* -----  end of method MatrixUnit::rows  ----- */

	unsigned int
MatrixUnit::cols ( ) const
{
	return _sizeC;
}		/* -----  end of method MatrixUnit::cols  ----- */

	double
MatrixUnit::get ( unsigned int m, unsigned int n ) const
{
	if (m >= _sizeR || n >= _sizeC ) 
	{
		throw std::out_of_range("In double get :: Matrix position arguments are out of range");
	}

	return (n == _data[m]) ? 1.0 : 0.0;
}		/* -----  end of method MatrixUnit::get  ----- */

	unsigned int
MatrixUnit::get ( unsigned int m ) const
{
	if (m >= _sizeR ) 
	{
		throw std::out_of_range("In uint get :: Matrix position arguments are out of range");
	}

	return _data[m];
}		/* -----  end of method MatrixUnit::get  ----- */


	std::vector<double>
MatrixUnit::getRow ( unsigned int row ) const
{
	std::vector<double> drow(_sizeC, 0.0);
	drow[_data[row]] = 1.0;
	return drow;
}		/* -----  end of method MatrixUnit::getRow  ----- */

	void
MatrixUnit::print ( std::ostream & os ) const
{
	os << _sizeR << std::endl;
	os << _sizeC << std::endl;
	for ( unsigned int i = 0; i < _sizeR; ++i ) {
		for ( unsigned int j = 0; j < _sizeC; ++j ) {
			os << get(i, j) << " ";
		}
		os << std::endl;
	}
	return ;
}		/* -----  end of method MatrixUnit::print  ----- */

	void
MatrixUnit::shape ( unsigned int rows, unsigned int cols )
{
	_sizeR = rows;
	_sizeC = cols;

	if (_data) {
		delete [] _data;
	}
	_data = new unsigned int[_sizeR]();
	return ;
}		/* -----  end of method MatrixUnit::shape  ----- */

	void
MatrixUnit::clear ( )
{
	_sizeR = 0;
	_sizeC = 0;

	if (_data) {
		delete [] _data;
	}
	_data = new unsigned int[0]();
	return ;
}		/* -----  end of method MatrixUnit::clear  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MatrixUnit
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
	MatrixUnit&
MatrixUnit::operator = ( const MatrixUnit &other )
{
	if (other._sizeR == _sizeR && other._sizeC == _sizeC)
	{
		for (unsigned int i = 0; i < _sizeR; i++)
		{
			_data[i] = other._data[i];
		}

		return *this;
	}

	delete [] _data;

	_sizeR = other._sizeR;
	_sizeC = other._sizeC;
	_data = new unsigned int[_sizeR]();

	for (unsigned int i = 0; i < _sizeR; i++)
	{
		_data[i] = other._data[i];
	}

	return *this;
}  /* -----  end of method MatrixUnit::operator =  (assignment operator)  ----- */

	double
MatrixUnit::operator () ( unsigned int m, unsigned int n ) const
{
	return get(m, n);
}		/* -----  end of method MatrixUnit::operator ()  ----- */

	unsigned int
MatrixUnit::operator () ( unsigned int m ) const
{
	return get(m);
}		/* -----  end of method MatrixUnit::operator ()  ----- */
