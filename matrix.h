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

Matrix *matrix_construct(coord numLines, coord numColumns);
Matrix * matrix_add_node(Matrix *m, Position pos, data_type value);
void matrix_print(Matrix *m);
void matrix_destroy(Matrix *m);

#endif