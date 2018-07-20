/*
 * =====================================================================================
 *
 *       Filename:  matrix.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2018 11:01:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andres Chamorro (ach), andresdavidchamorro@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  MATRIX_ROW_INC
#define  MATRIX_ROW_INC
/*
 * =====================================================================================
 *       Struct:  Matrix
 *  Description:  Matrices are stored in row-major order: 
 *                M(row, col) = *(M.elements + row * M.width + col) 
 * =====================================================================================
 */
typedef struct { 
  int width; 
  int height; 
  float* elements; 
  int stride;
} Matrix;                                       /* ----------  end of struct Matrix  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getElement
 *  Description:  Get matrix element
 * =====================================================================================
 */
__device__ float getElement(const Matrix A, int row, int col) { 
  return A.elements[row * A.stride + col]; 
} 

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  setElement
 *  Description:  Set a matrix element
 * =====================================================================================
 */
__device__ void setElement(Matrix A, int row, int col, float value) { 
  A.elements[row * A.stride + col] = value; 
} 

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  setElement
 *  Description:  Sum a matrix element
 * =====================================================================================
 */
__device__ void sumElement(Matrix A, int row, int col, float value) { 
  A.elements[row * A.stride + col] += value; 
} 

/*
 * =====================================================================================
 *       Struct:  Index
 *  Description:  
 * =====================================================================================
 */
typedef struct { 
  int size; 
  int* elements; 
} Index;                                       /* ----------  end of struct Vector  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getElement
 *  Description:  Get matrix element
 * =====================================================================================
 */
__device__ float getIndex(const Index A, int idx) {
  return A.elements[idx]; 
} 

/*
 * =====================================================================================
 *       Struct:  Vector
 *  Description:  
 * =====================================================================================
 */
typedef struct { 
  int size; 
  float* elements; 
} Vector;                                       /* ----------  end of struct Vector  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getElement
 *  Description:  Get matrix element
 * =====================================================================================
 */
__device__ float getIndex(const Vector A, int idx) {
  return A.elements[idx]; 
} 
#endif   /* ----- #ifndef MATRIX_ROW_INC  ----- */
