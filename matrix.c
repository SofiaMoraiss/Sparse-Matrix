#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "node.h"


void print_newLine(){
    printf("\n");
}

int position_valid(Matrix *m, coord x, coord y)
{
    if (x>=m->numColumns || y>=m->numLines || x<0 || y<0){
        return 0;
    }
    return 1;
}

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

void matrix_print(Matrix *m, int flagDense)
{
    qtt i=0, j, cont=0;
    Node * currentNode = m->vectorLines[i];
    Node * nextNode = NULL;
    for (i=0; i< m->numLines; i++)
    {
        currentNode = m->vectorLines[i];
        if (currentNode==NULL){
            for (j=cont; j<m->numColumns; j++){
                if (flagDense){
                    printf("  0  ");
                }
                else {
                    printf("     ");
                }
            }
        }
        
        else {
            while (currentNode != NULL)
            {
                if (cont<currentNode->pos.x){
                    for (j=cont; j<currentNode->pos.x; j++){
                        if (flagDense){
                            printf("  0  ");
                        }
                        else {
                            printf("     ");
                        }
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
                    if (flagDense){
                        printf("  0  ");
                    }
                    else {
                        printf("     ");
                    }
                }
            }
        }
        cont=0;
        print_newLine();
        print_newLine();
    }
}

void matrix_print_in_binary_file(Matrix *m, char* fileName) 
{
    FILE* file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Couldn't open the file!\n");
        return;
    }

    fwrite(&m->numLines, sizeof(int), 1, file);    
    fwrite(&m->numColumns, sizeof(int), 1, file);   

    for (int i=0; i< m->numColumns; i++)
    {
        Node * currentNode = m->vectorColumns[i];
        Node * nextNode = NULL;
        while (currentNode != NULL)
        {
            nextNode = currentNode->next_in_Column;
            fwrite(&currentNode->value, sizeof(data_type), 1, file);
            fwrite(&currentNode->pos.x, sizeof(coord), 1, file);
            fwrite(&currentNode->pos.y, sizeof(coord), 1, file);
            currentNode = nextNode;
        }     
    }

    fclose(file);
}

Matrix * matrix_read_binary(char* fileName)
{
    Matrix * m=NULL;
    FILE* file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Couldn't open the file!\n");
        return m;
    }
    int lines, columns;
    data_type value;
    coord x, y;

    fread(&lines, sizeof(int), 1, file);    
    fread(&columns, sizeof(int), 1, file);   

    m= matrix_construct(lines, columns);
    
    while (fread(&value, sizeof(data_type), 1, file))
    {            
        fread(&x, sizeof(coord), 1, file);
        fread(&y, sizeof(coord), 1, file);
        matrix_add_node(m, x, y, value);
    }  

    fclose(file);
    return m;
}

Matrix * matrix_read()
{
    qtt numLines, numColumns;
    data_type value;

    printf("Type the number of columns and lines: ");
    scanf("%d %d", &numColumns, &numLines);

    Matrix * m = matrix_construct(numLines, numColumns); 

    for (int i = 0; i < numLines; i++) {
        for (int j = 0; j < numColumns; j++) {
            scanf("%lf%*c", &value);
            if (value != 0){
                m=matrix_add_node(m, j, i, value);
            }
        }
    }

    return m;
}

// Matrix * matrix_add_node(Matrix *m, coord x, coord y, data_type value)
// {
//     Position pos;
//     int flagCreated=0;
//     pos.x=x;
//     pos.y=y;
//     if (pos.x >=m->numColumns){
//         matrix_realloc_columns(m, m->numColumns*2);
//     }
//     if (pos.y >=m->numLines){
//         matrix_realloc_lines(m, m->numLines*2);
//     }
//     Node * currentNode = m->vectorColumns[pos.x];
//     Node * newNode = NULL;
//     Node * nextNode = NULL;
//     Node * previousNode = NULL;

//     if (currentNode == NULL){
//         newNode=node_construct(value, NULL, nextNode, pos);
//         currentNode=newNode;
//         m->vectorColumns[pos.x]=currentNode;
//     }

//     else {
//         while (currentNode!=NULL){
//             nextNode = currentNode->next_in_Column;

//             if (pos.y == currentNode->pos.y){
//                 if (value!=0){
//                     currentNode->value=value;
//                     return m;
//                 }
//                 else {
//                     if (previousNode==NULL){
//                         m->vectorColumns[pos.x]=nextNode;
//                     }
//                     else if (nextNode!=NULL){
//                         previousNode->next_in_Column=nextNode;
//                     }
//                     node_destroy(currentNode);
//                 }
//                 flagCreated=1;
//                 previousNode=currentNode;
//                 break;
//             }
//             if (pos.y < currentNode->pos.y){
//                 newNode=node_construct(value, NULL, nextNode, pos);
//                 if (previousNode==NULL){
//                     m->vectorColumns[pos.x]=newNode;
//                 }
//                 else {
//                     previousNode->next_in_Column=currentNode;
//                 }
//                 previousNode=currentNode;
//                 flagCreated=1;
//                 break;
//             }

