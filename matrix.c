
#include <stdlib.h>
#include "matrix.h"

Matrix *matrix_construct(coord numLines, coord numColumns)
{
    Matrix *m = (Matrix *)calloc(1, sizeof(Matrix));
    m->numLines = numLines;
    m->numColumns = numColumns;
    m->vectorColumns = (Node **)calloc(1, sizeof(Node *));
    m->vectorLines = (Node **)calloc(1, sizeof(Node *));
    
    return m;
}

void matrix_destroy(Matrix *m)
{
    if (m == NULL)
    {
        return;
    }
    for (int i = 0; i < m->indiceMaximo; i++)
    {
        if (h->hashmap_lista[i] != NULL)
        {
            tListaPalavra *temp = h->hashmap_lista[i];
            tListaPalavra *temp_next = NULL;
            while (temp != NULL)
            {
                temp_next = temp->next;
                Palavra_destroi(temp->palavra);
                free(temp);
                temp = temp_next;
            }
        }
    }
    free(h->hashmap_lista);
    free(m);
}