
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}
node;

void deleteMid(node *ptr1, node *ptr2)
{
     
}

int main (void)
{
    node *list = malloc(sizeof(char));
    int i = 0;
    while (i < 10)
    {
        printf("%p\n",&list[i]);
        list[i].data = i;
        i++;
    }
    i = 0;
    while (i < 10)
    {
        printf("%i\n",list[i].data);
        list[i].data = i;
        i++;
    }
}