//             previousNode = currentNode;
//             currentNode = nextNode;
//         }
//         if (!flagCreated){
//             if (value!=0){
//                 newNode=node_construct(value, NULL, nextNode, pos);
//                 previousNode->next_in_Column=newNode;
//             }
//             else {
//                 return m;
//             } 
//         }  
//     }
    

//     currentNode = m->vectorLines[pos.y];
//     previousNode = NULL;
//     nextNode = NULL;

//     if (currentNode == NULL){
//         m->vectorLines[pos.y]=newNode;
//     }
//     else {
//         while (currentNode!=NULL){
//             nextNode = currentNode->next_in_Line;
//             if (pos.x == currentNode->pos.x){
//                 if (value==0){
//                     if (previousNode==NULL){
//                         m->vectorLines[pos.x]=nextNode;
//                     }
//                     else {
//                         previousNode->next_in_Line=currentNode->next_in_Line;
//                     }
//                     node_destroy(currentNode);
//                 }
//                 previousNode=currentNode;
//                 break;
//             }
//             if (pos.x < currentNode->pos.x){
//                 if (previousNode==NULL){
//                     m->vectorLines[pos.y]=newNode;
//                 }
//                 else {
//                     previousNode->next_in_Line=newNode;
//                 }
//                 newNode->next_in_Line=currentNode;
//                 return m;
//             }
//             previousNode = currentNode;
//             currentNode = nextNode;
//         }
//         previousNode->next_in_Line=newNode;
//     }
// return m;

// }



Matrix * matrix_add_node(Matrix *m, coord x, coord y, data_type value)
{
    Matrix *newM=m;
    Position pos;
    pos.x=x;
    pos.y=y;
    int flagCreated=0;

    if(m == NULL){
        printf("Matrix not valid!");
        return m;
    }
    if(!position_valid(m, x, y)){
        printf("Matrix not valid!");
        return m;
    }

    if (value==0){
        if(!matrix_get_node_value(m, x, y)){
            return m;
        }
    }
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
        newNode=node_construct(value, NULL, nextNode, pos);
        currentNode=newNode;
        newM->vectorColumns[pos.x]=currentNode;
    }

    else {
        while (currentNode!=NULL){
            nextNode = currentNode->next_in_Column;

            if (pos.y == currentNode->pos.y){
                if (value!=0){
                    currentNode->value=value;
                    return newM;
                }
                else {
                    if (previousNode==NULL){
                        newM->vectorColumns[pos.x]=nextNode;
                    }
                    else {
                        previousNode->next_in_Column=nextNode;
                    }
                    //node_destroy(currentNode);
                }
                flagCreated=1;
                break;
            }
            if (pos.y < currentNode->pos.y){
                newNode=node_construct(value, NULL, nextNode, pos);
                if (previousNode==NULL){
                    newM->vectorColumns[pos.x]=newNode;
                }
                else {
                    previousNode->next_in_Column=newNode;
                }
                flagCreated=1;
                break;
            }
            previousNode = currentNode;
            currentNode = nextNode;
        }
        if (!flagCreated){
            newNode=node_construct(value, NULL, nextNode, pos);
            previousNode->next_in_Column=newNode;
        }
    }
    
    currentNode = newM->vectorLines[pos.y];
    previousNode= NULL;
    nextNode = NULL;

    if (currentNode == NULL){
        currentNode=newNode;
        newM->vectorLines[pos.y]=currentNode;
    }
    else {
        while (currentNode!=NULL){
            nextNode = currentNode->next_in_Line;
            if(pos.x==currentNode->pos.x){
                if (previousNode==NULL){
                    newM->vectorLines[pos.y]=nextNode;
                }
                else {
                    previousNode->next_in_Line=nextNode;
                }
                node_destroy(currentNode);
                return newM;
            }
            if (pos.x < currentNode->pos.x){
                if (previousNode==NULL){
                    newM->vectorLines[pos.y]=newNode;
                }
                else {
                    previousNode->next_in_Line=newNode;
                }
                newNode->next_in_Line=currentNode;
                return newM;
            }
            previousNode = currentNode;
            currentNode = nextNode;
        }
        previousNode->next_in_Line=newNode;
    }
return newM;

}




