#include <stdio.h>

#include "matrix.h"

void print_int(int data)
{
    printf("%d", data);

}

int main()
{
    int qttMat=0, escolha;
    Matrix * m1=NULL;
    Matrix * m2=NULL;
    printf("\n\nMATRIZ ESPARSA DA SOFIA\n");
    do
    {
        printf("\n\nEscolha uma opcao:\n\n1- CRIAR MATRIZ\n2- CRIAR 2 MATRIZ\n3- ADICIONAR OU ATRIBUIR VALOR A UM NO\n4- LER VALOR DE UM NO\n5- SOMAR MATRIZES\n0- SAIR\n\n");
        scanf("%d", &escolha);
        scanf("%*c");

        switch (escolha)
        {
        case 1:
            m1=matrix_read();

            printf("\n\nLi a seguinte matriz 1:\n");
            matrix_print(m1);
            break;
        case 2:
            m2=matrix_read();

            printf("\n\nLi a seguinte matriz 2:\n");
            matrix_print(m2);
            break;
        case 3:
            printf("\n\n :\n");
            m2=matrix_read();

            printf("\n\nLi a seguinte matriz 2:\n");
            matrix_print(m2);
            break;
        /*case RELDOC:
            Listas_imprime_relatorio_documentos(hash, vetDocumentos, *qtdDocsLidos);
            break;
        case RELPAL:
            Listas_imprime_relatorio_palavra(hash);
            break;*/
        default:
            escolha = 0;
            break;
        }

    } while (escolha);

    print_newLine();
    print_newLine();
    
    matrix_destroy(m1);
    matrix_destroy(m2);

    return 0;
}