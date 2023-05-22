#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "node.h"
typedef int qtt;

typedef struct matrix
{
    qtt numLines, numColumns;
    Node ** vectorLines;
    Node ** vectorColumns;
}Matrix;

/**
 * @brief Construct a new Sparse Matrix:: Matrix object
 *  Allocates memory for a new matrix and returns a pointer to it.
 * @return Matrix*
 * Pointer to the newly allocated matrix.
 * @note
 * - The caller is responsible for freeing the memory allocated for the matrix using matrix_destroy().
 * @note
 * - Complexity O(1)
 */
Matrix *matrix_construct(coord numLines, coord numColumns);
/**
 * @brief Construct a new node at given position filled with given value or if node already exists substitutes its value in Sparse Matrix
 * @return Matrix*
 * Pointer to the updated matrix.
 * @note
 * - The caller is responsible for freeing the memory allocated for the possible new node using node_destroy().
 * @note
 * - Complexity O(1)
 */
Matrix * matrix_add_node(Matrix *m, coord x, coord y, data_type value);
/**
 * @brief prints new line 
 * @note
 * - Complexity O(1)
 */
void print_newLine();
/**
 * @brief 
 * @return data_type
 * if given position is valid, returns the value of the node at that position
 * @note
 * - The caller is responsible for freeing the memory allocated for the linked list using forward_list_destroy().
 * @note
 * - Complexity: best-case scenario O(1), worst-case scenario: O(size of column)=O(N), average: O(N/2)=0(N)
 */
data_type matrix_get_node_value(Matrix *m, coord x, coord y);
/**
 * @brief Reads number of lines and columns then the elements of the matrix
 * @return Matrix*
 * Pointer to the new matrix.
 * @note
 * - Complexity O(N²)
 */
Matrix * matrix_read();

/**
 * @brief Reads number of lines and columns then the elements of the matrix from binary file
 * @return Matrix*
 * Pointer to the new matrix.
 * @note
 * - Complexity O(N)
 */
Matrix * matrix_read_binary(char* fileName);
/**
 * @brief Prints given matrix, if flagDense==0, prints it sparsely, else, densely
 * @return void
 * @note
 * - Complexity O(N²)
 */
void matrix_print(Matrix *m, int flagDense);
/**
 * @brief Prints given matrix in binary file
 * @return void
 * @note
 * - Complexity O(N²)
 */
void matrix_print_in_binary_file(Matrix *m, char* fileName);
/**
 * @brief Sums ou multiplies two matrixes point by point, receives a pointer to function that either sums or multiplies elements
 * @return Matrix *
 * Pointer to the new matrix
 * @note
 * - Complexity O(N²)
 */
Matrix *matrix_sum_or_mult(Matrix *m1, Matrix *m2, data_type (*operation)(data_type, data_type));
/**
 * @brief swap two columns of the given matrix 
 * @return Matrix *
 * Pointer to the new matrix 
 * * @note
 * - Complexity O(N²)
 */
Matrix *matrix_swap_columns(Matrix *m, int x1, int x2);
/**
 * @brief Prints given matrix in binary file
 * @return Matrix *
 * Pointer to the new matrix 
 * @note
 * - Complexity O(N²)
 */
Matrix *matrix_swap_lines(Matrix *m, coord x1, coord x2);
/**
 * @brief Multiplies the whole matrix by a given scalar, point by point
 * @return Matrix *
 * Pointer to the new matrix 
 * @note
 * - Complexity O(N²)
 */
Matrix *matrix_multiply_by_scalar(Matrix*m, double scalar);
/**
 * @brief Multiplies the whole matrix by a given scalar, point by point
 * @return Matrix *
 * Pointer to the new matrix 
 * @note
 * - Complexity O(N²)
 */
Matrix *matrix_transpose(Matrix*m);
/**
 * @brief Given the starting and ending point, slices the matrix according
 * @return Matrix *
 * Pointer to sliced new matrix 
 * @note
 * - Complexity O(N²)
 */
Matrix *matrix_slice(Matrix*m, Position start, Position end);
/**
 * @brief Destroys the whole matrix and its nodes
 * @return void
 * @note
 * - Complexity O(N²)
 */
void matrix_destroy(Matrix *m);

#endif