data_type matrix_get_node_value(Matrix *m, coord x, coord y)
{

    if (!position_valid(m, x, y)){
        return 0;
    }
    Node * currentNode = m->vectorColumns[x];
    Node * nextNode = NULL;
    while (currentNode != NULL)
    {
        nextNode = currentNode->next_in_Column;
        if (currentNode->pos.y==y){
            return currentNode->value;
        }
        currentNode = nextNode;
    }
    return 0;
}



Matrix * matrix_sum_or_mult(Matrix *m1, Matrix *m2, data_type (*operation)(data_type, data_type))
{
    Matrix * newM = matrix_construct(m1->numLines, m1->numColumns);
    data_type value1, value2;
    for (int i=0; i< newM->numColumns; i++)
    {
        for (int j=0; j< newM->numLines; j++){
            value1=matrix_get_node_value(m1, i, j);
            value2=matrix_get_node_value(m2, i, j);
            if (value1||value2){
                matrix_add_node(newM, i, j, operation(value1, value2));
            }
        }     
    }

    return newM;

}
Matrix *matrix_swap_columns(Matrix *m, int x1, int x2)
{
    Node *nodeAux=m->vectorColumns[x1];
    m->vectorColumns[x1]=m->vectorColumns[x2];
    m->vectorColumns[x2]=nodeAux;

    for(int i=0; i < m->numLines; i++)
    {
        Node *currentNode1 = m->vectorLines[i];
        Node *previousNode1 = NULL;
        Node *currentNode2 = currentNode1;
        Node *previousNode2 = NULL;

        while (currentNode1 != NULL && currentNode1->pos.x != x1){
            previousNode1 = currentNode1;
            currentNode1 = currentNode1->next_in_Line;
        }
        while (currentNode2 != NULL && currentNode2->pos.x != x2){
            previousNode2 = currentNode2;
            currentNode2 = currentNode2->next_in_Line;
        }

        if (currentNode1 != NULL && currentNode2 != NULL){
            if (previousNode1 != NULL)
                previousNode1->next_in_Line = currentNode2;
            else
                m->vectorLines[i] = currentNode2;

            if (previousNode2 != NULL)
                previousNode2->next_in_Line = currentNode1;
            else
                m->vectorLines[i] = currentNode1;

            currentNode1->pos.x=x2;
            currentNode2->pos.x=x1;
            Node *tempNode = currentNode1->next_in_Line;
            currentNode1->next_in_Line = currentNode2->next_in_Line;
            currentNode2->next_in_Line = tempNode;
        }
    }

    return m;
}

Matrix *matrix_swap_lines(Matrix *m, coord x1, coord x2)
{
    Node *nodeAux = m->vectorLines[x1];
    m->vectorLines[x1] = m->vectorLines[x2];
    m->vectorLines[x2] = nodeAux;

    for (int j = 0; j < m->numColumns; j++)
    {
        Node *currentNode1 = m->vectorColumns[j];
        Node *previousNode1 = NULL;
        Node *currentNode2 = currentNode1;
        Node *previousNode2 = NULL;

        while (currentNode1 != NULL && currentNode1->pos.x != x1)
        {
            previousNode1 = currentNode1;
            currentNode1 = currentNode1->next_in_Column;
        }
        while (currentNode2 != NULL && currentNode2->pos.x != x2)
        {
            previousNode2 = currentNode2;
            currentNode2 = currentNode2->next_in_Column;
        }

        if (currentNode1 != NULL && currentNode2 != NULL)
        {
            if (previousNode1 != NULL)
                previousNode1->next_in_Column = currentNode2;
            else
                m->vectorColumns[j] = currentNode2;

            if (previousNode2 != NULL)
                previousNode2->next_in_Column = currentNode1;
            else
                m->vectorColumns[j] = currentNode1;

            currentNode1->pos.y = x2;
            currentNode2->pos.y = x1;
            Node *tempNode = currentNode1->next_in_Column;
            currentNode1->next_in_Column = currentNode2->next_in_Column;
            currentNode2->next_in_Column = tempNode;
        }
    }

    return m;
}


// O(n)

Matrix *matrix_multiply_by_scalar(Matrix*m, double scalar)
{
    Matrix*newM=m;
    if (m == NULL) {
        printf("Null Matrix!\n");
        return m;
    }
    qtt i=0;
    for (; i< m->numColumns; i++)
    {
        Node * currentNode = newM->vectorColumns[i];
        Node * nextNode = NULL;
        while (currentNode != NULL)
        {
            nextNode = currentNode->next_in_Column;
            currentNode->value*=scalar;
            currentNode = nextNode;
        }     
    }
    return newM;
}

