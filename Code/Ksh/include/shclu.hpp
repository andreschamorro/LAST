/*
 * =====================================================================================
 *
 *       Filename:  shclu.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/15/2018 09:30:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andres Chamorro (ach), andresdavidchamorro@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>
#include <limits>

#include "matrix.hpp"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  cpu_matrix_mem
 *  Description:  Compute M = S̃A
 * =====================================================================================
 */
	MatrixRow
cpu_matrix_mem ( const MatrixRow S, const std::vector<unsigned int> a , const unsigned int cols )
{
	MatrixRow M(S.rows(), cols);
	unsigned int col;
	double Mval = 0.0;
	for (unsigned int j = 0; j < a.size(); j++) {
		col = a[j];
		for (unsigned int i = 0; i < S.rows(); i++) {
			Mval = M(i, col) + S(i, j);
			M.set(i, col, Mval);
		}
	}
	return M;
}		/* -----  end of function cpu_matrix_mem  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  cpu_min_rows
 *  Description:  
 * =====================================================================================
 */
	void
cpu_min_rows ( const MatrixRow M, std::vector<unsigned int> &result_minIdx, 
																	std::vector<double> &result_minVal, double &resul_minsum )
{
	double min;
	int idx;
	double val;
	double sum = 0;
	for (unsigned int i = 0; i < M.rows(); i++) {
		min = std::numeric_limits<double>::infinity();
		idx = -1;
		for (unsigned int j = 0; j < M.cols(); j++) {
			val = M(i, j);
			if(val < min) {
				min = val;
				idx = i;
			}
		}
		result_minVal[i] = min;
		result_minIdx[i] = idx;
		sum += min;
	}
	resul_minsum = sum;
}		/* -----  end of function cpu_min_rows  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  cpu_shrinkageClustering
 *  Description:  
 * =====================================================================================
 */
	std::vector<unsigned int>
cpu_shrinkageClustering ( const MatrixRow S, int k0, unsigned maxiter = 500 )
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();//seed
	std::default_random_engine dre(seed);//engine
	std::uniform_int_distribution<int> di(0,(k0-1));//distribution

	std::vector<unsigned int> A(S.rows());
	std::vector<unsigned int> e_A(k0, 1);
	std::generate(A.begin(), A.end(), [&]{ return di(dre);});

// Delete empty columns in A.	
	for (unsigned int k = 0; k < A.size(); ++k) {
		e_A[A[k]] = 0;
	}
	unsigned int res = 0, old = 0;
	for (unsigned int k = 0; k < e_A.size(); ++k) {
		old = e_A[k];
		e_A[k] = res;
		res += old;
	}
	for (unsigned int k = 0; k < A.size(); ++k) {
		A[k] -= e_A[A[k]];
	}

	unsigned int cols = *std::max_element( A.begin(), A.end() ) + 1;

// Initialize M matix and S hat
	MatrixRow h_M;

	MatrixRow h_S;
	h_S.shape(S.rows(), S.cols());
	h_S = 1 - 2.0*S;

	double sumvi = 1;
	unsigned int i, size, it = 0;
	size_t h_X, h_C; 
	std::vector<double>::iterator min_elem;
	std::vector<double> r_M, h_min_val;
	std::vector<unsigned int> h_min_indx;
	old = 0;
	while ((abs(sumvi) > 1.0e-06) && (it < maxiter)) {
// Compute M = S̃A
		h_M = cpu_matrix_mem(h_S, A, cols);
		
		size = h_M.rows();
		h_min_val.resize(size);
		h_min_indx.resize(size);

		cpu_min_rows(h_M, h_min_indx, h_min_val, sumvi);

//		Compute v
		for (i = 0; i < size; ++i) {
			h_min_val[i] -= h_M(i, A[i]);
			sumvi -= h_M(i, A[i]);
		}

		min_elem = std::min_element(h_min_val.begin(), h_min_val.end());
		h_X = std::distance(h_min_val.begin(), min_elem);

		r_M.clear();
		r_M = h_M.getRow(h_X);
		if (h_X <= r_M.size()) {
			r_M[h_X] = std::numeric_limits<double>::infinity();
		}
		min_elem = std::min_element(r_M.begin(), r_M.end());
		h_C = std::distance(r_M.begin(), min_elem);

		std::cout << "h_X = " << h_X << " h_C = " << h_C << std::endl;

		old = A.at(h_X);
		A.at(h_X) = h_C; 

// Delete empty columns in A.	
		if (std::find(A.begin(), A.end(), old) == A.end()) {
			for (i = 0; i < A.size(); i++) {
				if (old < A.at(i)) {
					A.at(i) -= 1;
				}
			}
			cols -= 1;
		}
		it++;
	}
	return A;
}		/* -----  end of function cpu_shrinkageClustering  ----- */
