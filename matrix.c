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
    m->numLines = newSizeLines;
    m->vectorLines = (Node **)realloc(m->vectorLines, newSizeLines * sizeof(Node *));
    return m;
}

Matrix *matrix_realloc_columns(Matrix *m, coord newSizeColumns) 
{
    m->numColumns = newSizeColumns;
    m->vectorColumns = (Node **)realloc(m->vectorColumns, newSizeColumns * sizeof(Node *));
    return m;
}

void matrix_print(Matrix *m)
{
    qtt i=0, j, cont=0;
    Node * currentNode = m->vectorLines[i];
    Node * nextNode = NULL;
    for (; i< m->numLines; i++)
    {
        currentNode = m->vectorLines[i];
        if (currentNode==NULL){
            for (j=0; j<m->numColumns; j++){
                printf("0 ");
            }
            print_newLine();
        }
        
        while (currentNode != NULL)
        {
            if (cont<currentNode->pos.x){
                for (j=cont; j<currentNode->pos.x; j++){
                    printf("0 ");
                }
            }
            printf("%.2lf ", currentNode->value);
            nextNode = currentNode->next_in_Line;
            currentNode = nextNode;
            cont++;
        }
        cont=0;
        print_newLine();
    }
}


Matrix * matrix_add_node(Matrix *m, Position pos, data_type value)
{
    Matrix *newM=m;

    if (pos.x >=m->numColumns){
        matrix_realloc_columns(newM, m->numColumns*2);
    }
    if (pos.y >=m->numLines){
        matrix_realloc_lines(newM, m->numLines*2);
    }

    Node * currentNode = newM->vectorColumns[pos.x];
    Node * newNode = NULL;
    Node * nextNode = NULL;

    if (currentNode == NULL){
        printf("entrou\n");
        newNode=node_construct(value, NULL, nextNode, pos);
        node_print(newNode);
        currentNode=newNode;
        newM->vectorColumns[pos.x]=currentNode;
    }

    else {
        while (currentNode!=NULL){
            nextNode = currentNode->next_in_Column;
            if (pos.y == currentNode->pos.y){
                currentNode->value=value;
                return newM;
            }
            if (pos.y > nextNode->pos.y){
                newNode=node_construct(value, NULL, nextNode, pos);
                //node_print(newNode);
                currentNode->next_in_Column=newNode;
            }
            currentNode = nextNode;
        }
    }
    

    currentNode = newM->vectorLines[pos.y];
    nextNode = NULL;

    if (currentNode == NULL){
        printf("entrou\n");
        currentNode=newNode;
        newM->vectorColumns[pos.y]=currentNode;
    }
    else {
        while (currentNode!=NULL){
            nextNode = currentNode->next_in_Line;
            if (pos.x > nextNode->pos.x){
                newNode->next_in_Line=nextNode;
                currentNode->next_in_Line=newNode;
            }
            currentNode = nextNode;
        }
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