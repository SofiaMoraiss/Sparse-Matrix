#include <stdio.h>

#include "matrix.h"
#define CREATE_M1 1
#define CREATE_M2 2
#define ADD_NODE 3
#define READ_NODE 4
#define SUM 5
#define PRINT_MATRIX 6
#define SWAP 7
#define MULT_SCALAR 8
#define MULT_POINT 9
#define TRANS 10
#define SLICE 11
#define READ_BIN 12
#define WRITE_BIN 13

void print_int(int data)
{
    printf("%d", data);

}

data_type sum(data_type x1, data_type x2){
    return x1+x2;
}
data_type mult(data_type x1, data_type x2){
    return x1*x2;
}

int ask_matrix(){
    int nMatrix;
    printf("Type the matrix number: ");
    scanf("%d%*c", &nMatrix);
    return nMatrix;
}

Position ask_position(){
    Position p;
    printf("Type 'x' and 'y' axis : ");
    scanf("%d %d", &p.x, &p.y);
    return p;
}

int main()
{
    int action, nMatrix, x, y, choice;
    char ch;
    data_type val;
    Matrix * m1=NULL;
    Matrix * m2=NULL;
    Matrix * mAux=NULL;
    Position p1, p2;

    printf("\n\nWELCOME TO SOFIA'S SPARSE MATRIX OPERATOR!\n");
    do
    {
        printf("\nChoose an operation:\n\n1- CREATE MATRIX 1\n2- CREATE MATRIX 2\n3- ADD OR ATRIBUTE VALUE TO NODE\n");
        printf("4- READ NODE\n5- SUM MATRIXES\n6- PRINT BOTH MATRIXES\n7- SWAP COLUMNS OR LINES\n8- MULTIPLY BY A SCALAR\n");
        printf("9- MULTIPLY POINT-WISE\n10- TRANSPOSE\n11- SLICE\n12- READ BINARIES\n13- WRITE BINARIES\n");
        printf("0- EXIT\n\n");
        scanf("%d%*c", &action);

        switch (action)
        {
        case CREATE_M1:
            m1=matrix_read();

            printf("\nThis is matrix 1 now:\n");
            matrix_print(m1, 1);
            break;
        case CREATE_M2:
            m2=matrix_read();

            printf("\nThis is matrix 2 now:\n");
            matrix_print(m2, 1);
            break;
        case ADD_NODE:
            nMatrix=ask_matrix();
            printf("Type the 'x', 'y' axis and the value: ");
            scanf("%d %d %lf", &x, &y, &val);

            if (nMatrix==1)
            {
                matrix_add_node(m1, x, y, val);
                printf("\n\nNew Matrix 1:\n");
                matrix_print(m1, 0);
            }
            else if (nMatrix==2)
            {
                matrix_add_node(m2, x, y, val);
                printf("\n\nNew Matrix 2:\n");
                matrix_print(m2, 0);
            }
            break;
        case READ_NODE:
            nMatrix=ask_matrix();
            p1=ask_position();

            if (nMatrix==1)
            {
                val=matrix_get_node_value(m1, p1.x, p1.y);
            }
            else if (nMatrix==2)
            {
                val=matrix_get_node_value(m2, p1.x, p1.y);
            }
            printf("\n\nValue at node[%d, %d]: %.2lf\n", p1.x, p1.y, val);
            break;
        case SUM:
            mAux=matrix_sum_or_mult(m1, m2, sum);
            matrix_print(mAux, 1);
            matrix_destroy(mAux);
            break;
        case PRINT_MATRIX:
            printf("Type 0 to print them sparsely, and 1 densely\n");
            scanf("%d%*c", &choice);

            printf("Matrix 1:\n");
            matrix_print(m1, choice);
            printf("\nMatrix 2:\n");   
            matrix_print(m2, choice);
            break;
        case SWAP:
            nMatrix=ask_matrix();
            printf("Type 'l' or 'c' to choose line or column and then the two 'indexes' densely\n");
            scanf("%c %d %d%*c", &ch, &x, &y);
            printf("x: %d y: %d\n", x, y);
            if (nMatrix==1){
                if (ch=='l'){
                    m1=matrix_swap_lines(m1, x, y);
                }
                else {
                    m1=matrix_swap_columns(m1, x, y);
                    matrix_print(m1, 1);
                }
            }
            else if (nMatrix==2){
                if (ch=='l'){
                    m2=matrix_swap_lines(m2, x, y);
                }
                else {
                    m2=matrix_swap_columns(m2, x, y);
                }
            }
            break;
        case MULT_SCALAR:
            printf("Type the matrix number and the scalar ");
            scanf("%d %lf%*c", &nMatrix, &val);
            printf("New Matrix:\n");
            if (nMatrix==1){
                m1=matrix_multiply_by_scalar(m1, val);
                matrix_print(m1, 1);
            }
            else{
                m2=matrix_multiply_by_scalar(m2, val);
                matrix_print(m2, 1);
            }
            break;
        case MULT_POINT:
            mAux=matrix_sum_or_mult(m1, m2, mult);
            matrix_destroy(mAux);
            matrix_print(m1, 1);
            break;
        case TRANS:
            nMatrix=ask_matrix();
            printf("Transposed Matrix:\n");
            if (nMatrix==1){
                mAux=matrix_transpose(m1);            }
            else{
                mAux=matrix_transpose(m2);    
            }
            matrix_print(mAux, 1);
            matrix_destroy(mAux);
            break;
        case SLICE:
            nMatrix=ask_matrix();
            printf("\n- Starting point -\n");
            p1=ask_position();
            printf("- Ending point -\n");
            p2=ask_position();
            printf("\nSliced Matrix:\n");
            if (nMatrix==1){
                mAux=matrix_slice(m1, p1, p2);
            }
            else{
                mAux=matrix_slice(m2, p1, p2);
            }
            matrix_print(mAux, 1);
            matrix_destroy(mAux);
            break;
        case READ_BIN:
            m1=matrix_read_binary("m1.bin");
            m2=matrix_read_binary("m2.bin");
            printf("\nMatrix 1:\n");   
            matrix_print(m1,1);
            printf("\nMatrix 2:\n");   
            matrix_print(m2,1);
            break;
        case WRITE_BIN:
            if (m1!=NULL){
                matrix_print_in_binary_file(m1, "m1.bin");
            }
            if (m2!=NULL){
                matrix_print_in_binary_file(m2, "m2.bin");
            }
            break;
        default:
            action = 0;
            break;
        }

    } while (action);

    matrix_destroy(m1);
    matrix_destroy(m2);

    return 0;
}