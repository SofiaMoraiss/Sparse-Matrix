#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

// @category O(1)
Matrix *matrix_construct(coord numLines, coord numColumns)
{
    Matrix *m = (Matrix *)calloc(1, sizeof(Matrix));
    m->numLines = numLines;
    m->numColumns = numColumns;
    m->vectorColumns = (Node **)calloc(10, sizeof(Node *));
    m->vectorLines = (Node **)calloc(10, sizeof(Node *));
    
    return m;
}

Matrix * matrix_add_node(Position pos, );

// O(n)

void matrix_destroy(Matrix *m)
{
    if (m == NULL)
    {
        return;
    }
    qtt i=0, j=0;
    for (; i< m->numColumns; i++)
    {
        printf("+ 1 coluna\n");
        Node * currentNode = m->vectorColumns[i];

        Node * nextNode = NULL;
        while (currentNode != NULL)
        {
            printf("oi\n");
            nextNode = currentNode->next_in_Column;
            node_destroy(currentNode);
            currentNode = nextNode;
        }     
    }
    free(m->vectorColumns);
    free(m->vectorLines);
    free(m);
}