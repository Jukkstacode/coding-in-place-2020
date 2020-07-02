// problems from https://www.w3resource.com/c-programming-exercises/linked_list/index.php

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

typedef struct node
{
    int num;
    struct node* next;
}
node;

int main (void)
{
    int num_nodes = get_int("Input the number of nodes: ");
    node *n = malloc(sizeof(node));
    node *start = n;
    if (n == NULL)
    {
        return 1;
    }
    int i = 0;
    while (i < num_nodes)
    {
        n->num = get_int("Input data for node: ");
        n->next = malloc(sizeof(node));
        n = n->next;
        i++;
    }
    printf("Data entered in the list:\n");
    while (start->next != NULL)
    {
        printf("Data = %i\n",start->num);    
        start = start->next;
    }
    return 0;
}