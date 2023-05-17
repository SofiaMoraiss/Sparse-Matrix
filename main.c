#include <stdio.h>

#include "matrix.h"

void print_int(int data)
{
    printf("%d", data);
}

int main()
{
    qtt numLines, numColumns;
    data_type value;
    printf("Digite o numero de linhas e colunas: ");
    scanf("%d %d", &numLines, &numColumns);

    Matrix * m = matrix_construct(numLines, numColumns); 

    matrix_print(m);

    for (int i = 0; i < numLines; i++) {
        for (int j = 0; j < numColumns; j++) {
            scanf("%lf%*c", &value);
            if (value != 0){
                m=matrix_add_node(m, j, i, value);
            }
        }
        //scanf("%*c");
    }

    matrix_print(m);
    // test the destroy function
    matrix_destroy(m);

    return 0;
}