Matrix *matrix_transpose(Matrix*m)
{
    Matrix *newM=matrix_construct(m->numColumns,m->numLines);

    for (int i=0; i< m->numColumns; i++)
    {
        Node * currentNode = m->vectorColumns[i];
        Node * nextNode = NULL;
        while (currentNode != NULL)
        {
            nextNode = currentNode->next_in_Column;
            matrix_add_node(newM, currentNode->pos.y, currentNode->pos.x, currentNode->value);
            currentNode = nextNode;
        }     
    }

    return newM;
}

Matrix *matrix_slice(Matrix*m, Position start, Position end)
{

    Matrix *newM=matrix_construct(end.y-start.y+1,end.x-start.x+1);

    for (int i=start.x; i<= end.x; i++)
    {
        Node * currentNode = m->vectorColumns[i];
        Node * nextNode = NULL;
        while (currentNode != NULL  && currentNode->pos.y <=end.y)
        {
            nextNode = currentNode->next_in_Column;
            if (currentNode->pos.y>=start.y){
                matrix_add_node(newM, currentNode->pos.x-start.x, currentNode->pos.y-start.y, currentNode->value);
            }  
            currentNode = nextNode;
        }     
    }

    return newM;
}

Matrix * matrix_convolution(Matrix *m, Matrix *mKernel)
{
    matrix_print(mKernel,1 );
    matrix_print(m, 1);
    Matrix * newM = matrix_construct(m->numLines, m->numColumns);
    data_type soma=0;
    for (int i=0; i< newM->numColumns; i++){
        for (int j=0; j< newM->numLines; j++){
            for (int a=0; a<3; a++){
                for (int b=0; b<3; b++){
                    soma+=matrix_get_node_value(mKernel, a, b)*matrix_get_node_value(m, i+a-1, j+b-1);
                }
            }
            if (soma){
                matrix_add_node(newM, i, j, soma);
            }
            soma=0;
        }     
    }

    return newM;
}

data_type matrix_det_squared(Matrix *m)
{
    data_type det=0;
    int dim=m->numColumns;
    if (dim==2){
        det=matrix_get_node_value(m, 0, 0)*matrix_get_node_value(m, 1, 1);
        det-=matrix_get_node_value(m, 1, 0)*matrix_get_node_value(m, 0, 1);
    }
    else if (dim==3){
        det+=matrix_get_node_value(m, 0, 0)*matrix_get_node_value(m, 1, 1)*matrix_get_node_value(m, 2, 2);
        det+=matrix_get_node_value(m, 1, 0)*matrix_get_node_value(m, 2, 1)*matrix_get_node_value(m, 0, 2);
        det+=matrix_get_node_value(m, 2, 0)*matrix_get_node_value(m, 0, 1)*matrix_get_node_value(m, 1, 2);
        det-=matrix_get_node_value(m, 0, 0)*matrix_get_node_value(m, 2, 1)*matrix_get_node_value(m, 1, 2);
        det-=matrix_get_node_value(m, 1, 0)*matrix_get_node_value(m, 0, 1)*matrix_get_node_value(m, 2, 2);
        det-=matrix_get_node_value(m, 2, 0)*matrix_get_node_value(m, 1, 1)*matrix_get_node_value(m, 0, 2);
        
    }
    else if (dim>3){
        Position p;
        for (int i=0; i<dim; i++){
            p.x=i; p.y=0;
            det+=matrix_get_node_value(m,i, 0)*matrix_calculate_cofactor(m, p);
        }
    }
    return det;
}

data_type matrix_calculate_cofactor(Matrix *m, Position p)
{
    data_type cofactor=0;
    int dim=m->numColumns;
    Matrix *mAux=matrix_construct(dim-1, dim-1);

    int line = 0, column = 0;
    
    for (int i = 0; i < dim; i++) {
        if (i != p.y) {
            for (int j = 0; j < dim; j++) {
                if (j != p.x) {
                    mAux= matrix_add_node(mAux, column, line, matrix_get_node_value(m,j, i));
                    column++;
                }
            }
            line++;
            column = 0;
        }
    }

    cofactor= pow(-1, p.x+p.y)*matrix_det_squared(mAux);

    matrix_destroy(mAux);

    return cofactor;
}



void matrix_destroy(Matrix *m)
{
    if (m == NULL)
    {
        return;
    }
    qtt i=0;
    for (; i< m->numColumns; i++)
    {
        Node * currentNode = m->vectorColumns[i];
        Node * nextNode = NULL;
        while (currentNode != NULL)
        {
            nextNode = currentNode->next_in_Column;
            node_destroy(currentNode);
            currentNode = nextNode;
        }     
    }
    free(m->vectorColumns);
    free(m->vectorLines);
    free(m);
}