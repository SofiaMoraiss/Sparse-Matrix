
#include <stdlib.h>
#include "node.h"

Node *node_construct(data_type value, Node *nextLine, Node *nextColumn, Position pos)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->value = value;
    n->nextLine = nextLine;
    n->nextColumn = nextColumn;
    return n;
}

void node_destroy(Node *n)
{
    free(n);
}