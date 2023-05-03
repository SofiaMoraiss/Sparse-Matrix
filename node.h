
#ifndef _NODE_H_
#define _NODE_H_

typedef float data_type;
typedef int coord;

typedef struct Position
{
    coord x;
    coord y;
} Position;

typedef struct Node
{
    data_type value;
    Position pos;
    struct Node *nextLine;
    struct Node *nextColumn;
} Node;

Node *node_construct(data_type, Node *, Node *, Position);
void node_destroy(Node *n);

#endif