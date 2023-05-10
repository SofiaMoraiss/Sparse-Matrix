
#ifndef _NODE_H_
#define _NODE_H_

typedef double data_type;
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
    struct Node *next_in_Line;
    struct Node *next_in_Column;
} Node;

Node *node_construct(data_type, Node *, Node *, Position);
void node_destroy(Node *n);

#endif