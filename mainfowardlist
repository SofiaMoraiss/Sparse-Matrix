
#include <stdio.h>

#include "matrix.h"

void print_int(int data)
{
    printf("%d", data);
}

int main()
{
    int n, val;

    ForwardList *l = forward_list_construct();

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        forward_list_push_front(l, val);
    }

    // test the size and print functions
    printf("Size: %d\n", forward_list_size(l));
    printf("Lista: ");
    forward_list_print(l, print_int);
    printf("\n");

    // test the destroy function
    forward_list_destroy(l);

    return 0;
}