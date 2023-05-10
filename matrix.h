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
void matrix_destroy(Matrix *m);

#endif