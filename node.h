
#ifndef _NODE_H_
#define _NODE_H_

#include <stdio.h>
typedef double data_type;
typedef int coord;

struct position
{
    coord x;
    coord y;
};

typedef struct position Position;

struct node
{
    data_type value;
    Position pos;
    struct node *next_in_Line;
    struct node *next_in_Column;
};

typedef struct node Node;


Node *node_construct(data_type, Node *, Node *, Position);
void node_print(Node *n);
void node_destroy(Node *n);

#endif