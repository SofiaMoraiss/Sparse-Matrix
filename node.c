
#include <stdlib.h>
#include "node.h"

Node *node_construct(data_type value, Node *next_in_Line, Node *next_in_Column, Position pos)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->value = value;
    n->next_in_Line = next_in_Line;
    n->next_in_Column = next_in_Column;
    return n;
}

void node_destroy(Node *n)
{
    free(n);
}