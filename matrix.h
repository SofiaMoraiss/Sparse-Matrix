#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "node.h"
typedef float data_type;
typedef int inte;

typedef struct Matrix
{
    inte numLines, numColumns;
    Node ** vectorLines;
    Node ** vectorColumns;
} Matrix;

Matrix *matrix_construct(coord numLines, coord numColumns);
void matrix_destroy(Matrix *m);

#endif