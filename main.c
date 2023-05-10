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


    // test the size and print functions
    printf("numLines: %d\nnumColumns: %d\n", m->numLines, m->numColumns);
    //printf("Lista: ");
    //forward_list_print(l, print_int);
    //printf("\n");

    // test the destroy function
    matrix_destroy(m);

    return 0;
}