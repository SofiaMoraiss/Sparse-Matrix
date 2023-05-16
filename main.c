#include <stdio.h>

#include "matrix.h"

void print_int(int data)
{
    printf("%d", data);
}

int main()
{
    qtt numLines, numColumns;
    printf("Digite o numero de linhas e colunas: ");
    scanf("%d %d", &numLines, &numColumns);

    //for ()

    Matrix * m = matrix_construct(numLines, numColumns); 
    Position p;
    p.x=2;
    p.y=4;
    printf("1numLines: %d\nnumColumns: %d\n", m->numLines, m->numColumns);
    m=matrix_add_node(m, p, 100);

    printf("2numLines: %d\nnumColumns: %d\n", m->numLines, m->numColumns);
    matrix_print(m);

    // test the size and print functions
    printf("3numLines: %d\nnumColumns: %d\n", m->numLines, m->numColumns);
    //printf("Lista: ");
    //forward_list_print(l, print_int);
    //printf("\n");

    // test the destroy function
    matrix_destroy(m);

    return 0;
}