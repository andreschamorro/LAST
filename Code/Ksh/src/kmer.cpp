/*
 * =====================================================================================
 *
 *       Filename:  kmer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/04/2018 09:33:38 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andres Chamorro (ach), andresdavidchamorro@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <kmer.hpp>

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Kmer
 *      Method:  Kmer
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Kmer::Kmer ()
{
	_kmer = NULL;
}  /* -----  end of method Kmer::Kmer  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Kmer
 *      Method:  Kmer
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Kmer::Kmer (uint64_t key)
{
	_kmer = new BST(key);
}  /* -----  end of method Kmer::Kmer  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Kmer
 *      Method:  Kmer
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
//Kmer::Kmer ( const Kmer &other )
//{
//}  /* -----  end of method Kmer::Kmer  (copy constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Kmer
 *      Method:  ~Kmer
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
Kmer::~Kmer ()
{
	delete _kmer;
}  /* -----  end of method Kmer::~Kmer  (destructor)  ----- */


	unsigned int
Kmer::getNs ( )
{
	return _ns;
}		/* -----  end of method Kmer::getNs  ----- */

	void
Kmer::setK ( uint64_t key)
{
	if (!_kmer) {
		_kmer = new BST(key);
	} else {
		delete _kmer;
		_kmer = new BST(key);
	}
	return ;
}		/* -----  end of method Kmer::setK  ----- */

	std::string
Kmer::toSeq ( uint64_t key )
{
	std::string seq;
  uint64_t shift = 2;
  uint64_t mask = BASE_MASK << shift;

  /* get the i-th DNA base */
  uint64_t base = (key & mask) >> shift;

  switch (base)
  {
      case BASE_A:
          seq.append("A");
          break;
      case BASE_C:
          seq.append("C");
          break;
      case BASE_G:
          seq.append("G");
          break;
      case BASE_T:
          seq.append("T");
          break;
      default:
          throw std::runtime_error("invalid DNA base");
  }
	return seq;
}		/* -----  end of method Kmer::toSeq  ----- */


	uint64_t
Kmer::toBin ( std::string seq)
{
	uint64_t binary = 0x0;
	uint64_t shift = 2;
	
	for (size_t i = 0; i < seq.size(); ++i) {
  	switch (seq[i]){
  	    case 'A':
						binary = (binary << shift) | (BASE_A);
  	        break;
  	    case 'C':
						binary = (binary << shift) | (BASE_C);
  	        break;
  	    case 'G':
						binary = (binary << shift) | (BASE_G);
  	        break;
  	    case 'T':
						binary = (binary << shift) | (BASE_T);
  	        break;
  	    default:
  	        throw std::invalid_argument("invalid DNA base");
  	}
	}
	return binary;
}		/* -----  end of method Kmer::toBin  ----- */

	unsigned int
Kmer::fromSequence ( std::string seqs, unsigned int k )
{

	bool mark = false;
	unsigned int count;
	uint64_t bin = 0x0;
	std::string buf (seqs, 0, k);

	if (_kmer) {
		delete _kmer;
	}
	_kmer = new BST( 0x1 << (2*k-1) );
	_ns = 0;

	bin = toBin(buf);
	if ((bin == _kmer->getRootKey()) && mark) {
		_ns++;
		mark = true;
	} else {
		count = _kmer->add(bin);
		if (count == 1) {
			_ns++;
		}
	}

	for (std::size_t i = k; i < seqs.size(); i++) {
		buf = buf.substr(1) + seqs[i];
		bin = toBin(buf);
		if ((bin == _kmer->getRootKey()) && mark) {
			_ns++;
			mark = true;
		} else {
			count = _kmer->add(bin);
			if (count == 1) {
				_ns++;
			}
		}
	}
	return _ns;
}		/* -----  end of method Kmer::fromSequence  ----- */


	unsigned int
Kmer::getKs ( std::string seqs )
{
	bool mark = false;
	unsigned int count;
	uint64_t bin = 0x0;

	unsigned int k = 0;
	_ns = 0;
	while( k + _ns < seqs.size() + 1 ){
		k++;
//		_ns = fromSequence(seqs, k);
		std::string buf (seqs, 0, k);
		if (_kmer) {
			delete _kmer;
		}
		_kmer = new BST( 0x1 << (2*k-1) );
		_ns = 0;

		bin = toBin(buf);
		if ((bin == _kmer->getRootKey()) && mark) {
			_ns++;
			mark = true;
		} else {
			count = _kmer->add(bin);
			if (count == 1) {
				_ns++;
			}
		}

		for (std::size_t i = k; i < seqs.size(); i++) {
			buf = buf.substr(1) + seqs[i];
			bin = toBin(buf);
			if ((bin == _kmer->getRootKey()) && mark) {
				_ns++;
				mark = true;
			} else {
				count = _kmer->add(bin);
				if (count == 1) {
					_ns++;
				} else if (count > 2){
					_ns = 0;
					break;
				}
			}
		}
	}
	return k;
}		/* -----  end of method Kmer::getKs  ----- */


	std::vector<BST>
Kmer::BSTForest ( std::string seqs, unsigned int ks, unsigned int max )
{
	std::vector<BST> tk;
	for (unsigned int k = ks; k < max; k++) {
		fromSequence(seqs, k);
	}
	return tk;
}		/* -----  end of method Kmer::BSTForest  ----- */

	MatrixRow
Kmer::getSim ( )
{
	std::vector<uint64_t> keys;
	_kmer->getKeys(keys);

	MatrixRow S(keys.size(), keys.size());

	for (size_t i = 0; i < keys.size(); ++i) {
		for (size_t j = i; j < keys.size(); ++j) {
			S.set(i, j, hammitDist(toSeq(keys[i]), toSeq(keys[j])));
			S.set(j, i, S.get(i, j));
		}
	}
	return S;
}		/* -----  end of method Kmer::getSim  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Kmer
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
	Kmer&
Kmer::operator = ( const Kmer &other )
{
	if ( this != &other ) {
	}
	return *this;
}  /* -----  end of method Kmer::operator =  (assignment operator)  ----- */


	double
Kmer::hammitDist ( std::string xs, std::string ys )
{
	double hd = 0.0;
	for (size_t i = 0; i < xs.size(); ++i) {
		if (xs[i] != ys[i]) {
			hd += 1.0;
		}
	}
	return ((1.0 - hd)/double(xs.size()));
}		/* -----  end of method Kmer::hammitDist  ----- */

