#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "node.h"


void print_newLine(){
    printf("\n");
}
// @category O(1)
Matrix *matrix_construct(coord numLines, coord numColumns)
{
    Matrix *m = (Matrix *)calloc(1, sizeof(Matrix));
    m->numLines = numLines;
    m->numColumns = numColumns;
    m->vectorColumns = (Node **)calloc(numColumns, sizeof(Node *));
    m->vectorLines = (Node **)calloc(numLines, sizeof(Node *));
    
    return m;
}

Matrix *matrix_realloc_lines(Matrix *m, coord newSizeLines) 
{
    Matrix *newM = m;
    newM->numLines = newSizeLines;
    newM->vectorLines = (Node **)realloc(newM->vectorLines, newSizeLines * sizeof(Node *));
    return newM;
}

Matrix *matrix_realloc_columns(Matrix *m, coord newSizeColumns) 
{
    Matrix *newM = m;
    newM->numColumns = newSizeColumns;
    newM->vectorColumns = (Node **)realloc(newM->vectorColumns, newSizeColumns * sizeof(Node *));
    return newM;
}

void matrix_print(Matrix *m)
{
    qtt i=0, j, cont=0;
    Node * currentNode = m->vectorLines[i];
    Node * nextNode = NULL;
    //printf("numLines: %d\n",m->numLines);
    for (i=0; i< m->numLines; i++)
    {
        currentNode = m->vectorLines[i];
        if (currentNode==NULL){
            for (j=0; j<m->numColumns; j++){
                printf("0 ");
            }
        }
        
        else {
            //printf("não é nulo\n");
            while (currentNode != NULL)
            {
                if (cont<currentNode->pos.x){
                    for (j=cont; j<currentNode->pos.x; j++){
                        printf("0 ");
                        cont++;
                    }
                }
                printf("%.2lf ", currentNode->value);
                nextNode = currentNode->next_in_Line;
                currentNode = nextNode;
                cont++;
            }
            if (cont<m->numColumns){
                for (j=cont; j<m->numColumns; j++){
                    printf("0 ");
                }
            }
        }
        cont=0;
        print_newLine();
        print_newLine();
    }
}


Matrix * matrix_add_node(Matrix *m, coord x, coord y, data_type value)
{
    Matrix *newM=m;
    Position pos;
    pos.x=x;
    pos.y=y;
    if (pos.x >=m->numColumns){
        matrix_realloc_columns(newM, m->numColumns*2);
    }
    if (pos.y >=m->numLines){
        matrix_realloc_lines(newM, m->numLines*2);
    }

    Node * currentNode = newM->vectorColumns[pos.x];
    Node * newNode = NULL;
    Node * nextNode = NULL;
    Node * previousNode = NULL;

    if (currentNode == NULL){
        //printf("entrou\n");
        newNode=node_construct(value, NULL, nextNode, pos);
        node_print(newNode);
        currentNode=newNode;
        newM->vectorColumns[pos.x]=currentNode;
    }

    else {
        while (currentNode!=NULL){
            nextNode = currentNode->next_in_Column;
            node_print(nextNode);

            if (pos.y == currentNode->pos.y){
                currentNode->value=value;
                return newM;
            }
            if (pos.y < currentNode->pos.y){
                printf("entrou linha 116\n");
                newNode=node_construct(value, NULL, nextNode, pos);
                //node_print(newNode);
                //previousNode=newNode;

                return newM;
            }

            // !!!!se for zero remover no
            previousNode = currentNode;
            currentNode = nextNode;
        }
        newNode=node_construct(value, NULL, nextNode, pos);
        previousNode->next_in_Column=newNode;
    }
    

    currentNode = newM->vectorLines[pos.y];
    nextNode = NULL;

    if (currentNode == NULL){
        currentNode=newNode;
        newM->vectorLines[pos.y]=currentNode;
    }
    else {
        while (currentNode!=NULL){
            nextNode = currentNode->next_in_Line;
            if (pos.x < currentNode->pos.x){
                newNode->next_in_Line=nextNode;
                currentNode->next_in_Line=newNode;
                previousNode->next_in_Column=newNode;
                return newM;
            }
            previousNode = currentNode;
            currentNode = nextNode;
        }
        previousNode->next_in_Line=newNode;
    }
return newM;

}


// O(n)

void matrix_destroy(Matrix *m)
{
    if (m == NULL)
    {
        return;
    }
    qtt i=0;
    for (; i< m->numColumns; i++)
    {
        //printf("+ 1 coluna\n");
        Node * currentNode = m->vectorColumns[i];
        Node * nextNode = NULL;
        while (currentNode != NULL)
        {
            //printf("oi\n");
            nextNode = currentNode->next_in_Column;
            node_destroy(currentNode);
            currentNode = nextNode;
        }     
    }
    free(m->vectorColumns);
    free(m->vectorLines);
    free(m);
}